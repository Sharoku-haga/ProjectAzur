//==================================================================================================================================//
//!< @file		paPlayerFishShapeLine.cpp		
//!< @brief		pa::PlayerFishShapeLineクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/22	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "sl/Library/Utility/Calculation/slCalculationFunc.h"
#include "sl/Library/Utility/slTemplateFunction.h"
#include "sl/Library/Utility/slDefine.h"
#include "paPlayerFishShapeLine.h"
#include "../../../DrawingResrcDataFile/paDrawingResrcDataFile.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

PlayerFishShapeLine::PlayerFishShapeLine(const sl::DrawingID&	rIDs
										, const std::string&	rResrcDataFilePath)
	: m_rLibrary(sl::DX11GraphicsLibrary::Instance())
	, m_pDrawingData(new ObjDrawingData())
	, m_IsFacingRight(true)
{
	m_pDrawingData->m_Pos.x = 0.0f;
	m_pDrawingData->m_Pos.y = 0.0f;
	m_pDrawingData->m_Angle = 0.0f;
	m_pDrawingData->m_IDs = rIDs;

	// モデル作成
	//DrawingResrcDataFile::Instance().LoadDataFile(rResrcDataFilePath);

	int resrcDataID = 12;
	DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, resrcDataID);
	sl::Model2DCreationData data(rResrc.m_Width, rResrc.m_Height, rResrc.m_UVRect, true);
	m_pDrawingData->m_IDs.m_ModelID = m_rLibrary.CreateDXModel2D(data);

}

PlayerFishShapeLine::~PlayerFishShapeLine()
{
	m_rLibrary.ReleaseDXModel2D(m_pDrawingData->m_IDs.m_ModelID);
}

void PlayerFishShapeLine::ChangeStatus(const sl::fRect& rRectSize)
{
	m_rLibrary.SetDXModel2DSizeData(m_pDrawingData->m_IDs.m_ModelID
								, (rRectSize.m_Right - rRectSize.m_Left)
								, (rRectSize.m_Bottom -rRectSize.m_Top));
	
	sl::fRect currentUVRect;
	m_rLibrary.InformUVData(m_pDrawingData->m_IDs.m_ModelID, currentUVRect);

	if(currentUVRect.m_Left > currentUVRect.m_Right)
	{
		m_IsFacingRight = false;
	}
	else
	{
		m_IsFacingRight = true;
	}
}

void PlayerFishShapeLine::Update(const PlayerParam&	rParam)
{
	m_pDrawingData->m_Pos = rParam.m_Pos;
	m_pDrawingData->m_Angle = rParam.m_Angle;

	// 前の状態(右向いているかどうか)が異なっていたら反転処理を行う
	if(m_IsFacingRight != rParam.m_IsFacingRight)
	{
		ProcessImageReversal();
	}
}

void PlayerFishShapeLine::AdjustDrawingData(const PlayerParam&	rParam)
{
	m_pDrawingData->m_Pos = rParam.m_Pos;
}

void PlayerFishShapeLine::Draw(const D3DXVECTOR2&	rBasePointPos)
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

/* Private Functions ------------------------------------------------------------------------------------------ */

void PlayerFishShapeLine::ProcessImageReversal()
{
	sl::fRect currentUVRect;
	m_rLibrary.InformUVData(m_pDrawingData->m_IDs.m_ModelID, currentUVRect);
	
	if( currentUVRect.m_Left > currentUVRect.m_Right)
	{	
		sl::SwapTemplate(currentUVRect.m_Left, currentUVRect.m_Right);
		m_rLibrary.SetDXModel2DUVData(m_pDrawingData->m_IDs.m_ModelID, currentUVRect);
		m_IsFacingRight = true;
		return;
	}

	if(currentUVRect.m_Left < currentUVRect.m_Right)
	{	
		sl::SwapTemplate(currentUVRect.m_Left, currentUVRect.m_Right);
		m_rLibrary.SetDXModel2DUVData(m_pDrawingData->m_IDs.m_ModelID, currentUVRect);
		m_IsFacingRight = false;
	}
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
