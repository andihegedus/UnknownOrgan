#include "ToyInspector.h"

#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "Unknown/UnknownGameInstance.h"
#include "Unknown/Data/ItemDataStructs.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/System/UnknownHUD.h"

AToyInspector::AToyInspector()
{
	ToyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ToyMeshComponent"));
	ToyMeshComponent->SetupAttachment(GetRootComponent());

	ToyHitBoxExtender = CreateDefaultSubobject<UBoxComponent>(TEXT("ToyHitBoxExtender"));
	ToyHitBoxExtender->AttachToComponent(ToyMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ToyTag = "ToInspect";
	this->Tags.Add(ToyTag);

	HitBoxTag = "ToInspect";
	ToyHitBoxExtender->ComponentTags.Add(HitBoxTag);
}

void AToyInspector::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<AUnknownHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	GameInstance = Cast<UUnknownGameInstance>(GetWorld()->GetGameInstance());

	ToyMeshComponent->SetVisibility(false);

}

void AToyInspector::RotateToy()
{
	//UE_LOG(LogTemp, Warning, TEXT("AToyInspector: Rotate!"));
}

void AToyInspector::StopRotateToy()
{
	//UE_LOG(LogTemp, Warning, TEXT("AToyInspector: Stop!"));
}

void AToyInspector::SwapMesh(FText ID)
{
	ToyMeshComponent->SetVisibility(true);
	
	DesiredToyID = FName(ID.ToString());
	
	const FToyData* ToyData = ToyDataTable->FindRow<FToyData>(DesiredToyID, DesiredToyID.ToString());
	
	if (ToyData)
	{
		const FString TestNameFromData = ToyData->ToyTextData.NameText.ToString();
	
		UE_LOG(LogTemp, Warning, TEXT("AToyInspector: Swap mesh!"));
		UE_LOG(LogTemp, Warning, TEXT("%s"), *TestNameFromData);

		ToyMeshComponent->SetStaticMesh(ToyData->ToyAssetData.Mesh);
		ToyMeshComponent->SetWorldScale3D(FVector(0.3,0.3,0.3));
		ToyMeshComponent->SetWorldRotation(FRotator(0,180,0));
		ToyMeshComponent->SetMaterial(0, ToyData->ToyAssetData.ColorwayMaterial);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AToyInspector: SwapMesh, ToyData not valid."));
	}

	
}

