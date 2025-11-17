#include "LabelManagerGameInstance.h"
#include "UObject/UObjectGlobals.h"   // for some helpers
#include "UObject/Package.h"
#include "UObject/Object.h"
#include "Blueprint/UserWidget.h"
#include "UI/Layout.h"
#include "GameFramework/PlayerController.h"

ULabelManagerGameInstance::ULabelManagerGameInstance()
{
    UE_LOG(LogTemp, Warning, TEXT("ULayout::NativeOnInitialized this=%p Outer=%s"), this, *GetNameSafe(GetOuter()));
}

void ULabelManagerGameInstance::Init()
{
    //UE_LOG(LogTemp, Warning, TEXT("GI::Init — LayoutGUI=%p (should be null here)"), LayoutGUI);

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

void ULabelManagerGameInstance::OnStart()
{
    if (!IsValid(LayoutGUI))
    {
        LayoutGUI = nullptr;
    }

    if (!LayoutGUI && LayoutGUIClass)
    {
        LayoutGUI = CreateWidget<ULayout>(this, LayoutGUIClass);
    }

    if (UWorld* World = GetWorld())
    {
        UE_LOG(LogTemp, Warning, TEXT("OnStart — Map is %s"),
            *World->GetMapName());
    }
}
//
//ULayout* ULabelManagerGameInstance::EnsureLayoutForPlayer(APlayerController* OwningPlayer)
//{
//    //// If an instance exists but isn't owned by a ULocalPlayer, discard it.
//
//
//
//    //if (LayoutGUI && !Cast<ULocalPlayer>(LayoutGUI->GetOuter()))
//    //{
//    //    UE_LOG(LogTemp, Warning, TEXT("LayoutGUI has wrong Outer (%s). Recreating with LocalPlayer."),
//    //        *GetNameSafe(LayoutGUI->GetOuter()));
//    //    LayoutGUI->RemoveFromParent();
//    //    LayoutGUI = nullptr;
//    //}
//
//    //// Create with LocalPlayer owner (the one thing that survives OpenLevel)
//    //if (!LayoutGUI && LayoutGUIClass && OwningPlayer)
//    //{
//    //    LayoutGUI = CreateWidget<ULayout>(OwningPlayer, LayoutGUIClass);
//    //    if (LayoutGUI)
//    //    {
//    //        LayoutGUI->AddToViewport(0);
//    //    }
//    //}
//    //else if (LayoutGUI && !LayoutGUI->IsInViewport())
//    //{
//    //   LayoutGUI->AddToViewport(0);
//    //}
//
//    //return LayoutGUI;
//}

void ULabelManagerGameInstance::HandlePreLoadMap(const FWorldContext& worldContext, const FString& MapName)
{
    UE_LOG(LogTemp, Warning, TEXT("PreLoadMap: Loading map '%s' (context world type: %d)"),
        *MapName, (int32)worldContext.WorldType);
}

void ULabelManagerGameInstance::HandlePostLoadMap(UWorld* LoadedWorld)
{
    //UE_LOG(LogTemp, Warning, TEXT("PostLoadMap: Loaded world '%s'"),
    //    LoadedWorld ? *LoadedWorld->GetMapName() : TEXT("nullptr"));

    //// If you want to immediately re-attach your persistent UI after OpenLevel:
    //if (LoadedWorld)
    //{
    //    if (APlayerController* PC = LoadedWorld->GetFirstPlayerController())
    //    {
    //        // Call your existing helper
    //   ULayout* layout=    EnsureLayoutForPlayer(PC);
	   //layout->SetVisibility(ESlateVisibility::Visible);
	   //UE_LOG(LogTemp, Warning, TEXT("Re-attached layout to PC %s"),
		  // *GetNameSafe(PC));
    //   UE_LOG(LogTemp, Warning, TEXT("Layout  path=%s inViewport=%d"),
    //       
    //       *layout->GetPathName(),
    //       layout->IsInViewport());
    //    }
    //}
}