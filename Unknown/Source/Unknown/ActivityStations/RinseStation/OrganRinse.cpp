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
	DissolveProgressValue += 0.02;

	OrganMeshComponent->CreateDynamicMaterialInstance(0, OrganMaterialInstance)->SetScalarParameterValue("Progress", DissolveProgressValue);
}
