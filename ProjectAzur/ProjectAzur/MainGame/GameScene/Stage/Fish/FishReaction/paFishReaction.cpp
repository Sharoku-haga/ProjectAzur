//==================================================================================================================================//
//!< @file		paFishReaction.cpp
//!< @brief		pa::FishReactionクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/09	更新履歴：2018/01/23
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paFishReaction.h"
#include "paBalloon.h"
#include "ReactionMark/paReactionMarkFactory.h"
#include "ReactionMark\paReactionMarkManager.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

FishReaction::FishReaction(const sl::DrawingID&	rIDs
						, const std::string&	rResrcDataFilePath)
	: m_pBalloon(new Balloon(rIDs, rResrcDataFilePath))
	, m_pReactionMarkManager(new ReactionMarkManager())
{}

FishReaction::~FishReaction()
{}

void FishReaction::Initialize(const FishParam& rParam)
{
	m_pBalloon->Initialize(ReactionMarkFactory::Instance().GetFishDiffPos());
	m_pReactionMarkManager->Initialize(rParam);
}

void FishReaction::Upadte(const FishParam& rParam)
{
	m_pBalloon->Update(rParam);
	m_pReactionMarkManager->Update(rParam);
}

void FishReaction::Draw(const FishParam& rParam, const D3DXVECTOR2& rBasePointPos)
{
	m_pBalloon->Draw(rParam, rBasePointPos);
	m_pReactionMarkManager->Draw(rParam, rBasePointPos);
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
