﻿//==================================================================================================================================//
//!< @file		paMainGame.h	
//!< @brief		pa::MainGameクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017//11/17	更新履歴：2017//11/18
//==================================================================================================================================//

#ifndef PA_MAIN_GAME_H
#define PA_MAIN_GAME_H

#include "sl/Library/SmartPointer/slSmartpointer.h"
#include "sl/Library/Window/slWindow.h"

namespace pa
{

//===================================================================================//
//!< メインゲームクラス.ProjectAzur本体
//!< ゲーム起動時の初期化とゲームループを行う
//===================================================================================//
class MainGame final
{

public:
	/** Constructor */
	MainGame() = default;

	/** Destructor */
	~MainGame() = default;

	/** 初期化関数 */
	bool Initialize();

	/** ループ関数 */
	void Loop();

	/** 破棄関数 */
	void Finalize();

private:
	sl::UniquePtr<sl::IWindow>		m_pWindow;		//!< sl::IWindowクラスのインスタンスへのポインタ

	/** XBoxコントローラーを準備する関数 */
	void SetUpXInput();

	/** キーインプットを準備する関数 */
	void SetUpInputKey();

#ifdef _DEBUG
	/** デバック用インプットをカスタマイズする関数 */
	void SetUpDebugInput();

#endif // _DEBUG

};	// class MainGame

}	// namespace pa

#endif // PA_MAIN_GAME_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
