#include "PCharacter.h"

#include "PController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InterchangeTranslatorBase.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Unknown/UnknownGameInstance.h"
#include "Unknown/ActivityStations/DefendStation/Monster.h"
#include "Unknown/ActivityStations/RinseStation/OrganRinse.h"
#include "Unknown/ActivityStations/TestStation/ToyInspector.h"
#include "Unknown/System/UnknownHUD.h"
#include "Unknown/UserInterface/Interaction/OrganCutterWidget.h"
#include "Unknown/UserInterface/Inventory/PlayerInventoryWidget.h"

APCharacter::APCharacter()
{
	// Setup PC Camera components
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(GetRootComponent());
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	// Assign SpringArm class variables
	SpringArmComp->TargetArmLength = 0.f;
	SpringArmComp->bEnableCameraLag = false;
	SpringArmComp->bUsePawnControlRotation = true;

	// Take control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Interaction variables
	LineTraceStart = {FVector::ZeroVector};
	CheckInteractionDistance = 400.f;
}

void APCharacter::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<AUnknownHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	GameInstance = Cast<UUnknownGameInstance>(GetWorld()->GetGameInstance());

	CheckForInteractable();
}

void APCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (GameInstance)
	{
		if (GameInstance->MonsterPositionID == 1 || GameInstance->MonsterPositionID == 3)
		{
			OnMonsterStateUpdated.Broadcast();
			OnInventoryStateUpdated.Broadcast();

			if (HUD)
			{
				HUD->ShowMonsterLogger();
			}
		}
		else
		{
			if (HUD)
			{
				HUD->HideMonsterLogger();
			}
		}
	}
}

void APCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	APController* PlayerBaseController = CastChecked<APController>(Controller);

	check(EnhancedInputComponent && PlayerBaseController);

	EnhancedInputComponent->BindAction(PlayerBaseController->EscapeAction, ETriggerEvent::Completed, this, &APCharacter::OpenCloseWidget);
	EnhancedInputComponent->BindAction(PlayerBaseController->ShelfInventoryAction, ETriggerEvent::Completed, this, &APCharacter::OpenShelfInventory);
	EnhancedInputComponent->BindAction(PlayerBaseController->RinseAction, ETriggerEvent::Triggered, this, &APCharacter::StartInteraction);
	EnhancedInputComponent->BindAction(PlayerBaseController->RinseAction, ETriggerEvent::Completed, this, &APCharacter::StopInteraction);


	ULocalPlayer* LocalPlayer = PlayerBaseController->GetLocalPlayer();

	check(LocalPlayer);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	check(Subsystem);
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(PlayerBaseController->PCMappingContext, 0);
}

void APCharacter::OpenCloseWidget()
{
	if (!HUD->WidgetTags.Contains("ShelfInventory"))
	{
		HUD->ShowHideSaveLoadWidget();
	}
	if (HUD->WidgetTags.Contains("ShelfInventory"))
	{
		HUD->HideShelfInventoryWidget();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("APCharacter: No tags present in WidgetTages."));
	}
	
}

void APCharacter::OpenShelfInventory()
{
	HUD->ShowShelfInventoryWidget();
}

void APCharacter::StartInteraction()
{
	if (TagInFocus.Contains("ToRinse"))
	{
		if (this->GetWorld()->GetFirstPlayerController())
		{
			this->GetWorld()->GetFirstPlayerController()->CurrentMouseCursor = EMouseCursor::GrabHandClosed;

			CheckForInteraction();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("APCharacter: PlayerController not valid.")); 
		}
	}
	if (TagInFocus.Contains("ToInspect") || TagInFocus.Contains("Test"))
	{
		if (this->GetWorld()->GetFirstPlayerController())
		{
			this->GetWorld()->GetFirstPlayerController()->CurrentMouseCursor = EMouseCursor::GrabHand;

			CheckForInteraction();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("APCharacter: PlayerController not valid.")); 
		}
	}
	if (TagInFocus.Contains("ToSwat"))
	{
		if (this->GetWorld()->GetFirstPlayerController())
		{
			this->GetWorld()->GetFirstPlayerController()->CurrentMouseCursor = EMouseCursor::Hand;

			CheckForInteraction();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("APCharacter: PlayerController not valid.")); 
		}
	}
}

void APCharacter::StopInteraction()
{
	if (this->GetWorld()->GetFirstPlayerController())
	{
		this->GetWorld()->GetFirstPlayerController()->CurrentMouseCursor = EMouseCursor::Default;

		CheckForInteraction();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("APCharacter: PlayerController not valid."));
	}
}

void APCharacter::RotatePlayerCameraLeft()
{
	TagInFocus.Empty();
	
	UE_LOG(LogTemp, Warning, TEXT("APCharacter: Rotate Left!"));

	PlayerCameraRotation = CameraComp->GetComponentRotation();

	const FRotator NewRotation(PlayerCameraRotation.Pitch, PlayerCameraRotation.Yaw - 90.f, PlayerCameraRotation.Roll);

	CameraComp->SetRelativeRotation(NewRotation);

	// Convert FRotator to string
	FString PrintCurrentRotation = NewRotation.ToString();

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *PrintCurrentRotation);

	CheckForInteractable();
}

void APCharacter::RotatePlayerCameraRight()
{
	TagInFocus.Empty();

	UE_LOG(LogTemp, Warning, TEXT("APCharacter: Rotate Right!"));

	PlayerCameraRotation = CameraComp->GetComponentRotation();

	const FRotator NewRotation(PlayerCameraRotation.Pitch, PlayerCameraRotation.Yaw + 90.f, PlayerCameraRotation.Roll);

	CameraComp->SetRelativeRotation(NewRotation);

	FString PrintCurrentRotation = NewRotation.ToString();

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *PrintCurrentRotation);

	CheckForInteractable();
}


void APCharacter::CheckForInteractable()
{
	LineTraceStart = GetPawnViewLocation() - 50.f;
	
	FVector LineTraceEnd{LineTraceStart + (CameraComp->GetComponentRotation().Vector() * CheckInteractionDistance)};
	float LookDirection = FVector::DotProduct(GetActorForwardVector(), CameraComp->GetComponentRotation().Vector());

	if (LookDirection > 0)
	{
		// Visualize the trace hit line
		DrawDebugLine(GetWorld(), LineTraceStart, LineTraceEnd, FColor::Magenta, false, 1.0f, 0, 2.f);

		FCollisionQueryParams QueryParams;

		QueryParams.AddIgnoredActor(this);

		FHitResult TraceHit;

		if(GetWorld()->LineTraceSingleByChannel(TraceHit, LineTraceStart, LineTraceEnd, ECC_Visibility, QueryParams))
		{
			if (TraceHit.GetActor()->Tags.Contains("Cut"))
			{
				UE_LOG(LogTemp, Warning, TEXT("APCharacter: Cut!"));
				
				CurrentTag = "Cut";
				TagInFocus.Add(CurrentTag);
		
				return;
			}
			if (TraceHit.GetActor()->Tags.Contains("Rinse"))
			{
				UE_LOG(LogTemp, Warning, TEXT("APCharacter: Rinse!"));
				
				CurrentTag = "Rinse";
				TagInFocus.Add(CurrentTag);
		
				return;
			}
			if (TraceHit.GetActor()->Tags.Contains("Test"))
			{
				UE_LOG(LogTemp, Warning, TEXT("APCharacter: Test!"));
				
				CurrentTag = "Test";
				TagInFocus.Add(CurrentTag);
		
				return;
			}
			if (TraceHit.GetActor()->Tags.Contains("Door"))
			{
				UE_LOG(LogTemp, Warning, TEXT("APCharacter: Door!"));
				
				CurrentTag = "Door";
				TagInFocus.Add(CurrentTag);
		
				return;
			}
			if (TraceHit.GetActor()->Tags.Contains("ToRinse"))
			{
				CurrentTag = "ToRinse";
				TagInFocus.Add(CurrentTag);

				OrganRinse = Cast<AOrganRinse>(TraceHit.GetActor());

				if (OrganRinse)
				{
					OrganRinse->SpawnOrgansToRinse();
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("APCharacter: Rinse, OrganRinse not valid."));
				}
		
				return;
			}
			if (TraceHit.GetActor()->Tags.Contains("ToInspect"))
			{
				//UE_LOG(LogTemp, Warning, TEXT("APCharacter: Toy to inspect!"));
				
				CurrentTag = "ToInspect";
				TagInFocus.Add(CurrentTag);

				return;
			}
			if (TraceHit.GetActor()->Tags.Contains("ToSwat"))
			{
				UE_LOG(LogTemp, Warning, TEXT("APCharacter: Monster to swat!"));
				
				CurrentTag = "ToSwat";
				TagInFocus.Add(CurrentTag);

				return;
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("APCharacter: No interactables found."));
	TagInFocus.Empty();
}

void APCharacter::CheckForInteraction()
{
	if (this->GetWorld()->GetFirstPlayerController())
	{
		FCollisionQueryParams QueryParams;

		QueryParams.AddIgnoredActor(this);

		FHitResult CursorHit;
		
		if (this->GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorForObjects(ObjectTypes,false,CursorHit))
		{
			FName ActorName = FName(CursorHit.GetActor()->GetName());
			FString Stringy = ActorName.ToString();
							
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *Stringy);
							
			if (CursorHit.GetActor()->Tags.Contains("ToRinse"))
			{
				//UE_LOG(LogTemp, Warning, TEXT("APCharacter: Cursor hit on ToRinse!"));

				OrganRinse = Cast<AOrganRinse>(CursorHit.GetActor());

				if (OrganRinse)
				{
					if (this->GetWorld()->GetFirstPlayerController()->CurrentMouseCursor.GetValue() ==  EMouseCursor::GrabHandClosed)
					{
						OrganRinse->DissolveTimelineComp->Play();
					}
					else
					{
						OrganRinse->DissolveTimelineComp->Stop();	
					}
				}
			}
			else
			{
				//UE_LOG(LogTemp, Warning, TEXT("APCharacter: No rinse :("));
			}
			if (CursorHit.GetActor()->Tags.Contains("ToInspect") || CursorHit.GetComponent()->ComponentTags.Contains("ToInspect"))
			{
				//UE_LOG(LogTemp, Warning, TEXT("APCharacter: Cursor hit on ToInspect!"));
				
				ToyInspector = Cast<AToyInspector>(CursorHit.GetActor());

				if (ToyInspector)
				{
					if (this->GetWorld()->GetFirstPlayerController()->CurrentMouseCursor.GetValue() ==  EMouseCursor::GrabHand)
					{
						FRotator CurrentRotation = ToyInspector->GetActorRotation();
						
						float MouseX;
						float MouseY;
						
						this->GetWorld()->GetFirstPlayerController()->GetInputMouseDelta(MouseX, MouseY);

						FRotator NewActorRotation(CurrentRotation.Pitch + MouseX * 10, CurrentRotation.Yaw + MouseY * 10, 0);
						
						ToyInspector->SetActorRotation(NewActorRotation);
					}
					else
					{
						ToyInspector->StopRotateToy();
					}
				}
			}
			else
			{
				//UE_LOG(LogTemp, Warning, TEXT("APCharacter: No toy :("));
			}
			if (CursorHit.GetActor()->Tags.Contains("ToSwat"))
			{
				UE_LOG(LogTemp, Warning, TEXT("APCharacter: Cursor hit on ToSwat!"));

				Monster = Cast<AMonster>(CursorHit.GetActor());

				if (Monster)
				{
					if (Monster->MonsterPositionID == 3)
					{
						UE_LOG(LogTemp, Warning, TEXT("APCharacter: Swat!!"));

						this->GetWorld()->GetFirstPlayerController()->CurrentMouseCursor = EMouseCursor::Hand;
					
						SwatCount++;
						
						if (SwatCount > 5)
						{
							Monster->bIsRetreating = true;
							Monster->MonsterRetreatTimer();

							this->GetWorld()->GetFirstPlayerController()->CurrentMouseCursor = EMouseCursor::Default;
						}
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("APCharacter: No monster to swat :("));
				}
			}
			else
			{
				//UE_LOG(LogTemp, Warning, TEXT("APCharacter: No swat :("));
			}
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("APCharacter: No cursor hit :("))
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("APCharacter: PlayerController not valid.")); 
	}
}




