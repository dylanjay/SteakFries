// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterSpawnManagerComponent.generated.h"

#define TPoint UE::Math::TIntPoint<int32>

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterSpawned, ABattleCharacter*, Character);

class AStageGrid;
class ABattleCharacter;


UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class STEAKFRIES_API UCharacterSpawnManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnCharacterSpawned OnCharacterSpawnedDelegate;

protected:

	AStageGrid* StageGrid = nullptr;
	
public:

	void Initialize();

	template <typename T>
	T* Spawn(
		const TSubclassOf<ABattleCharacter>& Class, 
		ETeam Team, 
		const TPoint& SpawnPoint, 
		const FRotator& Rotation = FRotator::ZeroRotator);

};
