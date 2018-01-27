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
	m_pActionImpl.resize(PlayerActionImplBase::TYPE::ACTION_MAX);

	// オリジナルのアクション実装クラス
	m_pActionImpl.emplace_back(new PlayerOriginalAction());

	// プレイヤーの魚状態のアクション実装クラス
	m_pActionImpl.emplace_back(new PlayerFishAction());

	// 初期化
	for(auto& pImpl : m_pActionImpl)
	{
		pImpl->Initialize();
	}

	ChangeOriginalActionimpl();
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

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
