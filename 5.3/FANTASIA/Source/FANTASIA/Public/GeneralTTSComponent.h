// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FANTASIA.h"
#include "Engine.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FANTASIATypes.h"
#include "GeneralTTSThread.h"
#include <speechapi_cxx.h>
#include <iostream>
#include <string>
#include "Runtime/Engine/Classes/Sound/SoundWaveProcedural.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "Runtime/Json/Public/Json.h"
#include "Runtime/JsonUtilities/Public/JsonUtilities.h"
#include "GeneralTTSComponent.generated.h"

using namespace std;

UCLASS(meta = (BlueprintSpawnableComponent))
class UGeneralTTSComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGeneralTTSComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	TMap<FString, FTTSData> Buffer;
	TMap<FString, FString> PendingSSML;
	shared_ptr<SpeechConfig> config;
	GeneralTTSThread* handle;
	
	FDelegateHandle TTSResultAvailableHandle;

	void getResult(FTTSData response, FString id);

	FSynthesizedInternalEvent synthesisReadyInternal;

	FString idSynthesisReady = "";

public:

	UPROPERTY(BlueprintReadWrite, Category = "Speech to Text")
		UAudioComponent* Speaker;

	UPROPERTY(BlueprintAssignable, Category = "Speech to Text")
		FSynthesizedEvent SynthesisReady;

	UPROPERTY(EditAnywhere, Category = "Configuration")
		FString Endpoint;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "TTS Start", Keywords = "Plugin TTS"), Category = "TTS")
		void TTSSynthesize(FString ssml, FString id);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Sound", Keywords = "Plugin TTS"), Category = "TTS")
		USoundBase* TTSGetSound(FString id);
};