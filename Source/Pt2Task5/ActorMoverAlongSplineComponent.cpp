// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorMoverAlongSplineComponent.h"

UActorMoverAlongSplineComponent::UActorMoverAlongSplineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UActorMoverAlongSplineComponent::UpdateMeshStartLocation()
{
	Timer = StartAtProgress * Spline->Duration;
	SetWorldLocation(Spline->GetLocationAtTime(Timer, ESplineCoordinateSpace::World));
}

void UActorMoverAlongSplineComponent::SetSpline(USplineComponent* InSpline)
{
	Spline = InSpline;
}

void UActorMoverAlongSplineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	Timer += DeltaTime;
	if(Timer >= Spline->Duration)
	{
		Timer = 0.0f;
	}
	
	const FVector NewLocation = Spline->GetLocationAtTime(Timer, ESplineCoordinateSpace::World);

	SetWorldLocation(NewLocation);
}
