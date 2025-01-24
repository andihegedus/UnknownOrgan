#include "PController.h"
#include "PCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Unknown/Data/SaveData.h"

void APController::SetupKeyMap(UInputMappingContext* InputMappingContext, UInputAction* InputAction, FKey Key,
                               bool bNegate, bool bSwizzle, EInputAxisSwizzle SwizzleOrder)
{
	FEnhancedActionKeyMapping& KeyMapping = InputMappingContext->MapKey(InputAction, Key);
	UObject* MapObject = InputMappingContext->GetOuter();

	if (bNegate)
	{
		UInputModifierNegate* Negate = NewObject<UInputModifierNegate>(MapObject);
		KeyMapping.Modifiers.Add(Negate);
	}

	if (bSwizzle)
	{
		UInputModifierSwizzleAxis* Swizzle = NewObject<UInputModifierSwizzleAxis>(MapObject);
		Swizzle->Order = SwizzleOrder;
		KeyMapping.Modifiers.Add(Swizzle);
	}
}

void APController::SetupInputComponent()
{
	Super::SetupInputComponent();

	PCMappingContext = NewObject<UInputMappingContext>(this);

	// To open and close certain widgets
	EscapeAction = NewObject<UInputAction>(this);
	EscapeAction->ValueType = EInputActionValueType::Boolean;
	SetupKeyMap(PCMappingContext, EscapeAction, EKeys::Escape, false, false, EInputAxisSwizzle::YXZ);

	// To open the shelf inventory widget
	ShelfInventoryAction = NewObject<UInputAction>(this);
	ShelfInventoryAction->ValueType = EInputActionValueType::Boolean;
	SetupKeyMap(PCMappingContext, ShelfInventoryAction, EKeys::I, false, false, EInputAxisSwizzle::YXZ);

	// To rinse out the organ
	RinseAction = NewObject<UInputAction>(this);
	RinseAction->ValueType = EInputActionValueType::Boolean;
	SetupKeyMap(PCMappingContext, RinseAction, EKeys::LeftMouseButton, false, false, EInputAxisSwizzle::YXZ);
}

