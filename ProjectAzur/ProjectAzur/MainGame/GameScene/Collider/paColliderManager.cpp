//==================================================================================================================================//
//!< @file		paColliderManager.cpp
//!< @brief		pa::ColliderManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/05	更新履歴：2018/01/06
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paColliderManager.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

void ColliderManager::Update()
{
	if(m_pStageObjColliders.empty() || m_pPlayerCoolider.Get() == nullptr)
	{
		return;
	}

	// プレイヤーとステージオブジェクトの衝突判定確認
	CheckCollisionPlayer();

	// データをリセットする
	ResetColliderPointer();
}


void ColliderManager::RegisterStageObjCollider(sl::SharedPtr<ColliderBase> pStageObjCollider)
{
	m_pStageObjColliders.emplace_back(pStageObjCollider);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void ColliderManager::CheckCollisionPlayer()
{
	for(auto& pStageObjCollider : m_pStageObjColliders)
	{
		if(CheckRectCollision(m_pPlayerCoolider->GetCurrentRectData(), pStageObjCollider->GetCurrentRectData()))
		{
			m_pPlayerCoolider->ProcessCollision(*pStageObjCollider.Get());
			pStageObjCollider->ProcessCollision(*m_pPlayerCoolider.Get());
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
	m_pPlayerCoolider.Reset();

	for(auto& pStageObjCollider : m_pStageObjColliders)
	{
		pStageObjCollider.Reset();
	}

	std::vector<sl::SharedPtr<ColliderBase>>().swap(m_pStageObjColliders);
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
