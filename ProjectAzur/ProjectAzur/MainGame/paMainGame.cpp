//==================================================================================================================================//
//!< @file		paMainGame.cpp	
//!< @brief		pa::MainGameクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017//11/17	更新履歴：2017/11/18
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "sl/Library/Utility/slDefine.h"
#include "sl/Library/Graphics/slGraphics.h"
#include "sl/Library/InputDevice/slInputDevice.h"
#include "sl/Library/Sound/slSound.h"
#include "sl/Library/Scene/slScene.h"
#include "paMainGame.h"
#include "SceneFactory/paSceneFactory.h"
#include "SceneDeletor/paSceneDeletor.h"
#include "DrawingResrcDataFile/paDrawingResrcDataFile.h"
#include "DrawTask/paDrawTaskManager.h"
#include "EventManager\paEventManager.h"
#include "paCustomizeInput.h"

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

	//// サウンドライブラリの初期化
	result = sl::ISoundLibrary::Instance().Initialize(m_pWindow->GetWindowHandle());
	if(RESULT_FALSE(result))
	{
		return false;
	}

	// インプット処理設定
	SetUpInputKey();
	SetUpXInput();
#ifdef _DEBUG
	SetUpDebugInput();
#endif // _DEBUG

	// リソースデータマネージャーの初期化
	DrawingResrcDataFile::Instance().Initialize("../Resource/Data");

	//シーンマネージャー関連処理
	sl::SceneManager::Instance().Initialize(sl::UniquePtr<sl::ISceneFactory>(new SceneFactory())
											, sl::UniquePtr<sl::ISceneDeletor>(new SceneDeletor())
											, StartSceneName);
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

void MainGame::Finalize()
{
	sl::SceneManager::Instance().Finalize();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void MainGame::SetUpXInput()
{
	sl::IInputDeviceLibrary& rLibrary = sl::IInputDeviceLibrary::Instance();
	rLibrary.CreateInputDevice(sl::XINPUT_DEVICE);

	// UP	
	rLibrary.RegisterCustomizeXInputAction(CUSTOMIZE_INPUT_ACTION::UP
											, sl::XIDEVICE_DPAD_UP);
	// DOWN		
	rLibrary.RegisterCustomizeXInputAction(CUSTOMIZE_INPUT_ACTION::DOWN
											, sl::XIDEVICE_DPAD_DOWN);
	// RIGHT		
	rLibrary.RegisterCustomizeXInputAction(CUSTOMIZE_INPUT_ACTION::RIGHT
											, sl::XIDEVICE_DPAD_RIGHT);
	// LEFT					
	rLibrary.RegisterCustomizeXInputAction(CUSTOMIZE_INPUT_ACTION::LEFT
											, sl::XIDEVICE_DPAD_LEFT);
	// DECISION_BTN			
	rLibrary.RegisterCustomizeXInputAction(CUSTOMIZE_INPUT_ACTION::DECISION_BTN
											, sl::XIDEVICE_A);
	// BACK_BTN				
	rLibrary.RegisterCustomizeXInputAction(CUSTOMIZE_INPUT_ACTION::BACK_BTN	
											, sl::XIDEVICE_B);
	// PAUSE_BTN				
	rLibrary.RegisterCustomizeXInputAction(CUSTOMIZE_INPUT_ACTION::PAUSE_BTN
											, sl::XIDEVICE_START);
	// RIGHT_MOVE
	rLibrary.RegisterCustomizeXInputAction(CUSTOMIZE_INPUT_ACTION::RIGHT_MOVE
											, sl::XIDEVICE_LSTICK_RIGHT);
	// LEFT_MOVE	
	rLibrary.RegisterCustomizeXInputAction(CUSTOMIZE_INPUT_ACTION::LEFT_MOVE
											, sl::XIDEVICE_LSTICK_LEFT);
	// UP_MOVE				
	rLibrary.RegisterCustomizeXInputAction(CUSTOMIZE_INPUT_ACTION::UP_MOVE	
											, sl::XIDEVICE_LSTICK_UP);
	// DOWN_MOVE					
	rLibrary.RegisterCustomizeXInputAction(CUSTOMIZE_INPUT_ACTION::DOWN_MOVE
											, sl::XIDEVICE_LSTICK_DOWN);
	// RIGHT_ROTATION	
	rLibrary.RegisterCustomizeXInputAction(CUSTOMIZE_INPUT_ACTION::RIGHT_ROTATION	
											, sl::XIDEVICE_X);
	// LEFT_ROTATION	
	rLibrary.RegisterCustomizeXInputAction(CUSTOMIZE_INPUT_ACTION::LEFT_ROTATION
											, sl::XIDEVICE_Y);
	// SCOUTING_MODE_BTN			
	rLibrary.RegisterCustomizeXInputAction(CUSTOMIZE_INPUT_ACTION::SCOUTING_MODE_BTN	
											, sl::XIDEVICE_RTRIGGER);
	// SCOUTING_UP				
	rLibrary.RegisterCustomizeXInputAction(CUSTOMIZE_INPUT_ACTION::SCOUTING_UP
											, sl::XIDEVICE_RSTICK_UP);
	// SCOUTING_DOWN				
	rLibrary.RegisterCustomizeXInputAction(CUSTOMIZE_INPUT_ACTION::SCOUTING_DOWN
											, sl::XIDEVICE_RSTICK_DOWN);
	// SCOUTING_RIGHT				
	rLibrary.RegisterCustomizeXInputAction(CUSTOMIZE_INPUT_ACTION::SCOUTING_RIGHT
											, sl::XIDEVICE_RSTICK_RIGHT);
	// SCOUTING_LEFT				
	rLibrary.RegisterCustomizeXInputAction(CUSTOMIZE_INPUT_ACTION::DECISION_BTN
											, sl::XIDEVICE_RSTICK_LEFT);
}

void MainGame::SetUpInputKey()
{
	sl::IInputDeviceLibrary& rLibrary = sl::IInputDeviceLibrary::Instance();
	rLibrary.CreateInputDevice(sl::KEYBOARD);

	// 使用するキーを登録する
	rLibrary.RegisterUsingKey(sl::K_UP);
	rLibrary.RegisterUsingKey(sl::K_DOWN);
	rLibrary.RegisterUsingKey(sl::K_RIGHT);
	rLibrary.RegisterUsingKey(sl::K_LEFT);
	rLibrary.RegisterUsingKey(sl::K_RETURN);
	rLibrary.RegisterUsingKey(sl::K_R);
	rLibrary.RegisterUsingKey(sl::K_W);
	rLibrary.RegisterUsingKey(sl::K_S);
	rLibrary.RegisterUsingKey(sl::K_D);
	rLibrary.RegisterUsingKey(sl::K_A);
	rLibrary.RegisterUsingKey(sl::K_P);
	rLibrary.RegisterUsingKey(sl::K_LSHIFT);

	// UP	
	rLibrary.RegisterCustomizeKey(CUSTOMIZE_INPUT_ACTION::UP
								 , sl::K_UP);
	// DOWN		
	rLibrary.RegisterCustomizeKey(CUSTOMIZE_INPUT_ACTION::DOWN
								 , sl::K_DOWN);
	// RIGHT
	rLibrary.RegisterCustomizeKey(CUSTOMIZE_INPUT_ACTION::RIGHT
								 , sl::K_RIGHT);
	// LEFT					
	rLibrary.RegisterCustomizeKey(CUSTOMIZE_INPUT_ACTION::LEFT
								 , sl::K_LEFT);
	// DECISION_BTN			
	rLibrary.RegisterCustomizeKey(CUSTOMIZE_INPUT_ACTION::DECISION_BTN
								 , sl::K_RETURN);
	// BACK_BTN				
	rLibrary.RegisterCustomizeKey(CUSTOMIZE_INPUT_ACTION::BACK_BTN
								 , sl::K_R);
	// PAUSE_BTN	
	rLibrary.RegisterCustomizeKey(CUSTOMIZE_INPUT_ACTION::PAUSE_BTN
								 , sl::K_P);
	// RIGHT_MOVE
	rLibrary.RegisterCustomizeKey(CUSTOMIZE_INPUT_ACTION::RIGHT_MOVE
								 , sl::K_D);
	// LEFT_MOVE	
	rLibrary.RegisterCustomizeKey(CUSTOMIZE_INPUT_ACTION::LEFT_MOVE
								 , sl::K_A);
	// UP_MOVE				
	rLibrary.RegisterCustomizeKey(CUSTOMIZE_INPUT_ACTION::UP_MOVE
								 , sl::K_W);
	// DOWN_MOVE					
	rLibrary.RegisterCustomizeKey(CUSTOMIZE_INPUT_ACTION::DOWN_MOVE
								 , sl::K_S);
	// RIGHT_ROTATION					
	rLibrary.RegisterCustomizeKey(CUSTOMIZE_INPUT_ACTION::RIGHT_ROTATION
								 , sl::K_RIGHT);
	// LEFT_ROTATION					
	rLibrary.RegisterCustomizeKey(CUSTOMIZE_INPUT_ACTION::LEFT_ROTATION
								 , sl::K_LEFT);
	// SCOUTING_MODE_BTN			
	rLibrary.RegisterCustomizeKey(CUSTOMIZE_INPUT_ACTION::SCOUTING_MODE_BTN
								 , sl::K_LSHIFT);
	// SCOUTING_UP				
	rLibrary.RegisterCustomizeKey(CUSTOMIZE_INPUT_ACTION::SCOUTING_UP
								 , sl::K_W);
	// SCOUTING_DOWN				
	rLibrary.RegisterCustomizeKey(CUSTOMIZE_INPUT_ACTION::SCOUTING_DOWN
								 , sl::K_S);
	// SCOUTING_RIGHT				
	rLibrary.RegisterCustomizeKey(CUSTOMIZE_INPUT_ACTION::SCOUTING_RIGHT
								 , sl::K_D);
	// SCOUTING_LEFT				
	rLibrary.RegisterCustomizeKey(CUSTOMIZE_INPUT_ACTION::SCOUTING_LEFT
								 , sl::K_A);
}

#ifdef _DEBUG
	void MainGame::SetUpDebugInput()
	{}

#endif // _DEBUG

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
