//==================================================================================================================================//
//!< @file		paPlayerShape.cpp
//!< @brief		pa::PlayerShapeクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/05	更新履歴：2017/12/07
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <vector>
#include "sl/Library/Utility/Calculation/slCalculationFunc.h"
#include "sl/Library/Utility/slTemplateFunction.h"
#include "sl/Library/Utility/slDefine.h"
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "paPlayerShape.h"
#include "../../DrawingResrcDataFile/paDrawingResrcDataFile.h"

namespace pa
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const	D3DXCOLOR	NormalStateColorVal		= 0xffffffff;		// 通常状態のときのカラー値
const	D3DXCOLOR	InvisibleStateColorVal	= 0x55ffffff;		// 透明状態のときのカラー値 

}

/* Public Functions ------------------------------------------------------------------------------------------- */

PlayerShape::PlayerShape(const sl::DrawingID&	rIDs
						, const char*	pResrcDataFilePath)
	: m_rLibrary(sl::DX11GraphicsLibrary::Instance())
	, m_InitialShapeID(rIDs)
	, m_pResrcDataFilePath(pResrcDataFilePath)
	, m_IsInvisible(false)
{}

void PlayerShape::Initialize(const PlayerParam&	rParam)
{
	// 2Dモデル作成
	DrawingResrcDataFile::Instance().LoadDataFile(m_pResrcDataFilePath);
	DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(m_pResrcDataFilePath, 0);
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
	m_pDrawingData->m_Pos = rParam.m_Pos;
	m_pDrawingData->m_Angle = rParam.m_Angle;
	m_pDrawingData->m_IDs = m_InitialShapeID;
	int	 drawTaskPriority = 2;		// 描画タスクの優先度
	m_pDrawingData->m_pTask.Reset(new DrawTask(drawTaskPriority, std::bind(&pa::PlayerShape::Draw, this)));

	m_rLibrary.InformSizeData(m_pDrawingData->m_IDs.m_ModelID, m_CurrentRectSize);
	m_IsFacingRight = rParam.m_IsFacingRight;
}

void PlayerShape::Update(const PlayerParam&	rParam)
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

void PlayerShape::ChangeShape(const sl::DrawingID&	rIDs)
{
	m_pDrawingData->m_IDs = rIDs;
	m_rLibrary.InitUVAnime(m_pDrawingData->m_IDs.m_ModelID, m_pDrawingData->m_IDs.m_UVAnimeID);
	m_rLibrary.InformSizeData(m_pDrawingData->m_IDs.m_ModelID, m_CurrentRectSize);
	m_IsInvisible = false;		// 透明は初期形状のみの動作なので、ここでfalseにしておく
}

void PlayerShape::ChangeInitialShape()
{
	m_pDrawingData->m_IDs = m_InitialShapeID;
	m_rLibrary.InitUVAnime(m_pDrawingData->m_IDs.m_ModelID, m_pDrawingData->m_IDs.m_UVAnimeID);
	m_rLibrary.InformSizeData(m_pDrawingData->m_IDs.m_ModelID, m_CurrentRectSize);

	// 念の為、透明処理をきっておく
	std::vector<D3DXCOLOR> color(m_rLibrary.GetModel2DVertexCount(), NormalStateColorVal);
	m_rLibrary.SetDXModel2DColorData(m_pDrawingData->m_IDs.m_ModelID, color);
	m_IsInvisible = false;
}

const sl::fRect& PlayerShape::InformShapeSize()
{	/** @todo スケール処理も加えるかも知れない */
	return m_CurrentRectSize;
}

void PlayerShape::AdjustDrawingData(const PlayerParam& rParam)
{
	m_pDrawingData->m_Pos = rParam.m_Pos;
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

void PlayerShape::ProcessImageReversal(const PlayerParam&	rParam)
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

void PlayerShape::ProcessTransparent(const PlayerParam&	rParam)
{
	if(rParam.m_CurrentState != PLAYER_STATE::WAITING
		|| m_pDrawingData->m_IDs.m_ModelID.m_Num != m_InitialShapeID.m_ModelID.m_Num)
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
