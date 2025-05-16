// Fill out your copyright notice in the Description page of Project Settings.


#include "SmoothMovementComponent.h"

// Sets default values for this component's properties
USmoothMovementComponent::USmoothMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USmoothMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	SetTarget(Owner->GetActorLocation(), Owner->GetActorRotation());
}

void USmoothMovementComponent::SetTarget(const FVector &NewTargetPosition, const FRotator &NewTargetRotation)
{
	TargetPosition = NewTargetPosition;
	TargetRotation = NewTargetRotation;
}

// Called every frame
void USmoothMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Get the current position and rotation of the owner
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return;
	}

	FVector CurrentPosition = Owner->GetActorLocation();
	FRotator CurrentRotation = Owner->GetActorRotation();

	// Calculate the distance to the target position
	FVector ToTarget = TargetPosition - CurrentPosition;
	float DistanceToTarget = ToTarget.Size();

	// Calculate the desired speed and deceleration
	float acc = CalculateAcceleration(CurrentSpeed, DistanceToTarget, MaxSpeed, Acceleration, DeltaTime);
	float DesiredSpeed = FMath::Clamp(CurrentSpeed + acc * DeltaTime, 0.0f, MaxSpeed);

	// Move towards the target position
	if (DistanceToTarget > KINDA_SMALL_NUMBER)
	{
		FVector Direction = ToTarget.GetSafeNormal();
		FVector NewPosition = CurrentPosition + Direction * DesiredSpeed * DeltaTime;
		CurrentSpeed = DesiredSpeed; // Update the current speed
		Owner->SetActorLocation(NewPosition);
	}

	// Calculate the angular distance to the target rotation
	FRotator DeltaRotation = (TargetRotation - CurrentRotation).GetNormalized();
	float AngularDistanceToTarget = FMath::Abs(DeltaRotation.Yaw);

	// Calculate the desired angular speed and deceleration
	float aacc = CalculateAcceleration(CurrentAngularSpeed, AngularDistanceToTarget, MaxRotationSpeed, RotationAcceleration, DeltaTime);
	float DesiredAngularSpeed = FMath::Clamp(CurrentAngularSpeed + aacc * DeltaTime, 0.0f, MaxRotationSpeed);

	// Rotate towards the target rotation
	if (AngularDistanceToTarget > KINDA_SMALL_NUMBER)
	{
		float RotationStep = FMath::Sign(DeltaRotation.Yaw) * DesiredAngularSpeed * DeltaTime;
		FRotator NewRotation = CurrentRotation + FRotator(0.0f, RotationStep, 0.0f);
		CurrentAngularSpeed = DesiredAngularSpeed; // Update the current angular speed
		Owner->SetActorRotation(NewRotation);
	}
	// ...
}

float USmoothMovementComponent::CalculateAcceleration(float current_speed, float DistanceToTarget, float max_speed, float acc, float delta_time) const
{
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("current_speed: %f"), current_speed));
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("DistanceToTarget: %f"), DistanceToTarget));
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("check: %f"), 0.5 * (current_speed / acc) * current_speed));
	float stop_distance = (current_speed * current_speed) / (2 * acc);
	if (DistanceToTarget <= stop_distance)
		return -acc;
	float speed = FMath::Clamp(DistanceToTarget / delta_time, 0.0f, max_speed);
	float ret = (speed - current_speed) / delta_time;
	ret = FMath::Clamp(ret, -acc, acc);
	return ret;
}
