// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.


#include "AnimNotifies/TeleportOutAnimNotify.h"
#include "Interfaces/FrogInterface.h"
#include "Interfaces/GameModeInterface.h"

void UTeleportOutAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	UE_LOG(LogTemp, Warning, TEXT("UTeleportOutAnimNotify: %s triggered, while playing animation: %s"), *GetName(), *Animation->GetName());
	if (AActor* Owner = MeshComp->GetOwner())
	{
		if (Owner->Implements<UFrogInterface>())
		{
			IFrogInterface::Execute_SpellCastTeleportOut(Owner);
		}
	}
}