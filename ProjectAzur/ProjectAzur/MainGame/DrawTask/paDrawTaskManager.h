//==================================================================================================================================//
//!< @file		paDrawTaskManager.h
//!< @brief		pa::DrawTaskManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/20	更新履歴：2017/11/29
//==================================================================================================================================//

#ifndef PA_DRAW_TASK_MANAGER_H
#define PA_DRAW_TASK_MANAGER_H

#include <unordered_map>    
#include <vector>
#include "sl/Library/Singleton/slBasicSingleton.h"
#include "sl/Library/Utility/slDefine.h"

namespace pa
{

class DrawTask;

//===================================================================================//
//!< 描画タスクを管理するクラス
//===================================================================================//
class DrawTaskManager final : public sl::BasicSingleton<DrawTaskManager>
{

public:
	/**
	* 初期化関数.
	* @param[in] priorityNumMax タスク優先度番号の最大値
	*/
	void Initialize(int priorityNumMax);

	/**
	* 描画タスクを登録する関数
	* @param[in] pTask	登録したい描画タスク
	*/
	void RegisterDrawTask(DrawTask*	pTask);

	/** 登録している描画タスクを実行する関数 */
	void Run();

	/**
	* 指定した描画タスクを削除する関数
	* @param[in] pTask	削除したい描画タスク
	*/
	void DeleteTask(DrawTask* pTask);

	/** 登録している描画タスクを全て削除する関数 */
	void DeleteALL();

private:
	friend class sl::StaticCreation<DrawTaskManager>;

	std::unordered_map<int, std::vector<DrawTask*>>	m_DrawTasks;			//!< 登録している描画タスクmap
	int												m_PriorityNumMax;		//!< 優先度番号の最大値

	/** Constructor */
	DrawTaskManager() = default;

	/** Destructor */
	~DrawTaskManager() = default;

	SL_DISALLOW_COPY_AND_ASSIGN(DrawTaskManager);

};	// DrawTaskManager

}	// namespace pa

#endif	// PA_DRAW_TASK_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
