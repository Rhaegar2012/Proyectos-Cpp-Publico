#pragma once
#ifndef OBSERVER_H
#define OBSERVER_H
#include "Enums.h"
#include<iostream>

using namespace std;
template <typename TObserver,typename TEventType,typename TEventData>
class Observer
{
	public:
		virtual ~Observer() {};
		virtual void OnNotify(TObserver& observer, TEventType event, TEventData eventData) {};
};
#endif

