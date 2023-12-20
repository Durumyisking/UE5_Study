// Fill out your copyright notice in the Description page of Project Settings.


#include "SubObjects/Portal.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mBody = CreateDefaultSubobject<UBoxComponent>(TEXT("PortalBody"));
	mParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));

	RootComponent = mBody;
	mParticle->SetupAttachment(mBody);

}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	
	mBody->OnComponentBeginOverlap.AddDynamic(this, &APortal::BeginOverlap);
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortal::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::OpenLevel(GetWorld(), mLevelName);
}

