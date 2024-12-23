// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WorldGameMode.generated.h"

class UMySaveGame;
class USaveGame;
/**
 * 
 */
UCLASS()
class CODE_D_API AWorldGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AWorldGameMode();

	UFUNCTION(BlueprintCallable)
	void SaveGame(const FString& _slot_name);

	UFUNCTION(BlueprintCallable)
	void LoadGame();
	virtual void PreInitializeComponents() override;

	UFUNCTION(BlueprintCallable)
	void ShowActorInfo(const FText& _text, FVector2D _position) const;

	UFUNCTION(BlueprintCallable)
	void HideActorInfo() const;

	UFUNCTION(BlueprintCallable)
	void SetTimeDilation(float _dilation);

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type _endPlayReason) override;
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void NotifyOnLoadedGame();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void NotifyLoadedGame();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "save game", meta = (DisplayName = "save game class", ToolTip = "保存/加载类"))
	TSubclassOf<USaveGame> m_saveGameClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "data", meta = (DisplayName = "auto save time", ToolTip = "自动保存时间, 以秒为单位，0表示不自动保存"))
	float m_autoSaveTime = 0.0f;

	UPROPERTY(EditAnywhere, Category = "Widget", meta = (DisplayName = "widget", ToolTip = "UI控件类"))
	TSubclassOf<class UUserWidget> m_widgetClass = nullptr;

	UPROPERTY(EditAnywhere, Category = "Widget", meta = (DisplayName = "actor info view widget", ToolTip = "鼠标移入显示actor详情"))
	TSubclassOf<class UActorInfoViewWidget> m_actorInfoViewWidgetClass = nullptr;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UUserWidget> m_widget = nullptr;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UActorInfoViewWidget> m_actorInfoViewWidget = nullptr;

	void AutoSaveGame();
private:
	UMySaveGame* m_saveGame = nullptr;

	FTimerHandle* m_timerHandle = nullptr;
};
