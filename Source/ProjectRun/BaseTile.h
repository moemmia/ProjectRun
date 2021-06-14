// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Engine/EngineTypes.h"
#include "BaseTile.generated.h"

UCLASS()
class PROJECTRUN_API ABaseTile : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* Base;

	UPROPERTY(EditDefaultsOnly)
		TArray<FTransform> SpawnPoints;

	UPROPERTY(EditAnywhere)
		UClass* SpawnClass;

	UPROPERTY(EditAnywhere)
		float Damage = 25.0f;

	// Sets default values for this actor's properties
	ABaseTile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UPROPERTY()
		TArray<USceneComponent*> ChildrenList;

	UPROPERTY()
		TArray<AActor*> DamagedActors;

	UPROPERTY()
		AActor* Spawned;
};
