#include "ToyInspector.h"

#include "GameFramework/PlayerController.h"
#include "Unknown/UnknownGameInstance.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/System/UnknownHUD.h"

AToyInspector::AToyInspector()
{
	ToyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ToyMeshComponent"));
	ToyMeshComponent->SetupAttachment(GetRootComponent());

	ToyTag = "ToInspect";
	this->Tags.Add(ToyTag);
}

void AToyInspector::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<AUnknownHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	GameInstance = Cast<UUnknownGameInstance>(GetWorld()->GetGameInstance());

}

void AToyInspector::RotateToy()
{
	UE_LOG(LogTemp, Warning, TEXT("AToyInspector: Rotate!"));
}

void AToyInspector::StopRotateToy()
{
	UE_LOG(LogTemp, Warning, TEXT("AToyInspector: Stop!"));
}

