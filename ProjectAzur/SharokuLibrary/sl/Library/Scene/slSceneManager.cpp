//==================================================================================================================================//
//!< @file		slSceneManager.cpp		
//!< @brief		sl::SceneManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/11/15	更新履歴：2017/11/17
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slSceneManager.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

void SceneManager::Initialize(UniquePtr<ISceneFactory> pFactory
				, UniquePtr<ISceneDeletor> pDeletor
				, const std::string& rStartSceneName)
{
	m_pScene.Reset();
	m_pFactory.Reset(pFactory.Release());
	m_pDeletor.Reset(pDeletor.Release());
	m_State = CREATE_SCENE;
	m_CurrentSceneName = rStartSceneName;
	m_NextSceneName = rStartSceneName;
	m_IsEnd = false;
}

bool SceneManager::Update()
{
	switch(m_State)
	{
	case CREATE_SCENE:
		if(m_NextSceneName == "End")
		{
			m_IsEnd = true;
		}
		else
		{
			m_pScene.Reset(m_pFactory->CreateScene(m_NextSceneName));
			m_pScene->Enter();
			m_CurrentSceneName = m_NextSceneName;
			m_State = EXECUTE_SCENE;
		}
		break;

	case EXECUTE_SCENE:
		m_pScene->Execute();
		
		if(m_NextSceneName != m_CurrentSceneName)
		{
			m_State = DESTROY_SCENE;
		}
		break;

	case DESTROY_SCENE:
		m_pScene->Exit();
		m_pDeletor->DestroyScene(m_pScene.Release());
		m_State = CREATE_SCENE;
		break;

	default:
		// do nothing
		break;
	}

	return m_IsEnd;
}

void SceneManager::ChangeScene(const std::string& rSceneName)
{
	m_NextSceneName = rSceneName;
}

void SceneManager::End()
{
	m_NextSceneName = "End";
}

/* Private Functions------------------------------------------------------------------------------------------- */

SceneManager::~SceneManager()
{
	if(m_pScene.Get() != nullptr)
	{
		m_pDeletor->DestroyScene(m_pScene.Release());
	}
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
