// Fill out your copyright notice in the Description page of Project Settings.


#include "OperationRecorder.h"

FString OperationData::GetOperationString(FDateTime CurrentTime) const
{
	FTimespan TimeDiff = CurrentTime - Timestamp;
	FString TimeString = FString::Printf(TEXT("在%d分%d秒前，"), TimeDiff.GetMinutes(), TimeDiff.GetSeconds());
	return TimeString + ToString();
}

FString OperationData::ToString() const
{
	return FString::Printf(TEXT("Not Implemented"));
}

FString MoveData::ToString() const
{
	FString ret;
	if (DeltaPosition.X < 0)
		ret += FString::Printf(TEXT("向西移动了%.2f米，"), -DeltaPosition.X / 100);
	else if (DeltaPosition.X > 0)
		ret += FString::Printf(TEXT("向东移动了%.2f米，"), DeltaPosition.X / 100);
	if (DeltaPosition.Y < 0)
		ret += FString::Printf(TEXT("向南移动了%.2f米，"), -DeltaPosition.Y / 100);
	else if (DeltaPosition.Y > 0)
		ret += FString::Printf(TEXT("向北移动了%.2f米，"), DeltaPosition.Y / 100);
	if (DeltaPosition.Z < 0)
		ret += FString::Printf(TEXT("向下移动了%.2f米，"), -DeltaPosition.Z / 100);
	else if (DeltaPosition.Z > 0)
		ret += FString::Printf(TEXT("向上移动了%.2f米，"), DeltaPosition.Z / 100);
	return ret;
}

FString JumpData::ToString() const
{
	return FString(TEXT("跳了一下。"));
}

FString GrabData::ToString() const
{
	return FString(TEXT("拿起了") + TargetName + TEXT("。"));
}

FString ShootData::ToString() const
{
	return FString(TEXT("射了一箭。"));
}

FString HitData::ToString() const
{
	return FString(TEXT("射箭击中了") + TargetName + TEXT("。"));
}

FString AttackData::ToString() const
{
	return FString(TEXT("使用近战武器攻击了") + TargetName + TEXT("。"));
}

FString KillData::ToString() const
{
	return FString(TEXT("击杀了") + TargetName + TEXT("。"));
}

FString CollectData::ToString() const
{
	return FString(TEXT("收集了") + TargetName + TEXT("。"));
}

FString BuyData::ToString() const
{
	return FString(TEXT("购买了") + TargetName + TEXT("。"));
}

FString SummonData::ToString() const
{
	return FString(TEXT("召唤了") + TargetName + TEXT("。"));
}

// Sets default values for this component's properties
UOperationRecorder::UOperationRecorder()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOperationRecorder::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOperationRecorder::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UOperationRecorder::RecordMoveOperation(const FVector& DeltaPosition)
{
    TSharedPtr<MoveData> Data = MakeShared<MoveData>();
    Data->Timestamp = FDateTime::Now();
    Data->Type = OperationType::Move;
    Data->DeltaPosition = DeltaPosition;
    Operations.Add(Data);
}

void UOperationRecorder::RecordJumpOperation()
{
	TSharedPtr<JumpData> Data = MakeShared<JumpData>();
	Data->Timestamp = FDateTime::Now();
	Data->Type = OperationType::Jump;
	Operations.Add(Data);
}

void UOperationRecorder::RecordGrabOperation(const FString& TargetName)
{
	TSharedPtr<GrabData> Data = MakeShared<GrabData>();
	Data->Timestamp = FDateTime::Now();
	Data->Type = OperationType::Grab;
	Data->TargetName = TargetName;
	Operations.Add(Data);
}

void UOperationRecorder::RecordShootOperation()
{
	TSharedPtr<ShootData> Data = MakeShared<ShootData>();
	Data->Timestamp = FDateTime::Now();
	Data->Type = OperationType::Shoot;
	Operations.Add(Data);
}

void UOperationRecorder::RecordHitOperation(const FString& TargetName)
{
	TSharedPtr<HitData> Data = MakeShared<HitData>();
	Data->Timestamp = FDateTime::Now();
	Data->Type = OperationType::Hit;
	Data->TargetName = TargetName;
	Operations.Add(Data);
}

void UOperationRecorder::RecordAttackOperation(const FString& TargetName)
{
	TSharedPtr<AttackData> Data = MakeShared<AttackData>();
	Data->Timestamp = FDateTime::Now();
	Data->Type = OperationType::Attack;
	Data->TargetName = TargetName;
	Operations.Add(Data);
}

void UOperationRecorder::RecordKillOperation(const FString& TargetName)
{
	TSharedPtr<KillData> Data = MakeShared<KillData>();
	Data->Timestamp = FDateTime::Now();
	Data->Type = OperationType::Kill;
	Data->TargetName = TargetName;
	Operations.Add(Data);
}

void UOperationRecorder::RecordCollectOperation(const FString& TargetName)
{
	TSharedPtr<CollectData> Data = MakeShared<CollectData>();
	Data->Timestamp = FDateTime::Now();
	Data->Type = OperationType::Collect;
	Data->TargetName = TargetName;
	Operations.Add(Data);
}

void UOperationRecorder::RecordBuyOperation(const FString& TargetName)
{
	TSharedPtr<BuyData> Data = MakeShared<BuyData>();
	Data->Timestamp = FDateTime::Now();
	Data->Type = OperationType::Buy;
	Data->TargetName = TargetName;
	Operations.Add(Data);
}

void UOperationRecorder::RecordSummonOperation(const FString& TargetName)
{
	TSharedPtr<SummonData> Data = MakeShared<SummonData>();
	Data->Timestamp = FDateTime::Now();
	Data->Type = OperationType::Summon;
	Data->TargetName = TargetName;
	Operations.Add(Data);
}

void UOperationRecorder::ClearOperations()
{
	Operations.Empty();
}

FString UOperationRecorder::GetAllOperationsString() const
{
	FString Result;
	FDateTime CurrentTime = FDateTime::Now();
	for (const TSharedPtr<OperationData>& Operation : Operations)
	{
		Result += Operation->GetOperationString(CurrentTime) + TEXT("\n");
	}
	return Result;
}
