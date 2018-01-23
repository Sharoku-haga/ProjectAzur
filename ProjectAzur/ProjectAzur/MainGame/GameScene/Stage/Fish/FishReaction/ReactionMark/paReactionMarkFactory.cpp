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
	// インスタンス作成

	// HUNGER
	{
		int resrcDataID = 1;
		DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, resrcDataID);
		m_pMark[HUNGER].Reset(new ReactionMark(rIDs, rResrc, HUNGER, rFishDiffPos));
	}
	
	// WARNING 
	{
		int resrcDataID = 1;
		DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, resrcDataID);
		m_pMark[WARNING].Reset(new ReactionMark(rIDs, rResrc, WARNING, rFishDiffPos));
	}

	// ATTACK
	{
		int resrcDataID = 1;
		DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, resrcDataID);
		m_pMark[ATTACK].Reset(new ReactionMark(rIDs, rResrc, ATTACK, rFishDiffPos));
	}

	// DISCOVERY
	{
		int resrcDataID = 1;
		DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, resrcDataID);
		m_pMark[DISCOVERY].Reset(new ReactionMark(rIDs, rResrc, DISCOVERY, rFishDiffPos));
	}

	// REFUGE
	{
		int resrcDataID = 1;
		DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, resrcDataID);
		m_pMark[REFUGE].Reset(new ReactionMark(rIDs, rResrc, REFUGE, rFishDiffPos));
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
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
