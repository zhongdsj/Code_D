# pragma once
# include "CoreMinimal.h"
# include "PersonSave.generated.h"

USTRUCT(BlueprintType)
struct FPersonSave
{
	GENERATED_BODY()
	UPROPERTY(SaveGame)
	FVector location;
	UPROPERTY(SaveGame)
	FRotator rotation;
};
