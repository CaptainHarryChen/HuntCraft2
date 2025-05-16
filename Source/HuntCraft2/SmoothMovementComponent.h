// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SmoothMovementComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class HUNTCRAFT2_API USmoothMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USmoothMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:
	// Target position and rotation
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Smooth Movement", meta = (AllowPrivateAccess = "true"))
	FVector TargetPosition;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Smooth Movement", meta = (AllowPrivateAccess = "true"))
	FRotator TargetRotation;

	// Movement properties
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Smooth Movement", meta = (AllowPrivateAccess = "true"))
	float Acceleration = 500.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Smooth Movement", meta = (AllowPrivateAccess = "true"))
	float MaxSpeed = 1200.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Smooth Movement", meta = (AllowPrivateAccess = "true"))
	float RotationAcceleration = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Smooth Movement", meta = (AllowPrivateAccess = "true"))
	float MaxRotationSpeed = 360.0f;

	// Blueprint callable function to set target position and rotation
	UFUNCTION(BlueprintCallable, Category = "Smooth Movement")
	void SetTarget(const FVector &NewTargetPosition, const FRotator &NewTargetRotation);

private:
	float CurrentSpeed = 0.0f;
	float CurrentAngularSpeed = 0.0f;
	// Helper function to calculate deceleration
	float CalculateAcceleration(float CurrentSpeed, float DistanceToTarget, float MaxSpeed, float Acceleration, float delta_time) const;
};
