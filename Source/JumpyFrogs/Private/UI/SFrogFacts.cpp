// Copyright(c) 2011-2026 Jurij Gantar. All Rights Reserved.


#include "UI/SFrogFacts.h"
//#include "Fonts/SlateFontInfo.h"

#define LOCTEXT_NAMESPACE "FactsLibrary"

void SFrogFacts::Construct(const FArguments& InArgs)
{
//	/ Script / Engine.FontFace'/Game/UI/JFont.JFont'
	//int32 FontSize = 80;
	//FSlateFontInfo Font(
	//	FPaths::ProjectDir() / TEXT("Fonts/JFont.ttf"),
	//	//FPaths::ProjectContentDir() / TEXT("../Fonts/JFont.ttf"),
	//	90
	//);

	CurrentFont = FSlateFontInfo(FPaths::ProjectDir() / TEXT("Fonts/JFont.ttf"), 80);
	ChineseFont = FSlateFontInfo(FPaths::ProjectDir() / TEXT("Fonts/DroidSansFallback.ttf"), 80);

	const FMargin ContentPadding = FMargin(500.f, 300.f);

	DisplayText = LOCTEXT("Library", "The Ornate Horned Frog lives in the rainforests of South America. It is the most aggressive and will attack an animal way larger that itself. They are not poisonous but they are fearless. When they feel threatened they will jump toward the enemy and bite them! When hunting, they prefer to wait for their prey to come to them and will eat other frogs, lizards, mice, and large insects.");
	
	//float MaxTextWidth = 800.f;    // max width in pixels
	//float MaxTextHeight = 400.f;   // optional max height

	FVector2D ScreenSize = GetScreenSize();

	FSlateFontInfo FittedFont = FitTextToBox(DisplayText, bChineseFont ? ChineseFont : CurrentFont, ScreenSize.X, ScreenSize.Y);
	
	ChildSlot
		[
			SNew(SOverlay)
			/*	+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
						.ColorAndOpacity(FColor::Transparent)
				]*/
			+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				[
					SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						[
							SNew(SBox)
								.Padding(FMargin(50.f, 20.f, 50.f, 210.f)) // Left=50, Top=20, Right=50, Bottom=0
								//.MaxDesiredWidth(800.f)
								[
									SAssignNew(FactTextBlock, STextBlock)
										.Text(DisplayText)               // initial text
										.Font(FittedFont)                // initial font
										.AutoWrapText(true)              // multi-line
										.ColorAndOpacity(FLinearColor(0.701f, 0.68f, 0.672f, 0.9f)) // initial color
								/*	SNew(STextBlock)
										.Text(DisplayText)
										.Font(FittedFont)
										.AutoWrapText(true)
										.ColorAndOpacity(FLinearColor(0.701f, 0.68f, 0.672f))*/
								]
						]
				]
			+ SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Bottom)
				.Padding(FMargin(0.f, 0.f, 0.f, 65.f)) // 20 px from bottom
				[
					SAssignNew(PageNumberTextBlock, STextBlock)
						.Text(FText::FromString("Test"))
						.Font(CurrentFont) // you can use smaller font if desired
						.ColorAndOpacity(FLinearColor(0.101f, 0.18f, 0.12f, 0.9f))
				]
				/*+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(ContentPadding)
				[
					SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						[
							SNew(STextBlock)
								.Text(TitleText)
						]
				]*/
		];
}

void SFrogFacts::SetFactText(const FText& NewText, const FText& PageNumb, const bool bChinese)
{
	DisplayText = NewText;
	bChineseFont = bChinese;

	UpdateTextBlock();

	if (!PageNumberTextBlock.IsValid())
		return;
	PageNumberTextBlock->SetText(PageNumb);
}
void SFrogFacts::UpdateTextBlock()
{
	if (!FactTextBlock.IsValid())
		return;
	// Get the current viewport size
	FVector2D ScreenSize = GetScreenSize();

	/*if (true)
	{
		ChineseFont
	}*/
	// Fit the text to the box
	FSlateFontInfo FittedFont = FitTextToBox(DisplayText, bChineseFont ? ChineseFont : CurrentFont, ScreenSize.X, ScreenSize.Y);
	//  Apply the font to the text block
	FactTextBlock->SetText(DisplayText);
	FactTextBlock->SetFont(FittedFont);
}
FVector2D SFrogFacts::GetScreenSize()
{
	if (GEngine && GEngine->GameViewport)
	{
		FIntPoint Size = GEngine->GameViewport->Viewport->GetSizeXY();
		return FVector2D((float)Size.X, (float)Size.Y);
	}
	return FVector2D(1920.f, 1080.f); // fallback
}

FSlateFontInfo SFrogFacts::FitTextToBox(const FText& Text, const FSlateFontInfo& BaseFont, float MaxWidth, float MaxHeight, int32 MinFontSize)
{	
	int32 FontSize = BaseFont.Size;
	FSlateFontInfo FontInfo = BaseFont;
	TSharedRef<FSlateFontMeasure> FontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
	
	// Approximate multi-line fitting
	while (FontSize >= MinFontSize)
	{
		FontInfo.Size = FontSize;
		FVector2D TextSize = FontMeasure->Measure(Text, FontInfo);

		// Simple heuristic: if single-line width is larger than MaxWidth, assume it will wrap
		float EstimatedLines = FMath::CeilToFloat(TextSize.X / MaxWidth);
		float EstimatedHeight = EstimatedLines * TextSize.Y * 1.2f;

		if (TextSize.X <= MaxWidth || EstimatedHeight <= MaxHeight)
			break;

		FontSize--;
	}
	return FontInfo;
}
#undef LOCTEXT_NAMESPACE

