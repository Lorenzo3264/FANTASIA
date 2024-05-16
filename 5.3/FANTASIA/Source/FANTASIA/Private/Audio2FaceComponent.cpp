#include "Audio2FaceComponent.h"

using namespace std;
// Sets default values for this component's properties
UAudio2FaceComponent::UAudio2FaceComponent()
{
    //inizializazione default
    PlayerA2F_name = TEXT("/World/audio2face/audio_player_streaming");
    server_url = TEXT("localhost:50051");
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UAudio2FaceComponent::ReadAudioFile(USoundWave* SoundWave)
{
	TArray<float>  AudioData;
	int32 sampleRate;
	LoadSoundWaveFromFile_Internal(AudioData, sampleRate, SoundWave);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("sending audio.."));
	//////////////////////PARTE THREADS GRPC////////////////////////    
	A2FaceFMyThread(AudioData, sampleRate);
	UE_LOG(LogTemp, Log, TEXT("FineReadAudioFile"));
}

void UAudio2FaceComponent::A2FaceFMyThread(TArray<float> AudioData, int32 sampleRate)
{
	FMyThread* MyThread = FMyThread::setup(PlayerA2F_name, server_url, AudioData, sampleRate);
	FPlatformProcess::Sleep(0.01);
}

void UAudio2FaceComponent::LoadSoundWaveFromFile_Internal(TArray<float>& OutAudioData, int32& sampleRate, USoundWave* SoundWave)
{
    TArray<uint8> AudioBytes;
    uint32 SampleRate;
    uint16 NumChannels;
    if (SoundWave->GetImportedSoundWaveData(AudioBytes, SampleRate, NumChannels))
    {
        TArray<float> AudioData;
        for (int32 i = 0; i < AudioBytes.Num(); i += 2 * NumChannels)
        {
            float NormalizedSample = 0.0f;

            // Se l'audio è stereo, somma i campioni dei due canali e divide per 2 e poi converte il campione in TarrayFloat
            if (NumChannels == 2)
            {
                int16 Sample1 = *reinterpret_cast<int16*>(&AudioBytes[i]);
                int16 Sample2 = *reinterpret_cast<int16*>(&AudioBytes[i + 2]);
                NormalizedSample = (Sample1 + Sample2) / 2.0f / 32768.0f;
            }
            else // Se l'audio è mono, converte il campione in TarrayFloat
            {
                int16 Sample = *reinterpret_cast<int16*>(&AudioBytes[i]);
                NormalizedSample = Sample / 32768.0f;
            }

            AudioData.Add(NormalizedSample);

        }
        OutAudioData = AudioData;
        sampleRate = SampleRate;
    }
}

// Called when the game starts
void UAudio2FaceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAudio2FaceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

