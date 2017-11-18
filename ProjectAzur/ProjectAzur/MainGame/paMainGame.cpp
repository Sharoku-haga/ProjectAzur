//==================================================================================================================================//
//!< @file		paMainGame.cpp	
//!< @brief		pa::MainGameクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017//11/17	更新履歴：2017/11/18
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paMainGame.h"
#include "sl/Library/Utility/slDefine.h"
#include "sl/Library/Graphics/slGraphics.h"
#include "sl/Library/InputDevice/slInputDevice.h"
#include "sl/Library/Sound/slSound.h"
#include "sl/Library/Scene/slScene.h"
#include "SceneFactory/paSceneFactory.h"
#include "SceneDeletor/paSceneDeletor.h"

/* Define ----------------------------------------------------------------------------------------------------- */

#define WIN_TITLE "ProjectAzur"
#define WIN_WIDTH 1920
#define WIN_HEGHT 1080

namespace pa
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const sl::fRect			BackBufferSize = {0.0f, 0.0f, 1920.f, 1080.f};		// バックバッファのサイズ

#ifdef _DEBUG
	const	std::string StartSceneName = "TitleScene";						// 開始シーンネーム
#else
	const	std::string StartSceneName = "TitleScene";						// 開始シーンネーム
#endif

}

/* Public Functions ------------------------------------------------------------------------------------------- */

bool MainGame::Initialize()
{
	bool result = false;

	// ウィンドウの作成
	sl::WindowCreationData data;
	data.m_pTitle	= WIN_TITLE;
	data.m_Width	= WIN_WIDTH;
	data.m_Height	= WIN_HEGHT;
	m_pWindow = sl::CreateMainWindow(data);

	// グラフィックスライブラリの初期化
	sl::DX11GraphicsLibrary::Instance().Init(m_pWindow->GetWindowHandle(), BackBufferSize);

	// インプットデバイスライブラリの初期化
	result = sl::IInputDeviceLibrary::Instance().Initialize(m_pWindow->GetWindowHandle());
	if(RESULT_FALSE(result))
	{
		return false;
	}

	// サウンドライブラリの初期化
	result = sl::ISoundLibrary::Instance().Initialize(m_pWindow->GetWindowHandle());
	if(RESULT_FALSE(result))
	{
		return false;
	}

	//シーンマネージャー関連処理
	sl::SceneManager::Instance().Initialize(sl::UniquePtr<sl::ISceneFactory>(new SceneFactory())
											, sl::UniquePtr<sl::ISceneDeletor>(new SceneDeletor())
											, StartSceneName);

	// カスタマイズインプット処理

	return true;
}

void MainGame::Loop()
{
	while(RESULT_FALSE(m_pWindow->Update()))
	{
		if(sl::SceneManager::Instance().Update())
		{
			break;
		}
	}
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
