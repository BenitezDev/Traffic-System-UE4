// Fill out your copyright notice in the Description page of Project Settings.

#include "BoxTrigger.h"
#include "Displacer.h"


// Sets default values
ABoxTrigger::ABoxTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Crea el componente collider
	boxCollider = CreateDefaultSubobject<UBoxComponent>("Collider");

	//Modifica el tamaño del collider
	boxCollider->SetBoxExtent(FVector(50, 50, 50));

	//Establece la raíz de la jerarquía de componentes
	SetRootComponent(boxCollider);

	//Crea el componente collider
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	//Modifica la jerarquía de componentes
	mesh->AttachToComponent(boxCollider, FAttachmentTransformRules::SnapToTargetIncludingScale);



}

// Called when the game starts or when spawned
void ABoxTrigger::BeginPlay()
{
	Super::BeginPlay();

	//Oculta la malla en tiempo de ejecución
	mesh->SetVisibility(false);

	//Suscripción a los eventos trigger enter
	boxCollider->OnComponentBeginOverlap.AddDynamic(this, &ABoxTrigger::TriggerEnter);

	//Suscripción a los eventos trigger exit
	boxCollider->OnComponentEndOverlap.AddDynamic(this, &ABoxTrigger::TriggerExit);

	
}

// Called every frame
void ABoxTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Trigger Enter
void ABoxTrigger::TriggerEnter(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && (OtherActor != this) && OtherComp != nullptr)
	{
		ADisplacer* displacer = Cast<ADisplacer>(OtherActor);

		if (displacer != nullptr)
		{
			displacer->TurnSpeed();
			//displacer->StopDisplace();
		}

	}
}

//Trigger Exit
void ABoxTrigger::TriggerExit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	//Sin funcionalidad aún
}



