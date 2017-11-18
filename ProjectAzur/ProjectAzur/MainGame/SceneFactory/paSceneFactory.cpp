//==================================================================================================================================//
//!< @file		paSceneFactory.cpp
//!< @brief		pa::SceneFactoryクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/11/18	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paSceneFactory.h"
#include "sl/Library/Scene/slSceneBase.h"
#include "../TitleScene/paTitleScene.h"
#include "../GameScene/paGameScene.h"
#include "../ResultScene/paResultScene.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

SceneFactory::SceneFactory()
{}

SceneFactory::~SceneFactory()
{}

sl::SceneBase*	SceneFactory::CreateScene(const std::string& rSceneName)
{
	sl::SceneBase* pScene = nullptr;

	if(rSceneName == "TitleScene")
	{
		pScene = new TitleScene();
	}
	else if(rSceneName == "GameScene")
	{
		pScene = new GameScene();
	}
	else if(rSceneName == "ResultScene")
	{
		pScene = new ResultScene();
	}

	return pScene;
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
