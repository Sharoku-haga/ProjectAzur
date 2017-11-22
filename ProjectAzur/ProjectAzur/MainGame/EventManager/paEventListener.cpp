//==================================================================================================================================//
//!< @file		paEventListener.cpp
//!< @brief		pa::EventListenerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/11/21	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paEventListener.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

void EventListener::RegisterSynEventFunc(const std::string& rEventName
										, const std::function<void(void)>& rCallBackFunc)
{
	m_SynEventFunc[rEventName] = rCallBackFunc;
}

void EventListener::CallSynEventFunc(const std::string& rEventName)
{
	m_SynEventFunc[rEventName]();
}

void EventListener::DeleteCurrentEvent(void)
{
	m_CurrentEvent.clear();
	std::deque<std::string>().swap(m_CurrentEvent);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void EventListener::ReceiveEvent(const std::string& rEventName)
{
	m_CurrentEvent.push_back(rEventName);
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
