#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LabelManager/Public/UI/Layout.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "DeskActor.generated.h"

class UBoxComponent;
class UPrimitiveComponent;
class UStaticMeshComponent;
struct FKey;

/** Identifies the department or company function represented by a desk. */
UENUM(BlueprintType)
enum class EDeskCompanyFunction : uint8
{
    Finance UMETA(DisplayName = "Finance"),
    Marketing UMETA(DisplayName = "Marketing"),
    StudioManagement UMETA(DisplayName = "Studio Management"),
    TourPlanning UMETA(DisplayName = "Tour Planning"),
    ArtistRelations UMETA(DisplayName = "Artist Relations"),
    HumanResources UMETA(DisplayName = "Human Resources"),
    Custom UMETA(DisplayName = "Custom")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDeskClickedSignature, class ADeskActor*, DeskActor, EDeskCompanyFunction, FunctionType, FText, FunctionLabel);

/**
 * Actor representing a labeled office desk that players can interact with.
 */
UCLASS()
class MUSICLABEL_API ADeskActor : public AActor
{
    GENERATED_BODY()

public:
    ADeskActor();

    /** Visible mesh representing the office desk. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Desk")
    TObjectPtr<UStaticMeshComponent> DeskMesh;

    /** Invisible box used to capture click interactions. */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Desk")
    TObjectPtr<UBoxComponent> InteractionBox;

    /** Company function represented by this desk. */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Desk")
    EDeskCompanyFunction CompanyFunction = EDeskCompanyFunction::Finance;

    /**
     * Optional label override when the function is set to Custom.
     * Ignored for predefined function types.
     */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Desk", meta = (EditCondition = "CompanyFunction == EDeskCompanyFunction::Custom", MultiLine = true))
    FText CustomFunctionLabel;

    /** Broadcast whenever the desk is clicked. */
    UPROPERTY(BlueprintAssignable, Category = "Desk")
    FDeskClickedSignature OnDeskClicked;

    /** Updates the desk's company function and optional custom label. */
    UFUNCTION(BlueprintCallable, Category = "Desk")
    void SetCompanyFunction(EDeskCompanyFunction NewFunction, FText NewCustomLabel);

    /** Returns the localized label for the current company function. */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Desk")
    FText GetCompanyFunctionLabel() const;

    ULayout* Layout = nullptr;

protected:
    UFUNCTION()
    void HandleDeskClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};

