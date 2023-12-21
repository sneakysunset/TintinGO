#pragma once

#include "CoreMinimal.h"
#include "Barrier.h"
#include "TileActor_Character.h"
#include "Curves/CurveFloat.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundSubmix.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"
class ATileActor_MilouSign;
class ATileActor_Cadenas;
class ATileActor_Character_Peruvien;
class ATileActor_Character_Condor;
class ATileActor_Clue;
class UCoreUI;
class UState;

DECLARE_DYNAMIC_DELEGATE(FOnClickDelegate);
DECLARE_DYNAMIC_DELEGATE(FUIMilouClick);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnBoneConsumed, int32, NewBoneNumber, FColor, DisabledColor);


USTRUCT(BlueprintType)
struct FTileArray
{
    GENERATED_BODY()

    UPROPERTY()
    TArray<class ATile*> Tiles;
};

UCLASS()
class TINTINGO_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

	AMainGameMode();
	virtual ~AMainGameMode() override;

public:	
    UFUNCTION()
    ATile* WorldCoordinatesToTilePosition(const FVector& worldCoordinates);

    UFUNCTION()
        void LateInit();

    UPROPERTY(EditAnywhere)
    UBlueprint* _tileBP;

	UPROPERTY()
	APlayerController* pc;

	UFUNCTION()
    static void ChangeTile(UBarrier* barrier, ATile* previousTile, ATile* currentTile);

    UFUNCTION()
    void MarkStepsOnGrid(ATile* CenterTile);

    UFUNCTION()
    void SetStepOnAdjacentsRecursive(ATile* tile);
    
    UFUNCTION()
    void SetStepOnAdjacentTile(ATile* tile, FVector2D direction);

    UFUNCTION()
    bool TileIsAvailable(ATile* tile, FVector2D direction);

    UFUNCTION()
    TArray<ATile*> GetPath(ATile* endTile, bool getCurrentTile);

    UFUNCTION()
    ATile* GetNextTileInPath(ATile* tile);

    UFUNCTION()
    ATile* GetEndTile() const{return _endTile;}

    UPROPERTY()
    ATile* _endTile;
    
    UPROPERTY()
    TArray<FTileArray> _gridTiles;
    
    UPROPERTY()
    TArray<ATileActor_Character_Peruvien*> _peruviens;

    UPROPERTY()
    TArray<ATileActor_Character_Condor*> _condors;

    UPROPERTY()
    TArray<ATileActor_Clue*> _clues;
    
    UPROPERTY()
    TArray<ATile*> _nests;

	UPROPERTY()
	ATileActor_Cadenas* _cadenas;

	UPROPERTY()
	ATileActor_MilouSign* _milouSign;
	
protected:
    virtual void BeginPlay() override;

    virtual void Tick(float DeltaTime) override;

public:
    UPROPERTY(EditAnywhere, Category = "Grid Generation")
    int32 _rows;
    
    UPROPERTY(EditAnywhere, Category = "Grid Generation")
    int32 _columns;

    UPROPERTY(EditAnywhere, Category = "Grid Generation")
    double _tileWidth;

	UFUNCTION()
    void LevelTransi() const;

	UFUNCTION()
	void OnWin();

	UFUNCTION()
	ATile* GetTile(int32 i, int32 j);

	UFUNCTION()
	ATile* GetTileIfAccessible(int32 i, int32 j, EAngle angle);

	UFUNCTION()
	ATile* GetForwardTile(const ATile* tile, EAngle angle);

	UFUNCTION()
	void SetTilesPeruvienColor(bool toVisible, EAngle direction, const ATile* startTile);
	void SetSubmixVolume(USoundSubmix* Submix, float VolumeLevel) const;
	void CrossfadeSubmixes(USoundSubmix* FromSubmix, USoundSubmix* ToSubmix, float Duration);

	FOnClickDelegate OnClickD;
    FUIMilouClick OnMilouBoneClick;
    FOnBoneConsumed OnBoneConsumed;

    UPROPERTY()
    UState* _currentStateType;
	
    UFUNCTION()
    void StateChange(UState* NewState);
	
    UPROPERTY(EditAnywhere, Category = "Milou Parameters")
    int32 _milouBoneThrowRange;
	
    UPROPERTY()
    int32 _milouBonesNumber;

	UPROPERTY(EditDefaultsOnly)
	bool DebugStateChange;
	
    UFUNCTION(BlueprintCallable)
    void ReceiveMilouUIClick();

	UFUNCTION(BlueprintCallable)
	void ReceiveNextLevelClick1();

	UFUNCTION(BlueprintCallable)
	void ReceiveNextLevelClick2();
	
	UFUNCTION(BlueprintCallable)
	void ReceiveNextLevelClick3();
	
    UPROPERTY(EditAnywhere)
    int32 _clueNumber;

    UPROPERTY(EditAnywhere)
    float _inTileMoveSpeed;
	
    UPROPERTY(EditAnywhere)
    float _rotateSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float _fadeOutScreenSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float _fadeInScreenSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UCurveFloat* _fadeOutCurve;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UCurveFloat* _fadeInCurve;
	
	UFUNCTION()
	void StartGameOver();

	UPROPERTY()
	FString _nextLevelName;
	
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UCoreUI> YourWidgetClass;

	UPROPERTY()
	UCoreUI* _coreUI;

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_buttonClick;

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	TArray<USoundBase*> S_MoveSoundsArray;

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_GameOver;
	
	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_TileHover;

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_TileClick;

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_pursuitMusic;

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	USoundBase* S_music;
	
	UPROPERTY(EditAnywhere, Category = "Audio")
	UAudioComponent* _musicAudioComponent;

	UPROPERTY(EditAnywhere, Category = "Audio")
	UAudioComponent* _puruitMusicAudioComponent;
	
	UFUNCTION()
	void ChangeTextValue(int32 newValue, FColor DisabledColor);

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	float _fadeTime;

	UPROPERTY()
	float _musicFadeInterpolateValue;

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	UCurveFloat* _musicFadeUpCurve;

	UPROPERTY(EditDefaultsOnly, Category = AudioFiles)
	UCurveFloat* _musicFadeDownCurve;

	UPROPERTY()
	UCurveFloat* _musicCurve;

	UPROPERTY()
	UCurveFloat* _pursuitMusicCurve;
	
	UPROPERTY()
	bool chaseMusic;

	UFUNCTION()
	void ChangeMusic();

	UFUNCTION()
	void UpdateMusic(float DeltaTime);
	
public:
	UPROPERTY()
	TArray<ATileActor_Character_Peruvien*> _pursuitPeruviens;
};
