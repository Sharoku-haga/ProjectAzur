//==================================================================================================================================//
//!< @file		paFishCreator.cpp
//!< @brief		pa::FishCreatorクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/23	更新履歴：2018/01/15
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paFishCreator.h"
#include "paFishShapeCreator.h"

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
}

sl::UniquePtr<Fish> FishCreator::CreateFish(const D3DXVECTOR2& rPos)
{
	return sl::UniquePtr<Fish>(new Fish(rPos, m_pShapeCreator->CreateFishShape(), CreateFishReaction()));
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
