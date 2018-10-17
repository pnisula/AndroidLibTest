// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#if PLATFORM_ANDROID	
#include <jni.h> 
#endif
#include "GameFramework/Actor.h"

#include "LibActor.generated.h"

UCLASS()
class ANDROIDLIBTEST_API ALibActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALibActor();
	
	static int InitJNI();
	#if PLATFORM_ANDROID	
	jclass globalMyClass;
	#endif

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	void CreateLibInstance();
};
