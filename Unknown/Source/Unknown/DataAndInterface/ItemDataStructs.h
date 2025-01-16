#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemDataStructs.generated.h"

class UTexture2D;
class UStaticMesh;

UENUM()
enum class EToyType : uint8
{
	Talkers UMETA(DisplayName = "Talkers"),
	Walkers UMETA(DisplayName = "Walkers"),
	Critters UMETA(DisplayName = "Critters"),
};

USTRUCT()
struct FToyTextData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Text Data")
	FText NameText;

	UPROPERTY(EditAnywhere, Category="Text Data")
	FText DescriptionText;

	UPROPERTY(EditAnywhere, Category="Text Data")
	FText ColorwayText;

	UPROPERTY(EditAnywhere, Category="Text Data")
	FName Tag;
};

USTRUCT()
struct FToyAssetData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Asset Data")
	UTexture2D* Icon;

	// Not sure if this is right either, TBD
	UPROPERTY(EditAnywhere, Category="Asset Data")
	UAnimMontage* Animation;

	//Not sure if I need singles or arrays for both mesh and materials, will include both for now, TBD
	UPROPERTY(EditAnywhere, Category="Asset Data")
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(EditAnywhere, Category="Asset Data")
	TArray<UStaticMesh*> MeshOptions;

	UPROPERTY(EditAnywhere, Category="Asset Data")
	UMaterial* ColorwayMaterial;
	
	UPROPERTY(EditAnywhere, Category="Asset Data")
	TArray<UMaterial*> ColorwayOptions;
	
	UPROPERTY(EditAnywhere, Category="Numeric Data")
	int32 Quantity;
};

USTRUCT()
struct FToyData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Item Data")
	FName ID;

	UPROPERTY(EditAnywhere, Category="Item Data")
	EToyType ToyType;

	UPROPERTY(EditAnywhere, Category="Item Data")
	FToyTextData ToyTextData;

	UPROPERTY(EditAnywhere, Category="Item Data")
	FToyAssetData ToyAssetData;
};
