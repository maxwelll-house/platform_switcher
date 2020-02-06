// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ObstacleController.h"
#include "OrbController.h"
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMSWITCHER_API AMainGameMode : public AGameMode
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	bool Switched;
	void OnSwitch();
	void OnGameOver(bool win);
	void OnRestart();

	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

protected:

	int Score = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;
};
