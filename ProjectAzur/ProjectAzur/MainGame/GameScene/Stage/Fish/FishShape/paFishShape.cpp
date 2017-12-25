//==================================================================================================================================//
//!< @file		paFishShape.cpp
//!< @brief		pa::FishShapeクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/23	更新履歴：2017/12/26
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <algorithm>
#include <iterator> 
#include "sl/Library/Utility/Calculation/slCalculationFunc.h"
#include "sl/Library/Utility/slTemplateFunction.h"
#include "sl/Library/Utility/slDefine.h"
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "paFishShape.h"
#include "../../../../DrawingResrcDataFile/paDrawingResrcDataFile.h"
#include "../../../../paObjDrawingData.h"
#include "../../paStageObjBase.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

FishShape::FishShape(const sl::DrawingID&	rIDs
					, std::vector<sl::ModelID>&	rModelIDs
					, std::vector<sl::UVAnimeID>&	rUVAnimeIDs)
	: m_rLibrary(sl::DX11GraphicsLibrary::Instance())
	, m_pDrawingData(new ObjDrawingData())
	, m_IsFacingRight(false)
{
	m_pDrawingData->m_IDs = rIDs;
	std::copy(rModelIDs.begin(), rModelIDs.end(), std::back_inserter(m_ModelIDs) );
	std::copy(rUVAnimeIDs.begin(), rUVAnimeIDs.end(), std::back_inserter(m_UVAnimeIDs) );
}

FishShape::~FishShape()
{
	Finalize();
}

void FishShape::Initialize(const FishParam& rParam)
{
	// パラメータから情報を更新する
	m_pDrawingData->m_Pos = rParam.m_Pos;
	m_pDrawingData->m_Angle = rParam.m_Angle;

	// Param使用するモデルIDとアニメIDを設定する
	/** @todo 2017/12/26 仮の値を入れている */
	m_pDrawingData->m_IDs.m_ModelID		= m_ModelIDs[0];
	m_pDrawingData->m_IDs.m_UVAnimeID	= m_UVAnimeIDs[0];

	m_IsFacingRight = rParam.m_IsFacingRight;
}

void FishShape::Update(const FishParam& rParam)
{
	m_pDrawingData->m_Pos = rParam.m_Pos;
	m_pDrawingData->m_Angle = rParam.m_Angle;

	
	if(m_rLibrary.UpdateUVAnime(m_pDrawingData->m_IDs.m_ModelID, m_pDrawingData->m_IDs.m_UVAnimeID, true))
	{	// アニメーションが更新されたら反転処理
		ProcessImageReversal(rParam);
		if(m_IsFacingRight != rParam.m_IsFacingRight)
		{
			m_IsFacingRight = rParam.m_IsFacingRight;
		}
		return;
	}

	// 前の状態(右向いているかどうか)が異なっていたら反転処理を行う
	if(m_IsFacingRight != rParam.m_IsFacingRight)
	{
		ProcessImageReversal(rParam);
		m_IsFacingRight = rParam.m_IsFacingRight;
	}
}

void FishShape::Finalize()
{
	for(auto modelID : m_ModelIDs)
	{
		m_rLibrary.ReleaseDXModel2D(modelID);
	}

	for(auto uvANimeID : m_UVAnimeIDs)
	{
		m_rLibrary.ReleaseUVAnimation(uvANimeID);
	}
}

const sl::fRect& FishShape::FishShape::GetCurrentRectSize()
{
	m_rLibrary.InformSizeData(m_pDrawingData->m_IDs.m_ModelID, m_CurrentRectSize);
	return m_CurrentRectSize;
}

void FishShape::AdjustDrawingData(const FishParam& rParam)
{
	m_pDrawingData->m_Pos = rParam.m_Pos;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void FishShape::Draw()
{
	D3DXMATRIX matWorld;
	D3DXVECTOR2 drawingPos = (m_pDrawingData->m_Pos - StageObjBase::GetBasePointPos());

	sl::calculation::Calculate2DMatWorld(&matWorld, drawingPos);

	sl::Basic2DConstantBuffer constantBuffer;
	constantBuffer.m_MatWorld = matWorld;
	D3DXMatrixTranspose(&constantBuffer.m_MatWorld, &constantBuffer.m_MatWorld);

	sl::fRect bufferSize = m_rLibrary.GetBackBufferSize();
	constantBuffer.m_WindowSize.x = bufferSize.m_Right - bufferSize.m_Left;
	constantBuffer.m_WindowSize.y = bufferSize.m_Bottom - bufferSize.m_Top;
	m_rLibrary.DrawModel2D(m_pDrawingData->m_IDs, &constantBuffer);
}

void FishShape::ProcessImageReversal(const FishParam& rParam)
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

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
