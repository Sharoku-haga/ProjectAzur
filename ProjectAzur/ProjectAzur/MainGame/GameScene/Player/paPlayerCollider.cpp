//==================================================================================================================================//
//!< @file		paPlayerCollider.cpp
//!< @brief		pa::PlayerColliderクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/05	更新履歴：2018/01/08
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <cmath>
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
	ColliderManager::Instance().RegisterPlayerCollider(this);
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

	const D3DXVECTOR2& rMyPos = GetPos();
	const D3DXVECTOR2& rOtherPos = rCollider.GetPos();

	const PlayerParam& rParam = m_pOwner->GetPlayerParam();

	sl::fRect checkRect = rMyRect;

	if(std::abs(rMyPos.x - rOtherPos.x) > std::abs(rMyPos.y - rOtherPos.y))
	{
		if(rParam.m_CurrentHorizontalSpeed != 0.0f)
		{
			CalculateHorizontalDiffVal(rMyRect, rOtherRect);
			
			// 角の部分の処理
			if(std::abs(m_DiffPos.x) > std::abs(rParam.m_CurrentHorizontalSpeed))
			{
				if(m_DiffPos.x >  0.0f)
				{
					m_DiffPos.x = std::abs(rParam.m_CurrentHorizontalSpeed);
				}
				else if(m_DiffPos.x < 0.0f)
				{
					m_DiffPos.x = -std::abs(rParam.m_CurrentHorizontalSpeed);
				}
			}
		}

		checkRect.m_Left += m_DiffPos.x;
		checkRect.m_Right += m_DiffPos.x;

		if(ColliderManager::Instance().CheckRectCollision(checkRect, rOtherRect))
		{
			if(rParam.m_CurrentVerticalSpeed != 0.0f)
			{
				CalculateVerticalDiffVal(checkRect, rOtherRect);
				int i = 0;
			}
		}

	}
	else //if(std::abs(rMyPos.x - rOtherPos.x) < std::abs(rMyPos.y - rOtherPos.y))
	{
		if(rParam.m_CurrentVerticalSpeed != 0.0f)
		{
			CalculateVerticalDiffVal(rMyRect, rOtherRect);
		}

		checkRect.m_Top += m_DiffPos.y;
		checkRect.m_Bottom += m_DiffPos.y;

		if(ColliderManager::Instance().CheckRectCollision(checkRect, rOtherRect))
		{
			if(rParam.m_CurrentHorizontalSpeed != 0.0f)
			{
				CalculateHorizontalDiffVal(checkRect, rOtherRect);
			}
		}
	}
}

void PlayerCollider::CalculateHorizontalDiffVal(const sl::fRect& rMyRect, const sl::fRect& rOtherRect)
{
	if((rMyRect.m_Right - rOtherRect.m_Left) < (rOtherRect.m_Right - rMyRect.m_Left))
	{
		m_DiffPos.x = -(rMyRect.m_Right - rOtherRect.m_Left);
	}
	else
	{
		m_DiffPos.x = (rOtherRect.m_Right - rMyRect.m_Left);
	}
}

void PlayerCollider::CalculateVerticalDiffVal(const sl::fRect& rMyRect, const sl::fRect& rOtherRect)
{
	if((rMyRect.m_Bottom - rOtherRect.m_Top) < (rOtherRect.m_Bottom - rMyRect.m_Top))
	{
		m_DiffPos.y = -(rMyRect.m_Bottom - rOtherRect.m_Top);
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
