#include "OrganRinse.h"

#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/System/UnknownHUD.h"

AOrganRinse::AOrganRinse()
{
	OrganMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrganMeshComponent"));
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

	//OrganProximityTrigger->OnBeginCursorOver.AddDynamic(this, &AOrganRinse::OnMouseOverlapBegin);
}

void AOrganRinse::CloseAndDestroy()
{
}

void AOrganRinse::DissolveOrgan()
{
}

void AOrganRinse::OnMouseOverlapBegin(UPrimitiveComponent* OverlappedComp)
{
}
