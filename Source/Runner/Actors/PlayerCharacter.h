// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

// Forward Declarations:
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class ARunnerGameMode;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FKeyCountUpdated, int32, KeyCount);

UCLASS()
class RUNNER_API APlayerCharacter : public APawn
{
	GENERATED_BODY()
		
public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FKeyCountUpdated KeyCountUpdated;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION() // Required to bind to dynamic multi-cast delegate.
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
			FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION() // The names of these functions don't matter, but the signature does.
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;

	void RotateRightLeft(const FInputActionValue& Value);

	void InputFinished();

	void IncrementKeyCount();

	UFUNCTION()
	void AddPoints(int32 scoreDelta);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	int32 KeyCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	int32 Score = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setup)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setup)
	UArrowComponent* Arrow;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float NormalSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnSpeed = 500.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setup)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Setup)
	UCameraComponent* Camera;
};
