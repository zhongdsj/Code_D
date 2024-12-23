// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/WeaponAnimationEnum.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

class ABattleCharacter;

UCLASS()
class CODE_D_API AWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

	// Called every frame
	virtual void Tick(float _deltaTime) override;

	UFUNCTION(BlueprintCallable)
	void AttachToCharacter(ABattleCharacter* _character, FName _socketName);

	UAnimMontage* FindAnimation(EWeaponAnimationEnum _animationEnum) const;

	UFUNCTION(BlueprintCallable)
	ABattleCharacter* GetOwnerCharacter() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	TSoftObjectPtr<ABattleCharacter> m_weaponOwner = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> m_weaponMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "data")
	TMap<EWeaponAnimationEnum, TObjectPtr<UAnimMontage>> m_weaponAnimations;
};
