//==================================================================================================================================//
//!< @file		paPlayerFishShell.cpp
//!< @brief		pa::PlayerFishShellクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/21	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <algorithm>
#include <iterator> 
#include "sl/Library/Utility/Calculation/slCalculationFunc.h"
#include "sl/Library/Utility/slTemplateFunction.h"
#include "sl/Library/Utility/slDefine.h"
#include "paPlayerFishShell.h"
#include "../../Stage/Fish/FishShape/paFishShape.h"
#include "../../../DrawingResrcDataFile/paDrawingResrcDataFile.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

PlayerFishShell::PlayerFishShell()
	: m_rLibrary(sl::DX11GraphicsLibrary::Instance())
	, m_IsFacingRight(true)
{}

PlayerFishShell::~PlayerFishShell()
{}

void PlayerFishShell::Initialize(const sl::DrawingID&	rIDs
								, const std::string&	rResrcDataFilePath)
{
	//*
	m_pDrawingData.Reset();
	m_RectSize.m_Left	= 0.0f;
	m_RectSize.m_Bottom	= 0.0f;
	m_RectSize.m_Right	= 0.0f;
	m_RectSize.m_Top	= 0.0f;
	m_HasCreatedShell	= false;
	// */

	/* テストコードブロック
	m_pDrawingData.Reset(new ObjDrawingData());
	m_pDrawingData->m_Pos.x = 0.0f;
	m_pDrawingData->m_Pos.y = 0.0f;
	m_pDrawingData->m_Angle = 0.0f;
	m_pDrawingData->m_IDs = rIDs;
	DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, 20);
	sl::Model2DCreationData data(rResrc.m_Width, rResrc.m_Height, rResrc.m_UVRect, true);
	m_pDrawingData->m_IDs.m_ModelID = m_rLibrary.CreateDXModel2D(data);
	m_rLibrary.InformSizeData(m_pDrawingData->m_IDs.m_ModelID, m_RectSize);
	m_HasCreatedShell	= true;
	// */

	m_pFishLine.Reset( new PlayerFishShapeLine(rIDs, rResrcDataFilePath));
}

void PlayerFishShell::CreateShell(ObjDrawingData* pFishDrawingData)
{
	m_pDrawingData.Reset(pFishDrawingData);
	m_rLibrary.InformSizeData(m_pDrawingData->m_IDs.m_ModelID, m_RectSize);
	ProcessImageReversal();
	m_HasCreatedShell = true;

	m_pFishLine->ChangeStatus(m_RectSize);
}

void PlayerFishShell::DestroyShell()
{
	m_pDrawingData.Reset();
	m_RectSize.m_Left	= 0.0f;
	m_RectSize.m_Bottom	= 0.0f;
	m_RectSize.m_Right	= 0.0f;
	m_RectSize.m_Top	= 0.0f;
	m_HasCreatedShell	= false;
}

void PlayerFishShell::Update(const PlayerParam&	rParam)
{
	m_pDrawingData->m_Pos = rParam.m_Pos;
	m_pDrawingData->m_Angle = rParam.m_Angle;

	m_pFishLine->Update(rParam);

	// 前の状態(右向いているかどうか)が異なっていたら反転処理を行う
	if(m_IsFacingRight != rParam.m_IsFacingRight)
	{
		ProcessImageReversal();
	}
}

void PlayerFishShell::AdjustDrawingData(const PlayerParam&	rParam)
{
	m_pDrawingData->m_Pos = rParam.m_Pos;
	m_pFishLine->AdjustDrawingData(rParam);
}

void PlayerFishShell::Draw(const D3DXVECTOR2&	rBasePointPos)
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

	m_pFishLine->Draw(rBasePointPos);
}

void PlayerFishShell::Finalize()
{
	if(m_pDrawingData.UseRefCount() == 0)
	{
		return;
	}

	if(m_pDrawingData.UseRefCount() > 1)
	{
		return;
	}
	m_rLibrary.ReleaseDXModel2D(m_pDrawingData->m_IDs.m_ModelID);
	m_rLibrary.ReleaseUVAnimation(m_pDrawingData->m_IDs.m_UVAnimeID);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void PlayerFishShell::ProcessImageReversal()
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
