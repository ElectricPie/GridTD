// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "BasicEnemy.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	//RootComponent = SceneComponent;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnEnemy();
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnEnemy() const
{
	if (!EnemyToSpawn) return;

	ABasicEnemy* NewEnemy = GetWorld()->SpawnActor<ABasicEnemy>(
		EnemyToSpawn,
		GetActorLocation(),
		GetActorRotation()
	);

	NewEnemy->SetWaypoints(Waypoints);
}
