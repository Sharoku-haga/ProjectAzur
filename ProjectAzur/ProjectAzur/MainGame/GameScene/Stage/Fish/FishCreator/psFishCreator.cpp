//==================================================================================================================================//
//!< @file		paFishCreator.cpp
//!< @brief		pa::FishCreatorクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/23	更新履歴：2018/01/15
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paFishCreator.h"
#include "paFishShapeCreator.h"
#include "../FishSpawnPoint/paFishSpawnPoint.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

FishCreator::FishCreator(const sl::DrawingID&	rIDs
						, const char*	pResrcDataFilePath)
	: m_DrawingID(rIDs)
	, m_pResrcDataFilePath(pResrcDataFilePath)
{}

FishCreator::~FishCreator()
{}

void FishCreator::Initialize()
{
	m_pShapeCreator.Reset(new FishShapeCreator(m_DrawingID, m_pResrcDataFilePath));
	m_pFishSpawnPoint.Reset(new FishSpawnPoint());
	m_pFishSpawnPoint->Initialize();
}

sl::UniquePtr<Fish> FishCreator::CreateFish()
{
	sl::UniquePtr<Fish> pFish(new Fish(m_pFishSpawnPoint->GetPointPos(), m_pShapeCreator->CreateFishShape(), CreateFishReaction()));

	m_pFishSpawnPoint->UpdatePoint();

	return pFish;
}


/* Private Functions ------------------------------------------------------------------------------------------ */

sl::UniquePtr<FishReaction>	FishCreator::CreateFishReaction()
{
	return sl::UniquePtr<FishReaction>(new FishReaction(m_DrawingID, m_pResrcDataFilePath));
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
