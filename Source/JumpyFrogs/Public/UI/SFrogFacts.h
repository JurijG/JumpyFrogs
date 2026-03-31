// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"


class AJumpyFrogsHUD;
/**
 * 
 */
class JUMPYFROGS_API SFrogFacts : public SCompoundWidget
{
public:

	//void SetFactText(const FText& NewText);
	void SetFactText(const FText& NewText, const FText& PageNumb, const bool bChinese);


protected:
	void UpdateTextBlock();

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	float CurrentOpacity = 0.f;
	float TargetOpacity = 0.8f;
	float DeltaTime = 0.0045f;

	TSharedPtr<STextBlock> FactTextBlock;
	TSharedPtr<STextBlock> PageNumberTextBlock;

	FSlateFontInfo CurrentFont;
	FSlateFontInfo ChineseFont;
	bool bChineseFont = false;
	FText DisplayText;
	
	SLATE_BEGIN_ARGS(SFrogFacts) {}

	SLATE_ARGUMENT(TWeakObjectPtr<AJumpyFrogsHUD>, OwningHUD)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	TWeakObjectPtr<AJumpyFrogsHUD> OwningHUD;

	

	FVector2D GetScreenSize();

	FSlateFontInfo FitTextToBox(const FText& Text, const FSlateFontInfo& BaseFont, float MaxWidth = 0.f, float MaxHeight = 0.f, int32 MinFontSize = 10);
};
