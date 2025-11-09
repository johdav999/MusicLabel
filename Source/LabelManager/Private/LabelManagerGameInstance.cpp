#include "LabelManagerGameInstance.h"

#include "Blueprint/UserWidget.h"
#include "UI/Layout.h"
#include "GameFramework/PlayerController.h"

ULabelManagerGameInstance::ULabelManagerGameInstance()
{
    LayoutGUIClass = ULayout::StaticClass();
}

void ULabelManagerGameInstance::Init()
{
    Super::Init();

    if (!IsValid(LayoutGUI))
    {
        LayoutGUI = nullptr;
    }

    if (!LayoutGUI && LayoutGUIClass)
    {
        LayoutGUI = CreateWidget<ULayout>(this, LayoutGUIClass);
        if (LayoutGUI)
        {
            LayoutGUI->AddToViewport(0);
        }
    }
}

ULayout* ULabelManagerGameInstance::EnsureLayoutForPlayer(APlayerController* OwningPlayer)
{
    if (!IsValid(LayoutGUI))
    {
        LayoutGUI = nullptr;
    }

    if (!LayoutGUI && LayoutGUIClass)
    {
        LayoutGUI = CreateWidget<ULayout>(this, LayoutGUIClass);
    }

    if (!LayoutGUI)
    {
        return nullptr;
    }

    if (OwningPlayer && LayoutGUI->GetOwningPlayer() != OwningPlayer)
    {
        LayoutGUI->SetOwningPlayer(OwningPlayer);
    }

    if (!LayoutGUI->IsInViewport())
    {
        LayoutGUI->AddToViewport(0);
    }

    return LayoutGUI;
}
