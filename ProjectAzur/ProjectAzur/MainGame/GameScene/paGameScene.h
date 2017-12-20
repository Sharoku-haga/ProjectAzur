//==================================================================================================================================//
//!< @file		paGameScene.h
//!< @brief		pa::GameSceneクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/18	更新履歴：2017/12/09
//==================================================================================================================================//

#ifndef PA_GAME_SCENE_H
#define PA_GAME_SCENE_H

#include <vector>
#include "sl/Library/SmartPointer/SharedPtr/slSharedPtr.h"
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "sl/Library/Scene/slSceneBase.h"
#include "../paIObjectBase.h"

namespace sl
{

class DX11GraphicsLibrary;
class IInputDeviceLibrary;

}

namespace pa
{

class DrawTaskManager;
class EventListener;

//===================================================================================//
//!< ゲームシーンクラス
//===================================================================================//
class GameScene : public sl::SceneBase
{

public:
	/** Constructor */
	GameScene();

	/** Destructor */
	virtual ~GameScene() = default;

	/** シーンの最初に行う処理関数 */
	virtual void Enter()override;

	/** シーンの最後に行う処理関数 */
	virtual void Exit()override;

private:
	std::vector<sl::SharedPtr<IObjectBase>>				m_pObject;					//!< IObjBaseクラスのインスタンスへのポインタ
	sl::DX11GraphicsLibrary&							m_rGraphicsLibrary;			//!< DX11GraphicsLibraryクラスのインスタンスへの参照
	sl::IInputDeviceLibrary&							m_rInputDeviceLibrary;		//!< IInputDeviceLibraryクラスのインスタンスへの参照	
	DrawTaskManager&									m_rDrawTaskManager;			//!< DrawTaskManagerクラスのインスタンスへの参照
	sl::SharedPtr<EventListener>						m_pEventListener;			//!< EventListenerクラスのインスタンスへのユニークポインタ	

	/** 制御関数 */
	virtual void Control()override;

	/** 描画関数 */
	virtual void Draw()override;

	/** イベントを処理する関数 */
	void HandleEvent();

};	// class GameScene

}	// namespace pa

#endif	// PA_GAME_SCENE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
