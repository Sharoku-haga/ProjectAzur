//==================================================================================================================================//
//!< @file		paDrawTask.h
//!< @brief		pa::DrawTaskクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017//11/20	更新履歴：
//==================================================================================================================================//

#ifndef PA_DRAW_TASK_H
#define PA_DRAW_TASK_H

#include <functional>

namespace pa
{

//===================================================================================//
//!< 描画のタスククラス
//===================================================================================//
class DrawTask final
{

public:
	/** 
	* Constructor
	* @param[in] priority タスクの優先度. 低い値が優先される
	* @param[in] func	  タスクに登録する描画関数のポインタ
	*/
	DrawTask(int priority
			, std::function<void()> func);

	/** Destructor */
	~DrawTask() = default;

	/** タスク管理者にタスクを登録する関数 */
	void RegisterTaskManager();

	/** タスク実行関数 */
	void Run();

	/** タスクの現在の優先度を元の優先度に戻す関数 */
	void ReturnOriginalPriority();

	/**
	* Setter 
	* @param[in] priority 設定したい優先度
	*/
	inline void SetCurrentPriority(int priority) { m_CurrentPriority = priority; }

	/**
	* Getter
	* @return このタスクの現在の優先度
	*/
	inline int GetCurrentPriority() { return m_CurrentPriority; }

private:
	int							m_OriginalPriority;		//!< インスタンス化したときに設定した優先度
	int							m_CurrentPriority;		//!< 現在の優先度
	std::function<void()>		m_DrawFunc;				//!< 描画関数

};	// class DrawTask

}	// namespace pa

#endif	// PA_DRAW_TASK_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
