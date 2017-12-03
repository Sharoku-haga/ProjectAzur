//==================================================================================================================================//
//!< @file		paTitleScene.h		
//!< @brief		paTitleSceneクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/18	更新履歴：2017/12/02
//==================================================================================================================================//

#ifndef PA_TITLE_SCENE_H
#define PA_TITLE_SCENE_H

#include <vector>
#include "sl/Library/Scene/slSceneBase.h"
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "../paIObjectBase.h"

namespace sl
{

class DX11GraphicsLibrary;
class IInputDeviceLibrary;

}

namespace pa
{

class DrawTaskManager;

//===================================================================================//
//!< タイトルシーンクラス
//===================================================================================//
class TitleScene final : public sl::SceneBase
{
public:
	/** Constructor */
	TitleScene();

	/** Destructor */
	virtual ~TitleScene() = default;

	/** シーンの最初に行う処理関数 */
	virtual void Enter()override;

	/** シーンの最後に行う処理関数 */
	virtual void Exit()override;

private:
	std::vector<sl::UniquePtr<IObjectBase>>			m_pObject;					//!< IObjBaseクラスのインスタンスへのポインタ
	sl::DX11GraphicsLibrary&						m_rGraphicsLibrary;			//!< DX11GraphicsLibraryクラスのインスタンスへの参照
	sl::IInputDeviceLibrary&						m_rInputDeviceLibrary;		//!< IInputDeviceLibraryクラスのインスタンスへの参照	
	DrawTaskManager&								m_rDrawTaskManager;			//!< DrawTaskManagerクラスのインスタンスへの参照

	/** 制御関数 */
	virtual void Control()override;

	/** 描画関数 */
	virtual void Draw()override;

};	// class TitleScene

}	// namespace pa

#endif	// PA_TITLE_SCENE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
