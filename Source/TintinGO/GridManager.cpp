#include "GridManager.h"

#include "MainGameMode.h"
#include "Tile.h"
#include "TileActor.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


AGridManager::AGridManager()
{
	PrimaryActorTick.bCanEverTick = true;
	_rows = 10;
	_columns = 10;
	_tileWidth = 1;
	_useEditorTick = true;
}

void AGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
#if WITH_EDITOR
	//UE_LOG(LogTemp, Warning, TEXT("Test"));
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor)
	{
		BlueprintEditorTick(DeltaTime);
	}

#endif

}

void AGridManager::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::SpawnSoundAtLocation(this, music, GetActorLocation());
	_gameManager = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	_gameManager->_tileWidth = _tileWidth;
}

bool AGridManager::ShouldTickIfViewportsOnly() const
{
	if (GetWorld() != nullptr && GetWorld()->WorldType == EWorldType::Editor && _useEditorTick)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AGridManager::BlueprintEditorTick(float DeltaTime)
{
}

void AGridManager::InitializeGrid()	
{
	TArray<AActor*> tiles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATile::StaticClass(), tiles);
	for (const auto& tile : tiles)
	{
		tile->Destroy();
	}

	// Clear the grid array
	tiles.Empty();

	UE_LOG(LogTemp, Warning, TEXT("Initialization"));
	for (size_t i = 0; i < _rows; i++)
	{
		for (size_t j = 0; j < _columns; j++)
		{
			FActorSpawnParameters SpawnParams;
			FVector SpawnLocation = FVector(i * 100 * _tileWidth, j * 100 * _tileWidth , 0);
			FRotator SpawnRotation = FRotator(0, 0, 0);
			ATile* SpawnedTile = GetWorld()->SpawnActor<ATile>(_tileBP->GeneratedClass, SpawnLocation, SpawnRotation, SpawnParams);
#if WITH_EDITOR
			SpawnedTile->SetActorLabel(FString::Printf(TEXT("Tile_%d_%d"), static_cast<int>(i), static_cast<int>(j)));
#endif
			SpawnedTile->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
			SpawnedTile->SetActorLocation(SpawnLocation);
			SpawnedTile->_row = i;
			SpawnedTile->_column = j;
			SpawnedTile->SetActorScale3D(FVector(_tileWidth, _tileWidth, 1));
			//SpawnedTile->SetHighlighted(false);
		}
	}
}

void AGridManager::UpdateLinks()
{
	//UE_LOG(LogTemp, Warning, TEXT("grid tiles size %d"), tile.Tiles.Num());
	TArray<AActor*> tiles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATile::StaticClass(), tiles);
	for(const auto tile : tiles)
	{
		Cast<ATile>(tile)->RefreshLinks();
	}
}