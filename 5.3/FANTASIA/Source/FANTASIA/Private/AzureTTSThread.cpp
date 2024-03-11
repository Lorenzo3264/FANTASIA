#include "AzureTTSThread.h"

using namespace std;

AzureTTSThread* AzureTTSThread::Runnable = NULL;

AzureTTSThread::AzureTTSThread(FString inSsml, FString inID, FString url) : StopTaskCounter(0)
{
	ssml = inSsml;
	id = inID;
	Thread = FRunnableThread::Create(this, TEXT("AzureTTSThread"), 0, TPri_Normal);
	Endpoint = url;
}

AzureTTSThread::~AzureTTSThread() {
	delete Thread;
	Thread = NULL;
}


AzureTTSThread* AzureTTSThread::setup(FString ssml, FString id, FString Endpoint)
{
	if (!Runnable && FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new AzureTTSThread(ssml, id, Endpoint);
	}
	return Runnable;
}

bool AzureTTSThread::Init()
{
	return true;
}

uint32 AzureTTSThread::Run()
{
	Synthesize();
	return 0;
}

void AzureTTSThread::Stop()
{
	StopTaskCounter.Increment();
}

void AzureTTSThread::EnsureCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}

void AzureTTSThread::Shutdown()
{
	if (Runnable)
	{
		//Runnable->EnsureCompletion();
		//delete Runnable;
		Runnable = NULL;
	}
}

void AzureTTSThread::Synthesize()
{

	//Http request to CherryPy API

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			if (bWasSuccessful && Response.IsValid())
			{
				TArray<uint8> ResponseData = Response->GetContent();

				FTTSData SyntResult;
				SyntResult.AudioData = ResponseData;
				SyntResult.ssml = ssml;

				TTSResultAvailable.Broadcast(SyntResult, id);

			}
			else
			{
				// Gestione errori
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Richiesta non riuscita o risposta non valida");
			}
		});
	Request->SetURL(Endpoint);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/x-www-form-urlencoded");
	FString Content = "line=";
	Content = Content + ssml;
	Request->SetContentAsString(Content);
	Request->ProcessRequest();

}

void AzureTTSThread::OnHttpResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		FString ResponseContent = Response->GetContentAsString();
	}
	else
	{
	}
}

FDelegateHandle AzureTTSThread::TTSResultAvailableSubscribeUser(FTTSResultAvailableDelegate& UseDelegate)
{
	return TTSResultAvailable.Add(UseDelegate);
}

void AzureTTSThread::TTSResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle)
{
	TTSResultAvailable.Remove(DelegateHandle);
}

TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> AzureTTSThread::ExecuteRequest(TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest, float LoopDelay)
{
	bool bStartedRequest = HttpRequest->ProcessRequest();
	if (!bStartedRequest)
	{
		//UE_LOG(LogMyGame, Error, TEXT("Failed to start HTTP Request."));
		return nullptr;
	}

	TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> Response = HttpRequest->GetResponse();
	while (true)
	{
		int32 Code = Response->GetResponseCode();

		if (Code != 0)
			break;

		FPlatformProcess::Sleep(LoopDelay);
	}

	return Response;
}