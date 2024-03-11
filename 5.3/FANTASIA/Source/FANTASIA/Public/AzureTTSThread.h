#pragma once
#include "FANTASIATypes.h"
#include <speechapi_cxx.h>
#include "Http.h"
#include "Runtime/Json/Public/Json.h"
#include "Runtime/JsonUtilities/Public/JsonUtilities.h"


using namespace std;
using namespace Microsoft::CognitiveServices::Speech;

DECLARE_EVENT_TwoParams(AzureTTSThread, FAzureResultAvailableEvent, FTTSData, FString);

//~~~~~ Multi Threading ~~~
class AzureTTSThread : public FRunnable
{
private:
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static AzureTTSThread* Runnable;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	FAzureResultAvailableEvent TTSResultAvailable;

	shared_ptr<SpeechConfig> TTSConfig;
	shared_ptr<SpeechSynthesizer> synthesizer;

	FString ssml;
	FString id;
	FString Endpoint;

	

public:

	//~~~ Thread Core Functions ~~~

	//Constructor
	AzureTTSThread(FString inSsml, FString inID, FString Endpoint);

	virtual ~AzureTTSThread();

	static AzureTTSThread* setup(FString ssml, FString id, FString Endpoint);

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	// End FRunnable interface

	void Synthesize();

	void OnHttpResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	FDelegateHandle TTSResultAvailableSubscribeUser(FTTSResultAvailableDelegate& UseDelegate);
	void TTSResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle);

	static TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> ExecuteRequest(TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest, float LoopDelay);
};