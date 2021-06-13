// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTile.h"

// Sets default values
ABaseTile::ABaseTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Base = CreateDefaultSubobject<USceneComponent>(TEXT("BASE"));

    RootComponent = Base;
}

// Called when the game starts or when spawned
void ABaseTile::BeginPlay()
{
	Super::BeginPlay();

    DamagedActors.Reset();

    Base->GetChildrenComponents(true, ChildrenList);
    
    for (int i = 0; i < ChildrenList.Num(); i++) {
        UShapeComponent* Collision = Cast<UShapeComponent>(ChildrenList[i]);
        if(Collision)
            Collision->OnComponentBeginOverlap.AddDynamic(this, &ABaseTile::BeginOverlap);
    }
    
}

// Called every frame
void ABaseTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseTile::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor->CanBeDamaged() && !DamagedActors.Contains(OtherActor)) {
        OtherActor->TakeDamage(Damage, FDamageEvent(UDamageType::StaticClass()), NULL, this);
        DamagedActors.Push(OtherActor);
    }
}