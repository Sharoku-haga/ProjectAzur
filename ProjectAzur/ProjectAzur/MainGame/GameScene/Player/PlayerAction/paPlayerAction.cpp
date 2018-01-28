//==================================================================================================================================//
//!< @file		paPlayerAction.cpp
//!< @brief		pa::PlayerActionクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/05	更新履歴：2018/01/28
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "sl/Library/InputDevice/IInputDeviceLibrary/slIInputDeviceLibrary.h"
#include "paPlayerAction.h"
#include "paPlayerOriginalAction.h"
#include "paPlayerFishAction.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

PlayerAction::PlayerAction()
	: m_ActiveImplIndex(0)
{}

void PlayerAction::Initialize()
{
	// オリジナルのアクション実装クラス
	m_pActionImpl.emplace_back(new PlayerOriginalAction());

	// プレイヤーの魚状態のアクション実装クラス
	m_pActionImpl.emplace_back(new PlayerFishAction());

	// 初期化
	for(auto& pImpl : m_pActionImpl)
	{
		pImpl->Initialize();
	}
	//*
	ChangeOriginalActionimpl();
	//*/

	/*
	ChangeFishActionImpl();
	//*/
}

void PlayerAction::Update(PlayerParam& rParam)
{
	if(rParam.m_CurrentState == PLAYER_STATE::BEING_EATEN)
	{
		return;
	}

	m_pActionImpl[m_ActiveImplIndex]->Update(rParam);
}

void PlayerAction::Finalize()
{
	for(auto& pImpl : m_pActionImpl)
	{
		pImpl->Finalize();
	}
}

void PlayerAction::ChangeFishActionImpl()
{
	m_ActiveImplIndex = PlayerActionImplBase::TYPE::FISH_ACTION;
}

void PlayerAction::ChangeOriginalActionimpl()	
{
	m_ActiveImplIndex = PlayerActionImplBase::TYPE::ORIGINAL_ACTION;
}

void PlayerAction::StopHorizontalSpeed(PlayerParam& rParam)
{
	rParam.m_CurrentSpeed.m_Left = m_pActionImpl[m_ActiveImplIndex]->GetSpeedMinVal();
	rParam.m_CurrentSpeed.m_Right = m_pActionImpl[m_ActiveImplIndex]->GetSpeedMinVal();
}

void PlayerAction::StopVerticalSpeed(PlayerParam& rParam)
{
	rParam.m_CurrentSpeed.m_Up = m_pActionImpl[m_ActiveImplIndex]->GetSpeedMinVal();
	rParam.m_CurrentSpeed.m_Down = m_pActionImpl[m_ActiveImplIndex]->GetSpeedMinVal();
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
