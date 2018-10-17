// Fill out your copyright notice in the Description page of Project Settings.

#include "LibActor.h"
#if PLATFORM_ANDROID	
#include "Android/AndroidApplication.h"
#include <jni.h> 
#include <android/log.h>
#endif
#include "Engine/GameEngine.h"

#define LOG_TAG "com_testlib"

#ifdef ENABLE_VERBOSE_LOGGING
#undef ENABLE_VERBOSE_LOGGING
#endif
#define ENABLE_VERBOSE_LOGGING true

#define EXCEPTION_RETURN(env) \
	if (env->ExceptionOccurred()) { \
		env->ExceptionDescribe(); \
		env->ExceptionClear(); \
		return; \
	}

// Sets default values
ALibActor::ALibActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALibActor::BeginPlay()
{
	Super::BeginPlay();	
	CreateLibInstance();
}

// Called every frame
void ALibActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}
void ALibActor::CreateLibInstance()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Creating lib instance"));	
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Using Android JNI"));		
	InitJNI();			
	
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Creating Lib Ends!"));
}

int ALibActor::InitJNI()
{
	#if PLATFORM_ANDROID
	JNIEnv* env = FAndroidApplication::GetJavaEnv();
	{		
		const char* strClass = "com/mycompany/myproduct/mylibrary/MyTestClass";
		//C:\Users\pekka.nisula\Desktop\androidLib\classes\com\mycompany\myproduct\mylibrary
		#if ENABLE_VERBOSE_LOGGING
		__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Searching for %s", strClass);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Searching for com/mycompany/myproduct/mylibrary/MyTestClass"));
		#endif
		jclass localRef = FAndroidApplication::FindJavaClass(strClass);
		if (localRef)
		{
		#if ENABLE_VERBOSE_LOGGING
			__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "Found %s", strClass);
		#endif
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Found com/mycompany/myproduct/mylibrary/MyTestClass"));
			
			jmethodID mid = env->GetStaticMethodID(localRef, "IntTest", "()I");
			
			jint test = env->CallStaticIntMethod(localRef, mid);

			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *FString("VITTU SAATANA NAKKYY PERKELE Test int: " + FString::FromInt((int)test)));
			__android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, "test int was %d", (int)test);
			
			env->DeleteLocalRef(localRef);
		}
		else
		{
			__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to find %s", strClass);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Failed to find com/epicgames/ue4/GameActivity"));
			return JNI_ERR;
		}
	}
#endif
	return -1;
}
