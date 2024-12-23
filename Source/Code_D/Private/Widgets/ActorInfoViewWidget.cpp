// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/ActorInfoViewWidget.h"

#include "Components/RichTextBlock.h"

void UActorInfoViewWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UActorInfoViewWidget::SetText(const FText& _data) const
{
	if(this->m_richText != nullptr)
	{
		this->m_richText->SetText(_data);
	}
}

void UActorInfoViewWidget::Show(const FText& _data, const FVector2D& _position)
{
	if(this->m_richText == nullptr)
	{
		return;
	}
	this->m_componentHover = true;
	if(this->GetVisibility() != ESlateVisibility::Visible)
	{
		this->m_richText->SetText(_data);
		this->SetPositionInViewport(_position, true);
		this->SetVisibility(ESlateVisibility::Visible);
	}
}

void UActorInfoViewWidget::NativeOnMouseEnter(const FGeometry& _inGeometry, const FPointerEvent& _inMouseEvent)
{
	this->m_hover = true;
	Super::NativeOnMouseEnter(_inGeometry, _inMouseEvent);
}

void UActorInfoViewWidget::NativeOnMouseLeave(const FPointerEvent& _inMouseEvent)
{
	this->m_hover = false;
	this->GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UActorInfoViewWidget::Collapsed);
	Super::NativeOnMouseLeave(_inMouseEvent);
}

void UActorInfoViewWidget::Collapsed()
{
	if (!this->m_hover && !this->m_componentHover)
	{
		this->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UActorInfoViewWidget::Hide()
{

	this->m_componentHover = false;

	this->Collapsed();
}
