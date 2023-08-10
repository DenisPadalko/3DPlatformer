// Fill out your copyright notice in the Description page of Project Settings.


#include "UActorMoverComponent.h"

// Sets default values for this component's properties
UUActorMoverComponent::UUActorMoverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUActorMoverComponent::BeginPlay()
{
	Super::BeginPlay();

	OriginalLocation = GetOwner()->GetActorLocation();
	TargetLocation = OriginalLocation + (MovementDirection * DistanceToMove);
	if(FMath::IsNearlyEqual(MovingSpeed,0.0f))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("MovingSpeed was equal to 0"));
		TimeToMove = 0.0f;
	}
	else
	{
		TimeToMove = DistanceToMove / MovingSpeed;
	}
	
}

FVector UUActorMoverComponent::GetNewLocation(const float Alpha) const
{
	switch (EasingType)
	{
	case EEasingType::EaseIn:
		return FMath::InterpEaseIn(OriginalLocation, TargetLocation, Alpha, Exponent);
	case EEasingType::EaseOut:
		return FMath::InterpEaseOut(OriginalLocation, TargetLocation, Alpha, Exponent);
	case EEasingType::EaseInOut:
		return FMath::InterpEaseInOut(OriginalLocation, TargetLocation, Alpha, Exponent);
	case EEasingType::ExpoIn:
		return FMath::InterpExpoIn(OriginalLocation, TargetLocation, Alpha);
	case EEasingType::ExpoOut:
		return FMath::InterpExpoOut(OriginalLocation, TargetLocation, Alpha);
	case EEasingType::ExpoInOut:
		return FMath::InterpExpoInOut(OriginalLocation, TargetLocation, Alpha);
	case EEasingType::SinIn:
		return FMath::InterpSinIn(OriginalLocation, TargetLocation, Alpha);
	case EEasingType::SinOut:
		return FMath::InterpSinOut(OriginalLocation, TargetLocation, Alpha);
	case EEasingType::SinInOut:
		return FMath::InterpSinInOut(OriginalLocation, TargetLocation, Alpha);
	case EEasingType::Step:
		return FMath::InterpStep(OriginalLocation, TargetLocation, Alpha, 1000000);
	case EEasingType::Linear:
		return FMath::Lerp(OriginalLocation, TargetLocation, Alpha);
	default:
		return OriginalLocation;
	}
}

// Called every frame
void UUActorMoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const float Alpha = FMath::Clamp(RunningTime / TimeToMove, 0.0f, 1.0f);
	RunningTime += DeltaTime;
	
	GetOwner()->SetActorLocation(GetNewLocation(Alpha));
	
	if(GetOwner()->GetActorLocation().Equals(TargetLocation))
	{
		OriginalLocation = TargetLocation;
		DirectionMultiplier *= -1.0f;
		TargetLocation = OriginalLocation + (MovementDirection * DirectionMultiplier * DistanceToMove);
		RunningTime = 0.0f;
	}
}

