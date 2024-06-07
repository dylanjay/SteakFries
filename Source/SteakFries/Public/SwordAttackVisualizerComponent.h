// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SwordAttackVisualizerComponent.generated.h"

class UActionScriptGeneratorComponent;
class AStageGrid;


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class STEAKFRIES_API USwordAttackVisualizerComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> VisualizerClass;

public:

	void Initialize(AStageGrid* InStageGrid, UActionScriptGeneratorComponent* InActionScriptGenerator);

public:

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	void Reset();

protected:

	UFUNCTION()
	void OnScriptActionAdded(AAction* Action);

protected:

	virtual void BeginPlay() override;

protected:

	AStageGrid* StageGrid = nullptr;

	UActionScriptGeneratorComponent* ActionScriptGenerator = nullptr;

	AActor* Visualizer = nullptr;

};