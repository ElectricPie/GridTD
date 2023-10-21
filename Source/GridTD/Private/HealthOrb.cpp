// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthOrb.h"

#include "TowerDefencePlayer.h"

// Sets default values
AHealthOrb::AHealthOrb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void AHealthOrb::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHealthOrb::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EndPlayReason != EEndPlayReason::Destroyed) return;

	ATowerDefencePlayer* TowerPlayer = Cast<ATowerDefencePlayer>(GetWorld()->GetFirstPlayerController());
	if (!TowerPlayer) return;
	TowerPlayer->ReduceHealth();
}

// Called every frame
void AHealthOrb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

