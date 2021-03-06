﻿//==================================================================================================================================//
//!< @file		paEventManager.cpp
//!< @brief		pa::EventManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/11/21	更新履歴：2017/11/22
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paEventManager.h"
#include "paEventListener.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

void EventManager::Initialize()
{
	m_CurrentEvent.clear();
	std::deque<std::string>().swap(m_CurrentEvent);

	for(auto& pListener : m_pEventListener)
	{
		pListener.second.clear();
		std::list<sl::WeakPtr<EventListener>>().swap(pListener.second);
	}

	m_pEventListener.clear();
}

void EventManager::Update()
{
	if(m_CurrentEvent.empty())
	{	// イベントが空なら即戻す
		return;
	}
	else
	{	// イベントがある場合はそれそれ対応するリスナーに通知する
		for(auto& currentEvent : m_CurrentEvent)
		{
			std::list<sl::WeakPtr<EventListener>>& pListeners = m_pEventListener[currentEvent];

			sl::SharedPtr<EventListener> pTmp;
			for(auto& pListener : pListeners)
			{
				pTmp = pListener.Lock();
				pTmp->ReceiveEvent(currentEvent);
			}
		}

		m_CurrentEvent.clear();
		std::deque<std::string>().swap(m_CurrentEvent);
	}
}

void EventManager::RegisterEventListener(const std::string& rEventName, sl::SharedPtr<EventListener> pListener)
{
	m_pEventListener[rEventName].emplace_back(pListener);
}

void EventManager::DeleteEvent(const std::string& rEventName)
{
	m_pEventListener[rEventName].clear();
	std::list<sl::WeakPtr<EventListener>>().swap(m_pEventListener[rEventName]);
	m_pEventListener.erase(rEventName);
}

void EventManager::DeleteEventListener(const std::string& rEventName, sl::SharedPtr<EventListener> pListener)
{
	std::list<sl::WeakPtr<EventListener>>& pListeners = m_pEventListener[rEventName];
	
	for(auto& itr = pListeners.begin(); itr != pListeners.end(); ++itr )
	{
		if((*itr).Get() == pListener.Get())
		{
			pListeners.erase(itr);
			break;
		}
	}
}

void EventManager::TriggerSynEvent(const std::string& rEventName)
{
	std::list<sl::WeakPtr<EventListener>>& pListeners = m_pEventListener[rEventName];

	sl::SharedPtr<EventListener> pTmp;		// WeakPtrのLockを受けるための入れ物
	for(auto& pListener: pListeners)
	{
		pTmp = pListener.Lock();
		pTmp->CallSynEventFunc(rEventName);
	}
}

void EventManager::ReceiveEvent(const std::string& rEventName)
{
	for(auto& currentEvent : m_CurrentEvent)
	{
		if(currentEvent == rEventName)
		{	// すでにイベントが登録されていたらreturn
			return;
		}
	}
	m_CurrentEvent.push_back(rEventName);
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
