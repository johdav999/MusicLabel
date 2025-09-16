#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LabelManager/Public/LabelDataAssets.h"
#include "ArtistContractSubsystem.generated.h"

class UArtistAsset;

/** Current lifecycle state of an artist contract. */
UENUM(BlueprintType)
enum class EContractStatus : uint8
{
    Negotiating UMETA(DisplayName = "Negotiating"),
    Signed UMETA(DisplayName = "Signed"),
    Active UMETA(DisplayName = "Active"),
    Completed UMETA(DisplayName = "Completed"),
    Terminated UMETA(DisplayName = "Terminated")
};

/** Runtime information for a label contract with an artist. */
USTRUCT(BlueprintType)
struct MUSICLABEL_API FArtistContract
{
    GENERATED_BODY()

    FArtistContract();

    /** Artist associated with this contract. */
    UPROPERTY(BlueprintReadOnly, Category = "Contract")
    TWeakObjectPtr<UArtistAsset> Artist;

    /** Negotiated contract terms. */
    UPROPERTY(BlueprintReadOnly, Category = "Contract")
    FContractTerms Terms;

    /** Current status of the contract. */
    UPROPERTY(BlueprintReadOnly, Category = "Contract")
    EContractStatus Status;

    /** Timestamp when the contract was signed. */
    UPROPERTY(BlueprintReadOnly, Category = "Contract")
    FDateTime SignedDate;

    /** Number of records delivered under this contract. */
    UPROPERTY(BlueprintReadOnly, Category = "Contract")
    int32 RecordsDelivered;

    /** Helper to check whether the artist pointer is still valid. */
    bool IsValid() const { return Artist.IsValid(); }
};

/**
 * Handles negotiation, signing and lifecycle of artist contracts for the label.
 */
UCLASS()
class MUSICLABEL_API UArtistContractSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    /** Sign an artist using the contract terms defined on their data asset. */
    UFUNCTION(BlueprintCallable, Category = "Contracts")
    bool SignContract(UArtistAsset* Artist);

    /** Sign an artist using explicit contract terms. */
    UFUNCTION(BlueprintCallable, Category = "Contracts")
    bool SignContractWithTerms(UArtistAsset* Artist, const FContractTerms& Terms);

    /** Update the lifecycle status of an existing contract. */
    UFUNCTION(BlueprintCallable, Category = "Contracts")
    bool UpdateContractStatus(UArtistAsset* Artist, EContractStatus NewStatus);

    /** Mark one record as delivered for the supplied artist contract. */
    UFUNCTION(BlueprintCallable, Category = "Contracts")
    bool MarkRecordDelivered(UArtistAsset* Artist);

    /** Returns whether the artist currently has a signed or active contract. */
    UFUNCTION(BlueprintPure, Category = "Contracts")
    bool IsArtistSigned(UArtistAsset* Artist) const;

    /** Retrieve the stored contract for the supplied artist. */
    UFUNCTION(BlueprintPure, Category = "Contracts")
    FArtistContract GetContract(UArtistAsset* Artist, bool& bFound) const;

    /** Blueprint friendly accessor that returns a copy of all tracked contracts. */
    UFUNCTION(BlueprintPure, Category = "Contracts")
    TArray<FArtistContract> GetContractsCopy() const { return ArtistContracts; }

    /** Native accessor returning the internal array by const reference. */
    const TArray<FArtistContract>& GetContracts() const { return ArtistContracts; }

private:
    FArtistContract* FindContract(UArtistAsset* Artist);
    const FArtistContract* FindContract(UArtistAsset* Artist) const;

    /** Contracts tracked by this subsystem. */
    UPROPERTY()
    TArray<FArtistContract> ArtistContracts;
};

