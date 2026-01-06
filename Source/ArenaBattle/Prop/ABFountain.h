//분수대 액터 선언 파일

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ABFountain.generated.h"

UCLASS()
class ARENABATTLE_API AABFountain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABFountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> Water;

	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override; // 멀티플레이어 환경에서 변수 복제를 위한 함수 재정의
	virtual void OnActorChannelOpen(class FInBunch& InBunch, class UNetConnection* Connection) override; // Connection에서 Bunch정보를 해석해 어떤 리플리 케이션을 작업하여 수행하는지 알려주는 것. (서버와의 포탈이 열렸다?)
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override; // 액터의 네트워크 관련성을 결정하는 함수 재정의
	
	//UPROPERTY(Replicated) // Replicated를 달아야 서버-클라이언트 간 동기화가 이루어짐
	UPROPERTY(ReplicatedUsing = OnRep_ServerRotationYaw) // Replicated를 Tick마다가 아닌 필요할 때마다 호출
	float ServerRotationYaw; // 분수대 회전값을 서버-클라이언트 간 동기화할 변수 (OnRep_ServerRotationYaw 함수에 따라 동기화)
	
	
	UPROPERTY(Replicated) // Replicated를 달아야 서버-클라이언트 간 동기화가 이루어짐
	TArray<float> BigData; // 대용량 데이터 예시 변수 (의도적인 고ㅓㅏ부화)
	
	UFUNCTION() // 언리얼에서 인식할 수 있는 Function 
	void OnRep_ServerRotationYaw(); // RepNotify 콜백 함수 선언
	
	float RotationRate = 30.f; // 분수대 회전 속도
	float ClientTimeSinceUpdate = 0.0f; // 클라이언트가 서버로부터 마지막으로 업데이트된 이후 경과한 시간
	float ClientTimeBetweenLastUpdate = 0.0f; // 클라이언트가 서버로부터 데이터를 받고 그 다음 데이터를 받았을 때 걸린 시간.
	float BigDataElement = 0.0f; // 대용량 데이터 예시 변수 (의도적인 과부화)
};
