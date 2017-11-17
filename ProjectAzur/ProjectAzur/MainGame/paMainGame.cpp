//==================================================================================================================================//
//!< @file		paMainGame.h	
//!< @brief		pa::MainGameクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017//11/17	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paMainGame.h"
#include "sl/Library/Utility/slDefine.h"
#include "sl/Library/Graphics/slGraphics.h"
#include "sl/Library/InputDevice/slInputDevice.h"
#include "sl/Library/Sound/slSound.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

bool MainGame::Initialize()
{
	bool result = false;

	// ウィンドウの作成
	sl::WindowCreationData data;
	data.m_pTitle = "ProjectAzur";
	data.m_Width = 1920;
	data.m_Height = 1080;
	m_pWindow = sl::CreateMainWindow(data);

	// グラフィックスライブラリの初期化
	sl::fRect backBufferSize = {0.0f, 0.0f, 1920.f, 1020.f};
	sl::DX11GraphicsLibrary::Instance().Init(m_pWindow->GetWindowHandle(), backBufferSize);

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


	// カスタマイズインプット処理

	return true;
}

void MainGame::Loop()
{
	while(RESULT_FALSE(m_pWindow->Update()))
	{

	}
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
