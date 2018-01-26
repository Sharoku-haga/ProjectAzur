//==================================================================================================================================//
//!< @file		paPalyer.cpp
//!< @brief		pa::Playerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/05	更新履歴：2018/01/06
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paPlayer.h"
#include "PlayerAction/paPlayerAction.h"
#include "PlayerShape/paPlayerShape.h"
#include "paPlayerCollider.h"
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

Player::~Player()
{}

void Player::Initialize()
{
	/** @todo  2017/12/07現在 仮の値を入れている */
	m_pPlayerParam->m_Pos = InitialPos;
	m_pPlayerParam->m_Acceleration = Acceleration;

	m_pPlayerAction->Initialize();
	m_pPlayerShape->Initialize(*m_pPlayerParam);

	m_pPlayerCollider.Reset(new PlayerCollider(m_pPlayerShape->InformShapeSize(), this, *m_pPlayerParam));
	m_pPlayerCollider->Initialize();
}

void Player::Update()
{
	m_pPlayerAction->Update(*m_pPlayerParam);
	m_pPlayerShape->Update(*m_pPlayerParam);
	m_pPlayerCollider->Update(*m_pPlayerParam);
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

const PlayerParam& Player::GetPlayerParam()
{
	return *m_pPlayerParam;
}

void Player::SetBasePointPos(const D3DXVECTOR2& rBasePointPos)
{
	m_pPlayerShape->SetBasePointPos(rBasePointPos);
}

void Player::AdjustData()
{
	m_pPlayerCollider->AdjustPlayerParam(*m_pPlayerParam);
	m_pPlayerShape->AdjustDrawingData(*m_pPlayerParam);
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
