// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FNLUResponse;
#ifdef FANTASIA_AzureNLUComponent_generated_h
#error "AzureNLUComponent.generated.h already included, missing '#pragma once' in AzureNLUComponent.h"
#endif
#define FANTASIA_AzureNLUComponent_generated_h

#define HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_21_DELEGATE \
struct _Script_FANTASIA_eventIncomingNLUEvent_Parms \
{ \
	FNLUResponse NLUResponse; \
}; \
static inline void FIncomingNLUEvent_DelegateWrapper(const FMulticastScriptDelegate& IncomingNLUEvent, FNLUResponse NLUResponse) \
{ \
	_Script_FANTASIA_eventIncomingNLUEvent_Parms Parms; \
	Parms.NLUResponse=NLUResponse; \
	IncomingNLUEvent.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_SPARSE_DATA
#define HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execAzureNLUStart);


#define HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execAzureNLUStart);


#define HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAzureNLUComponent(); \
	friend struct Z_Construct_UClass_UAzureNLUComponent_Statics; \
public: \
	DECLARE_CLASS(UAzureNLUComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UAzureNLUComponent)


#define HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_INCLASS \
private: \
	static void StaticRegisterNativesUAzureNLUComponent(); \
	friend struct Z_Construct_UClass_UAzureNLUComponent_Statics; \
public: \
	DECLARE_CLASS(UAzureNLUComponent, UActorComponent, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/FANTASIA"), NO_API) \
	DECLARE_SERIALIZER(UAzureNLUComponent)


#define HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAzureNLUComponent(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAzureNLUComponent) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAzureNLUComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAzureNLUComponent); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAzureNLUComponent(UAzureNLUComponent&&); \
	NO_API UAzureNLUComponent(const UAzureNLUComponent&); \
public:


#define HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAzureNLUComponent(UAzureNLUComponent&&); \
	NO_API UAzureNLUComponent(const UAzureNLUComponent&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAzureNLUComponent); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAzureNLUComponent); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UAzureNLUComponent)


#define HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_PRIVATE_PROPERTY_OFFSET
#define HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_23_PROLOG
#define HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_SPARSE_DATA \
	HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_RPC_WRAPPERS \
	HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_INCLASS \
	HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_PRIVATE_PROPERTY_OFFSET \
	HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_SPARSE_DATA \
	HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_INCLASS_NO_PURE_DECLS \
	HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h_26_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> FANTASIA_API UClass* StaticClass<class UAzureNLUComponent>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID HostProject_Plugins_FANTASIA_Source_FANTASIA_Public_AzureNLUComponent_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
