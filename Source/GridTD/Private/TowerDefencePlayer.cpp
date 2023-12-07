// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerDefencePlayer.h"

#include "TurretSocket.h"
#include "Kismet/GameplayStatics.h"
#include "Ui/TowerDefenceHudWidget.h"


void ATowerDefencePlayer::BeginPlay()
{
	Super::BeginPlay();

	bShowMouseCursor = true;

	SetupUi();
}


void ATowerDefencePlayer::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Select", IE_Pressed, this, &ATowerDefencePlayer::Select);
}

void ATowerDefencePlayer::GameOver_Implementation()
{
}


void ATowerDefencePlayer::Select()
{
	if (!HudWidget) return;
	HudWidget->CloseTurretSelectionWidget();
	
	// Get the screen position of the mouse
	FVector2D MouseScreenPos;
	if (!GetMouseScreenPos(MouseScreenPos)) return;
	
	FVector HitLocation;
	AActor* HitActor = nullptr;
	if (!RaycastToMouse(MouseScreenPos, HitLocation, HitActor)) return;

	ATurretSocket* TurretSocket = Cast<ATurretSocket>(HitActor);
	if (!TurretSocket) return;
	
	HudWidget->SelectTurretSocket(TurretSocket);
}

void ATowerDefencePlayer::SetupUi()
{
	if (!HudWidgetBlueprint) return;
	HudWidget = CreateWidget<UTowerDefenceHudWidget>(GetWorld(), HudWidgetBlueprint);
	HudWidget->AddToViewport();
}

bool ATowerDefencePlayer::GetMouseScreenPos(FVector2D& MouseScreenPos) const
{
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// Get the screen position of the mouse
	return GetMousePosition(MouseScreenPos.X, MouseScreenPos.Y);
}

bool ATowerDefencePlayer::RaycastToMouse(const FVector2D& MouseScreenPos, FVector& HitLocation, AActor*& HitActor) const
{
	// Get the direction of the mouse
	FVector WorldPosition;
	FVector WorldDirection;
	DeprojectScreenPositionToWorld(MouseScreenPos.X, MouseScreenPos.Y, WorldPosition, WorldDirection);
	
	// Raycast
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	
	if (GetWorld()->LineTraceSingleByChannel(HitResult, WorldPosition,
	WorldPosition + WorldDirection * SelectionRaycastDistance, ECC_Visibility, QueryParams))
	{
		HitActor = HitResult.GetActor();
		HitLocation = HitResult.ImpactPoint;
		return true;
	}

	return false;
}

void ATowerDefencePlayer::RegisterPlayerHealth(const int32 AdditionalHealth)
{
	MaxHealth += AdditionalHealth;
	Health += AdditionalHealth;
}

void ATowerDefencePlayer::ReduceHealth()
{
	Health--;

	if (Health > 0) return;
	GameOver();
}
