#include "Monster.h"

#include "GameFramework/PlayerController.h"
#include "Unknown/UnknownGameInstance.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/System/UnknownHUD.h"

AMonster::AMonster()
{
	MonsterMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MonsterMeshComponent"));
	MonsterMeshComponent->SetupAttachment(GetRootComponent());

	MonsterTag = "ToSwat";
	this->Tags.Add(MonsterTag);
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<AUnknownHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	GameInstance = Cast<UUnknownGameInstance>(GetWorld()->GetGameInstance());
}
