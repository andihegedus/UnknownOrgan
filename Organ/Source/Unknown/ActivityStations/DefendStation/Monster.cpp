#include "Monster.h"

#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/PlayerController.h"
#include "Unknown/UnknownGameInstance.h"
#include "Unknown/PlayerCharacter/PCharacter.h"
#include "Unknown/System/UnknownHUD.h"

AMonster::AMonster()
{
	MonsterMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MonsterMeshComponent"));
	MonsterMeshComponent->SetupAttachment(GetRootComponent());

	MonsterTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("MonsterTimelineComp"));
	
	InitialMonsterLocation = MonsterMeshComponent->GetComponentLocation();
	bIsProwling = false;
	bIsRetreating = false;
	
	MonsterTag = "ToSwat";
	this->Tags.Add(MonsterTag);
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<AUnknownHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	PlayerCharacter = Cast<APCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	GameInstance = Cast<UUnknownGameInstance>(GetWorld()->GetGameInstance());

	MonsterPositionID = 0;

	if (GameInstance)
	{
		GameInstance->MonsterPositionID = MonsterPositionID;
		GameInstance->bIsRetreating = bIsRetreating;
	}

	UpdateFunctionFloat.BindDynamic(this, &AMonster::UpdateTimelineComp);
	
	if (MonsterTimelineCurveFloat)
	{
		MonsterTimelineComp->AddInterpFloat(MonsterTimelineCurveFloat, UpdateFunctionFloat);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AMonster: MonsterTimelineCurveFloat not valid."));
	}

	//MonsterTrigger->OnComponentBeginOverlap.AddDynamic(this, &AMonster::OnOverlapBegin);
	MonsterTimer();
}

void AMonster::UpdateTimelineComp(float Output)
{

	switch (MonsterPositionID)
	{
		case 1:
			MonsterLocation1 = FVector(InitialMonsterLocation.X + 200.f, InitialMonsterLocation.Y - 25.f, InitialMonsterLocation.Z);
			MonsterMeshComponent->SetRelativeLocation(MonsterLocation1);
			break;
		case 2:
			MonsterLocation2 = FVector(MonsterLocation1.X + 100.f, MonsterLocation1.Y - 75.f, MonsterLocation1.Z);
			MonsterMeshComponent->SetRelativeLocation(MonsterLocation2);
			break;
		case 3:
			MonsterLocation3 = FVector(MonsterLocation2.X + 250.f, MonsterLocation2.Y + 425.f, MonsterLocation2.Z);
			MonsterMeshComponent->SetRelativeLocation(MonsterLocation3);
			break;
		case 0:
			MonsterMeshComponent->SetRelativeLocation(InitialMonsterLocation);
			break;
		default:
			MonsterMeshComponent->SetRelativeLocation(InitialMonsterLocation);
			break;
		
	}
}

void AMonster::MonsterTimer()
{
	if (bIsProwling)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AMonster: MonsterTimer, prowling!"));
		
		GetWorld()->GetTimerManager().SetTimer(MonsterProwlTimerHandle, this, &AMonster::MonsterTimer, 1.f, true);

		if (MonsterTimerLoopCount < 25.f)
		{
			MonsterTimerLoopCount += 1.f;
		}
		else if (MonsterTimerLoopCount >= 25.f)
		{
			if (MonsterPositionID > 0 && MonsterPositionID < 3)
			{
				/*if (MonsterPositionID == 1)
				{
					OnMonsterStateUpdated.Broadcast();
				}*/
				
				GetWorld()->GetTimerManager().SetTimer(MonsterProwlTimerHandle, this, &AMonster::MonsterTimer, 1.f, true);
				MonsterPositionID++;

				if (GameInstance)
				{
					GameInstance->MonsterPositionID = MonsterPositionID;
				}
				
				MonsterTimerLoopCount = 0;
				MoveMonster();
				MonsterTimer();
			}
			else
			{
				if (MonsterPositionID == 3)
				{
					//OnMonsterStateUpdated.Broadcast();
					//AudioComponent->Play();
					
					if (GameInstance)
					{
						if (GameInstance->AcquiredToyIDs.Num() > 0)
						{
							FRandomStream RandomStream;
							RandomStream.Initialize(FMath::Rand());

							int32 ArrayLength = GameInstance->AcquiredToyIDs.Num();
							int32 Min = 0;
							int32 Max = ArrayLength - 1;
							int32 RandomInt = RandomStream.RandRange(Min,Max);

							GameInstance->AcquiredToyIDs.RemoveAt(RandomInt);

							if (PlayerCharacter)
							{
								PlayerCharacter->OnInventoryStateUpdated.Broadcast();
							}

							UE_LOG(LogTemp, Warning, TEXT("AMonster: Monster removed item from inventory!"));
						}
					}
				}
				GetWorld()->GetTimerManager().ClearTimer(MonsterProwlTimerHandle);
				bIsProwling = false;
				MonsterPositionID = 0;
				
				if (GameInstance)
				{
					GameInstance->MonsterPositionID = MonsterPositionID;
				}
				
				MonsterTimerLoopCount = 0;
				MoveMonster();
				MonsterTimer();
			}
		}
	}
	else if (!bIsProwling)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AMonster: MonsterTimer, not prowling."));
		
		GetWorld()->GetTimerManager().ClearTimer(MonsterProwlTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(MonsterIdleTimerHandle, this, &AMonster::MonsterTimer, 1.f, true);

		if (MonsterTimerLoopCount < 120.f)
		{
			MonsterTimerLoopCount += 1.f;
		}
		else if (MonsterTimerLoopCount >=  120.f)
		{
			GetWorld()->GetTimerManager().ClearTimer(MonsterIdleTimerHandle);
			bIsProwling = true;
			MonsterPositionID = 1;

			if (GameInstance)
			{
				GameInstance->MonsterPositionID = MonsterPositionID;
			}
			
			MonsterTimerLoopCount = 0;
			MoveMonster();
			MonsterTimer();
		}
	}
}

void AMonster::MonsterRetreatTimer()
{
	if (bIsRetreating)
	{
		//UE_LOG(LogTemp, Warning, TEXT("AMonster: MonsterRetreatTimer, retreating."));
		
		GetWorld()->GetTimerManager().ClearTimer(MonsterProwlTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(MonsterRetreatTimerHandle, this, &AMonster::MonsterRetreatTimer, 1.f, true);

		if (MonsterTimerLoopCount < 2.f)
		{
			MonsterTimerLoopCount += 1.f;
		}
		else if (MonsterTimerLoopCount >= 2.f)
		{
			if (MonsterPositionID > 0)
			{
				GetWorld()->GetTimerManager().SetTimer(MonsterRetreatTimerHandle, this, &AMonster::MonsterRetreatTimer, 1.f, true);
				MonsterPositionID--;
				MonsterTimerLoopCount = 0;
				MoveMonster();
				MonsterRetreatTimer();
			}
			else
			{
				GetWorld()->GetTimerManager().ClearTimer(MonsterRetreatTimerHandle);
				bIsProwling = false;
				bIsRetreating = false;
				MonsterPositionID = 0;

				if (GameInstance)
				{
					GameInstance->MonsterPositionID = MonsterPositionID;
				}
				
				MonsterTimerLoopCount = 0;
				MoveMonster();
				MonsterTimer();
			}
		}
	}
	else if (!bIsRetreating)
	{
		GetWorld()->GetTimerManager().ClearTimer(MonsterRetreatTimerHandle);
		bIsProwling = false;
		MonsterPositionID = 0;

		if (GameInstance)
		{
			GameInstance->MonsterPositionID = MonsterPositionID;
		}
		
		MonsterTimerLoopCount = 0;
		MoveMonster();
		MonsterTimer();
	}
	
}

void AMonster::MoveMonster()
{
	MonsterTimelineComp->Play();
	UE_LOG(LogTemp, Warning, TEXT("AMonster: MoveMonster triggered."));
}

/*
void AMonster::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* Actor, UPrimitiveComponent* OtherComp,
                              int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("AMonster: Overlap has begun with MonsterTrigger."));
	MonsterPositionID = 0;
	MonsterTimer();
}*/
