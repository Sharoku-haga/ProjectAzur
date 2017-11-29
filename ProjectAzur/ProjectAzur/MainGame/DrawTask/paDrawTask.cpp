//==================================================================================================================================//
//!< @file		paDrawTask.cpp
//!< @brief		pa::DrawTaskクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017//11/20	更新履歴：2017//11/29
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paDrawTask.h"
#include "paDrawTaskManager.h"

namespace pa
{

/* FunctionPrototype ------------------------------------------------------------------------------------------ */

void EmptyFunc();

/* Public Functions ------------------------------------------------------------------------------------------- */

DrawTask::DrawTask(int priority
					, std::function<void()> func)
	: m_OriginalPriority(priority)
	, m_CurrentPriority(priority)
	, m_CurrentFunc(func)
	, m_DrawFunc(func)
{
	DrawTaskManager::Instance().RegisterDrawTask(this);
}

DrawTask::~DrawTask()
{
	DrawTaskManager::Instance().DeleteTask(this);
}

void DrawTask::Run()
{
	m_CurrentFunc();
}

void DrawTask::Activate()
{
	m_CurrentFunc = m_DrawFunc;
}

void DrawTask::Deactivate()
{
	m_CurrentFunc = EmptyFunc;
}

void DrawTask::ReturnOriginalPriority()
{
	DrawTaskManager::Instance().DeleteTask(this);
	m_CurrentPriority = m_OriginalPriority;
	DrawTaskManager::Instance().RegisterDrawTask(this);
}

void DrawTask::ChangeCurrentPriority(int priority)
{
	DrawTaskManager::Instance().DeleteTask(this);
	m_CurrentPriority = priority;
	DrawTaskManager::Instance().RegisterDrawTask(this);
}

/* Global Functions ------------------------------------------------------------------------------------------- */

// タスクが非アクティブ状態(Deactivateをよんだあと)の際によばれる関数
void EmptyFunc()
{
	return;
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
