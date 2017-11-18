//==================================================================================================================================//
//!< @file		paSceneFactory.h
//!< @brief		pa::SceneFactoryクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/18	更新履歴：
//==================================================================================================================================//

#ifndef PA_SCENE_FACTORY_H
#define	PA_SCENE_FACTORY_H

#include "sl/Library/Scene/slISceneFactory.h"

namespace sl
{
class SceneBase;
}

namespace pa
{

//===================================================================================//
//!< シーンを生成するクラス
//===================================================================================//
class SceneFactory : public sl::ISceneFactory
{

public:
	/** Constructor */
	SceneFactory();

	/** Destructor */
	~SceneFactory();

	/**
	* シーンを生成する関数
	* @param[in] rSceneName		生成したいシーンの名前
	*/
	virtual sl::SceneBase*	CreateScene(const std::string& rSceneName)override;

};	// class SceneFactory

}	// namespace pa

#endif	// PA_SCENE_FACTORY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
