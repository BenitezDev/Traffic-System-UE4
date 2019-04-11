// Fill out your copyright notice in the Description page of Project Settings.

#include "Baliza.h"
#include "Engine.h"


// Sets default values
ABaliza::ABaliza()
{
	occupied = false;
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Crea el colisionador
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	collider->SetSphereRadius(128);
	RootComponent = collider;
	
	//Crea el componente malla
	light = CreateDefaultSubobject<UPointLightComponent>("Light");
	light->AttachToComponent(collider, FAttachmentTransformRules::SnapToTargetIncludingScale);



}

// Called when the game starts or when spawned
void ABaliza::BeginPlay()
{
	Super::BeginPlay();

	state = State::Off;
	currentNumSwitchs = 0;

	//Equivalete al nivel
	UWorld* world = GetWorld();

	// Suscripción a los eventos trigger enter
	collider->OnComponentBeginOverlap.AddDynamic(this, &ABaliza::TriggerEnter);
	// Suctipcion a los eventos de trigger exit
	collider->OnComponentEndOverlap.AddDynamic(this, &ABaliza::TriggerExit);

	if (world != nullptr)
	{
		//Se crea un timer en modo loop, manejado por el método Switching
		//https://api.unrealengine.com/INT/API/Runtime/Engine/FTimerManager/
		
		// world->GetTimerManager().SetTimer(timerId, this, &ABaliza::Switching, switchTime, true);
	}

	
}

// Called every frame
void ABaliza::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//occupied = cars.Num() != 0 ? false : true;
	if (cars.Num() == 0) ChangeLightToGreen();
	else ChangeLightToRed();

}

//Enciende o apaga la luz
void ABaliza::SetLigth(bool lighting)
{
	light->SetVisibility(lighting);
}


//Cambia el estado lógico de la baliza
void ABaliza::Switching()
{
	if (state == State::Off)
	{
		state = State::On;
		SetLigth(true);
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, "On");
	}
	else
	{
		state = State::Off;
		SetLigth(false);
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, "Off");
		currentNumSwitchs++;
	}

	if (currentNumSwitchs >= numSwitchs)
	{
		currentNumSwitchs = 0;
		GetWorldTimerManager().ClearTimer(timerId);
	}

}

void ABaliza::ChangeLightToRed()
{
	light->SetLightColor(FColor::Red);
}

void ABaliza::ChangeLightToGreen()
{
	light->SetLightColor(FColor::Green);
}

void ABaliza::TriggerEnter(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && (OtherActor != this) && OtherComp != nullptr)
	{
		ADisplacer* displacer = Cast<ADisplacer>(OtherActor);

		if (displacer != nullptr)
		{
			cars.Add(displacer);

			//if()
			

			// Dejamos pasar al primer coche de la lista

			//// Si esta parado, le hacemos que se mueva
			//if (!cars[0]->IsDisplacing() && !occupied)
			//{
			//	cars[0]->Displace(true);
			//}

			

			// Si esta en movimiento no hacemos nada porque pasara sin parar
			
		}

	}
}

void ABaliza::TriggerExit(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

	// Other Actor is the actor that triggered the event. Check that is not ourself.  
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ADisplacer* displacer = Cast<ADisplacer>(OtherActor);

		if (displacer != nullptr)
		{
			//ChangeLightToGreen();
			cars.Remove(displacer);

		/*	cars.Remove(displacer);
			if (cars.Num() == 0)
			{
				occupied = false;
				ChangeLightToGreen();
			}
			else 
			{
				cars[0]->Displace(true);
				ChangeLightToRed();
				occupied = true;
			}*/
		}
	}
}

