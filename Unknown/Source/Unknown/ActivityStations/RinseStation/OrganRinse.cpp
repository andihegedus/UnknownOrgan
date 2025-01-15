#include "OrganRinse.h"

#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "Materials/MaterialInstance.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/System/UnknownHUD.h"
#include "Components/TimelineComponent.h"

AOrganRinse::AOrganRinse()
{
	OrganMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrganMeshComponent"));
	DissolveTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DissolveTimelineComp"));
	OrganMeshComponent->SetupAttachment(GetRootComponent());

	OrganProximityTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("OrganProxmityTrigger"));
	OrganProximityTrigger->AttachToComponent(OrganMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);

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
		UE_LOG(LogTemp, Warning, TEXT("AOrganRinse: DissolveCurveFloat valid!"));
		DissolveTimelineComp->AddInterpFloat(DissolveTimelineCurveFloat, UpdateFunctionFloat);
	}
}

void AOrganRinse::CloseAndDestroy()
{
}

void AOrganRinse::DissolveOrgan()
{
	
}

void AOrganRinse::UpdateTimelineComp(float Output)
{
	//UE_LOG(LogTemp, Warning, TEXT("AOrganRinse: UpdateTimelineComp firing!"));
	Output += 0.001;

	// convert float to string
	FString PrintDissolveProgressValue = FString::SanitizeFloat(Output);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *PrintDissolveProgressValue);

	OrganMeshComponent->CreateDynamicMaterialInstance(0, OrganMaterialInstance)->SetScalarParameterValue("Progress", Output);

	/*FHashedMaterialParameterInfo ParameterInfo;

	OrganMeshComponent->CreateDynamicMaterialInstance(0, OrganMaterialInstance)->GetScalarParameterValue(ParameterInfo,DissolveProgressValue);
	FString PrintScalarValue = FString::SanitizeFloat(DissolveProgressValue);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *PrintDissolveProgressValue);*/
}
