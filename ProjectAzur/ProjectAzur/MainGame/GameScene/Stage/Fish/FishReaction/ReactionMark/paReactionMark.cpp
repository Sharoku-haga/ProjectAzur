//==================================================================================================================================//
//!< @file		paReactionMark.cpp
//!< @brief		pa::ReactionMarkクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/22	更新履歴：2018/01/23
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "sl/Library/Utility/Calculation/slCalculationFunc.h"
#include "sl/Library/Utility/slTemplateFunction.h"
#include "sl/Library/Utility/slDefine.h"
#include "paReactionMark.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

ReactionMark::ReactionMark(const sl::DrawingID& rIDs
						, const DrawingResrcData& rResrc
						, const REACTION_MARK_TYPE& rMarkType
						, const D3DXVECTOR2& rFishDiffPos)
	: m_rLibrary(sl::DX11GraphicsLibrary::Instance())
	, m_pDrawingData(new ObjDrawingData())
	, m_FishDiffPos(rFishDiffPos)
	, m_MarkType(rMarkType)
	, m_IsFacingRight(true)
{
	m_pDrawingData->m_Pos.x = 0.0f;
	m_pDrawingData->m_Pos.y = 0.0f;
	m_pDrawingData->m_Angle = 0.0f;
	m_pDrawingData->m_IDs = rIDs;	

	sl::Model2DCreationData data(rResrc.m_Width, rResrc.m_Height, rResrc.m_UVRect, true);
	m_pDrawingData->m_IDs.m_ModelID = m_rLibrary.CreateDXModel2D(data);
}

ReactionMark::~ReactionMark()
{
	m_rLibrary.ReleaseDXModel2D(m_pDrawingData->m_IDs.m_ModelID);
}

void ReactionMark::Update(const FishParam& rParam)
{
	// 前の状態(右向いているかどうか)が異なっていたら反転処理を行う
	if(m_IsFacingRight != rParam.m_IsFacingRight)
	{
		m_FishDiffPos.x = -m_FishDiffPos.x;
		m_IsFacingRight = rParam.m_IsFacingRight;
	}
}

void ReactionMark::Draw(const FishParam& rParam, const D3DXVECTOR2& rBasePointPos)
{
	m_pDrawingData->m_Pos = rParam.m_Pos + m_FishDiffPos;
	m_pDrawingData->m_Angle = rParam.m_Angle;

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

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
