#include "DeskActor.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/CollisionProfile.h"
#include "InputCoreTypes.h"
#include "LabelManager/Public/LabelManagerGameInstance.h"
#include "LabelManager/Public/UI/Layout.h"

#define LOCTEXT_NAMESPACE "DeskActor"

namespace
{
    constexpr float DefaultBoxExtent = 75.0f;
}

ADeskActor::ADeskActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // 1) Create the box first and make it root
    InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
    SetRootComponent(InteractionBox);

    InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractionBox->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
    InteractionBox->SetBoxExtent(FVector(DefaultBoxExtent));
    InteractionBox->SetHiddenInGame(true);
    InteractionBox->SetGenerateOverlapEvents(false);
    InteractionBox->SetCanEverAffectNavigation(false);

    // 2) Create the mesh and attach to the box
    DeskMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DeskMesh"));
    DeskMesh->SetupAttachment(InteractionBox);

    DeskMesh->SetCollisionProfileName(UCollisionProfile::BlockAll_ProfileName);
    DeskMesh->SetGenerateOverlapEvents(false);
    // Important: make sure the mesh does NOT eat the mouse trace
    DeskMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);

    // 3) Bind click on the box
    InteractionBox->OnClicked.AddDynamic(this, &ADeskActor::HandleDeskClicked);

    TArray<UUserWidget*> FoundWidgets;
    UWidgetBlueprintLibrary::GetAllWidgetsOfClass(
        GetWorld(),
        FoundWidgets,
        ULayout::StaticClass(),
        false   // includeOnlyVisibleWidgets = false
    );

    if (FoundWidgets.Num() > 0)
    {
        Layout = Cast<ULayout>(FoundWidgets[0]);
       
    }
}

void ADeskActor::SetCompanyFunction(EDeskCompanyFunction NewFunction, FText NewCustomLabel)
{
    CompanyFunction = NewFunction;

    if (CompanyFunction == EDeskCompanyFunction::Custom)
    {
        CustomFunctionLabel = MoveTemp(NewCustomLabel);
    }
}

FText ADeskActor::GetCompanyFunctionLabel() const
{
    switch (CompanyFunction)
    {
    case EDeskCompanyFunction::Finance:
        return LOCTEXT("DeskFunctionFinance", "Finance");
    case EDeskCompanyFunction::Marketing:
        return LOCTEXT("DeskFunctionMarketing", "Marketing");
    case EDeskCompanyFunction::StudioManagement:
        return LOCTEXT("DeskFunctionStudio", "Studio Management");
    case EDeskCompanyFunction::TourPlanning:
        return LOCTEXT("DeskFunctionTour", "Tour Planning");
    case EDeskCompanyFunction::ArtistRelations:
        return LOCTEXT("DeskFunctionArtistRelations", "Artist Relations");
    case EDeskCompanyFunction::HumanResources:
        return LOCTEXT("DeskFunctionHR", "Human Resources");
    case EDeskCompanyFunction::Custom:
        return !CustomFunctionLabel.IsEmpty() ? CustomFunctionLabel : LOCTEXT("DeskFunctionCustom", "Custom");
    default:
        break;
    }

    return FText::GetEmpty();
}

void ADeskActor::HandleDeskClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
    OnDeskClicked.Broadcast(this, CompanyFunction, GetCompanyFunctionLabel());

    const auto ShowSignedArtists = [this]()
    {
        if (UWorld* World = GetWorld())
        {
            if (ULabelManagerGameInstance* GameInstance = World->GetGameInstance<ULabelManagerGameInstance>())
            {
                
                    Layout->ShowSignedArtistsWidget();
                
            }
        }
    };

    switch (CompanyFunction)
    {
    case EDeskCompanyFunction::ArtistRelations:
        ShowSignedArtists();
        break;
    case EDeskCompanyFunction::Custom:
        if (GetCompanyFunctionLabel().EqualTo(LOCTEXT("DeskFunctionArtistManagement", "Artist Mangement")))
        {
            ShowSignedArtists();
        }
        break;
    default:
        break;
    }
}

#if WITH_EDITOR
void ADeskActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    if (!PropertyChangedEvent.Property)
    {
        return;
    }

    const FName PropertyName = PropertyChangedEvent.Property->GetFName();
    if (PropertyName == GET_MEMBER_NAME_CHECKED(ADeskActor, CompanyFunction) && CompanyFunction != EDeskCompanyFunction::Custom)
    {
        CustomFunctionLabel = FText();
    }
}
#endif

#undef LOCTEXT_NAMESPACE

