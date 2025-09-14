#include "EventSubsystem.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/Widget_DashboardLayout.h"

void UEventSubsystem::TriggerEvent(const FGameEvent& Event)
{
    UE_LOG(LogTemp, Log, TEXT("Event Triggered: %s - %s"), *Event.Headline, *Event.Description);

    if (!Layout && GetWorld())
    {
        TArray<UUserWidget*> Widgets;
        UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), Widgets, UWidget_DashboardLayout::StaticClass(), false);
        if (Widgets.Num() > 0)
        {
            Layout = Cast<UWidget_DashboardLayout>(Widgets[0]);
        }
    }

    if (Layout)
    {
        static const FName FuncName(TEXT("AddNewsItemToTop"));
        if (UFunction* Func = Layout->FindFunction(FuncName))
        {
            struct
            {
                FGameEvent EventParam;
            } Params;
            Params.EventParam = Event;
            Layout->ProcessEvent(Func, &Params);
        }
    }
}

void UEventSubsystem::ResolveEvent()
{
    if (EventQueue.Num() > 0)
    {
        const FGameEvent Event = EventQueue[0];
        UE_LOG(LogTemp, Log, TEXT("Resolving Event: %s"), *Event.Headline);
        EventQueue.RemoveAt(0);
    }
}

void UEventSubsystem::ScheduleEvent(const FGameEvent& Event)
{
    EventQueue.Add(Event);
}

void UEventSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    Layout = nullptr;

    // Setup two sample events
    FGameEvent GenreEvent;
    GenreEvent.Headline = TEXT("New Genre Emerges");
    GenreEvent.Date = FDateTime::Now();
    GenreEvent.Description = TEXT("New genre: 50ies rock and roll has emerged.");
    GenreEvent.EventCategory = EEventCategory::NewGenreEmerged;

    FGameEvent GigEvent;
    GigEvent.Headline = TEXT("Unsigned Artist Playing Gig");
    GigEvent.Date = FDateTime::Now();
    GigEvent.Description = TEXT("An new unsigned artist will play at a local bar in Detroit.");
    GigEvent.EventCategory = EEventCategory::NewArtistGigging;

    PendingEvents.Add(GenreEvent);
    PendingEvents.Add(GigEvent);

    // Start timer to trigger events every 5 seconds
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(EventTimer, this, &UEventSubsystem::GenerateNextEvent, 5.0f, true);
    }
}

void UEventSubsystem::GenerateNextEvent()
{
    if (PendingEvents.Num() > 0)
    {
        TriggerEvent(PendingEvents[0]);
        PendingEvents.RemoveAt(0);
    }
    else if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(EventTimer);
    }
}

