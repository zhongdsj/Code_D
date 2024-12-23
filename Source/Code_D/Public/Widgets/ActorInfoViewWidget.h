// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActorInfoViewWidget.generated.h"

class URichTextBlock;
/**
 * 
 */
UCLASS()
class CODE_D_API UActorInfoViewWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

	void SetText(const FText& _data) const;

	void Show(const FText& _data, const FVector2D& _position);

	void Hide();

protected:
	virtual void NativeOnMouseEnter(const FGeometry& _inGeometry, const FPointerEvent& _inMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& _inMouseEvent) override;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<URichTextBlock> m_richText = nullptr;
private:

	void Collapsed();

	bool m_hover = false;
	bool m_componentHover = false;
};
