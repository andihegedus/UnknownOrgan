#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Monster.generated.h"

class AUnknownHUD;
class APCharacter;
class APController;
class UUnknownGameInstance;
class UStaticMeshComponent;
class UTimelineComponent;
class UBoxComponent;
class UCurveFloat;
class FName;
class UPrimitiveComponent;

//DECLARE_MULTICAST_DELEGATE(FOnMonsterStateUpdated);

UCLASS()
class UNKNOWN_API AMonster : public AActor
{
	GENERATED_BODY()
	
public:
	// FUNCTIONS
	// -----------------------------
	AMonster();

	virtual void BeginPlay() override;

	void MonsterRetreatTimer();

	// PROPERTIES & VARIABLES
	// -----------------------------

	UPROPERTY()
	AUnknownHUD* HUD;

	UPROPERTY()
	APCharacter* PlayerCharacter;

	UPROPERTY()
	APController* PlayerController;

	UPROPERTY()
	UUnknownGameInstance* GameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MonsterTag;

	UPROPERTY(EditAnywhere)
	UCurveFloat* MonsterTimelineCurveFloat;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UTimelineComponent* MonsterTimelineComp;

	UPROPERTY(EditAnywhere)
	FVector InitialMonsterLocation;

	UPROPERTY(EditAnywhere)
	FVector MonsterLocation1;

	UPROPERTY(EditAnywhere)
	FVector MonsterLocation2;

	UPROPERTY(EditAnywhere)
	FVector MonsterLocation3;

	UPROPERTY(EditAnywhere)
	int32 MonsterPositionID;

	bool bIsRetreating;

	//FOnMonsterStateUpdated OnMonsterStateUpdated;

protected:
	// FUNCTIONS
	// -----------------------------
	UFUNCTION()
	void UpdateTimelineComp(float Output);

	void MonsterTimer();

	void MoveMonster();

	/*UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* Actor,
		class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);*/


	// PROPERTIES & VARIABLES
	// -----------------------------

	// It was a mesh!
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MonsterMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* MonsterTrigger;

	FOnTimelineFloat UpdateFunctionFloat;

	FTimerHandle MonsterProwlTimerHandle;

	FTimerHandle MonsterIdleTimerHandle;

	FTimerHandle MonsterRetreatTimerHandle;

	float MonsterTimerLoopCount;

	bool bIsProwling;
};
