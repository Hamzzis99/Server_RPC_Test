// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/ABFountain.h"

#include "ArenaBattle.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AABFountain::AABFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Water = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Water"));

	RootComponent = Body;
	Water->SetupAttachment(Body);
	Water->SetRelativeLocation(FVector(0.0f, 0.0f, 132.0f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01'"));
	if (BodyMeshRef.Object)
	{
		Body->SetStaticMesh(BodyMeshRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> WaterMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/ArenaBattle/Environment/Props/SM_Plains_Fountain_02.SM_Plains_Fountain_02'"));
	if (WaterMeshRef.Object)
	{
		Water->SetStaticMesh(WaterMeshRef.Object);
	}
	
	bReplicates = true; // 멀티플레이 액터 복제 설정
	NetUpdateFrequency = 1.0f; // 네트워크 업데이트 빈도 설정 (초당 10회) (작을수록 좋은 것.) 프레임이 끊겨보이는거 (틱마다인데 확실히 보인다.)
}

// Called when the game starts or when spawned
void AABFountain::BeginPlay()
{
	Super::BeginPlay();
	
	// if (HasAuthority()) // 블루프린트 HasAuthority는 이렇게 구현해도 된다.
	// {
	// 	FTimerHandle Handle;
	// 	GetWorld()->GetTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda([&]
	// 	{
	// 		ServerRotationYaw += 10.0f; // 서버에다 얼마나 더 값을 더할지..
	// 	}
	// 		), 1.0f, true, 0.0f);
	// }
}

// Called every frame
void AABFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (HasAuthority()) // 클라와 서버를 분리하는 함수. 다만 데디 서버일경우는 서버 로직만 구현하면 되니 만들지 않아도 됨.
	{
		AddActorLocalRotation(FRotator(0.0f, RotationRate * DeltaTime, 0.0f));
		ServerRotationYaw = RootComponent->GetComponentRotation().Yaw;
	}
	// else // 클라이언트에서는 서버에서 전달받은 회전값으로 회전 처리 (매 틱마다 받는 것이기 때문에 OnRep_ServerRotationYaw에다가 선언하면 필요한만큼 가능)
	// {
	// 	FRotator NewRotator = RootComponent->GetComponentRotation();
	// 	NewRotator.Yaw = ServerRotationYaw;
	// 	RootComponent->SetWorldRotation(NewRotator);
	// }
}
	
// 멀티플레이어 환경에서 변수 복제를 위한 함수 재정의
void AABFountain::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AABFountain, ServerRotationYaw); // ServerRotationYaw 변수를 복제 대상으로 지정 (프로퍼티 리플리케이션 활성화 방법?) GetLifetimeReplicatedProps의 함수.
}

void AABFountain::OnActorChannelOpen(class FInBunch& InBunch, class UNetConnection* Connection) // Connection에서 Bunch정보를 해석해 어떤 리플리 케이션을 작업하여 수행하는지 알려주는 것. (서버와의 포탈이 열렸다?)
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	
	Super::OnActorChannelOpen(InBunch, Connection); // 플레이어 컨트롤러나 특별한 부분들은 이 함수를 재정의해서 사용.
	
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AABFountain::OnRep_ServerRotationYaw() // 동적 액터는 이런 식으로 RepNotify 콜백 함수를 구현해야함.
{
	AB_LOG(LogABNetwork, Log, TEXT("YAW : %f"), ServerRotationYaw); // RepNotify 콜백 함수 구현 (서버에서 클라이언트로 값이 복제될 때마다 호출됨)
	
	FRotator NewRotator = RootComponent->GetComponentRotation();
	NewRotator.Yaw = ServerRotationYaw;
	RootComponent->SetWorldRotation(NewRotator);
}

