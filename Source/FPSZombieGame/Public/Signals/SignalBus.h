// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SignalBus.generated.h"

class USignal;

/**
 * 
 */
DECLARE_EVENT_OneParam(USignalBus,SignalEvent,TObjectPtr<USignal>)
UCLASS()
class FPSZOMBIEGAME_API USignalBus : public UObject
{
	GENERATED_BODY()


	TMap<FName,SignalEvent> Signals = {};
public:
	template <typename T>
	void AddSignal();

	template <typename T>
	void InvokeSignal(T* Signal);

	template <typename T>
	SignalEvent* GetSignalEventPtr();
};

template <typename T>
void USignalBus::AddSignal()
{
	Signals.Add(TNameOf<T>::GetName(), {});
}

template <typename T>
void USignalBus::InvokeSignal(T* Signal)
{
	if(SignalEvent* signalEvent = GetSignalEventPtr<T>())
	{
		signalEvent->Broadcast(Signal);
	}
}

template <typename T>
SignalEvent* USignalBus::GetSignalEventPtr()
{
	if(Signals.Contains(TNameOf<T>::GetName()))
	{
		return	Signals.Find(TNameOf<T>::GetName());
	}

	return nullptr;
}

Expose_TNameOf(USignalBus);
