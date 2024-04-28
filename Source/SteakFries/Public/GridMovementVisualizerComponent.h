// All rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GridMovementVisualizerComponent.generated.h"

class UActionScriptGeneratorComponent;


UCLASS( Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STEAKFRIES_API UGridMovementVisualizerComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ArrowClass;

public:	

	void Initialize(UActionScriptGeneratorComponent* InActionScriptGenerator);

public:

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	void Reset();

protected:

	UFUNCTION()
	void OnScriptActionAdded(UAction* Action);

protected:

	virtual void BeginPlay() override;

protected:

	UActionScriptGeneratorComponent* ActionScriptGenerator;

	TArray<AActor*> Arrows;

};