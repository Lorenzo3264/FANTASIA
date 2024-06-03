﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Audio2FaceComponent.h"
#include "HAL/Runnable.h"
#include "HAL/ThreadSafeBool.h"
#include "Templates/UniquePtr.h"
#include <grpcpp/grpcpp.h>

class FMyThread : public FRunnable
{
private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static FMyThread* Runnable;
	FDateTime StartTime;
	FDateTime EndTime;
	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	FString PlayerA2F_name;
	FString server_url;
	TArray<float> AudioData;
	int32 SampleRate;

public:
	bool bIsRunning;
	//~~~ Thread Core Functions ~~~

	//Constructor
	FMyThread(FString inPlayerA2F_name, FString inserver_url, TArray<float>  inAudioData, int32 inSampleRate);
	virtual ~FMyThread();
	static FMyThread* setup(FString inPlayerA2F_name, FString inserver_url, TArray<float>  inAudioData, int32 inSampleRate);

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	

	
	virtual void Stop();
	// End FRunnable interface

	void SendToAudio2FaceGrpc();

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();
	static void PrintTimeThread();
	/** Checks if the thread is running */
	bool IsThreadRunning() const;
};
