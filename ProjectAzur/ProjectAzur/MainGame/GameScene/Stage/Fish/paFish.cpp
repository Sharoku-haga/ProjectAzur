﻿//==================================================================================================================================//
//!< @file		paFish.cpp
//!< @brief		pa::Fishクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/23	更新履歴：2018/01/23
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "sl/Library/Utility/slDefine.h"
#include "paFish.h"
#include "../../../DrawTask/paDrawTask.h"
#include "FishCollider/paFishCollider.h"

namespace pa
{

namespace
{

const int	 DrawTaskPriority = 3;						// 描画優先度

}

/* Public Functions ------------------------------------------------------------------------------------------- */

Fish::Fish(const D3DXVECTOR2& rPos
			, sl::UniquePtr<FishShape> pShape
			, sl::UniquePtr<FishReaction> pReaction)
	: m_pShape(std::move(pShape))
	, m_pReaction(std::move(pReaction))
{
	m_Param.m_Pos = rPos;
}

Fish::~Fish()
{}

void Fish::Initialize()
{
	m_pShape->Initialize(m_Param);
	m_pReaction->Initialize(m_Param);

	m_pDrawTask.Reset(new DrawTask(DrawTaskPriority, std::bind(&pa::Fish::Draw, this)));

	m_pCollider.Reset(new FishCollider(m_pShape->GetCurrentRectSize(), this, m_Param));
	m_pCollider->Initialize();
}

void Fish::Update()
{
	m_pShape->Update(m_Param);
	m_pReaction->Upadte(m_Param);
	m_pCollider->Update(m_Param);
}

void Fish::Finalize()
{
	m_pShape->Finalize();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Fish::Draw()
{
	if(RESULT_FALSE(CheckScreenArea(m_Param.m_Pos, m_pShape->GetCurrentRectSize())))
	{
		return;
	}

	m_pShape->Draw();
	m_pReaction->Draw(m_Param, GetBasePointPos());
}

} // namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
