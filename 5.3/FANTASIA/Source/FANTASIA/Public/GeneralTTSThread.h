#pragma once
#include "FANTASIATypes.h"
#include <speechapi_cxx.h>
#include "Http.h"
#include "Runtime/Json/Public/Json.h"
#include "Runtime/JsonUtilities/Public/JsonUtilities.h"


using namespace std;
using namespace Microsoft::CognitiveServices::Speech;

DECLARE_EVENT_TwoParams(GeneralTTSThread, ResultAvailableEvent, FTTSData, FString);

//~~~~~ Multi Threading ~~~
class GeneralTTSThread : public FRunnable
{
private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static GeneralTTSThread* Runnable;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	ResultAvailableEvent TTSResultAvailable;

	shared_ptr<SpeechConfig> TTSConfig;
	shared_ptr<SpeechSynthesizer> synthesizer;

	FString ssml;
	FString id;
	FString Endpoint;

	

public:

	//~~~ Thread Core Functions ~~~

	//Constructor
	GeneralTTSThread(FString inSsml, FString inID, FString Endpoint);

	virtual ~GeneralTTSThread();

	static GeneralTTSThread* setup(FString ssml, FString id, FString Endpoint);

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	// End FRunnable interface

	void Synthesize();

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	FDelegateHandle TTSResultAvailableSubscribeUser(FTTSResultAvailableDelegate& UseDelegate);
	void TTSResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle);
};