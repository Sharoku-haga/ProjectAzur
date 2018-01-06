//==================================================================================================================================//
//!< @file		paPlayerCollider.cpp
//!< @brief		pa::PlayerColliderクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/05	更新履歴：2018/01/06
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paPlayerCollider.h"
#include "../Collider/paColliderManager.h"
#include "paPlayer.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

PlayerCollider::PlayerCollider(const sl::fRect& rSize
							, Player* pPlayer
							, const PlayerParam& rParam)
	: ColliderBase("PlayerCollider")
	, m_pOwner(pPlayer)
	, m_DiffPos(0.0f, 0.0f)
{
	SetSize(rSize);
	SetPos(rParam.m_Pos);
	SetAngle(rParam.m_Angle);
}

PlayerCollider::~PlayerCollider()
{}

void PlayerCollider::Initialize()
{
	UpdateCurrentRectData();
}

void PlayerCollider::ProcessCollision(ColliderBase& rCollider)
{
	// 差分を計算
	CalculateDiffVal(rCollider);

	// プレイヤーに差分データを反映
	m_pOwner->AdjustData();

	m_DiffPos.x = 0.0f;
	m_DiffPos.y = 0.0f;
}

void PlayerCollider::Update(const PlayerParam&	rParam)
{
	// 座標と角度を更新
	SetPos(rParam.m_Pos);
	SetAngle(rParam.m_Angle);

	UpdateCurrentRectData();

	// ColliderManagerに登録
	//ColliderManager::Instance().RegisterPlayerCollider(this);
}

void PlayerCollider::AdjustPlayerParam(PlayerParam&	rParam)
{
	rParam.m_Pos += m_DiffPos;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void PlayerCollider::CalculateDiffVal(ColliderBase& rCollider)
{
	const sl::fRect& rMyRect = GetCurrentRectData();
	const sl::fRect& rOtherRect = rCollider.GetCurrentRectData();

	// 左右の差分取得
	if((rMyRect.m_Right - rOtherRect.m_Left) < (rOtherRect.m_Right - rMyRect.m_Left))
	{
		m_DiffPos.x = -(rMyRect.m_Right - rOtherRect.m_Left);
	}
	else
	{
		m_DiffPos.x = (rOtherRect.m_Right - rMyRect.m_Left);
	}

	// 上下の差分取得
	if((rMyRect.m_Bottom - rOtherRect.m_Top) < (rOtherRect.m_Bottom - rMyRect.m_Top))
	{
		m_DiffPos.y = -(rMyRect.m_Bottom - rOtherRect.m_Top) ;
	}
	else
	{
		m_DiffPos.y = (rOtherRect.m_Bottom - rMyRect.m_Top);
	}
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
