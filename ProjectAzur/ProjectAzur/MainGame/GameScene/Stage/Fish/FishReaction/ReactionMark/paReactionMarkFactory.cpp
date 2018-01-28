//=================================================================================================================================//
//!< @file		paReactionMarkFactory.cpp		
//!< @brief		pa::ReactionMarkFactoryクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/22	更新履歴：2018/01/23
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "sl/Library/Graphics/slGraphicsDeclaration.h"
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "paReactionMarkFactory.h"
#include "../../../../../DrawingResrcDataFile/paDrawingResrcDataFile.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

void ReactionMarkFactory::Initialize(const sl::DrawingID&	rIDs
									, const std::string&	rResrcDataFilePath
									, const D3DXVECTOR2&	rFishDiffPos)
{
	m_FishDiffPos = rFishDiffPos;

	// インスタンス作成

	// HUNGER
	{
		int resrcDataID = 33;
		DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, resrcDataID);
		m_pMark[HUNGER].Reset(new ReactionMark(rIDs, rResrc, HUNGER, m_FishDiffPos));
	}
	
	// WARNING 
	{
		int resrcDataID = 39;
		DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, resrcDataID);
		m_pMark[WARNING].Reset(new ReactionMark(rIDs, rResrc, WARNING, m_FishDiffPos));
	}

	// ATTACK
	{
		int resrcDataID = 36;
		DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, resrcDataID);
		m_pMark[ATTACK].Reset(new ReactionMark(rIDs, rResrc, ATTACK, m_FishDiffPos));
	}

	// DISCOVERY
	{
		int resrcDataID = 34;
		DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, resrcDataID);
		m_pMark[DISCOVERY].Reset(new ReactionMark(rIDs, rResrc, DISCOVERY, m_FishDiffPos));
	}

	// REFUGE
	{
		int resrcDataID = 40;
		DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, resrcDataID);
		m_pMark[REFUGE].Reset(new ReactionMark(rIDs, rResrc, REFUGE, m_FishDiffPos));
	}

	// EATING
	{
		int resrcDataID = 37;
		DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, resrcDataID);
		m_pMark[EATING].Reset(new ReactionMark(rIDs, rResrc, EATING, m_FishDiffPos));
	}

	// TARGET
	{
		int resrcDataID = 35;
		DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, resrcDataID);
		m_pMark[TARGET].Reset(new ReactionMark(rIDs, rResrc, TARGET, m_FishDiffPos));
	}

	// DETECTION
	{
		int resrcDataID = 38;
		DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, resrcDataID);
		m_pMark[DETECTION].Reset(new ReactionMark(rIDs, rResrc, DETECTION, m_FishDiffPos));
	}
}

void ReactionMarkFactory::CreateReactionMarks(int reactionMarkFlag
											, std::vector<REACTION_MARK_TYPE>& rMarks)
{
	std::vector<REACTION_MARK_TYPE>().swap(rMarks);

	if(reactionMarkFlag & HUNGER)
	{
		rMarks.push_back(HUNGER);
	}

	if(reactionMarkFlag & WARNING)
	{
		rMarks.push_back(WARNING);
	}

	if(reactionMarkFlag & ATTACK)
	{
		rMarks.push_back(ATTACK);
	}

	if(reactionMarkFlag & DISCOVERY)
	{
		rMarks.push_back(DISCOVERY);
	}

	if(reactionMarkFlag & REFUGE)
	{
		rMarks.push_back(REFUGE);
	}

	if(reactionMarkFlag & EATING)
	{
		rMarks.push_back(EATING);
	}

	if(reactionMarkFlag & TARGET)
	{
		rMarks.push_back(TARGET);
	}

	if(reactionMarkFlag & DETECTION)
	{
		rMarks.push_back(DETECTION);
	}
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
