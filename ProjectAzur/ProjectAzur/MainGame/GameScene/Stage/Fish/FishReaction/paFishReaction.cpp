//==================================================================================================================================//
//!< @file		paFishReaction.cpp
//!< @brief		pa::FishReactionクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/09	更新履歴：2018/01/14
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paFishReaction.h"
#include "paBalloon.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

FishReaction::FishReaction(const sl::DrawingID&	rIDs
						, const std::string&	rResrcDataFilePath)
	: m_pBalloon(new Balloon(rIDs, rResrcDataFilePath))
{}

FishReaction::~FishReaction()
{}

void FishReaction::Initialize()
{
	D3DXVECTOR2 balloonDiffPos = { 10.0f, 10.f};
	m_pBalloon->Initialize(balloonDiffPos);
}

void FishReaction::Upadte(const FishParam& rParam)
{
	m_pBalloon->Update(rParam);
}

void FishReaction::Draw(const FishParam& rParam)
{
	m_pBalloon->Draw(rParam);
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
