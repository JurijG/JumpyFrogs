// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.


#include "Actors/JumpVisualizer.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraDataInterfaceArrayFunctionLibrary.h"

#include "NiagaraFunctionLibrary.h"
// Sets default values
AJumpVisualizer::AJumpVisualizer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	NS_TeleportRingArray.Add(CreateDefaultSubobject<UNiagaraComponent>(TEXT("NS_TeleportRing")));
	NS_TeleportRingArray[0]->SetupAttachment(Root);
	//NS_TeleportRing->SetupAttachment(Root);

	//NS_PlayAreaBounds = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NS_PlayAreaBounds"));
	//NS_PlayAreaBounds->SetupAttachment(Root);
	
	TeleportTraceNiagaraSystem = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TeleportTraceNiagaraSystem"));
	TeleportTraceNiagaraSystem->bHiddenInGame = true;

	TeleportTraceNiagaraSystem2 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TeleportTraceNiagaraSystem2"));
	//TeleportTraceNiagaraSystem2->bHiddenInGame = true;

	//NS_PlayAreaBounds->SetupAttachment(Root);

		  // Create and attach the Niagara component
	//NS_TeleportRing = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));

	/*static ConstructorHelpers::FObjectFinder<UNiagaraComponent> NS_TeleportRingAsset(TEXT("NiagaraSystem'/Game/Effects/MyNiagaraEffect.MyNiagaraEffect'"));
	if (NS_TeleportRingAsset.Succeeded())
	{
		NS_TeleportRing->SetAsset(NS_TeleportRingAsset.Object);
	}*/

	// Optionally, set the Niagara System to be used by default
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_TeleportRingAsset(TEXT("NiagaraSystem'/Game/VRTemplate/VFX/NS_TeleportRing.NS_TeleportRing'"));
	if (NS_TeleportRingAsset.Succeeded())
	{
		//NS_TeleportRing->SetAsset(NS_TeleportRingAsset.Object);
		NS_TeleportRingArray[0]->SetAsset(NS_TeleportRingAsset.Object);
	}
	//static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NS_PlayAreaBoundsAsset(TEXT("NiagaraSystem'/Game/VRTemplate/VFX/NS_PlayAreaBounds.NS_PlayAreaBounds'"));
	//if (NS_PlayAreaBoundsAsset.Succeeded())
	//{
	//	NS_PlayAreaBounds->SetAsset(NS_PlayAreaBoundsAsset.Object);
	//}
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> TeleportTraceNiagaraSystemAsset(TEXT("NiagaraSystem'/Game/VRTemplate/VFX/NS_TeleportTrace.NS_TeleportTrace'"));
	if (TeleportTraceNiagaraSystemAsset.Succeeded())
	{
		TeleportTraceNiagaraSystem->SetAsset(TeleportTraceNiagaraSystemAsset.Object);
		
	}
	/*/Script/Niagara.NiagaraSystem'/Game/VRTemplate/VFX/NS_PlayAreaBounds.NS_PlayAreaBounds'
/Script/Niagara.NiagaraSystem'/Game/VRTemplate/VFX/NS_TeleportRing.NS_TeleportRing'
/Script/Niagara.NiagaraSystem'/Game/VRTemplate/VFX/NS_TeleportTrace.NS_TeleportTrace'*/
}

// Called when the game starts or when spawned
void AJumpVisualizer::BeginPlay()
{
	Super::BeginPlay();
	if (NS_TeleportRingArray[0])
	{
		//NS_TeleportRing->SetAsset(NiagaraSystem);
		//NS_TeleportRing->Activate();
		NS_TeleportRingArray[0]->Activate();

		//NS_PlayAreaBounds->Activate();
		
		TeleportTraceNiagaraSystem->Activate();
		//TeleportTraceNiagaraSystem2->Activate();
	}
	
}
void AJumpVisualizer::SetTraceNiagaraVectorArray(TArray<FVector> TracePathLocations)
{
	//TeleportTraceNiagaraSystem->SetVectorArrayParameter("User.PointArray", TracePathLocations);
	//TeleportTraceNiagaraSystem->SetVectorParameter("User.PointArray", TracePathLocations);
	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(TeleportTraceNiagaraSystem, "User.PointArray", TracePathLocations);
	if (TeleportTraceNiagaraSystem->bHiddenInGame)
	{
		TeleportTraceNiagaraSystem->bHiddenInGame = false;
	}
	
	//SetVectorParameter(FName ParameterName, FVector Param) override;
}
void AJumpVisualizer::AddDestinationRing(FVector RingLocation, TArray<FVector> TracePathLocations)
{
	UNiagaraComponent* NewComp = NewObject<UNiagaraComponent>(this);
	NewComp->SetRelativeLocation(GetActorTransform().InverseTransformPosition(RingLocation));
	NewComp->SetupAttachment(RootComponent);
	NewComp->RegisterComponent();

	// Reuse the same Niagara system asset
	NewComp->SetAsset(NS_TeleportRingArray[0]->GetAsset());

	NewComp->Activate();
	
	UNiagaraComponent* Trace = NewObject<UNiagaraComponent>(this);
	Trace->SetRelativeLocation(TeleportTraceNiagaraSystem->GetRelativeLocation());
	Trace->SetupAttachment(RootComponent);
	Trace->RegisterComponent();
	// Reuse the same Niagara system asset
	Trace->SetAsset(TeleportTraceNiagaraSystem->GetAsset());
	UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(Trace, "User.PointArray", TracePathLocations);
	Trace->Activate();

	//UNiagaraComponent* NewTrace = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
	//	GetWorld(),
	//	TeleportTraceNiagaraSystem->GetAsset(),
	//	GetActorLocation(),
	//	FRotator::ZeroRotator,
	//	FVector(1.f),
	//	true, // auto destroy
	//	true, // auto activate
	//	ENCPoolMethod::None,
	//	true  // auto attach
	//);

	if (Trace && TracePathLocations.Num() > 0)
	{
		// Copy the array to the new component
		UNiagaraDataInterfaceArrayFunctionLibrary::SetNiagaraArrayVector(
			Trace,
			FName("User.PointArray"),
			TracePathLocations
		);
	}
	//UNiagaraComponent* Comp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
	//	World,
	//	NiagaraSystem,
	//	SpawnLocation,
	//	SpawnRotation,
	//	true, // auto activate
	//	true, // auto destroy
	//	ENCPoolMethod::None,
	//	true  // auto attach
	//);
}
// Called every frame
void AJumpVisualizer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

