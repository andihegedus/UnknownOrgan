#include "PCharacter.h"

#include "PController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InterchangeTranslatorBase.h"
#include "Camera/CameraComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Unknown/ActivityStations/RinseStation/OrganRinse.h"
#include "Unknown/System/UnknownHUD.h"

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

void APCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
}

void APCharacter::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<AUnknownHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());

	CheckForInteractable();
}

void APCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	APController* PlayerBaseController = CastChecked<APController>(Controller);

	check(EnhancedInputComponent && PlayerBaseController);

	EnhancedInputComponent->BindAction(PlayerBaseController->EscapeAction, ETriggerEvent::Completed, this, &APCharacter::OpenCloseWidget);
	EnhancedInputComponent->BindAction(PlayerBaseController->ShelfInventoryAction, ETriggerEvent::Completed, this, &APCharacter::OpenShelfInventory);
	EnhancedInputComponent->BindAction(PlayerBaseController->RinseAction, ETriggerEvent::Triggered, this, &APCharacter::RinseOrgan);
	EnhancedInputComponent->BindAction(PlayerBaseController->RinseAction, ETriggerEvent::Completed, this, &APCharacter::StopRinseOrgan);


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

void APCharacter::RinseOrgan()
{
	if (TagInFocus.Contains("ToRinse"))
	{
		if (this->GetWorld()->GetFirstPlayerController())
		{
			this->GetWorld()->GetFirstPlayerController()->CurrentMouseCursor = EMouseCursor::GrabHandClosed;

			CheckForOrgan();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("APCharacter: PlayerController not valid.")); 
		}
	}
}

void APCharacter::StopRinseOrgan()
{
	if (this->GetWorld()->GetFirstPlayerController())
	{
		this->GetWorld()->GetFirstPlayerController()->CurrentMouseCursor = EMouseCursor::Default;

		CheckForOrgan();
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
	LineTraceStart = GetPawnViewLocation();
	
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
		
				FoundInteractable();

				return;
			}
			if (TraceHit.GetActor()->Tags.Contains("Rinse"))
			{
				UE_LOG(LogTemp, Warning, TEXT("APCharacter: Rinse!"));
				
				CurrentTag = "Rinse";
				TagInFocus.Add(CurrentTag);
		
				FoundInteractable();

				return;
			}
			if (TraceHit.GetActor()->Tags.Contains("Test"))
			{
				UE_LOG(LogTemp, Warning, TEXT("APCharacter: Test!"));
				
				CurrentTag = "Test";
				TagInFocus.Add(CurrentTag);
		
				FoundInteractable();

				return;
			}
			if (TraceHit.GetActor()->Tags.Contains("Door"))
			{
				UE_LOG(LogTemp, Warning, TEXT("APCharacter: Door!"));
				
				CurrentTag = "Door";
				TagInFocus.Add(CurrentTag);
		
				FoundInteractable();

				return;
			}
			if (TraceHit.GetActor()->Tags.Contains("ToRinse"))
			{
				//UE_LOG(LogTemp, Warning, TEXT("APCharacter: Organ to rinse!"));
				
				CurrentTag = "ToRinse";
				TagInFocus.Add(CurrentTag);
		
				FoundInteractable();

				return;
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("APCharacter: No interactables found."));
	TagInFocus.Empty();
}

void APCharacter::CheckForOrgan()
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
				UE_LOG(LogTemp, Warning, TEXT("APCharacter: No rinse :("));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("APCharacter: No cursor hit :("))
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("APCharacter: PlayerController not valid.")); 
	}
}

void APCharacter::FoundInteractable()
{
}
