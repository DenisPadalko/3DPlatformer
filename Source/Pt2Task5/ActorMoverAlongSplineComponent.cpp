// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorMoverAlongSplineComponent.h"

UActorMoverAlongSplineComponent::UActorMoverAlongSplineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UActorMoverAlongSplineComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Timer = 0.0f;
	this->SetWorldLocation(Spline->GetLocationAtDistanceAlongSpline(Spline->GetSplineLength() * StartAtProgress, ESplineCoordinateSpace::World));
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
		Timer -= Spline->Duration;
	}
	
	float TimeToGetLocationAt = Timer + (Spline->Duration * StartAtProgress);
	if(TimeToGetLocationAt >= Spline->Duration)
	{
		TimeToGetLocationAt -= Spline->Duration;
	}
	
	const FVector NewLocation = Spline->GetLocationAtTime(TimeToGetLocationAt, ESplineCoordinateSpace::World);

	this->SetWorldLocation(NewLocation);
}
