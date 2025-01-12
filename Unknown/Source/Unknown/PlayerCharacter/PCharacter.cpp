#include "PCharacter.h"

#include "PController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/SpringArmComponent.h"
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

	PlayerRotation = CameraComp->GetComponentRotation();
}

void APCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APCharacter::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<AUnknownHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void APCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	APController* PlayerBaseController = CastChecked<APController>(Controller);

	check(EnhancedInputComponent && PlayerBaseController);

	EnhancedInputComponent->BindAction(PlayerBaseController->EscapeAction, ETriggerEvent::Completed, this, &APCharacter::OpenCloseWidget);
	EnhancedInputComponent->BindAction(PlayerBaseController->ShelfInventoryAction, ETriggerEvent::Completed, this, &APCharacter::OpenShelfInventory);

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

void APCharacter::RotatePlayerCameraLeft()
{
	UE_LOG(LogTemp, Warning, TEXT("APCharacter: Rotate Left!"));

	const FRotator NewActorRotation(PlayerRotation.Pitch, PlayerRotation.Yaw + 90.f, PlayerRotation.Roll);

	CameraComp->SetRelativeRotation(NewActorRotation);

	FString PrintCurrentRotaion = NewActorRotation.ToString();

	UE_LOG(LogTemp, Warning, TEXT("%s"), *PrintCurrentRotaion);
}

void APCharacter::RotatePlayerCameraRight()
{
	UE_LOG(LogTemp, Warning, TEXT("APCharacter: Rotate Right!")); 
}
