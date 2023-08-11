// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorMoverAlongSplineComponent.h"

void UActorMoverAlongSplineComponent::BeginPlay()
{
	TimerDynamicDelegate.BindDynamic(this, &UActorMoverAlongSplineComponent::TimerFunction);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDynamicDelegate, 1.0f, true, 0.0f);
}


void UActorMoverAlongSplineComponent::TimerFunction()
{
	if(TimerHandle.ToString() >= Spline->Duration())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDynamicDelegate, 1.0f, true, 0.0f);
	}
	const float TimeElapsed = GetWorld()->GetTimerManager().GetTimerElapsed(TimerHandle) + 1.0f;
	const FVector NewLocation = Spline->GetLocationAtTime(TimeElapsed, ESplineCoordinateSpace::World, true);
	const FRotator NewRotation = Spline->GetRotationAtTime(TimeElapsed, ESplineCoordinateSpace::World, true);
	MoveComponent(NewLocation, NewRotation, false);
}
