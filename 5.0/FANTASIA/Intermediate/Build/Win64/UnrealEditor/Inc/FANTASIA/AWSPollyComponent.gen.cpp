// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "FANTASIA/Public/AWSPollyComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAWSPollyComponent() {}
// Cross Module References
	FANTASIA_API UClass* Z_Construct_UClass_UAWSPollyComponent_NoRegister();
	FANTASIA_API UClass* Z_Construct_UClass_UAWSPollyComponent();
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	UPackage* Z_Construct_UPackage__Script_FANTASIA();
	FANTASIA_API UScriptStruct* Z_Construct_UScriptStruct_FTTSTimedStruct();
	ENGINE_API UClass* Z_Construct_UClass_USoundWave_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UAudioComponent_NoRegister();
	FANTASIA_API UFunction* Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature();
	FANTASIA_API UEnum* Z_Construct_UEnum_FANTASIA_TTSVoiceType();
// End Cross Module References
	DEFINE_FUNCTION(UAWSPollyComponent::execAWSPollyGetNotifies)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_id);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FTTSTimedStruct>*)Z_Param__Result=P_THIS->AWSPollyGetNotifies(Z_Param_id);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAWSPollyComponent::execAWSPollyGetLipSync)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_id);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FTTSTimedStruct>*)Z_Param__Result=P_THIS->AWSPollyGetLipSync(Z_Param_id);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAWSPollyComponent::execAWSPollyGetSound)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_id);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(USoundWave**)Z_Param__Result=P_THIS->AWSPollyGetSound(Z_Param_id);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UAWSPollyComponent::execAWSPollySynthesize)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_ssml);
		P_GET_PROPERTY(FStrProperty,Z_Param_id);
		P_GET_UBOOL(Z_Param_getLipSync);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AWSPollySynthesize(Z_Param_ssml,Z_Param_id,Z_Param_getLipSync);
		P_NATIVE_END;
	}
	void UAWSPollyComponent::StaticRegisterNativesUAWSPollyComponent()
	{
		UClass* Class = UAWSPollyComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AWSPollyGetLipSync", &UAWSPollyComponent::execAWSPollyGetLipSync },
			{ "AWSPollyGetNotifies", &UAWSPollyComponent::execAWSPollyGetNotifies },
			{ "AWSPollyGetSound", &UAWSPollyComponent::execAWSPollyGetSound },
			{ "AWSPollySynthesize", &UAWSPollyComponent::execAWSPollySynthesize },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics
	{
		struct AWSPollyComponent_eventAWSPollyGetLipSync_Parms
		{
			FString id;
			TArray<FTTSTimedStruct> ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_id;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWSPollyComponent_eventAWSPollyGetLipSync_Parms, id), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FTTSTimedStruct, METADATA_PARAMS(nullptr, 0) }; // 2268810518
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWSPollyComponent_eventAWSPollyGetLipSync_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) }; // 2268810518
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::NewProp_id,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "DisplayName", "Get LipSync" },
		{ "Keywords", "AWS Plugin TTS" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAWSPollyComponent, nullptr, "AWSPollyGetLipSync", nullptr, nullptr, sizeof(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::AWSPollyComponent_eventAWSPollyGetLipSync_Parms), Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics
	{
		struct AWSPollyComponent_eventAWSPollyGetNotifies_Parms
		{
			FString id;
			TArray<FTTSTimedStruct> ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_id;
		static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWSPollyComponent_eventAWSPollyGetNotifies_Parms, id), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FTTSTimedStruct, METADATA_PARAMS(nullptr, 0) }; // 2268810518
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWSPollyComponent_eventAWSPollyGetNotifies_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) }; // 2268810518
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::NewProp_id,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "DisplayName", "Get Notifies" },
		{ "Keywords", "AWS Plugin TTS" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAWSPollyComponent, nullptr, "AWSPollyGetNotifies", nullptr, nullptr, sizeof(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::AWSPollyComponent_eventAWSPollyGetNotifies_Parms), Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics
	{
		struct AWSPollyComponent_eventAWSPollyGetSound_Parms
		{
			FString id;
			USoundWave* ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_id;
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWSPollyComponent_eventAWSPollyGetSound_Parms, id), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWSPollyComponent_eventAWSPollyGetSound_Parms, ReturnValue), Z_Construct_UClass_USoundWave_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::NewProp_id,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "DisplayName", "Get Sound" },
		{ "Keywords", "AWS Plugin TTS" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAWSPollyComponent, nullptr, "AWSPollyGetSound", nullptr, nullptr, sizeof(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::AWSPollyComponent_eventAWSPollyGetSound_Parms), Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics
	{
		struct AWSPollyComponent_eventAWSPollySynthesize_Parms
		{
			FString ssml;
			FString id;
			bool getLipSync;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_ssml;
		static const UECodeGen_Private::FStrPropertyParams NewProp_id;
		static void NewProp_getLipSync_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_getLipSync;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::NewProp_ssml = { "ssml", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWSPollyComponent_eventAWSPollySynthesize_Parms, ssml), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::NewProp_id = { "id", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AWSPollyComponent_eventAWSPollySynthesize_Parms, id), METADATA_PARAMS(nullptr, 0) };
	void Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::NewProp_getLipSync_SetBit(void* Obj)
	{
		((AWSPollyComponent_eventAWSPollySynthesize_Parms*)Obj)->getLipSync = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::NewProp_getLipSync = { "getLipSync", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, sizeof(bool), sizeof(AWSPollyComponent_eventAWSPollySynthesize_Parms), &Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::NewProp_getLipSync_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::NewProp_ssml,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::NewProp_id,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::NewProp_getLipSync,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::Function_MetaDataParams[] = {
		{ "Category", "TTS" },
		{ "DisplayName", "TTS Start" },
		{ "Keywords", "AWS Plugin TTS" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAWSPollyComponent, nullptr, "AWSPollySynthesize", nullptr, nullptr, sizeof(Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::AWSPollyComponent_eventAWSPollySynthesize_Parms), Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UAWSPollyComponent);
	UClass* Z_Construct_UClass_UAWSPollyComponent_NoRegister()
	{
		return UAWSPollyComponent::StaticClass();
	}
	struct Z_Construct_UClass_UAWSPollyComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Speaker_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_Speaker;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SynthesisReady_MetaData[];
#endif
		static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_SynthesisReady;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Voice_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Voice;
		static const UECodeGen_Private::FBytePropertyParams NewProp_voiceType_Underlying;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_voiceType_MetaData[];
#endif
		static const UECodeGen_Private::FEnumPropertyParams NewProp_voiceType;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AccessKey_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_AccessKey;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SecretAccessKey_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_SecretAccessKey;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAWSPollyComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UAWSPollyComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetLipSync, "AWSPollyGetLipSync" }, // 4153751247
		{ &Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetNotifies, "AWSPollyGetNotifies" }, // 1719402925
		{ &Z_Construct_UFunction_UAWSPollyComponent_AWSPollyGetSound, "AWSPollyGetSound" }, // 879327494
		{ &Z_Construct_UFunction_UAWSPollyComponent_AWSPollySynthesize, "AWSPollySynthesize" }, // 1833885860
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAWSPollyComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "AmazonWebServices" },
		{ "Comment", "//using namespace std;\n" },
		{ "IncludePath", "AWSPollyComponent.h" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
		{ "ToolTip", "using namespace std;" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Speaker_MetaData[] = {
		{ "Category", "Speech to Text" },
		{ "EditInline", "true" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Speaker = { "Speaker", nullptr, (EPropertyFlags)0x001000000008000c, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAWSPollyComponent, Speaker), Z_Construct_UClass_UAudioComponent_NoRegister, METADATA_PARAMS(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Speaker_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Speaker_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SynthesisReady_MetaData[] = {
		{ "Category", "Speech to Text" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SynthesisReady = { "SynthesisReady", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAWSPollyComponent, SynthesisReady), Z_Construct_UDelegateFunction_FANTASIA_SynthesizedEvent__DelegateSignature, METADATA_PARAMS(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SynthesisReady_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SynthesisReady_MetaData)) }; // 2338922286
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Voice_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Voice = { "Voice", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAWSPollyComponent, Voice), METADATA_PARAMS(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Voice_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Voice_MetaData)) };
	const UECodeGen_Private::FBytePropertyParams Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_voiceType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, nullptr, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_voiceType_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UECodeGen_Private::FEnumPropertyParams Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_voiceType = { "voiceType", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAWSPollyComponent, voiceType), Z_Construct_UEnum_FANTASIA_TTSVoiceType, METADATA_PARAMS(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_voiceType_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_voiceType_MetaData)) }; // 528394798
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_AccessKey_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_AccessKey = { "AccessKey", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAWSPollyComponent, AccessKey), METADATA_PARAMS(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_AccessKey_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_AccessKey_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SecretAccessKey_MetaData[] = {
		{ "Category", "Configuration" },
		{ "ModuleRelativePath", "Public/AWSPollyComponent.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SecretAccessKey = { "SecretAccessKey", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAWSPollyComponent, SecretAccessKey), METADATA_PARAMS(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SecretAccessKey_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SecretAccessKey_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAWSPollyComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Speaker,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SynthesisReady,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_Voice,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_voiceType_Underlying,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_voiceType,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_AccessKey,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAWSPollyComponent_Statics::NewProp_SecretAccessKey,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAWSPollyComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAWSPollyComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UAWSPollyComponent_Statics::ClassParams = {
		&UAWSPollyComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UAWSPollyComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UAWSPollyComponent_Statics::PropPointers),
		0,
		0x00A000A4u,
		METADATA_PARAMS(Z_Construct_UClass_UAWSPollyComponent_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAWSPollyComponent_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAWSPollyComponent()
	{
		if (!Z_Registration_Info_UClass_UAWSPollyComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAWSPollyComponent.OuterSingleton, Z_Construct_UClass_UAWSPollyComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UAWSPollyComponent.OuterSingleton;
	}
	template<> FANTASIA_API UClass* StaticClass<UAWSPollyComponent>()
	{
		return UAWSPollyComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAWSPollyComponent);
	struct Z_CompiledInDeferFile_FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_AWSPollyComponent_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_AWSPollyComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UAWSPollyComponent, UAWSPollyComponent::StaticClass, TEXT("UAWSPollyComponent"), &Z_Registration_Info_UClass_UAWSPollyComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAWSPollyComponent), 2730337443U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_AWSPollyComponent_h_3999184421(TEXT("/Script/FANTASIA"),
		Z_CompiledInDeferFile_FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_AWSPollyComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Jason_Plugins_FANTASIA_Source_FANTASIA_Public_AWSPollyComponent_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
