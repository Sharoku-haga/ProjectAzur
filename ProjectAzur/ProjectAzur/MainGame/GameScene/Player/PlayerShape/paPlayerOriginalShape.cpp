//==================================================================================================================================//
//!< @file		paPlayerOriginalShape.cpp
//!< @brief		pa::PlayerOriginalShapeクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/21	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "sl/Library/Utility/Calculation/slCalculationFunc.h"
#include "sl/Library/Utility/slTemplateFunction.h"
#include "sl/Library/Utility/slDefine.h"
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "paPlayerOriginalShape.h"
#include "../../../DrawingResrcDataFile/paDrawingResrcDataFile.h"

namespace pa
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const	D3DXCOLOR	NormalStateColorVal		= 0xffffffff;		// 通常状態のときのカラー値
const	D3DXCOLOR	InvisibleStateColorVal	= 0x55ffffff;		// 透明状態のときのカラー値 

}

/* Public Functions ------------------------------------------------------------------------------------------- */

PlayerOriginalShape::PlayerOriginalShape()
	: m_rLibrary(sl::DX11GraphicsLibrary::Instance())
	, m_IsInvisible(false)
{}

PlayerOriginalShape::~PlayerOriginalShape()
{}

void PlayerOriginalShape::Initialize(const sl::DrawingID&	rIDs
									, const std::string&	rResrcDataFilePath
									, const PlayerParam&	rParam)
{
	//  描画データの作成
	m_pDrawingData.Reset(new ObjDrawingData());
	m_pDrawingData->m_Pos = rParam.m_Pos;
	m_pDrawingData->m_Angle = rParam.m_Angle;
	m_pDrawingData->m_IDs = rIDs;

	// 2Dモデル作成
	DrawingResrcDataFile::Instance().LoadDataFile(rResrcDataFilePath);
	DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, 1);
	sl::Model2DCreationData data(rResrc.m_Width, rResrc.m_Height, rResrc.m_UVRect, true);
	m_pDrawingData->m_IDs.m_ModelID = m_rLibrary.CreateDXModel2D(data);

	// アニメーション作成
	sl::UVAnimeCreationData animeData;
	animeData.m_AnimePatternCount = 1;
	animeData.m_AnimeWaitingTime = 0;
	animeData.m_StartUV = rResrc.m_UVRect;
	animeData.m_ScrollTu = 0.0f;
	animeData.m_ScrollTv = 0.0f;
	m_pDrawingData->m_IDs.m_UVAnimeID = m_rLibrary.CreateAnimatoin(animeData);

	m_IsFacingRight = rParam.m_IsFacingRight;
}

void PlayerOriginalShape::Update(const PlayerParam&	rParam)
{
	m_pDrawingData->m_Pos = rParam.m_Pos;
	m_pDrawingData->m_Angle = rParam.m_Angle;

	if(m_rLibrary.UpdateUVAnime(m_pDrawingData->m_IDs.m_ModelID, m_pDrawingData->m_IDs.m_UVAnimeID, true))
	{	// アニメーションが更新されたら反転処理を行う
		ProcessImageReversal(rParam);
		if(m_IsFacingRight != rParam.m_IsFacingRight)
		{
			m_IsFacingRight = rParam.m_IsFacingRight;
		}
	
		ProcessTransparent(rParam);
		return;
	}

	// 前の状態(右向いているかどうか)が異なっていたら反転処理を行う
	if(m_IsFacingRight != rParam.m_IsFacingRight)
	{
		ProcessImageReversal(rParam);
		m_IsFacingRight = rParam.m_IsFacingRight;
	}

	ProcessTransparent(rParam);
}

void PlayerOriginalShape::AdjustDrawingData(const PlayerParam&	rParam)
{
	m_pDrawingData->m_Pos = rParam.m_Pos;
}

void PlayerOriginalShape::Draw(const D3DXVECTOR2&	rBasePointPos)
{
	D3DXMATRIX matWorld;
	D3DXVECTOR2 drawingPos = (m_pDrawingData->m_Pos - rBasePointPos);

	sl::calculation::Calculate2DMatWorld(&matWorld, drawingPos);

	sl::Basic2DConstantBuffer constantBuffer;
	constantBuffer.m_MatWorld = matWorld;
	D3DXMatrixTranspose(&constantBuffer.m_MatWorld, &constantBuffer.m_MatWorld);

	sl::fRect bufferSize = m_rLibrary.GetBackBufferSize();
	constantBuffer.m_WindowSize.x = bufferSize.m_Right - bufferSize.m_Left;
	constantBuffer.m_WindowSize.y = bufferSize.m_Bottom - bufferSize.m_Top;
	m_rLibrary.DrawModel2D(m_pDrawingData->m_IDs, &constantBuffer);	
}

void PlayerOriginalShape::Finalize()
{
	m_rLibrary.ReleaseUVAnimation(m_pDrawingData->m_IDs.m_UVAnimeID);
	m_rLibrary.ReleaseDXModel2D(m_pDrawingData->m_IDs.m_ModelID);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void PlayerOriginalShape::ProcessImageReversal(const PlayerParam&	rParam)
{
	sl::fRect currentUVRect;
	m_rLibrary.InformUVData(m_pDrawingData->m_IDs.m_ModelID, currentUVRect);
	
	if(rParam.m_IsFacingRight
		&& currentUVRect.m_Left > currentUVRect.m_Right)
	{	// 左向きにする
		sl::SwapTemplate(currentUVRect.m_Left, currentUVRect.m_Right);
		m_rLibrary.SetDXModel2DUVData(m_pDrawingData->m_IDs.m_ModelID, currentUVRect);
		return;
	}

	if(RESULT_FALSE(rParam.m_IsFacingRight)
		&& currentUVRect.m_Left < currentUVRect.m_Right)
	{	// 右向きにする
		sl::SwapTemplate(currentUVRect.m_Left, currentUVRect.m_Right);
		m_rLibrary.SetDXModel2DUVData(m_pDrawingData->m_IDs.m_ModelID, currentUVRect);
	}
}

void PlayerOriginalShape::ProcessTransparent(const PlayerParam&	rParam)
{
	if(rParam.m_CurrentState != PLAYER_STATE::WAITING)
	{
		if(m_IsInvisible)
		{	// 透明処理を元に戻す
			std::vector<D3DXCOLOR> color(m_rLibrary.GetModel2DVertexCount(), NormalStateColorVal);
			m_rLibrary.SetDXModel2DColorData(m_pDrawingData->m_IDs.m_ModelID, color);
			m_IsInvisible = false;
		}

		return;
	}

	if(RESULT_FALSE(m_IsInvisible))
	{
		std::vector<D3DXCOLOR> color(m_rLibrary.GetModel2DVertexCount(), InvisibleStateColorVal);
		m_rLibrary.SetDXModel2DColorData(m_pDrawingData->m_IDs.m_ModelID, color);
		m_IsInvisible = true;
	}
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
