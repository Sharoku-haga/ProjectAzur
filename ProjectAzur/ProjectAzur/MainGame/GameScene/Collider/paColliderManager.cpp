//==================================================================================================================================//
//!< @file		paColliderManager.cpp
//!< @brief		pa::ColliderManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/05	更新履歴：2018/01/07
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paColliderManager.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

void ColliderManager::Update()
{
	if(m_pStageObjColliders.empty() || m_pPlayerCoolider == nullptr)
	{
		return;
	}

	// プレイヤーとステージオブジェクトの衝突判定確認
	CheckCollisionPlayer();

	// データをリセットする
	ResetColliderPointer();
}


void ColliderManager::RegisterStageObjCollider(ColliderBase* pStageObjCollider)
{
	m_pStageObjColliders.emplace_back(pStageObjCollider);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

ColliderManager::ColliderManager()
	: m_pPlayerCoolider(nullptr)
{}

void ColliderManager::CheckCollisionPlayer()
{
	for(auto& pStageObjCollider : m_pStageObjColliders)
	{
		if(CheckRectCollision(m_pPlayerCoolider->GetCurrentRectData(), pStageObjCollider->GetCurrentRectData()))
		{
			m_pPlayerCoolider->ProcessCollision(*pStageObjCollider);
			pStageObjCollider->ProcessCollision(*m_pPlayerCoolider);
		}
	}
}

bool ColliderManager::CheckRectCollision(const sl::fRect& rRectA, const sl::fRect& rRectB)
{
	if(rRectA.m_Right > rRectB.m_Left
		&& rRectA.m_Top < rRectB.m_Bottom
		&& rRectA.m_Left < rRectB.m_Right
		&& rRectA.m_Bottom > rRectB.m_Top)
	{
		return true;
	}

	return false;
}

void ColliderManager::ResetColliderPointer()
{
	m_pPlayerCoolider = nullptr;
	std::vector<ColliderBase*>().swap(m_pStageObjColliders);
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
