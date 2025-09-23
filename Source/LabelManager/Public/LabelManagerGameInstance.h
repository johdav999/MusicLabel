#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LabelManagerGameInstance.generated.h"

class ULayout;
class APlayerController;

/**
 * Game instance responsible for keeping the dashboard UI alive across level loads.
 */
UCLASS()
class LABELMANAGER_API ULabelManagerGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    ULabelManagerGameInstance();
    virtual void Init() override;

    /** Returns the dashboard layout widget if it has been created. */
    UFUNCTION(BlueprintPure, Category = "UI")
    ULayout* GetLayoutWidget() const { return LayoutGUI; }

    /** Ensures the layout widget exists, is owned by the supplied player and added to the viewport. */
    UFUNCTION(BlueprintCallable, Category = "UI")
    ULayout* EnsureLayoutForPlayer(APlayerController* OwningPlayer);

protected:
    /** Class used to instantiate the persistent dashboard layout widget. */
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<ULayout> LayoutGUIClass;

    /** Persistent layout widget instance kept alive for the lifetime of the game instance. */
    UPROPERTY()
    ULayout* LayoutGUI = nullptr;
};
