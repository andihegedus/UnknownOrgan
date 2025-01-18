#include "Monster.h"

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

	MonsterPosition1 = CreateDefaultSubobject<UBoxComponent>(TEXT("MonsterPosition1"));
	MonsterPosition1->AttachToComponent(MonsterMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);

	MonsterPosition2 = CreateDefaultSubobject<UBoxComponent>(TEXT("MonsterPosition2"));
	MonsterPosition2->AttachToComponent(MonsterMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);

	MonsterPosition3 = CreateDefaultSubobject<UBoxComponent>(TEXT("MonsterPosition3"));
	MonsterPosition3->AttachToComponent(MonsterMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);

	MonsterTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("MonsterTrigger"));
	MonsterTrigger->AttachToComponent(MonsterMeshComponent, FAttachmentTransformRules::KeepRelativeTransform);

	MonsterTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("MonsterTimelineComp"));
	
	InitialMonsterLocation = MonsterMeshComponent->GetComponentLocation();
	bIsProwling = false;
	
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

	UpdateFunctionFloat.BindDynamic(this, &AMonster::UpdateTimelineComp);
	
	if (MonsterTimelineCurveFloat)
	{
		MonsterTimelineComp->AddInterpFloat(MonsterTimelineCurveFloat, UpdateFunctionFloat);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AMonster: MonsterTimelineCurveFloat not valid."));
	}

	MonsterTrigger->OnComponentBeginOverlap.AddDynamic(this, &AMonster::OnOverlapBegin);
	MonsterTimer();
}

void AMonster::UpdateTimelineComp(float Output)
{

	switch (MonsterPositionID)
	{
		case 1:
			MonsterLocation1 = FVector(InitialMonsterLocation.X + 300.f, InitialMonsterLocation.Y - 300.f, InitialMonsterLocation.Z);
			MonsterMeshComponent->SetRelativeLocation(MonsterLocation1);
			break;
		case 2:
			MonsterLocation2 = FVector(MonsterLocation1.X + 300.f, MonsterLocation1.Y - 300.f, MonsterLocation1.Z);
			MonsterMeshComponent->SetRelativeLocation(MonsterLocation2);
			break;
		case 3:
			MonsterLocation3 = FVector(MonsterLocation2.X + 300.f, MonsterLocation2.Y - 300.f, MonsterLocation2.Z);
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
		UE_LOG(LogTemp, Warning, TEXT("AMonster: MonsterTimer, prowling!"));
		
		GetWorld()->GetTimerManager().SetTimer(MonsterProwlTimerHandle, this, &AMonster::MonsterTimer, 1.f, true);

		if (MonsterTimerLoopCount < 5.f)
		{
			MonsterTimerLoopCount += 1.f;
		}
		else if (MonsterTimerLoopCount >= 5.f)
		{
			if (MonsterPositionID > 0 && MonsterPositionID < 3)
			{
				GetWorld()->GetTimerManager().SetTimer(MonsterProwlTimerHandle, this, &AMonster::MonsterTimer, 1.f, true);
				MonsterPositionID++;
				MonsterTimerLoopCount = 0;
				MoveMonster();
				MonsterTimer();
			}
			else
			{
				GetWorld()->GetTimerManager().ClearTimer(MonsterProwlTimerHandle);
				bIsProwling = false;
				MonsterPositionID = 0;
				MonsterTimerLoopCount = 0;
				MoveMonster();
				MonsterTimer();
			}
		}
	}
	else if (!bIsProwling)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMonster: MonsterTimer, not prowling."));
		
		GetWorld()->GetTimerManager().ClearTimer(MonsterProwlTimerHandle);
		GetWorld()->GetTimerManager().SetTimer(MonsterIdleTimerHandle, this, &AMonster::MonsterTimer, 1.f, true);

		if (MonsterTimerLoopCount < 5.f)
		{
			MonsterTimerLoopCount += 1.f;
		}
		else if (MonsterTimerLoopCount >=  5.f)
		{
			GetWorld()->GetTimerManager().ClearTimer(MonsterIdleTimerHandle);
			bIsProwling = true;
			MonsterPositionID = 1;
			MonsterTimerLoopCount = 0;
			MoveMonster();
			MonsterTimer();
		}
	}
}

void AMonster::MoveMonster()
{
	MonsterTimelineComp->Play();
	UE_LOG(LogTemp, Warning, TEXT("AMonster: MoveMonster triggered."));
}

void AMonster::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* Actor, UPrimitiveComponent* OtherComp,
                              int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("AMonster: Overlap has begun with MonsterTrigger."));
	MonsterPositionID = 0;
	MonsterTimer();
}
