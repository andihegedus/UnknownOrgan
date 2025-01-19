#include "ToyInspector.h"

#include "GameFramework/PlayerController.h"
#include "Unknown/UnknownGameInstance.h"
#include "Unknown/Data/ItemDataStructs.h"
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

void AToyInspector::SwapMesh(FText ID)
{
	DesiredToyID = FName(ID.ToString());
	
	const FToyData* ToyData = ToyDataTable->FindRow<FToyData>(DesiredToyID, DesiredToyID.ToString());
	
	if (ToyData)
	{
		const FString TestNameFromData = ToyData->ToyTextData.NameText.ToString();
	
		UE_LOG(LogTemp, Warning, TEXT("AToyInspector: Swap mesh!"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *TestNameFromData);

		ToyMeshComponent->SetStaticMesh(ToyData->ToyAssetData.Mesh);
		ToyMeshComponent->SetMaterial(0, ToyData->ToyAssetData.ColorwayMaterial);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AToyInspector: SwapMesh, ToyData not valid."));
	}

	
}

