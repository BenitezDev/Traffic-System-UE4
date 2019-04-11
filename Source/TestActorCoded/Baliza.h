// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Displacer.h"
#include "Containers/Array.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/PointLightComponent.h"
#include "Baliza.generated.h"

UCLASS()
class TESTACTORCODED_API ABaliza : public AActor
{
	GENERATED_BODY()
	
public:	

	//Colisionador de la baliza
	UPROPERTY(VisibleAnywhere, Category = "Collider")
		USphereComponent* collider;

	//Tiempo de encendido
	UPROPERTY(EditAnywhere, Category = "Timing Params")
		float switchTime = 2;

	//Número de parpadeos
	UPROPERTY(EditAnywhere, Category = "Timing Params")
		float numSwitchs = 5;

	UPROPERTY(EditAnywhere, Category = "Lista de coches a la espera")
	TArray<ADisplacer*> cars;

	//Punto de luz
	UPROPERTY(EditAnywhere, Category = "Propiedad de la luz")
	UPointLightComponent* light;

	//Estado de la baliza
	enum State { On, Off };
	State state;

	bool occupied;
	//Cuenta el número de parpadeos acumulados
	int currentNumSwitchs;

	//Manejador que identifica a un timer de manera única
	//https://api.unrealengine.com/INT/API/Runtime/Engine/Engine/FTimerHandle/index.html
	FTimerHandle timerId;

	
	// Sets default values for this actor's properties
	ABaliza();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SetLigth(bool lighting);

	UFUNCTION()
		void Switching();

	UFUNCTION()
		void ChangeLightToRed();

	UFUNCTION()
		void ChangeLightToGreen();

	//Trigger Enter
	UFUNCTION()
		void TriggerEnter(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	//Trigger Exit
	UFUNCTION()
		void TriggerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
