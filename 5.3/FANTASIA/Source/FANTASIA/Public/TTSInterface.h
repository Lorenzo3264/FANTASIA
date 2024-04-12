// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TTSInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UTTSInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FANTASIA_API ITTSInterface
{
	GENERATED_BODY()

public:
	/**
	* To obtain the synthesis results
	*
	*	@param response - synthesis results
	*	@param id - buffer synthesis id
	*
	**/
	virtual void getResult(FTTSData results, FString id) = 0;


	/**
	* To manage speech synthesis
	*
	*	@param ssml - synthesis data
	*	@param id - buffer synthesis id
	*
	**/
	UFUNCTION(Category = "TTS")
	virtual void TTSSynthesize(FString ssml, FString id) PURE_VIRTUAL(ITTSInterface::TTSSynthesize, );


	/**
	* To format the synthesis result into audio playable by Unreal
	*
	*	buffer synthesis id
	*
	**/
	UFUNCTION(Category = "TTS")
	virtual USoundBase* TTSGetSound(FString id) PURE_VIRTUAL(ITTSInterface::TTSGetSound, return nullptr;);
};
