//==================================================================================================================================//
//!< @file		paDrawTask.cpp
//!< @brief		pa::DrawTaskクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017//11/20	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paDrawTask.h"
#include "paDrawTaskManager.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DrawTask::DrawTask(int priority
					, std::function<void()> func)
	: m_OriginalPriority(priority)
	, m_CurrentPriority(priority)
	, m_DrawFunc(func)
{}

void DrawTask::RegisterTaskManager()
{
	DrawTaskManager::Instance().RegisterDrawTask(this);
}

void DrawTask::Run()
{
	m_DrawFunc();
}

void DrawTask::ReturnOriginalPriority()
{
	m_CurrentPriority = m_OriginalPriority;
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
