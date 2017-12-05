//==================================================================================================================================//
//!< @file		paPlayerShape.cpp
//!< @brief		pa::PlayerShapeクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/05	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "sl/Library/Utility/Calculation/slCalculationFunc.h"
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "paPlayerShape.h"
#include "../../DrawingResrcDataFile/paDrawingResrcDataFile.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

PlayerShape::PlayerShape()
	: m_rLibrary(sl::DX11GraphicsLibrary::Instance())
{}

void PlayerShape::Initialize(const D3DXVECTOR2& rInitialPos
				, float initialAngle
				, const char*	pResrcDataFilePath
				, const sl::DrawingID&	rIDs)
{
	m_InitialShapeID = rIDs;
	
	// 2Dモデル作成
	DrawingResrcDataFile::Instance().LoadDataFile(pResrcDataFilePath);
	DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(pResrcDataFilePath, 0);
	sl::Model2DCreationData data(rResrc.m_Width, rResrc.m_Height, rResrc.m_UVRect, true);
	m_pDrawingData->m_IDs.m_ModelID = m_rLibrary.CreateDXModel2D(data);

	// アニメーション作成
	sl::UVAnimeCreationData animeData;
	animeData.m_AnimePatternCount = 1;
	animeData.m_AnimeWaitingTime = 0;
	animeData.m_StartUV = rResrc.m_UVRect;
	animeData.m_ScrollTu = 0.0f;
	animeData.m_ScrollTv = 0.0f;
	m_InitialShapeID.m_UVAnimeID = m_rLibrary.CreateAnimatoin(animeData);

	// 描画データの設定
	m_pDrawingData.Reset(new ObjDrawingData());
	m_pDrawingData->m_Pos = rInitialPos;
	m_pDrawingData->m_Angle = initialAngle;
	m_pDrawingData->m_IDs = m_InitialShapeID;
	int	 drawTaskPriority = 2;		// 描画タスクの優先度
	m_pDrawingData->m_pTask.Reset(new DrawTask(drawTaskPriority, std::bind(&pa::PlayerShape::Draw, this)));
}

void PlayerShape::Update(const D3DXVECTOR2& rPos, float angle)
{
	m_pDrawingData->m_Pos = rPos;
	m_pDrawingData->m_Angle = angle;
	m_rLibrary.UpdateUVAnime(m_pDrawingData->m_IDs.m_UVAnimeID, true);
}

void PlayerShape::ChangeShape(const sl::DrawingID&	rIDs)
{
	m_pDrawingData->m_IDs = rIDs;
	m_rLibrary.InitUVAnime(m_pDrawingData->m_IDs.m_UVAnimeID);
}

void PlayerShape::ChangeInitialShape()
{
	m_pDrawingData->m_IDs = m_InitialShapeID;
	m_rLibrary.InitUVAnime(m_pDrawingData->m_IDs.m_UVAnimeID);
}

sl::fRect PlayerShape::InformShapeSize()
{	// スケール値の処理も加える
	return sl::fRect();
}

void PlayerShape::Finalize()
{
	m_rLibrary.ReleaseUVAnimation(m_pDrawingData->m_IDs.m_UVAnimeID);
	m_rLibrary.ReleaseDXModel2D(m_pDrawingData->m_IDs.m_ModelID);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void PlayerShape::Draw()
{
	D3DXMATRIX matWorld;
	sl::calculation::Calculate2DMatWorld(&matWorld, m_pDrawingData->m_Pos);

	sl::Basic2DConstantBuffer constantBuffer;
	constantBuffer.m_MatWorld = matWorld;

	sl::fRect bufferSize = m_rLibrary.GetBackBufferSize();
	constantBuffer.m_WindowSize.x = bufferSize.m_Right - bufferSize.m_Left;
	constantBuffer.m_WindowSize.y = bufferSize.m_Bottom - bufferSize.m_Top;
	m_rLibrary.DrawModel2D(m_pDrawingData->m_IDs, &constantBuffer);	
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
