#include "LabelSimSubsystem.h"

#include "ArtistContractSubsystem.h"
#include "Engine/GameInstance.h"

void ULabelSimSubsystem::TickDay()
{
    // 1. Apply decade modifiers (tech, marketing reach, piracy risk).
    ApplyDecadeModifiers();

    // 2. Process queued events (scandals, awards, trends).
    ProcessEvents();

    // 3. Update marketing exposures for all active releases.
    UpdateMarketingExposures();

    // 4. Calculate consumer demand (demographic × region × genre).
    CalculateDemand();

    // 5. Convert demand into sales/streams for active releases.
    ConvertDemandToSales();

    // 6. Update charts weekly.
    UpdateCharts();

    // 7. Update artist state (fame, morale, fatigue).
    UpdateArtistStates();

    // 8. Apply finance transactions (revenue, costs, royalties).
    ApplyFinanceTransactions();
}

void ULabelSimSubsystem::UpdateCharts()
{
    // TODO: Recalculate chart positions based on current sales and streams.
}

void ULabelSimSubsystem::ProcessEvents()
{
    // TODO: Resolve queued events such as scandals, awards, and trends.
}

void ULabelSimSubsystem::ApplyDecadeModifiers()
{
    // TODO: Adjust simulation parameters according to current decade.
}

void ULabelSimSubsystem::UpdateMarketingExposures()
{
    // TODO: Update marketing reach for each active release.
}

void ULabelSimSubsystem::CalculateDemand()
{
    // TODO: Calculate demand considering demographics, regions, and genres.
}

void ULabelSimSubsystem::ConvertDemandToSales()
{
    // TODO: Convert demand metrics into sales and streaming numbers.
}

void ULabelSimSubsystem::UpdateArtistStates()
{
    if (UGameInstance* GameInstance = GetGameInstance())
    {
        if (UArtistContractSubsystem* ContractSubsystem = GameInstance->GetSubsystem<UArtistContractSubsystem>())
        {
            SignedArtists.Reset();

            const TArray<FArtistContract>& Contracts = ContractSubsystem->GetContracts();
            for (const FArtistContract& Contract : Contracts)
            {
                if (!Contract.IsValid())
                {
                    continue;
                }

                if (Contract.Status == EContractStatus::Signed || Contract.Status == EContractStatus::Active)
                {
                    if (UArtistAsset* Artist = Contract.Artist.Get())
                    {
                        SignedArtists.AddUnique(Artist);
                    }
                }
            }
        }
    }

    // TODO: Update fame, morale, and fatigue for signed artists.
}

void ULabelSimSubsystem::ApplyFinanceTransactions()
{
    // TODO: Apply daily financial transactions like revenue, costs, and royalties.
}

