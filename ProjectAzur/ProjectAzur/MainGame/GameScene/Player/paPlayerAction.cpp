//==================================================================================================================================//
//!< @file		paPlayerAction.cpp
//!< @brief		pa::PlayerActionクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/05	更新履歴：2017/12/07
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <algorithm>
#include "sl/Library/InputDevice/IInputDeviceLibrary/slIInputDeviceLibrary.h"
#include "paPlayerAction.h"
#include "../../paCustomizeInput.h"

namespace pa
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const float		AttenuationSpeed = 0.7f;		//!< 減衰スピード

}

/* Public Functions ------------------------------------------------------------------------------------------- */

PlayerAction::PlayerAction()
	: m_rInputLibrary(sl::IInputDeviceLibrary::Instance())
{}

void PlayerAction::Initialize()
{
	/** @todo 現在は仮の数値 */
	m_SpeedMaxVal = 4.0f;
	m_SpeedMinVal = 0.0f;
	m_CurrentVerticalSpeed = 0.0f;
	m_CurrentHorizontalSpeed = 0.0f;
}

void PlayerAction::Update(PlayerParam& rParam)
{
	MoveHorizontally(rParam);
	MoveVertically(rParam);
	Rotate(rParam);

	// 待機状態かどうかのチェックを行う
	if(m_CurrentHorizontalSpeed == m_SpeedMinVal
		&& m_CurrentVerticalSpeed == m_SpeedMinVal)
	{
		rParam.m_CurrentState = PLAYER_STATE::WAITING;
		return;
	}
	rParam.m_CurrentState = PLAYER_STATE::MOVING;
}

void PlayerAction::Finalize()
{
	/** @todo 現状処理なし. すべての実装を終えて処理がなければ削除も検討 */
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void PlayerAction::MoveHorizontally(PlayerParam& rParam)
{
	// 右移動
	if(m_rInputLibrary.CheckCustomizeInputState(RIGHT_MOVE, sl::ON))
	{
		m_CurrentHorizontalSpeed += rParam.m_IsFacingRight ? rParam.m_Acceleration : -rParam.m_Acceleration;
	}
	else if(m_rInputLibrary.CheckCustomizeInputState(RIGHT_MOVE, sl::OFF)
			&& m_CurrentHorizontalSpeed != m_SpeedMinVal)
	{
		m_CurrentHorizontalSpeed += rParam.m_IsFacingRight ? -AttenuationSpeed : AttenuationSpeed;
	}

	// 左移動
	if(m_rInputLibrary.CheckCustomizeInputState(LEFT_MOVE, sl::ON))
	{
		m_CurrentHorizontalSpeed += rParam.m_IsFacingRight ? -rParam.m_Acceleration : rParam.m_Acceleration;
	}
	else if(m_rInputLibrary.CheckCustomizeInputState(LEFT_MOVE, sl::OFF)
			&& m_CurrentHorizontalSpeed != m_SpeedMinVal)
	{
		m_CurrentHorizontalSpeed += rParam.m_IsFacingRight ? AttenuationSpeed : -AttenuationSpeed;
	}

	// スピードの最小値と最大値の間におさめる
	m_CurrentHorizontalSpeed = std::max<float>(m_SpeedMinVal, std::min<float>(m_SpeedMaxVal, m_CurrentHorizontalSpeed));

	rParam.m_Pos.x += m_CurrentHorizontalSpeed;
}

void PlayerAction::MoveVertically(PlayerParam& rParam)
{
	// 上移動
	if(m_rInputLibrary.CheckCustomizeInputState(UP_MOVE, sl::ON))
	{
		m_CurrentVerticalSpeed -= rParam.m_Acceleration;
	}
	else if(m_rInputLibrary.CheckCustomizeInputState(UP_MOVE, sl::OFF)
			&& m_CurrentVerticalSpeed != m_SpeedMinVal)
	{
		m_CurrentVerticalSpeed += AttenuationSpeed;
	}

	// 下移動
	if(m_rInputLibrary.CheckCustomizeInputState(DOWN_MOVE, sl::ON))
	{
		m_CurrentVerticalSpeed += rParam.m_Acceleration;
	}
	else if(m_rInputLibrary.CheckCustomizeInputState(DOWN_MOVE, sl::OFF)
			&& m_CurrentVerticalSpeed != m_SpeedMinVal)
	{
		m_CurrentVerticalSpeed -= AttenuationSpeed;
	}

	// スピードの最小値と最大値の間におさめる
	m_CurrentVerticalSpeed = std::max<float>(m_SpeedMinVal, std::min<float>(m_SpeedMaxVal, m_CurrentVerticalSpeed));

	rParam.m_Pos.y += m_CurrentVerticalSpeed;
}

void PlayerAction::Rotate(PlayerParam& rParam)
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
