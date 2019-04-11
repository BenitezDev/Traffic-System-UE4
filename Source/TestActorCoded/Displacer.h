// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "Displacer.generated.h"

UCLASS()
class TESTACTORCODED_API ADisplacer : public AActor
{
	GENERATED_BODY()
	
public:	

	//Colisionador del objeto
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collider")
		class UBoxComponent* boxCollider;

	//Malla del objeto
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		class UStaticMeshComponent* mesh;

	//Velocidad de desplazamiento del objeto
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
		float displacementSpeed = 10;

private:

	//Indica si el objeto se está desplazando
	bool isDisplacing;

public:

	// Sets default values for this actor's properties
	ADisplacer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void TurnSpeed();

	UFUNCTION()
		bool IsDisplacing();

	UFUNCTION()
		//Desplaza al objeto
		void Displace(float DeltaTime);

	UFUNCTION()
		//Desplaza al objeto
		void StartDisplace();

	UFUNCTION()
		//Desplaza al objeto
		void StopDisplace();

	UFUNCTION()
		//Callback del evento click sobre este actor
		void OnClic(AActor* actor, FKey keyname);

	UFUNCTION()
		//Callback de una tecla pulsada
		void OnActionKeyPressed();

};
