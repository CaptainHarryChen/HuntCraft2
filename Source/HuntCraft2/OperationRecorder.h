// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OperationRecorder.generated.h"

enum class OperationType
{
	Move,
	Jump,
	Grab,
	Shoot,
	Hit,
	Attack,
	Kill,
	Collect,
	Buy,
	Summon
};

struct OperationData
{
	FDateTime Timestamp;
	OperationType Type;

	virtual FString GetOperationString(FDateTime CurrentTime) const;
	virtual FString ToString() const;
};

struct MoveData : public OperationData
{
	FVector DeltaPosition;
	virtual FString ToString() const override;
};

struct JumpData : public OperationData
{
	virtual FString ToString() const override;
};

struct GrabData : public OperationData
{
	FString TargetName;
	virtual FString ToString() const override;
};

struct ShootData : public OperationData
{
	virtual FString ToString() const override;
};

struct HitData : public OperationData
{
	FString TargetName;
	virtual FString ToString() const override;
};

struct AttackData : public OperationData
{
	FString TargetName;
	virtual FString ToString() const override;
};

struct KillData : public OperationData
{
	FString TargetName;
	virtual FString ToString() const override;
};

struct CollectData : public OperationData
{
	FString TargetName;
	virtual FString ToString() const override;
};

struct BuyData : public OperationData
{
	FString TargetName;
	virtual FString ToString() const override;
};

struct SummonData : public OperationData
{
	FString TargetName;
	virtual FString ToString() const override;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HUNTCRAFT2_API UOperationRecorder : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOperationRecorder();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Record Function")
	void RecordMoveOperation(const FVector& DeltaPosition);

	UFUNCTION(BlueprintCallable, Category = "Record Function")
	void RecordJumpOperation();

	UFUNCTION(BlueprintCallable, Category = "Record Function")
	void RecordGrabOperation(const FString& TargetName);

	UFUNCTION(BlueprintCallable, Category = "Record Function")
	void RecordShootOperation();

	UFUNCTION(BlueprintCallable, Category = "Record Function")
	void RecordHitOperation(const FString& TargetName);

	UFUNCTION(BlueprintCallable, Category = "Record Function")
	void RecordAttackOperation(const FString& TargetName);

	UFUNCTION(BlueprintCallable, Category = "Record Function")
	void RecordKillOperation(const FString& TargetName);

	UFUNCTION(BlueprintCallable, Category = "Record Function")
	void RecordCollectOperation(const FString& TargetName);

	UFUNCTION(BlueprintCallable, Category = "Record Function")
	void RecordBuyOperation(const FString& TargetName);

	UFUNCTION(BlueprintCallable, Category = "Record Function")
	void RecordSummonOperation(const FString& TargetName);

	UFUNCTION(BlueprintCallable, Category = "Record Function")
	void ClearOperations();

	UFUNCTION(BlueprintCallable, Category = "Record Function")
	FString GetAllOperationsString() const;

private:
	TArray<TSharedPtr<OperationData>> Operations;
};
