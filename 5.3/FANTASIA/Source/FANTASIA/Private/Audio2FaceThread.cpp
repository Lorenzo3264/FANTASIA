// Fill out your copyright notice in the Description page of Project Settings.

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Audio2FaceThread.h"

using namespace grpc;
using namespace std;
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace nvidia;
using audio2face::Audio2Face;
using audio2face::PushAudioRequestStart;
using audio2face::PushAudioStreamRequest;
using audio2face::PushAudioStreamResponse;


FMyThread* FMyThread::Runnable = NULL;

FMyThread::FMyThread(FString inPlayerA2F_name, FString inserver_url, TArray<float> inAudioData, int32 inSampleRate) : StopTaskCounter(0)
{

    PlayerA2F_name = inPlayerA2F_name;
    server_url = inserver_url;
    AudioData = inAudioData;
    SampleRate = inSampleRate;

    Thread = FRunnableThread::Create(this, TEXT("A2FaceThread"), 0, TPri_Normal);
}

FMyThread::~FMyThread() {
    if (Thread != NULL) {
        delete Thread;
        Thread = NULL;
    }
}

FMyThread* FMyThread::setup(FString inPlayerA2F_name, FString inserver_url, TArray<float> inAudioData, int32 inSampleRate)
{
    if (!Runnable && FPlatformProcess::SupportsMultithreading())
    {
        grpc_init();
        Runnable = new FMyThread(inPlayerA2F_name, inserver_url, inAudioData, inSampleRate);
    }
    return Runnable;
}


bool FMyThread::Init()
{
    StartTime = FDateTime::UtcNow();
    return true;
}

uint32 FMyThread::Run()
{
    bIsRunning = true;
    SendToAudio2FaceGrpc();
    bIsRunning = false;
    return 0;
}

void FMyThread::Stop()
{
    StopTaskCounter.Increment();
}

void FMyThread::EnsureCompletion()
{
    Stop();
    Thread->WaitForCompletion();
}

void FMyThread::Shutdown()
{
    if (Runnable)
    {
        //Runnable->bIsFinished = false;
        //Runnable->EnsureCompletion();
        //delete Runnable;
        grpc_shutdown();
        PrintTimeThread();
        Runnable->StopRecording = false;
        Runnable = NULL;
    }
}



void FMyThread::PrintTimeThread()
{
    Runnable->EndTime = FDateTime::UtcNow();
    FTimespan TempoTrascorso = Runnable->EndTime - Runnable->StartTime;
    int32 MillisecondiTrascorsi = TempoTrascorso.GetTotalMilliseconds();

    // Stampa o salva il tempo trascorso
    UE_LOG(LogTemp, Log, TEXT("Tempo di esecuzione del thread: %d ms"), MillisecondiTrascorsi);
}

bool FMyThread::IsThreadRunning() const
{
    
        return bIsRunning;
    
   
}

void FMyThread::StopSending() {

    StopRecording = true;

}
void FMyThread::SendToAudio2FaceGrpc()
{
    string url = TCHAR_TO_UTF8(*server_url);
    std::shared_ptr<Channel> channel2 = grpc::CreateChannel(url, grpc::InsecureChannelCredentials());
    //controllo se channel e stub sono caricati correttamente
    if (channel2!=nullptr) {
        UE_LOG(LogTemp, Log, TEXT("channel non vuoto"));
    }
    else {
        UE_LOG(LogTemp, Log, TEXT("channel  vuoto-->Shutdown()"));
        Shutdown();
    }
    std::unique_ptr<Audio2Face::Stub> stub2 = Audio2Face::NewStub(channel2);
    if (stub2 != nullptr) {
        UE_LOG(LogTemp, Log, TEXT("stub_ non vuoto"));
    }
    else {
        UE_LOG(LogTemp, Log, TEXT("stub_  vuoto-->Shutdown()"));
        Shutdown();
    }
    //TimeLogging
    int TimeLog = 0;
    FDateTime TimeInvioPrimoCHunk;
    //
    string PlayerA2FaceName = TCHAR_TO_UTF8(*PlayerA2F_name);
    int chunk_size = SampleRate / 10;
    double sleep_between_chunks = (double)chunk_size / SampleRate;//0.10
    bool block_until_playback_is_finished = true;
    UE_LOG(LogTemp, Log, TEXT("step1"));

    ClientContext context;
    PushAudioRequestStart start_marker;
    start_marker.set_instance_name(PlayerA2FaceName);
    start_marker.set_samplerate(SampleRate);
    start_marker.set_block_until_playback_is_finished(block_until_playback_is_finished);
    UE_LOG(LogTemp, Log, TEXT("step2"));
    // Prima mandiamo start_marker
    PushAudioStreamRequest* request = new PushAudioStreamRequest();
    request->set_allocated_start_marker(&start_marker);
    UE_LOG(LogTemp, Log, TEXT("step3"));

    PushAudioStreamResponse response;
    std::unique_ptr<grpc::ClientWriter<PushAudioStreamRequest>> writer(stub2->PushAudioStream(&context, &response));
    FDateTime TimeInvioStartMarker = FDateTime::UtcNow();
    UE_LOG(LogTemp, Log, TEXT("Tempo invio del start marker: %s"), *TimeInvioStartMarker.ToString());
    writer->Write(*request);
    UE_LOG(LogTemp, Log, TEXT("step4"));

  
    // Invia i messaggi con audio_data
    for (int32 i = 0; i < AudioData.Num(); i += chunk_size) {
        if (StopRecording == true) {
            UE_LOG(LogTemp, Log, TEXT("Primo IF del interrupted"));
            break;
        }
        TimeLog++;
       
        int32 chunk_end = FMath::Min(i + chunk_size, AudioData.Num());
        const float* chunk_data = AudioData.GetData() + i;
        chunk_size = chunk_end - i;
        PushAudioStreamRequest* requestAudio = new PushAudioStreamRequest();
        requestAudio->set_audio_data(chunk_data, chunk_size * sizeof(float));
        if (!writer->Write(*requestAudio)) {
            // Gestione degli errori: se Write ritorna false, c'è stato un errore
            UE_LOG(LogTemp, Log, TEXT("Error pushing audio chunk: %s"), context.debug_error_string().c_str());
            break;
        }
        if (TimeLog == 1) {
            TimeInvioPrimoCHunk = FDateTime::UtcNow();
            UE_LOG(LogTemp, Log, TEXT("Tempo invio del primo chunk: %s e di conseguenza fine StartMarker"), *TimeInvioPrimoCHunk.ToString());
            FTimespan TempoTrascorsoStarterMark = TimeInvioPrimoCHunk - TimeInvioStartMarker;
            int32 MillisecondiTrascorsiStarterMark = TempoTrascorsoStarterMark.GetTotalMilliseconds();
            UE_LOG(LogTemp, Log, TEXT("Tempo trascorso in totale per StartMarker: %d ms"), MillisecondiTrascorsiStarterMark);

        }
       // Sleep(static_cast<DWORD>(round(sleep_between_chunks * 1000))); // Converti in millisecondi
        FPlatformProcess::Sleep(sleep_between_chunks);
    }
    UE_LOG(LogTemp, Log, TEXT("step5"));
    writer->WritesDone();
    Status status = writer->Finish();

    FDateTime FineInvio = FDateTime::UtcNow();
    if (TimeInvioPrimoCHunk != NULL) {      
        FTimespan TempoTrascorsoChunks = FineInvio - TimeInvioPrimoCHunk;
        int32 MillisecondiTrascorsiChunks = TempoTrascorsoChunks.GetTotalMilliseconds();
        UE_LOG(LogTemp, Log, TEXT("Tempo trascorso in totale dal 1 chunk al response: %d ms"), MillisecondiTrascorsiChunks);
    }
    UE_LOG(LogTemp, Log, TEXT("Tempo ricezione del response: %s"), *FineInvio.ToString());
    if (StopRecording == true) {
        
        UE_LOG(LogTemp, Log, TEXT("Stream interrupted!"));
    }
    else {
        if (status.ok()) {
            if (response.success()) {
                UE_LOG(LogTemp, Log, TEXT("Audio stream pushed successfully!"));
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Audio stream pushed successfully!"));
            }
            else {
                UE_LOG(LogTemp, Log, TEXT("Response Error: %s"), response.message().c_str());
            }
        }
        else {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Audio stream failed to push!"));
            UE_LOG(LogTemp, Log, TEXT("Error pushing audio stream: %s"), status.error_message().c_str());
            UE_LOG(LogTemp, Log, TEXT("gRPC failed with error code: %s"), status.error_message().c_str());
        }
    }
   Shutdown();
}


