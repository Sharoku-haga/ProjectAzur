//==================================================================================================================================//
//!< @file		slSceneManager.h		
//!< @brief		sl::SceneManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/15	更新履歴：2017/12/02
//==================================================================================================================================//

#ifndef SL_SCENE_MANAGER_H
#define SL_SCENE_MANAGER_H

#include <string>
#include "../SmartPointer/UniquePtr/slUniquePtr.h"
#include "../Singleton/slBasicSingleton.h"
#include "slSceneBase.h"
#include "slISceneFactory.h"
#include "slISceneDeletor.h"

namespace sl
{

//===================================================================================//
//!< シーン(SceneBase)を管理するクラス
//!< Singletonパターン
//===================================================================================//
class SceneManager : public BasicSingleton<SceneManager>
{

public:
	/**
	* 初期化関数
	* @param		pFactory			ISceneFactoryクラスのインスタンスへのポインタ
	* @param		pDeletor			ISceneDeletorクラスのインスタンスへのポインタ
	* @param[in]	rStartSceneName		開始したいシーンの名前
	*/
	void Initialize(UniquePtr<ISceneFactory> pFactory
				, UniquePtr<ISceneDeletor> pDeletor
				, const std::string& rStartSceneName);

	/**
	* 更新関数
	* @return シーン管理が終了したかどうか true→終了した false →終了していない
	*/
	bool Update();

	/**
	* シーンを変更する関数
	* @prama[in]  rSceneName シーン名
	*/
	void ChangeScene(const std::string& rSceneName);

	/** シーン管理を終了する関数 */
	void End();

	/** 破棄関数 */
	void Finalize();

private:
	friend class StaticCreation<SceneManager>;

	/** このクラスの状態の列挙 */
	enum STATE
	{
		CREATE_SCENE,		//!< シーン生成
		EXECUTE_SCENE,		//!< シーン実行
		DESTROY_SCENE,		//!< シーン破棄

	};	// enum STATE

	UniquePtr<SceneBase>		m_pScene;				//!< SceneBaseクラスのインスタンスへのポインタ
	UniquePtr<ISceneFactory>	m_pFactory;				//!< ISceneFactoryクラスのインスタンスへのポインタ
	UniquePtr<ISceneDeletor>	m_pDeletor;				//!< ISceneDeletorクラスのインスタンスへのポインタ
	STATE						m_State;				//!< このクラスの状態を格納する変数
	std::string					m_CurrentSceneName;		//!< 現在のシーン名
	std::string					m_NextSceneName;		//!< 次のシーン名
	bool						m_IsEnd;				//!< 終了かどうかのフラグ true→終了 false → 終了していない

	/** Constructor */
	SceneManager() = default;

	/** Destructor */
	~SceneManager();

};	// class SceneManager

}	// namespace sl

#endif	// SL_SCENE_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
