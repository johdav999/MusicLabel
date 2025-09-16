#pragma once

#include "CoreMinimal.h"

#include "CoreMinimal.h"

// Some engine versions keep UPrimaryDataAsset in this header; older keep it in DataAsset.h.
// This conditional include keeps you safe across UE versions.
#if __has_include("Engine/PrimaryDataAsset.h")
#include "Engine/PrimaryDataAsset.h"
#else
#include "Engine/DataAsset.h"
//using UPrimaryDataAsset = UDataAsset; // fallback to compile; adjust if needed
#endif

#include "LabelDataAssets.generated.h"

class UCurveFloat;
class USoundWave;
class UGenreAsset;
class UObject;



/** Represents a financial transaction in the game's economy. */
USTRUCT(BlueprintType)
struct FTransaction
{
    GENERATED_BODY()

    /** Description of the transaction. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transaction")
    FString Description;

    /** Monetary value of the transaction. Positive for revenue, negative for expense. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transaction")
    float Amount = 0.0f;
};

/** Data describing an artist tour. */
USTRUCT(BlueprintType)
struct FTour
{
    GENERATED_BODY()

    /** Name of the tour. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tour")
    FString Name;

    /** Cities or venues to visit during the tour. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tour")
    TArray<FString> Stops;
};

UENUM(BlueprintType)
enum class EEventCategory : uint8
{
    NewArtistGigging      UMETA(DisplayName = "New Artist Gigging (to scout)"),
    ArtistSignedRecordDeal UMETA(DisplayName = "Artist Signed a record Deal"),
    ArtistBookedForTour   UMETA(DisplayName = "Artist Booked for a tour"),
    NewGenreEmerged       UMETA(DisplayName = "New Genre has emerged")
};

/** Definition of an event entry for data tables. */
USTRUCT(BlueprintType)
struct FGameEvent : public FTableRowBase
{
    GENERATED_BODY()

    /** Short headline for the event. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
    FString Headline;

    /** When the event occurred. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
    FDateTime Date;

    /** Detailed description of the event. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
    FString Description;

    /** Category of the event. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event")
    EEventCategory EventCategory = EEventCategory::NewArtistGigging;
};

/** Represents a single piece of music. */
USTRUCT(BlueprintType)
struct FSong
{
    GENERATED_BODY()

    /** Title of the song. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Song")
    FString Title;

    /** Length of the song in seconds. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Song")
    int32 LengthSec = 0;

    /** Tempo of the song in beats per minute. */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Song")
    int32 TempoBPM = 0;
};


/** Rights type for song licensing */
UENUM(BlueprintType)
enum class ERightsType : uint8
{
    Owned UMETA(DisplayName="Owned"),
    Licensed UMETA(DisplayName="Licensed")
};

/** Artist entity type */
UENUM(BlueprintType)
enum class EArtistType : uint8
{
    Solo UMETA(DisplayName="Solo"),
    Band UMETA(DisplayName="Band")
};

/** Personality flag markers */
UENUM(BlueprintType)
enum class EPersonalityFlag : uint8
{
    Ego UMETA(DisplayName="Ego"),
    Activism UMETA(DisplayName="Activism"),
    RiskTaker UMETA(DisplayName="RiskTaker")
};

/** Trait values for an artist */
USTRUCT(BlueprintType)
struct FArtistAttributes
{
    GENERATED_BODY()
private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes", meta=(AllowPrivateAccess="true"))
    FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes", meta=(AllowPrivateAccess="true"))
    TArray<USongAsset*> Songs;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes", meta=(AllowPrivateAccess="true"))
    float Talent = 0.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes", meta=(AllowPrivateAccess="true"))
    float Charisma = 0.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes", meta=(AllowPrivateAccess="true"))
    float Reliability = 0.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes", meta=(AllowPrivateAccess="true"))
    float MarketAppeal = 0.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes", meta=(AllowPrivateAccess="true"))
    float Stamina = 0.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes", meta=(AllowPrivateAccess="true"))
    float Musicality = 0.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes", meta=(AllowPrivateAccess="true"))
    float Creativity = 0.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes", meta=(AllowPrivateAccess="true"))
    TArray<TSoftObjectPtr<UGenreAsset>> Genres;
public:
    const FString& GetName() const { return Name; }
    const TArray<USongAsset*>& GetSongs() const { return Songs; }
    float GetTalent() const { return Talent; }
    float GetCharisma() const { return Charisma; }
    float GetReliability() const { return Reliability; }
    float GetMarketAppeal() const { return MarketAppeal; }
    float GetStamina() const { return Stamina; }
    float GetMusicality() const { return Musicality; }
    float GetCreativity() const { return Creativity; }
    const TArray<TSoftObjectPtr<UGenreAsset>>& GetGenres() const { return Genres; }

    void SetName(const FString& InName) { Name = InName; }
    void SetSongs(const TArray<USongAsset*>& InSongs) { Songs = InSongs; }
    void SetTalent(float InTalent) { Talent = InTalent; }
    void SetCharisma(float InCharisma) { Charisma = InCharisma; }
    void SetReliability(float InReliability) { Reliability = InReliability; }
    void SetMarketAppeal(float InMarketAppeal) { MarketAppeal = InMarketAppeal; }
    void SetStamina(float InStamina) { Stamina = InStamina; }
    void SetMusicality(float InMusicality) { Musicality = InMusicality; }
    void SetCreativity(float InCreativity) { Creativity = InCreativity; }
    void SetGenres(const TArray<TSoftObjectPtr<UGenreAsset>>& InGenres) { Genres = InGenres; }
};

/** Contractual terms with an artist */
USTRUCT(BlueprintType)
struct FContractTerms
{
    GENERATED_BODY()
private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Contract", meta=(AllowPrivateAccess="true"))
    int32 Advance = 0;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Contract", meta=(AllowPrivateAccess="true"))
    float RoyaltySplit = 0.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Contract", meta = (AllowPrivateAccess = "true"))
	int32 RecordsNumber = 1; // Number of records in the contract
public:
    int32 GetAdvance() const { return Advance; }
    float GetRoyaltySplit() const { return RoyaltySplit; }
    int32 GetRecordsNumber() const { return RecordsNumber; }
};

/** Song data asset */
UCLASS(BlueprintType)
class LABELMANAGER_API USongAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category="Song") const FString& GetSongId() const { return SongId; }
    UFUNCTION(BlueprintPure, Category="Song") const FString& GetTitle() const { return Title; }
    UFUNCTION(BlueprintPure, Category="Song") const TSoftObjectPtr<UGenreAsset>& GetGenre() const { return Genre; }
    UFUNCTION(BlueprintPure, Category="Song") const TSoftObjectPtr<UGenreAsset>& GetSubgenre() const { return Subgenre; }
    UFUNCTION(BlueprintPure, Category="Song") const TArray<FString>& GetTags() const { return Tags; }
    UFUNCTION(BlueprintPure, Category="Song") float GetQualityBase() const { return QualityBase; }
    UFUNCTION(BlueprintPure, Category="Song") int32 GetLengthSec() const { return LengthSec; }
    UFUNCTION(BlueprintPure, Category="Song") int32 GetTempoBPM() const { return TempoBPM; }
    UFUNCTION(BlueprintPure, Category="Song") UCurveFloat* GetEnergyCurve() const { return EnergyCurve; }
    UFUNCTION(BlueprintPure, Category="Song") USoundWave* GetAudioRef() const { return AudioRef; }
    UFUNCTION(BlueprintPure, Category="Song") float GetPreviewStartSec() const { return PreviewStartSec; }
    UFUNCTION(BlueprintPure, Category="Song") ERightsType GetRights() const { return Rights; }
    UFUNCTION(BlueprintPure, Category="Song") int32 GetCostToUse() const { return CostToUse; }
    UFUNCTION(BlueprintPure, Category="Song") float GetRoyaltyRate() const { return RoyaltyRate; }

    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Song", meta=(AllowPrivateAccess="true"))
    FString SongId;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Song", meta=(AllowPrivateAccess="true"))
    FString Title;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Song", meta=(AllowPrivateAccess="true"))
    TSoftObjectPtr<UGenreAsset> Genre;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Song", meta=(AllowPrivateAccess="true"))
    TSoftObjectPtr<UGenreAsset> Subgenre;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Song", meta=(AllowPrivateAccess="true"))
    TArray<FString> Tags;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Song", meta=(AllowPrivateAccess="true"))
    float QualityBase = 0.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Song", meta=(AllowPrivateAccess="true"))
    int32 LengthSec = 0;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Song", meta=(AllowPrivateAccess="true"))
    int32 TempoBPM = 0;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Song", meta=(AllowPrivateAccess="true"))
    UCurveFloat* EnergyCurve = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Song", meta=(AllowPrivateAccess="true"))
    USoundWave* AudioRef = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Song", meta=(AllowPrivateAccess="true"))
    float PreviewStartSec = 0.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Song", meta=(AllowPrivateAccess="true"))
    ERightsType Rights = ERightsType::Owned;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Song", meta=(AllowPrivateAccess="true"))
    int32 CostToUse = 0;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Song", meta=(AllowPrivateAccess="true"))
    float RoyaltyRate = 0.f;
};

/** Artist data asset */
UCLASS(BlueprintType)
class LABELMANAGER_API UArtistAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category="Artist") const FString& GetName() const { return Name; }
    UFUNCTION(BlueprintPure, Category="Artist") EArtistType GetType() const { return Type; }
    UFUNCTION(BlueprintPure, Category="Artist") const FArtistAttributes& GetAttributes() const { return Attributes; }
    UFUNCTION(BlueprintPure, Category="Artist") const TArray<TSoftObjectPtr<UGenreAsset>>& GetGenreAffinity() const { return GenreAffinity; }
    UFUNCTION(BlueprintPure, Category="Artist") const TArray<EPersonalityFlag>& GetPersonalityFlags() const { return PersonalityFlags; }
    UFUNCTION(BlueprintPure, Category="Artist") const TSoftObjectPtr<UObject>& GetMetaHumanProfileRef() const { return MetaHumanProfileRef; }
    UFUNCTION(BlueprintPure, Category="Artist") const FContractTerms& GetContractTerms() const { return ContractTerms; }

    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Artist", meta=(AllowPrivateAccess="true"))
    FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Artist", meta=(AllowPrivateAccess="true"))
    EArtistType Type = EArtistType::Solo;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Artist", meta=(AllowPrivateAccess="true"))
    FArtistAttributes Attributes;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Artist", meta=(AllowPrivateAccess="true"))
    TArray<TSoftObjectPtr<UGenreAsset>> GenreAffinity;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Artist", meta=(AllowPrivateAccess="true"))
    TArray<EPersonalityFlag> PersonalityFlags;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Artist", meta=(AllowPrivateAccess="true"))
    TSoftObjectPtr<UObject> MetaHumanProfileRef;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Artist", meta=(AllowPrivateAccess="true"))
    FContractTerms ContractTerms;
};

/** Decade data asset */
UCLASS(BlueprintType)
class LABELMANAGER_API UDecadeAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category="Decade") int32 GetStartYear() const { return StartYear; }
    UFUNCTION(BlueprintPure, Category="Decade") int32 GetEndYear() const { return EndYear; }
    UFUNCTION(BlueprintPure, Category="Decade") const TArray<FString>& GetTechUnlocks() const { return TechUnlocks; }
    UFUNCTION(BlueprintPure, Category="Decade") const TArray<FString>& GetMarketingChannels() const { return MarketingChannels; }
    UFUNCTION(BlueprintPure, Category="Decade") const TMap<FString,float>& GetEventWeights() const { return EventWeights; }

    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Decade", meta=(AllowPrivateAccess="true"))
    int32 StartYear = 0;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Decade", meta=(AllowPrivateAccess="true"))
    int32 EndYear = 0;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Decade", meta=(AllowPrivateAccess="true"))
    TArray<FString> TechUnlocks;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Decade", meta=(AllowPrivateAccess="true"))
    TArray<FString> MarketingChannels;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Decade", meta=(AllowPrivateAccess="true"))
    TMap<FString, float> EventWeights;
};

/** Genre data asset */
UCLASS(BlueprintType)
class LABELMANAGER_API UGenreAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category="Genre") const FString& GetName() const { return Name; }
    UFUNCTION(BlueprintPure, Category="Genre") UCurveFloat* GetPopularityCurveByDecade() const { return PopularityCurveByDecade; }
    UFUNCTION(BlueprintPure, Category="Genre") const TArray<FString>& GetDemographicAffinity() const { return DemographicAffinity; }
    UFUNCTION(BlueprintPure, Category="Genre") const TArray<FString>& GetTechFit() const { return TechFit; }
    UFUNCTION(BlueprintPure, Category="Genre") float GetCrossOverPotential() const { return CrossOverPotential; }

    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Genre", meta=(AllowPrivateAccess="true"))
    FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Genre", meta=(AllowPrivateAccess="true"))
    UCurveFloat* PopularityCurveByDecade = nullptr;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Genre", meta=(AllowPrivateAccess="true"))
    TArray<FString> DemographicAffinity;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Genre", meta=(AllowPrivateAccess="true"))
    TArray<FString> TechFit;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Genre", meta=(AllowPrivateAccess="true"))
    float CrossOverPotential = 0.f;
};

/** Region market data asset */
UCLASS(BlueprintType)
class LABELMANAGER_API URegionMarketAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category="Region") const FString& GetName() const { return Name; }
    UFUNCTION(BlueprintPure, Category="Region") int32 GetPopulation() const { return Population; }
    UFUNCTION(BlueprintPure, Category="Region") float GetIncomeIndex() const { return IncomeIndex; }
    UFUNCTION(BlueprintPure, Category="Region") const TMap<FString,float>& GetTasteWeightsPerGenre() const { return TasteWeightsPerGenre; }
    UFUNCTION(BlueprintPure, Category="Region") const TMap<FString,float>& GetChannelReachMultipliers() const { return ChannelReachMultipliers; }

    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Region", meta=(AllowPrivateAccess="true"))
    FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Region", meta=(AllowPrivateAccess="true"))
    int32 Population = 0;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Region", meta=(AllowPrivateAccess="true"))
    float IncomeIndex = 0.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Region", meta=(AllowPrivateAccess="true"))
    TMap<FString, float> TasteWeightsPerGenre;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Region", meta=(AllowPrivateAccess="true"))
    TMap<FString, float> ChannelReachMultipliers;
};

/** Venue data asset */
UCLASS(BlueprintType)
class LABELMANAGER_API UVenueAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category="Venue") const FString& GetName() const { return Name; }
    UFUNCTION(BlueprintPure, Category="Venue") int32 GetCapacity() const { return Capacity; }
    UFUNCTION(BlueprintPure, Category="Venue") float GetCostProfile() const { return CostProfile; }
    UFUNCTION(BlueprintPure, Category="Venue") float GetAcoustics() const { return Acoustics; }
    UFUNCTION(BlueprintPure, Category="Venue") const FString& GetCity() const { return City; }
    UFUNCTION(BlueprintPure, Category="Venue") float GetPrestige() const { return Prestige; }

    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Venue", meta=(AllowPrivateAccess="true"))
    FString Name;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Venue", meta=(AllowPrivateAccess="true"))
    int32 Capacity = 0;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Venue", meta=(AllowPrivateAccess="true"))
    float CostProfile = 0.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Venue", meta=(AllowPrivateAccess="true"))
    float Acoustics = 0.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Venue", meta=(AllowPrivateAccess="true"))
    FString City;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Venue", meta=(AllowPrivateAccess="true"))
    float Prestige = 0.f;
};

/** Economy configuration data */
UCLASS(BlueprintType)
class LABELMANAGER_API UEconomyConfigAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category="Economy") float GetStudioHourlyRate() const { return StudioHourlyRate; }
    UFUNCTION(BlueprintPure, Category="Economy") const TMap<FString,float>& GetDistributionFees() const { return DistributionFees; }
    UFUNCTION(BlueprintPure, Category="Economy") float GetMarketingCPM() const { return MarketingCPM; }
    UFUNCTION(BlueprintPure, Category="Economy") UCurveFloat* GetSeasonalEffects() const { return SeasonalEffects; }

    virtual FPrimaryAssetId GetPrimaryAssetId() const override;

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Economy", meta=(AllowPrivateAccess="true"))
    float StudioHourlyRate = 0.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Economy", meta=(AllowPrivateAccess="true"))
    TMap<FString, float> DistributionFees;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Economy", meta=(AllowPrivateAccess="true"))
    float MarketingCPM = 0.f;
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Economy", meta=(AllowPrivateAccess="true"))
    UCurveFloat* SeasonalEffects = nullptr;
};

