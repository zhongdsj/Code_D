// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/WorldGameMode.h"

#include "MyGameInstance.h"
#include "MySaveGame.h"
#include "Actors/SaveGameInterface.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/ActorInfoViewWidget.h"


AWorldGameMode::AWorldGameMode()
{
	this->m_timerHandle = new FTimerHandle;
}

void AWorldGameMode::SaveGame(const FString& _slot_name)
{
	if (this->m_saveGame == nullptr)
	{
		this->m_saveGame = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(this->m_saveGameClass));
	}
	auto game_instance = Cast<UMyGameInstance>(this->GetGameInstance());
	this->m_saveGame->SaveFactionTable(game_instance->GetFactionDataTable());
	this->m_saveGame->SavePersonTable(game_instance->GetPersonDataTable());
	this->m_saveGame->SaveCityTable(game_instance->GetCityDataTable());
	TArray<AActor*> save_actor_array;
	UGameplayStatics::GetAllActorsWithInterface(this->GetWorld(), USaveGameInterface::StaticClass(), save_actor_array);
	for(auto item : save_actor_array)
	{
		auto save_actor = Cast<ISaveGameInterface>(item);
		save_actor->SaveGame(this->m_saveGame);
	}
	UGameplayStatics::AsyncSaveGameToSlot(this->m_saveGame,  _slot_name.IsEmpty() ? "auto_save" : _slot_name, 0, FAsyncSaveGameToSlotDelegate::CreateLambda([&](const FString& _name, const int32 _index, bool _saved)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("name: %s, saved"), GetData(_name)));
	}));
}

void AWorldGameMode::LoadGame()
{
	auto game_instance = Cast<UMyGameInstance>(this->GetGameInstance());
	if(game_instance == nullptr)
	{
		return;
	}
	if(game_instance->GetLoadName().IsEmpty())
	{
		return;
	}
	this->NotifyOnLoadedGame();
	/*UGameplayStatics::AsyncLoadGameFromSlot(game_instance->GetLoadName(), 0, FAsyncLoadGameFromSlotDelegate::CreateLambda([&, game_instance](const FString& _name, const int32 _index, USaveGame* _saveGame)
	{
		this->m_saveGame = Cast<UMySaveGame>(_saveGame);
		if(this->m_saveGame == nullptr)
		{
			return;
		}
		this->m_saveGame->LoadPersonTable(game_instance->GetPersonDataTable());
		this->m_saveGame->LoadFactionTable(game_instance->GetFactionDataTable());
		this->m_saveGame->LoadCityTable(game_instance->GetCityDataTable());
		
		TArray<AActor*> save_actor_array;
		UGameplayStatics::GetAllActorsWithInterface(this->GetWorld(), USaveGameInterface::StaticClass(), save_actor_array);
		for (auto item : save_actor_array)
		{
			auto save_actor = Cast<ISaveGameInterface>(item);
			save_actor->LoadGame(this->m_saveGame);
		}
		this->NotifyLoadedGame();
	}));*/
	this->m_saveGame = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(game_instance->GetLoadName(), 0));
	if (this->m_saveGame == nullptr)
	{
		return;
	}
	this->m_saveGame->LoadPersonTable(game_instance->GetPersonDataTable());
	this->m_saveGame->LoadFactionTable(game_instance->GetFactionDataTable());
	this->m_saveGame->LoadCityTable(game_instance->GetCityDataTable());

	TArray<AActor*> save_actor_array;
	UGameplayStatics::GetAllActorsWithInterface(this->GetWorld(), USaveGameInterface::StaticClass(), save_actor_array);
	for (auto item : save_actor_array)
	{
		auto save_actor = Cast<ISaveGameInterface>(item);
		save_actor->LoadGame(this->m_saveGame);
	}
	this->NotifyLoadedGame();
	// game_instance->SetLoadName("");
}

void AWorldGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	this->LoadGame();
	this->m_widget = CreateWidget(this->GetWorld(), this->m_widgetClass);
	this->m_actorInfoViewWidget = Cast<UActorInfoViewWidget>(CreateWidget(this->GetWorld(), this->m_actorInfoViewWidgetClass));
	if (this->m_widget != nullptr)
	{
		this->m_widget->AddToViewport();
	}
	if (this->m_actorInfoViewWidget != nullptr)
	{
		this->m_actorInfoViewWidget->Hide();
		this->m_actorInfoViewWidget->AddToViewport();
	}
}

void AWorldGameMode::ShowActorInfo(const FText& _text, FVector2D _position) const
{
	if(this->m_actorInfoViewWidget != nullptr)
	{
		this->m_actorInfoViewWidget->Show(_text, _position);
	}
}

void AWorldGameMode::HideActorInfo() const
{
	if (this->m_actorInfoViewWidget != nullptr)
	{
		this->m_actorInfoViewWidget->Hide();
	}
}

void AWorldGameMode::SetTimeDilation(float _dilation)
{
	FName func_name("PauseButtonClick");
	UFunction* func = nullptr;

	if(_dilation == 0.0f)
	{
		func_name = "PauseButtonClick";
	}else if(_dilation == 1.0f)
	{
		func_name = "OneButtonClick";
	}else if(_dilation == 2.0f)
	{
		func_name = "TwoButtonClick";
	}

	func = this->m_widget->FindFunction(func_name);
	if (func == nullptr)
	{
		return;
	}
	this->m_widget->ProcessEvent(func, nullptr);
}

void AWorldGameMode::BeginPlay()
{
	Super::BeginPlay();
	if(this->m_autoSaveTime != 0)
	{
		GetWorld()->GetTimerManager().SetTimer(*this->m_timerHandle, this, &AWorldGameMode::AutoSaveGame, this->m_autoSaveTime, true);
	}
}

void AWorldGameMode::EndPlay(const EEndPlayReason::Type _endPlayReason)
{
	Super::EndPlay(_endPlayReason);
	if (this->m_timerHandle != nullptr)
	{
		GetWorldTimerManager().ClearTimer(*this->m_timerHandle);
		delete this->m_timerHandle;
	}
}

void AWorldGameMode::AutoSaveGame()
{
	this->SaveGame("");
}
