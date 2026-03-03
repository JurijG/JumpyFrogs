// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.


#include "AnimNotifies/FrogsAnimNotify.h"
#include "Interfaces/FrogInterface.h"

void UFrogsAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	/*UE_LOG(LogTemp, Warning, TEXT("Anim Notify: %s triggered, while playing animation: %s"), *GetName(), *Animation->GetName());
	if (AActor* Owner = MeshComp->GetOwner())
	{
		if (Owner->Implements<UFrogInterface>())
		{
			IFrogInterface::Execute_PlayNextAnimation(Owner);
		}
	}*/
}
