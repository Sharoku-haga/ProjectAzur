﻿//==================================================================================================================================//
//!< @file		paResultScene.h
//!< @brief		pa::ResultSceneクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/18	更新履歴：
//==================================================================================================================================//

#ifndef PA_RESULT_SCENE_H
#define PA_RESULT_SCENE_H

#include "sl/Library/Scene/slSceneBase.h"

namespace pa
{

//===================================================================================//
//!< リザルトシーンクラス
//===================================================================================//
class ResultScene : public sl::SceneBase
{

public:
	/** Constructor */
	ResultScene();

	/** Destructor */
	~ResultScene();
	
	/** シーンの最初に行う処理関数 */
	virtual void Enter()override;

	/** シーンの最後に行う処理関数 */
	virtual void Exit()override;

private:
	/** 制御関数 */
	virtual void Control()override;

	/** 描画関数 */
	virtual void Draw()override;

};	// class ResultScene

}	// namespace pa

#endif	// PA_RESULT_SCENE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
