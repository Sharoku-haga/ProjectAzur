//==================================================================================================================================//
//!< @file		paSceneDeletor.h
//!< @brief		pa::SceneDeletorクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/18	更新履歴：
//==================================================================================================================================//

#ifndef PA_SCENE_DELETOR_H
#define PA_SCENE_DELETOR_H

#include "sl/Library/Scene/slISceneDeletor.h"

namespace sl
{
class SceneBase;
}	// namespace sl

namespace pa
{

//===================================================================================//
//!< シーンの破棄を担当するクラス
//===================================================================================//
class SceneDeletor : public sl::ISceneDeletor
{

public:
	/**
	* シーンを破棄する関数
	* @param pScene 破棄したいsl::SceneBaseクラスのインスタンスへのポインタ
	*/
	virtual void DestroyScene(sl::SceneBase* pScene)override;

	/** Constructor */
	SceneDeletor() = default;

	/** Destructor */
	~SceneDeletor() = default;

};	// class SceneDeletor

}	// namespace pa

#endif	// PA_SCENE_DELETOR_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
