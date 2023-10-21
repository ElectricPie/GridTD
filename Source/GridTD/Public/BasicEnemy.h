// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicEnemy.generated.h"

class AHealthOrb;
class UCapsuleComponent;

UCLASS()
class GRIDTD_API ABasicEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasicEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:	
	void MoveToCurrentWaypoint(const FVector& Position);
	void CheckDistanceToTarget();
	
protected:
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere, Category="Components", meta=(Tooltip="A place for a Health Orb"))
	USceneComponent* OrbSlot;

	UPROPERTY(EditAnywhere, Category="Movement")
	float MovementSpeed = 100.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement")
	TArray<AActor*> Waypoints;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement")
	int32 CurrentWaypoint;

	// The distance from a waypoint to change to the next waypoint
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaypointTriggerDistance = 10.f;

	UPROPERTY(VisibleAnywhere)
	AHealthOrb* HealthOrb = nullptr;
	
public:
	/**
	 * Assigns the waypoints to the enemy, and starts it moving to the first in the array.
	 * @param NewWaypoints The array of waypoints.
	 */
	void SetWaypoints(const TArray<AActor*>& NewWaypoints);
};
