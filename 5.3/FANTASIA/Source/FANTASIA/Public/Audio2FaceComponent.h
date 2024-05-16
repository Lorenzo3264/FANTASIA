// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "FANTASIA.h"
#include "FANTASIATypes.h"
#if PLATFORM_WINDOWS
#include "Windows/AllowWindowsPlatformAtomics.h"
#include "Windows/PreWindowsApi.h"

	// Add native Windows/gRPC headers here
#include"Proto/audio2face.grpc.pb.h"
#include "Proto/audio2face.pb.h"
#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformAtomics.h"
#endif	

#include "Audio2FaceThread.h"
#include<string>
#include <sound/soundwaveprocedural.h>
#include <kismet/gameplaystatics.h>
#include "Sound/SoundWave.h"
#include "Sound/SoundWaveProcedural.h"
#include "Misc/FileHelper.h"
#include "AudioDecompress.h"
#include "Components/ActorComponent.h"
#include "Audio2FaceComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FANTASIA_API UAudio2FaceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAudio2FaceComponent();
	UPROPERTY(EditAnywhere, Category = "Audio2Face")
	FString PlayerA2F_name;

	UPROPERTY(EditAnywhere, Category = "Audio2Face")
	FString server_url;
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "NvidiaReadAudioFile", Keywords = "Nvidia Plugin"), Category = "Audio2Face")
	void ReadAudioFile(USoundWave* SoundWave);
	void A2FaceFMyThread(TArray<float> AudioData, int32 sampleRate);
	void LoadSoundWaveFromFile_Internal(TArray<float>& OutAudioData, int32& sampleRate, USoundWave* SoundWave);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
