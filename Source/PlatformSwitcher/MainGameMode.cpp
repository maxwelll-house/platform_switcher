// Fill out your copyright notice in the Description page of Project Settings.

#include "PlatformSwitcher.h"
#include "MainGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameWidget.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"

void AMainGameMode::BeginPlay()
{

	Super::BeginPlay();

	ChangeMenuWidget(StartingWidgetClass);

	((UGameWidget*)CurrentWidget)->Load();

	//GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("Switch", IE_Pressed, this, &AMainGameMode::OnSwitch);
	GetWorld()->GetFirstPlayerController()->InputComponent->BindAction("Restart", IE_Pressed, this, &AMainGameMode::OnRestart).bExecuteWhenPaused = true;
}

void AMainGameMode::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
}

void AMainGameMode::OnSwitch()
{
	if (Switched) {
		FVector NewLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		NewLocation.X = 2000.0f;
		GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(NewLocation);
	}
	else {
		FVector NewLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
		NewLocation.X = 1200.0f;
		GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(NewLocation);
	}
	Switched = !Switched;
}

void AMainGameMode::OnGameOver(bool win)
{
	((UGameWidget*)CurrentWidget)->OnGameOver(win);

	UGameplayStatics::SetGamePaused(GetWorld(), true);
	
}

void AMainGameMode::OnRestart()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AMainGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr) {
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);

		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}
}