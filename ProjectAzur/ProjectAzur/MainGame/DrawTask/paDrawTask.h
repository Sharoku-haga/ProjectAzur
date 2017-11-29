//==================================================================================================================================//
//!< @file		paDrawTask.h
//!< @brief		pa::DrawTaskクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017//11/20	更新履歴：2017//11/29
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
	* Manager登録もここで行う
	* @param[in] priority タスクの優先度. 低い値が優先される
	* @param[in] func	  タスクに登録する描画関数のポインタ
	*/
	DrawTask(int priority
			, std::function<void()> func);

	/** Destructor */
	~DrawTask();

	/** タスク実行関数 */
	void Run();

	/** タスクをアクティブにする関数 */
	void Activate();

	/** タスクを非アクティブにする関数 */
	void Deactivate();

	/** タスクの現在の優先度を元の優先度に戻す関数 */
	void ReturnOriginalPriority();

	/**
	* 現在のタスクの優先度を変更する関数
	* @param[in] priority 設定したい優先度
	*/
	void ChangeCurrentPriority(int priority);

	/**
	* Getter
	* @return このタスクの現在の優先度
	*/
	inline int GetCurrentPriority() { return m_CurrentPriority; }

private:
	int							m_OriginalPriority;		//!< インスタンス化したときに設定した優先度
	int							m_CurrentPriority;		//!< 現在の優先度
	std::function<void()>		m_CurrentFunc;			//!< 現在のタスク関数
	std::function<void()>		m_DrawFunc;				//!< 描画関数

};	// class DrawTask

}	// namespace pa

#endif	// PA_DRAW_TASK_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
