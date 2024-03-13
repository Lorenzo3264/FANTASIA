#include "GeneralTTSThread.h"

using namespace std;

GeneralTTSThread* GeneralTTSThread::Runnable = NULL;

GeneralTTSThread::GeneralTTSThread(FString inSsml, FString inID, FString url) : StopTaskCounter(0)
{
	ssml = inSsml;
	id = inID;
	Thread = FRunnableThread::Create(this, TEXT("GeneralTTSThread"), 0, TPri_Normal);
	Endpoint = url;
}

GeneralTTSThread::~GeneralTTSThread() {
	delete Thread;
	Thread = NULL;
}


GeneralTTSThread* GeneralTTSThread::setup(FString ssml, FString id, FString Endpoint)
{
	if (!Runnable && FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new GeneralTTSThread(ssml, id, Endpoint);
	}
	return Runnable;
}

bool GeneralTTSThread::Init()
{
	return true;
}

uint32 GeneralTTSThread::Run()
{
	Synthesize();
	return 0;
}

void GeneralTTSThread::Stop()
{
	StopTaskCounter.Increment();
}

void GeneralTTSThread::EnsureCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}

void GeneralTTSThread::Shutdown()
{
	if (Runnable)
	{
		//Runnable->EnsureCompletion();
		//delete Runnable;
		Runnable = NULL;
	}
}

void GeneralTTSThread::Synthesize()
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

void GeneralTTSThread::OnHttpResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (bWasSuccessful && Response.IsValid())
	{
		FString ResponseContent = Response->GetContentAsString();
	}
	else
	{
	}
}

FDelegateHandle GeneralTTSThread::TTSResultAvailableSubscribeUser(FTTSResultAvailableDelegate& UseDelegate)
{
	return TTSResultAvailable.Add(UseDelegate);
}

void GeneralTTSThread::TTSResultAvailableUnsubscribeUser(FDelegateHandle DelegateHandle)
{
	TTSResultAvailable.Remove(DelegateHandle);
}

TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> GeneralTTSThread::ExecuteRequest(TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest, float LoopDelay)
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