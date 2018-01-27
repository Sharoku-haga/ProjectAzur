//==================================================================================================================================//
//!< @file		paPlayerFishAction.cpp	
//!< @brief		pa::PlayerFishActionクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/26	更新履歴：2018/01/27
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paPlayerFishAction.h"
#include "../../../paCustomizeInput.h"
#include "../../../EventManager/paEventManager.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

PlayerFishAction::PlayerFishAction()
{}

PlayerFishAction::~PlayerFishAction()
{}

void PlayerFishAction::Initialize()
{}

void PlayerFishAction::Update(PlayerParam& rParam)
{}

void PlayerFishAction::Finalize()
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void PlayerFishAction::MoveHorizontally(PlayerParam& rParam)
{}

void PlayerFishAction::MoveVertically(PlayerParam& rParam)
{}

void PlayerFishAction::Rotate(PlayerParam& rParam)
{
	/** 
	* @todo 回転機能に関してはオミットしている。 
	* ここではボタンがおされたら 反転するだけ 
	*/
	if(m_rInputLibrary.CheckCustomizeInputState(RIGHT_ROTATION, sl::ON))
	{
		rParam.m_IsFacingRight = true;
	}
	else if(m_rInputLibrary.CheckCustomizeInputState(LEFT_ROTATION, sl::ON))
	{
		rParam.m_IsFacingRight = false;
	}
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
