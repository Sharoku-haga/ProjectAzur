//==================================================================================================================================//
//!< @file		paPlayerFishAction.cpp	
//!< @brief		pa::PlayerFishActionクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/26	更新履歴：2018/01/27
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <algorithm>
#include "paPlayerFishAction.h"
#include "../../../paCustomizeInput.h"
#include "../../../EventManager/paEventManager.h"

namespace pa
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const float		AttenuationSpeed = 0.02f;		//!< 減衰スピード

}

/* Public Functions ------------------------------------------------------------------------------------------- */

PlayerFishAction::PlayerFishAction()
{}

PlayerFishAction::~PlayerFishAction()
{}

void PlayerFishAction::Initialize()
{
	SetSpeedMinVal(0.0f);
	SetSpeedMaxVal(5.0f);
}

void PlayerFishAction::Update(PlayerParam& rParam)
{
	D3DXVECTOR2 oldPos = rParam.m_Pos;
	MoveHorizontally(rParam);
	MoveVertically(rParam);
	Rotate(rParam);

	// 待機状態かどうかのチェックを行う
	if(rParam.m_Pos == oldPos)
	{
		rParam.m_CurrentState = PLAYER_STATE::WAITING;
		return;
	}
	rParam.m_CurrentState = PLAYER_STATE::MOVING;

	EventManager::Instance().TriggerSynEvent("player_move");
}

void PlayerFishAction::Finalize()
{
	// 現在は処理なし
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void PlayerFishAction::MoveHorizontally(PlayerParam& rParam)
{
	//*
	// 右移動
	if(m_rInputLibrary.CheckCustomizeInputState(RIGHT_MOVE, sl::ON))
	{
		if(rParam.m_IsFacingRight)
		{
			rParam.m_CurrentSpeed.m_Right += rParam.m_Acceleration.m_Right;
		}
		else
		{
			if(rParam.m_CurrentSpeed.m_Left > GetSpeedMinVal())
			{
				rParam.m_CurrentSpeed.m_Right = AttenuationSpeed;		 
			}
			else
			{
				rParam.m_CurrentSpeed.m_Right = 0.0f;
			}
		}
	}
	else if(m_rInputLibrary.CheckCustomizeInputState(RIGHT_MOVE, sl::OFF))
	{
		rParam.m_CurrentSpeed.m_Right -= AttenuationSpeed;
	}

	// 左移動
	if(m_rInputLibrary.CheckCustomizeInputState(LEFT_MOVE, sl::ON))
	{
		if(rParam.m_IsFacingRight)
		{
			if(rParam.m_CurrentSpeed.m_Right > GetSpeedMinVal())
			{
				rParam.m_CurrentSpeed.m_Left = AttenuationSpeed;
			}
			else
			{
				rParam.m_CurrentSpeed.m_Left = 0.0f;
			}
		}
		else 
		{
			rParam.m_CurrentSpeed.m_Left += rParam.m_Acceleration.m_Left;
		}
	}
	else if(m_rInputLibrary.CheckCustomizeInputState(LEFT_MOVE, sl::OFF))
	{
		rParam.m_CurrentSpeed.m_Left -=  AttenuationSpeed;
	}

	// スピードの最小値と最大値の間に調整する
	rParam.m_CurrentSpeed.m_Right = AdjustSpeedBetweenMaxandMinVal(rParam.m_CurrentSpeed.m_Right);
	rParam.m_CurrentSpeed.m_Left = AdjustSpeedBetweenMaxandMinVal(rParam.m_CurrentSpeed.m_Left);
	
	// スピードを足す
	rParam.m_Pos.x += ((-rParam.m_CurrentSpeed.m_Left) + rParam.m_CurrentSpeed.m_Right);
	// */
}

void PlayerFishAction::MoveVertically(PlayerParam& rParam)
{
	//*
	// 上移動
	if(m_rInputLibrary.CheckCustomizeInputState(UP_MOVE, sl::ON))
	{
		rParam.m_CurrentSpeed.m_Up += rParam.m_Acceleration.m_Up;
	}
	else if(m_rInputLibrary.CheckCustomizeInputState(UP_MOVE, sl::OFF))
	{
		rParam.m_CurrentSpeed.m_Up -= AttenuationSpeed;
	}

	// 下移動
	if(m_rInputLibrary.CheckCustomizeInputState(DOWN_MOVE, sl::ON))
	{
		rParam.m_CurrentSpeed.m_Down += rParam.m_Acceleration.m_Down;
	}
	else if(m_rInputLibrary.CheckCustomizeInputState(DOWN_MOVE, sl::OFF))
	{
		rParam.m_CurrentSpeed.m_Down -= AttenuationSpeed;
	}

	// スピードの最小値と最大値の間に調整する
	rParam.m_CurrentSpeed.m_Up = AdjustSpeedBetweenMaxandMinVal(rParam.m_CurrentSpeed.m_Up);
	rParam.m_CurrentSpeed.m_Down = AdjustSpeedBetweenMaxandMinVal(rParam.m_CurrentSpeed.m_Down);

	// スピードを足す
	rParam.m_Pos.y += ((-rParam.m_CurrentSpeed.m_Up) + rParam.m_CurrentSpeed.m_Down);
	// */
}

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
