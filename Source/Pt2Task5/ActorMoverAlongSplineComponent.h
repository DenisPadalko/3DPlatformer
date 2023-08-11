// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/EngineTypes.h"
#include "ActorMoverAlongSplineComponent.generated.h"

/**
 * 
 */
UCLASS()
class PT2TASK5_API UActorMoverAlongSplineComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	
	void TimerFunction();
public:
	UPROPERTY(BlueprintReadWrite, Category="Defualt")
	USplineComponent* Spline;

	UPROPERTY(EditAnywhere, Category="Default")
	float StartAtProgress;

	UPROPERTY(VisibleAnywhere, Category="Default")
	FTimerHandle TimerHandle;
	
	FTimerDynamicDelegate TimerDynamicDelegate;
};
