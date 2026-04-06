// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TeleporterComponent.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ETeleporterType : uint8
{
    Start,
    End
};


UCLASS()
class JUMPYFROGS_API UTeleporterComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//void SetType(ETeleporterType TelType);
	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleporter")
	ETeleporterType TeleporterType = ETeleporterType::Start;
//protected:
	


};
