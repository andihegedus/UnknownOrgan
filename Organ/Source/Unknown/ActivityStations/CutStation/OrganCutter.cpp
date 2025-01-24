#include "OrganCutter.h"

#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/PlayerCharacter/PController.h"
#include "Unknown/System/UnknownHUD.h"

AOrganCutter::AOrganCutter()
{
	OrganMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrganMeshComponent"));
	OrganMeshComponent->SetupAttachment(GetRootComponent());

	OrganProximityTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("OrganProxmityTrigger"));
	OrganProximityTrigger->AttachToComponent(OrganMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void AOrganCutter::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<AUnknownHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	OrganProximityTrigger->OnBeginCursorOver.AddDynamic(this, &AOrganCutter::OnMouseOverlapBegin);

	if (PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("AOrganCutter: PlayerCharatcer valid!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AOrganCutter: PlayerCharatcer not valid."));
	}
}

void AOrganCutter::CloseAndDestroy()
{
	//HUD->HideInteractionWidget();
}

void AOrganCutter::SwapOrganMesh()
{
}

void AOrganCutter::OnMouseOverlapBegin(UPrimitiveComponent* OverlappedComp)
{
	UE_LOG(LogTemp, Warning, TEXT("AOrganCutter: Mouse has overlapped trigger"));
}




