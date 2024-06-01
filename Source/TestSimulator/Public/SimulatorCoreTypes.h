#pragma once

#include "SimulatorCoreTypes.generated.h"

#define INTERACT_TRACE_CHANNEL ECC_GameTraceChannel1
#define INTERACT_OBJECT ECC_GameTraceChannel2
#define PRINT_DEBUG_MESSAGE_ON_SCREEN(...) (GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT(__VA_ARGS__)))

DECLARE_MULTICAST_DELEGATE(FOnGameEndSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnQuestCompliteSignature, EQuestStage);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnConfirmMistakeSignature, EMistakeType);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChangeSignature, EGameState);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnShowInteractWidgetSignature, FString&);

UENUM()
enum class EQuestStage : uint8
{
    None = 0,
    CardStage,
    BrokenEngine,
    ElectricityOff,
    FixEngine,
    ElectricityOn,
    StartEngine
};

UENUM()
enum class EGameState : uint8
{
    Pause = 0,
    StartPlay,
    InProgress,
    EndPlay
};

UENUM()
enum  EMistakeType : uint8
{
    None            = 0,
    YellowLine      = 2,
    PPELost         = 4,
    StepladderLost  = 16,
    ElectricityLost = 32
};

ENUM_CLASS_FLAGS(EMistakeType)

UENUM()
enum class EObjectType : uint8
{
    None = 0,
    QuestType,
    PPE,
    PhysicsType
};

UENUM()
enum class EQuestStatus : uint8
{
    Inactive = 0,
    Active,
    Complited
};

USTRUCT()
struct FQuestData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere)
    EQuestStatus QuestStatus;

    UPROPERTY(EditAnywhere)
    EQuestStage QuestStage;
};

USTRUCT()
struct FObjectData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere)
    EObjectType ObjectType;

    UPROPERTY(EditAnywhere)
    EQuestStage ObjectStage;

    UPROPERTY(EditAnywhere)
    FString InteractText;
};
