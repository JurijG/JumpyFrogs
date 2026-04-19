// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NiagaraSpawnInterface.generated.h"


UENUM()
enum ENiagaraFX : uint8
{
	TeleportIn,
	TeleportOut,
	WaterMagic,
	WaterMagicBuff,
	WaterSplash,
	WaterSplashRipple,
	RippleShort
};



// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UNiagaraSpawnInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class JUMPYFROGS_API INiagaraSpawnInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	void SpawnNiagara(ENiagaraFX NiagaraType, FVector SpawnLoc);
};
