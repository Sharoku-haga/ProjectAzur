//==================================================================================================================================//
//!< @file		paDrawTaskManager.cpp
//!< @brief		pa::DrawTaskManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/11/20	更新履歴：2017/11/29
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paDrawTaskManager.h"
#include "paDrawTask.h"

namespace pa
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

constexpr int		PriorityNumMin = 0;		// 優先度番号の最小値

}

/* Public Functions ------------------------------------------------------------------------------------------- */

void DrawTaskManager::Initialize(int priorityNumMax)
{
	m_PriorityNumMax = priorityNumMax;
}

void DrawTaskManager::RegisterDrawTask(DrawTask*	pTask)
{
	m_DrawTasks[pTask->GetCurrentPriority()].push_back(pTask);
}

void DrawTaskManager::Run()
{
	for(int i = PriorityNumMin; i <= m_PriorityNumMax; ++i)
	{
		for(auto& pTask : m_DrawTasks[i])
		{
			pTask->Run();
		}
	}
}

void DrawTaskManager::DeleteTask(DrawTask* pTask)
{
	std::vector<DrawTask*>& pDrawTasks = m_DrawTasks[pTask->GetCurrentPriority()];

	for(auto& itr = pDrawTasks.begin(); itr != pDrawTasks.end(); ++itr)
	{
		if((*itr) == pTask)
		{
			pDrawTasks.erase(itr);
			break;
		}
	}
}

void DrawTaskManager::DeleteALL()
{
	for(int i = PriorityNumMin; i <= m_PriorityNumMax; ++i)
	{
		m_DrawTasks[i].clear();
		std::vector<DrawTask*>().swap(m_DrawTasks[i]);
	}
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
