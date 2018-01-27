//==================================================================================================================================//
//!< @file		paPlayerOriginalAction.cpp		
//!< @brief		pa::PlayerOriginalActionクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/26	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paPlayerOriginalAction.h"
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

PlayerOriginalAction::PlayerOriginalAction()
{}

PlayerOriginalAction::~PlayerOriginalAction()
{}

void PlayerOriginalAction::Initialize()
{
	SetSpeedMinVal(0.0f);
	SetSpeedMaxVal(5.0f);
}

void PlayerOriginalAction::Update(PlayerParam& rParam)
{
	D3DXVECTOR2 oldPos = rParam.m_Pos;
	MoveHorizontally(rParam);
	MoveVertically(rParam);

	// 待機状態かどうかのチェックを行う
	if(rParam.m_Pos == oldPos)
	{
		rParam.m_CurrentState = PLAYER_STATE::WAITING;
		return;
	}
	rParam.m_CurrentState = PLAYER_STATE::MOVING;

	EventManager::Instance().TriggerSynEvent("player_move");
}

void PlayerOriginalAction::Finalize()
{
	// 現在処理なし
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void PlayerOriginalAction::MoveHorizontally(PlayerParam& rParam)
{
	// 右移動
	if(m_rInputLibrary.CheckCustomizeInputState(RIGHT_MOVE, sl::ON))
	{
		rParam.m_CurrentSpeed.m_Right += rParam.m_Acceleration.m_Right;
	}
	else if(m_rInputLibrary.CheckCustomizeInputState(RIGHT_MOVE, sl::OFF))
	{
		rParam.m_CurrentSpeed.m_Right -= AttenuationSpeed;
	}

	// 左移動
	if(m_rInputLibrary.CheckCustomizeInputState(LEFT_MOVE, sl::ON))
	{
		rParam.m_CurrentSpeed.m_Left += rParam.m_Acceleration.m_Left;
	}
	else if(m_rInputLibrary.CheckCustomizeInputState(LEFT_MOVE, sl::OFF))
	{
		rParam.m_CurrentSpeed.m_Left  -= AttenuationSpeed;
	}

	// スピードの最小値と最大値の間に調整する
	rParam.m_CurrentSpeed.m_Right = AdjustSpeedBetweenMaxandMinVal(rParam.m_CurrentSpeed.m_Right);
	rParam.m_CurrentSpeed.m_Left = AdjustSpeedBetweenMaxandMinVal(rParam.m_CurrentSpeed.m_Left);
	
	// スピードを足す
	rParam.m_Pos.x += ((-rParam.m_CurrentSpeed.m_Left) + rParam.m_CurrentSpeed.m_Right);
}

void PlayerOriginalAction::MoveVertically(PlayerParam& rParam)
{
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
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
