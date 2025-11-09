#include "UI/WidgetLibrary.h"
#include "Blueprint/UserWidget.h"
#include "LabelManagerGameInstance.h"
#include "UI/Layout.h"
#include "Engine/World.h"

ULayout* UWidgetLibrary::CreateDashboard(UWorld* World, APlayerController* PC)
{
    if (!World)
    {
        return nullptr;
    }

    //if (ULabelManagerGameInstance* GameInstance = World->GetGameInstance<ULabelManagerGameInstance>())
    //{
    //    return GameInstance->EnsureLayoutForPlayer(PC);
    //}

    APlayerController* TargetPC = PC ? PC : World->GetFirstPlayerController();
    ULayout* Layout = nullptr;

    //if (TargetPC)
    //{
    //    Layout = CreateWidget<ULayout>(TargetPC, ULayout::StaticClass());
    //}
    //else
    //{
    //    Layout = CreateWidget<ULayout>(World, ULayout::StaticClass());
    //}

    //if (Layout)
    //{
    //    Layout->AddToViewport();
    //}

    return Layout;
}
