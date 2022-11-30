// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AzureASRComponent.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef FANTASIA_AzureASRComponent_generated_h
#error "AzureASRComponent.generated.h already included, missing '#pragma once' in AzureASRComponent.h"
#endif
#define FANTASIA_AzureASRComponent_generated_h

#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_21_DELEGATE \
struct _Script_FANTASIA_eventIncomingASREvent_Parms \
{ \
	FString message; \
}; \
static inline void FIncomingASREvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingASREvent, const FString& message) \
{ \
	_Script_FANTASIA_eventIncomingASREvent_Parms Parms; \
	Parms.message=message; \
	IncomingASREvent.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_SPARSE_DATA
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execAzureASRStop); \
	DECLARE_FUNCTION(execAzureASRStart);


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execAzureASRStop); \
	DECLARE_FUNCTION(execAzureASRStart);


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_ACCESSORS
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAzureASRComponent(); \
	friend struct Z_Construct_UClass_UAzureASRComponent_Statics; \
public: \
	DECLARE_CLASS(UAzureASRComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UAzureASRComponent)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_INCLASS \
private: \
	static void StaticRegisterNativesUAzureASRComponent(); \
	friend struct Z_Construct_UClass_UAzureASRComponent_Statics; \
public: \
	DECLARE_CLASS(UAzureASRComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UAzureASRComponent)


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAzureASRComponent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAzureASRComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAzureASRComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAzureASRComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAzureASRComponent(UAzureASRComponent&&); \
	NO_API UAzureASRComponent(const UAzureASRComponent&); \
public: \
	NO_API virtual ~UAzureASRComponent();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAzureASRComponent(UAzureASRComponent&&); \
	NO_API UAzureASRComponent(const UAzureASRComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAzureASRComponent); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAzureASRComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UAzureASRComponent) \
	NO_API virtual ~UAzureASRComponent();


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_23_PROLOG
#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_SPARSE_DATA \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_RPC_WRAPPERS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_ACCESSORS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_INCLASS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_SPARSE_DATA \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_ACCESSORS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_INCLASS_NO_PURE_DECLS \
	FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h_26_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UAzureASRComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_Perforce_FANTASIADevelopment_Plugins_FANTASIA_Source_FANTASIA_Public_AzureASRComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
