﻿#include "OrganRinse.h"

#include "Components/BoxComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/System/UnknownHUD.h"
#include "Components/TimelineComponent.h"
#include "Unknown/UserInterface/Interaction/RinseObjectsWidget.h"
#include "Unknown/UserInterface/Inventory/PlayerInventoryWidget.h"

AOrganRinse::AOrganRinse()
{
	OrganMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrganMeshComponent"));
	OrganMeshComponent->SetupAttachment(GetRootComponent());

	ToyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ToyMeshComponent"));
	ToyMeshComponent->SetupAttachment(OrganMeshComponent);

	OrganProximityTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("OrganProxmityTrigger"));
	OrganProximityTrigger->AttachToComponent(OrganMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);

	DissolveTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DissolveTimelineComp"));
	
	OrganTag = "ToRinse";
	this->Tags.Add(OrganTag);
}

void AOrganRinse::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<AUnknownHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	UpdateFunctionFloat.BindDynamic(this, &AOrganRinse::UpdateTimelineComp);

	if (DissolveTimelineCurveFloat)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AOrganRinse: DissolveCurveFloat valid!"));
		DissolveTimelineComp->AddInterpFloat(DissolveTimelineCurveFloat, UpdateFunctionFloat);
	}

	// Temp hardcode to test
	//DesiredToyID = "T0001R";

	FRandomStream RandomStream;
	RandomStream.Initialize(FMath::Rand());

	if (ToyDataTable)
	{
		int32 RowsQuantity = ToyDataTable->GetRowNames().Num();
		int32 Min = 0;
		int32 Max = RowsQuantity - 1;
		int32 RandomInt = RandomStream.RandRange(Min,Max);

		DesiredToyID = ToyDataTable->GetRowNames()[RandomInt];

		UE_LOG(LogTemp, Warning, TEXT("%s"), *DesiredToyID.ToString());

		if (!DesiredToyID.IsNone())
		{
			const FToyData* ToyData = ToyDataTable->FindRow<FToyData>(DesiredToyID, DesiredToyID.ToString());

			ToyMeshComponent->SetStaticMesh(ToyData->ToyAssetData.Mesh);
			ToyMeshComponent->SetMaterial(0, ToyData->ToyAssetData.ColorwayMaterial);
		
			ToyMeshComponent->SetRelativeScale3D(FVector(0.25,0.25,0.25));

			IconBrushTexture = ToyData->ToyAssetData.Icon;
			ToyNameText = ToyData->ToyTextData.NameText;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AOrganRinse: ToyID not valid."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AOrganRinse: DataTable not valid."));
	}
}

void AOrganRinse::CloseAndDestroy()
{
	this->Destroy();
}

void AOrganRinse::UpdateTimelineComp(float Output)
{
	//UE_LOG(LogTemp, Warning, TEXT("AOrganRinse: UpdateTimelineComp firing!"));
	Output += 0.001;

	// convert float to string
	FString PrintDissolveProgressValue = FString::SanitizeFloat(Output);

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *PrintDissolveProgressValue);

	OrganMeshComponent->CreateDynamicMaterialInstance(0, OrganMaterialInstance)->SetScalarParameterValue("Progress", Output);

	if (Output >= 0.675)
	{
		CloseAndDestroy();

		if (HUD)
		{
			PlayerInventoryWidget = Cast<UPlayerInventoryWidget>(HUD->PlayerInventoryWidget);

			if (PlayerInventoryWidget)
			{
				PlayerInventoryWidget->WBP_RinseTool->TreasureImage->SetBrushFromTexture(IconBrushTexture);
				PlayerInventoryWidget->WBP_RinseTool->TreasureText->SetText(ToyNameText);
				PlayerInventoryWidget->WBP_RinseTool->SetVisibility(ESlateVisibility::Visible);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("AOrganRinse, UpdateTimelineComp(): Can't access PlayerInventoryWidget in this fashion."));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AOrganRinse, UpdateTimelineComp(): Can't access HUD."));
		}
		
	}
}
