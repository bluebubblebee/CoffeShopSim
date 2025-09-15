// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ActorPoolingSubsystem.generated.h"

USTRUCT()
struct FActorPool
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TObjectPtr<AActor>> FreeActors;
};

UCLASS()
class COFFEESHOPSIM_API UActorPoolingSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:

	UFUNCTION(BlueprintCallable, Category= "Actor Pooling", meta = (WorldContext="WorldContextObject"))
	static AActor* SpawnActorPooled(const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform, ESpawnActorCollisionHandlingMethod SpawnHandling);

	static bool ReleaseToPool(AActor* Actor);
	
	static AActor* AcquireFromPool(const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform, FActorSpawnParameters SpawnParams);

	static bool IsPoolingEnabled(const UObject* WorldContextObject);

	void PrimeActorPool(TSubclassOf<AActor> ActorClass, int32 Amount);

protected:
	
	AActor* AcquireFromPool_Internal(TSubclassOf<AActor> ActorClass, const FTransform& SpawnTransform, FActorSpawnParameters SpawnParams);

	bool ReleaseToPool_Internal(AActor* Actor);

protected:

	/* Holds collection of available Actors, stored per class */
	// This marks the AvailableActorPool map as transient, meaning that the contents of this map are temporary and should not be saved or loaded from disk.
	// This is useful when the map is used to store runtime data (like pools of actors) that doesn’t need to be preserved across game sessions (i.e., when you quit and restart the game).
	// For example, actor pools may need to be reset or recreated every time the game session starts, so there is no need to save the data to disk.
	UPROPERTY(Transient)
	TMap<TSubclassOf<AActor>, FActorPool> AvailableActorPool;
	
};
