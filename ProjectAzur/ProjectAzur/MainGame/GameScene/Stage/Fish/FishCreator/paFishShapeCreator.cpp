//==================================================================================================================================//
//!< @file		paFishShapeCreator.cpp
//!< @brief		pa::FishShapeCreatorクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/28	更新履歴：2018/01/21
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paFishShapeCreator.h"
#include "../../../../DrawingResrcDataFile/paDrawingResrcDataFile.h"

namespace pa
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const int		m_DrawingDataID = 20;		// 描画データID

}

/* Public Functions ------------------------------------------------------------------------------------------- */

FishShapeCreator::FishShapeCreator(const sl::DrawingID&	rIDs
									, const char*	pResrcDataFilePath)
	: m_rLibrary(sl::DX11GraphicsLibrary::Instance())
	, m_BaseShapeID(rIDs)
	, m_pResrcDataFilePath(pResrcDataFilePath)
{}

FishShapeCreator::~FishShapeCreator()
{}

sl::UniquePtr<FishShape> FishShapeCreator::CreateFishShape()
{
	// モデルの生成
	std::vector<sl::ModelID> modelIDs;
	CreateModel(modelIDs);

	// UVアニメの生成
	std::vector<sl::UVAnimeID> uvAnimeIDs;
	CreateUVAnime(uvAnimeIDs);

	return sl::UniquePtr<FishShape>(new FishShape(m_BaseShapeID, modelIDs, uvAnimeIDs));
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void FishShapeCreator::CreateModel(std::vector<sl::ModelID>& rModelIDs)
{
	/** 現在はモデル1つのみ生成 */
	DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(m_pResrcDataFilePath, m_DrawingDataID);
	sl::Model2DCreationData data(rResrc.m_Width, rResrc.m_Height, rResrc.m_UVRect, true);
	rModelIDs.emplace_back(m_rLibrary.CreateDXModel2D(data));
}

void FishShapeCreator::CreateUVAnime(std::vector<sl::UVAnimeID>& rUVAnimeIDs)
{
	DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(m_pResrcDataFilePath, m_DrawingDataID);

	/** @todo 現在はアニメを1つだけ生成 */
	sl::UVAnimeCreationData animeData;
	animeData.m_AnimePatternCount = 1;
	animeData.m_AnimeWaitingTime = 0;
	animeData.m_StartUV = rResrc.m_UVRect;
	animeData.m_ScrollTu = 0.0f;
	animeData.m_ScrollTv = 0.0f;
	rUVAnimeIDs.emplace_back(m_rLibrary.CreateAnimatoin(animeData));
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
