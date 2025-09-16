#include "ArtistContractSubsystem.h"

#include "Engine/GameInstance.h"
#include "LabelManager/Public/LabelDataAssets.h"

FArtistContract::FArtistContract()
    : Status(EContractStatus::Negotiating)
    , SignedDate(FDateTime::MinValue())
    , RecordsDelivered(0)
{
}

bool UArtistContractSubsystem::SignContract(UArtistAsset* Artist)
{
    if (!Artist)
    {
        UE_LOG(LogTemp, Warning, TEXT("SignContract called with invalid artist."));
        return false;
    }

    return SignContractWithTerms(Artist, Artist->GetContractTerms());
}

bool UArtistContractSubsystem::SignContractWithTerms(UArtistAsset* Artist, const FContractTerms& Terms)
{
    if (!Artist)
    {
        UE_LOG(LogTemp, Warning, TEXT("SignContractWithTerms called with invalid artist."));
        return false;
    }

    if (FArtistContract* ExistingContract = FindContract(Artist))
    {
        // Only allow re-signing once a previous contract has concluded.
        if (ExistingContract->Status == EContractStatus::Completed || ExistingContract->Status == EContractStatus::Terminated)
        {
            ExistingContract->Terms = Terms;
            ExistingContract->Status = EContractStatus::Signed;
            ExistingContract->SignedDate = FDateTime::UtcNow();
            ExistingContract->RecordsDelivered = 0;
            ExistingContract->Artist = Artist;
            return true;
        }

        UE_LOG(LogTemp, Warning, TEXT("Artist %s already has an active contract."), *Artist->GetName());
        return false;
    }

    FArtistContract NewContract;
    NewContract.Artist = Artist;
    NewContract.Terms = Terms;
    NewContract.Status = EContractStatus::Signed;
    NewContract.SignedDate = FDateTime::UtcNow();
    NewContract.RecordsDelivered = 0;

    ArtistContracts.Add(NewContract);
    return true;
}

bool UArtistContractSubsystem::UpdateContractStatus(UArtistAsset* Artist, EContractStatus NewStatus)
{
    if (FArtistContract* Contract = FindContract(Artist))
    {
        Contract->Status = NewStatus;

        if (NewStatus == EContractStatus::Signed && Contract->SignedDate == FDateTime::MinValue())
        {
            Contract->SignedDate = FDateTime::UtcNow();
        }
        return true;
    }

    UE_LOG(LogTemp, Warning, TEXT("UpdateContractStatus failed. No contract found for artist."));
    return false;
}

bool UArtistContractSubsystem::MarkRecordDelivered(UArtistAsset* Artist)
{
    if (FArtistContract* Contract = FindContract(Artist))
    {
        Contract->RecordsDelivered = FMath::Max(Contract->RecordsDelivered + 1, 0);

        const int32 RequiredRecords = Contract->Terms.GetRecordsNumber();
        if (RequiredRecords > 0 && Contract->RecordsDelivered >= RequiredRecords)
        {
            Contract->Status = EContractStatus::Completed;
        }
        else if (Contract->Status == EContractStatus::Signed)
        {
            Contract->Status = EContractStatus::Active;
        }

        return true;
    }

    UE_LOG(LogTemp, Warning, TEXT("MarkRecordDelivered failed. No contract found for artist."));
    return false;
}

bool UArtistContractSubsystem::IsArtistSigned(UArtistAsset* Artist) const
{
    if (const FArtistContract* Contract = FindContract(Artist))
    {
        return Contract->Status == EContractStatus::Signed || Contract->Status == EContractStatus::Active;
    }

    return false;
}

FArtistContract UArtistContractSubsystem::GetContract(UArtistAsset* Artist, bool& bFound) const
{
    if (const FArtistContract* Contract = FindContract(Artist))
    {
        bFound = true;
        return *Contract;
    }

    bFound = false;
    return FArtistContract();
}

FArtistContract* UArtistContractSubsystem::FindContract(UArtistAsset* Artist)
{
    if (!Artist)
    {
        return nullptr;
    }

    for (FArtistContract& Contract : ArtistContracts)
    {
        if (Contract.Artist.Get() == Artist)
        {
            return &Contract;
        }
    }

    return nullptr;
}

const FArtistContract* UArtistContractSubsystem::FindContract(UArtistAsset* Artist) const
{
    if (!Artist)
    {
        return nullptr;
    }

    for (const FArtistContract& Contract : ArtistContracts)
    {
        if (Contract.Artist.Get() == Artist)
        {
            return &Contract;
        }
    }

    return nullptr;
}

