// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "Engine/EngineTypes.h"
#include "ActorMoverAlongSplineComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PT2TASK5_API UActorMoverAlongSplineComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UActorMoverAlongSplineComponent();
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category="Default")
	void SetSpline(USplineComponent* InSpline);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	UPROPERTY(BlueprintReadWrite, Category="Default")
	USplineComponent* Spline = nullptr;

	UPROPERTY(EditAnywhere, Category="Default")
	float StartAtProgress = 0.0f;

	UPROPERTY(VisibleAnywhere, Category="Default")
	float Timer = 0.0f;
	
};
