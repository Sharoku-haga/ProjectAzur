//==================================================================================================================================//
//!< @file		paFishCollider.cpp
//!< @brief		pa::FishColliderクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/05	更新履歴：2018/01/06
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paFishCollider.h"
#include "../../../Collider/paColliderManager.h"
#include "../paFish.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

FishCollider::FishCollider(const sl::fRect& rSize
						, Fish* pFish
						, const FishParam& rParam)
	: ColliderBase("FishCollider")
	, m_pOwner(pFish)
{
	SetSize(rSize);
	SetPos(rParam.m_Pos);
	SetAngle(rParam.m_Angle);
}

FishCollider::~FishCollider()
{}

void FishCollider::Initialize()
{
	UpdateCurrentRectData();
}

void FishCollider::ProcessCollision(ColliderBase& rCollider)
{
	// 現在 空関数
}

void FishCollider::Update(const FishParam& rParam)
{
	// 座標と角度を更新
	SetPos(rParam.m_Pos);
	SetAngle(rParam.m_Angle);

	UpdateCurrentRectData();

	// ColliderManagerに登録
	ColliderManager::Instance().RegisterStageObjCollider(this);
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
