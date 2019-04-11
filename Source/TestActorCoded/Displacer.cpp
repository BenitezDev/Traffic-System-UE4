// Fill out your copyright notice in the Description page of Project Settings.

#include "Displacer.h"
#include "Engine.h"


// Sets default values
ADisplacer::ADisplacer()
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

	//Suscripción al evento del clic sobre este actor
	OnClicked.AddDynamic(this, &ADisplacer::OnClic);

}

// Called when the game starts or when spawned
void ADisplacer::BeginPlay()
{
	Super::BeginPlay();

	//Comprueba 
	if (GEngine != nullptr)
	{
		//Equivalete al nivel
		UWorld* world = GetWorld();

		if (world != nullptr)
		{
			//Player Controller
			APlayerController* playerController = GEngine->GetFirstLocalPlayerController(world);

			if (playerController != nullptr)
			{
				//Muestra el cursor
				playerController->bShowMouseCursor = true;
				//Permite los eventos de clic del ratón
				playerController->bEnableClickEvents = true;
				//Permite que el playerController le envíe a este actor eventos relacionados con inputs
				EnableInput(playerController);
				//Enlaza una acción de input concreta
				InputComponent->BindAction(FName("Displace_AK"), EInputEvent::IE_Pressed, this, &ADisplacer::OnActionKeyPressed);
				
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, "No hay player controller");
			}
		}
		else
		{ 
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, "No hay mundo");
		}
		
	}
	
	
}

// Called every frame
void ADisplacer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//Si el flag está activo
	if (isDisplacing)
		Displace(DeltaTime);

}

void ADisplacer::TurnSpeed()
{
	this->displacementSpeed *= -1;
}

bool ADisplacer::IsDisplacing()
{
	return isDisplacing;
}

//Desplaza al objeto
void ADisplacer::Displace(float DeltaTime)
{
	//Posiciona al actor
	SetActorLocation(GetActorLocation() - GetActorRightVector() * DeltaTime * displacementSpeed);
}

void ADisplacer::StartDisplace()
{
	isDisplacing = true;
}

void ADisplacer::StopDisplace()
{
	isDisplacing = false;
}



//Callback del evento click sobre este actor
void ADisplacer::OnClic(AActor * actor, FKey keyname)
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "Mouse Clicked");
	isDisplacing = !isDisplacing;
}

//Callback de una acción de entrada (pulsación de una tecla)
void ADisplacer::OnActionKeyPressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, "Key Pressed");
	isDisplacing = !isDisplacing;
}

