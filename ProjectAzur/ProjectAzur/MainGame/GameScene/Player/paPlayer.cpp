//==================================================================================================================================//
//!< @file		paPalyer.cpp
//!< @brief		pa::Playerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/05	更新履歴：2017/12/09
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paPlayer.h"
#include "paPlayerAction.h"
#include "paPlayerShape.h"
#include "paPlayerCommonDeclaration.h"

namespace pa
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const D3DXVECTOR2	InitialPos				= { 100.0f, 100.0f};		// 初期座標
const float			Acceleration			= 0.07f;					// 加速度

}

/* Public Functions ------------------------------------------------------------------------------------------- */

Player::Player(const sl::DrawingID& rIDs
			, const char*	pResrcDataFilePath)
	: m_pPlayerParam(new PlayerParam())
	, m_pPlayerAction(new PlayerAction())
	, m_pPlayerShape(new PlayerShape(rIDs, pResrcDataFilePath))
{}

void Player::Initialize()
{
	/** @todo  2017/12/07現在 仮の値を入れている */
	m_pPlayerParam->m_Pos = InitialPos;
	m_pPlayerParam->m_Acceleration = Acceleration;

	m_pPlayerAction->Initialize();
	m_pPlayerShape->Initialize(*m_pPlayerParam);
}

void Player::Update()
{
	m_pPlayerAction->Update(*m_pPlayerParam);
	m_pPlayerShape->Update(*m_pPlayerParam);
}

void Player::Finalize()
{
	m_pPlayerShape->Finalize();
	m_pPlayerAction->Finalize();
}

const D3DXVECTOR2& Player::GetPos()
{
	return m_pPlayerParam->m_Pos;
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
