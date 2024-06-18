// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "../../../../../../Source/FANTASIA/Public/Audio2FaceComponent.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAudio2FaceComponent() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UActorComponent();
	ENGINE_API UClass* Z_Construct_UClass_USoundWave_NoRegister();
	FANTASIA_API UClass* Z_Construct_UClass_UAudio2FaceComponent();
	FANTASIA_API UClass* Z_Construct_UClass_UAudio2FaceComponent_NoRegister();
	UPackage* Z_Construct_UPackage__Script_FANTASIA();
// End Cross Module References
	DEFINE_FUNCTION(UAudio2FaceComponent::execReadAudioFile)
	{
		P_GET_OBJECT(USoundWave,Z_Param_SoundWave);
		P_GET_UBOOL(Z_Param_tts);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ReadAudioFile(Z_Param_SoundWave,Z_Param_tts);
		P_NATIVE_END;
	}
	void UAudio2FaceComponent::StaticRegisterNativesUAudio2FaceComponent()
	{
		UClass* Class = UAudio2FaceComponent::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "ReadAudioFile", &UAudio2FaceComponent::execReadAudioFile },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile_Statics
	{
		struct Audio2FaceComponent_eventReadAudioFile_Parms
		{
			USoundWave* SoundWave;
			bool tts;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_SoundWave;
		static void NewProp_tts_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_tts;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile_Statics::NewProp_SoundWave = { "SoundWave", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(Audio2FaceComponent_eventReadAudioFile_Parms, SoundWave), Z_Construct_UClass_USoundWave_NoRegister, METADATA_PARAMS(0, nullptr) };
	void Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile_Statics::NewProp_tts_SetBit(void* Obj)
	{
		((Audio2FaceComponent_eventReadAudioFile_Parms*)Obj)->tts = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile_Statics::NewProp_tts = { "tts", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(Audio2FaceComponent_eventReadAudioFile_Parms), &Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile_Statics::NewProp_tts_SetBit, METADATA_PARAMS(0, nullptr) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile_Statics::NewProp_SoundWave,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile_Statics::NewProp_tts,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile_Statics::Function_MetaDataParams[] = {
		{ "Category", "Audio2Face" },
		{ "DisplayName", "NvidiaReadAudioFile" },
		{ "Keywords", "Nvidia Plugin" },
		{ "ModuleRelativePath", "Public/Audio2FaceComponent.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UAudio2FaceComponent, nullptr, "ReadAudioFile", nullptr, nullptr, Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile_Statics::Audio2FaceComponent_eventReadAudioFile_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile_Statics::Function_MetaDataParams) };
	static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile_Statics::PropPointers) < 2048);
	static_assert(sizeof(Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile_Statics::Audio2FaceComponent_eventReadAudioFile_Parms) < MAX_uint16);
	UFunction* Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UAudio2FaceComponent);
	UClass* Z_Construct_UClass_UAudio2FaceComponent_NoRegister()
	{
		return UAudio2FaceComponent::StaticClass();
	}
	struct Z_Construct_UClass_UAudio2FaceComponent_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PlayerA2F_name_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_PlayerA2F_name;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_server_url_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_server_url;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAudio2FaceComponent_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UActorComponent,
		(UObject* (*)())Z_Construct_UPackage__Script_FANTASIA,
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAudio2FaceComponent_Statics::DependentSingletons) < 16);
	const FClassFunctionLinkInfo Z_Construct_UClass_UAudio2FaceComponent_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UAudio2FaceComponent_ReadAudioFile, "ReadAudioFile" }, // 1701972595
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAudio2FaceComponent_Statics::FuncInfo) < 2048);
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAudio2FaceComponent_Statics::Class_MetaDataParams[] = {
		{ "BlueprintSpawnableComponent", "" },
		{ "ClassGroupNames", "Custom" },
		{ "IncludePath", "Audio2FaceComponent.h" },
		{ "ModuleRelativePath", "Public/Audio2FaceComponent.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAudio2FaceComponent_Statics::NewProp_PlayerA2F_name_MetaData[] = {
		{ "Category", "Audio2Face" },
		{ "ModuleRelativePath", "Public/Audio2FaceComponent.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAudio2FaceComponent_Statics::NewProp_PlayerA2F_name = { "PlayerA2F_name", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudio2FaceComponent, PlayerA2F_name), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAudio2FaceComponent_Statics::NewProp_PlayerA2F_name_MetaData), Z_Construct_UClass_UAudio2FaceComponent_Statics::NewProp_PlayerA2F_name_MetaData) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAudio2FaceComponent_Statics::NewProp_server_url_MetaData[] = {
		{ "Category", "Audio2Face" },
		{ "ModuleRelativePath", "Public/Audio2FaceComponent.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UAudio2FaceComponent_Statics::NewProp_server_url = { "server_url", nullptr, (EPropertyFlags)0x0010000000000001, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UAudio2FaceComponent, server_url), METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAudio2FaceComponent_Statics::NewProp_server_url_MetaData), Z_Construct_UClass_UAudio2FaceComponent_Statics::NewProp_server_url_MetaData) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAudio2FaceComponent_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudio2FaceComponent_Statics::NewProp_PlayerA2F_name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAudio2FaceComponent_Statics::NewProp_server_url,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAudio2FaceComponent_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAudio2FaceComponent>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UAudio2FaceComponent_Statics::ClassParams = {
		&UAudio2FaceComponent::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UAudio2FaceComponent_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UAudio2FaceComponent_Statics::PropPointers),
		0,
		0x00B000A4u,
		METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAudio2FaceComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UAudio2FaceComponent_Statics::Class_MetaDataParams)
	};
	static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAudio2FaceComponent_Statics::PropPointers) < 2048);
	UClass* Z_Construct_UClass_UAudio2FaceComponent()
	{
		if (!Z_Registration_Info_UClass_UAudio2FaceComponent.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAudio2FaceComponent.OuterSingleton, Z_Construct_UClass_UAudio2FaceComponent_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UAudio2FaceComponent.OuterSingleton;
	}
	template<> FANTASIA_API UClass* StaticClass<UAudio2FaceComponent>()
	{
		return UAudio2FaceComponent::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAudio2FaceComponent);
	UAudio2FaceComponent::~UAudio2FaceComponent() {}
	struct Z_CompiledInDeferFile_FID_Users_ynapa_Documents_Unreal_Projects_A2F_Plugin_Plugins_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_ynapa_Documents_Unreal_Projects_A2F_Plugin_Plugins_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UAudio2FaceComponent, UAudio2FaceComponent::StaticClass, TEXT("UAudio2FaceComponent"), &Z_Registration_Info_UClass_UAudio2FaceComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAudio2FaceComponent), 283239260U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_ynapa_Documents_Unreal_Projects_A2F_Plugin_Plugins_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_3883876018(TEXT("/Script/FANTASIA"),
		Z_CompiledInDeferFile_FID_Users_ynapa_Documents_Unreal_Projects_A2F_Plugin_Plugins_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_ynapa_Documents_Unreal_Projects_A2F_Plugin_Plugins_FANTASIA_Source_FANTASIA_Public_Audio2FaceComponent_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
