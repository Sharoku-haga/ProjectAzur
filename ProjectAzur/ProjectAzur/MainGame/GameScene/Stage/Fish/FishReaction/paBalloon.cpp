//==================================================================================================================================//
//!< @file		paBalloon.cpp
//!< @brief		pa::Balloonクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/09	更新履歴：2018/01/23
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "sl/Library/Graphics/slGraphicsDeclaration.h"
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "sl/Library/Utility/Calculation/slCalculationFunc.h"
#include "paBalloon.h"
#include "../../../../paObjDrawingData.h"
#include "../../../../DrawingResrcDataFile/paDrawingResrcDataFile.h"

namespace pa
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const int ResrcDataID = 24;		// リソースデータID

}

Balloon::Balloon(const sl::DrawingID&	rIDs
				, const std::string&	rResrcDataFilePath)
	: m_pDrawingData(new ObjDrawingData())
	, m_IsFacingRight(true)
{
	m_pDrawingData->m_IDs = rIDs;
	DrawingResrcDataFile::Instance().LoadDataFile(rResrcDataFilePath);

	DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, ResrcDataID);
	sl::Model2DCreationData data(rResrc.m_Width, rResrc.m_Height, rResrc.m_UVRect, true);
	m_pDrawingData->m_IDs.m_ModelID = sl::DX11GraphicsLibrary::Instance().CreateDXModel2D(data);
}

Balloon::~Balloon()
{
	sl::DX11GraphicsLibrary::Instance().ReleaseDXModel2D(m_pDrawingData->m_IDs.m_ModelID);
}

void Balloon::Initialize(const D3DXVECTOR2&	rFishPosDiff)
{
	m_FishDiffPos = rFishPosDiff;
}

void Balloon::Update(const FishParam& rParam)
{
	// 魚の向きによって画像反転処理を行う
	if(m_IsFacingRight != rParam.m_IsFacingRight)
	{
		ProcessImageReversal(rParam);
		m_IsFacingRight = rParam.m_IsFacingRight;
	}
}

void Balloon::Draw(const FishParam& rParam, const D3DXVECTOR2& rBasePointPos)
{
	// 座標を更新 ゲージの座標に差分を足して表示
	m_pDrawingData->m_Pos = (rParam.m_Pos + m_FishDiffPos) - rBasePointPos;
	m_pDrawingData->m_Angle = rParam.m_Angle;

	D3DXMATRIX matWorld;
	sl::calculation::Calculate2DMatWorld(&matWorld, m_pDrawingData->m_Pos, m_pDrawingData->m_Scale, m_pDrawingData->m_Angle);

	sl::Basic2DConstantBuffer constantBuffer;
	constantBuffer.m_MatWorld = matWorld;
	D3DXMatrixTranspose(&constantBuffer.m_MatWorld, &constantBuffer.m_MatWorld);

	sl::fRect bufferSize = sl::DX11GraphicsLibrary::Instance().GetBackBufferSize();
	constantBuffer.m_WindowSize.x = bufferSize.m_Right - bufferSize.m_Left;
	constantBuffer.m_WindowSize.y = bufferSize.m_Bottom - bufferSize.m_Top;
	sl::DX11GraphicsLibrary::Instance().DrawModel2D(m_pDrawingData->m_IDs, &constantBuffer);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void Balloon::ProcessImageReversal(const FishParam& rParam)
{
	m_FishDiffPos.x = -m_FishDiffPos.x;
	sl::fRect currentUVRect;
	sl::DX11GraphicsLibrary::Instance().InformUVData(m_pDrawingData->m_IDs.m_ModelID, currentUVRect);
	
	if(rParam.m_IsFacingRight
		&& currentUVRect.m_Left > currentUVRect.m_Right)
	{	// 左向きにする
		sl::SwapTemplate(currentUVRect.m_Left, currentUVRect.m_Right);
		sl::DX11GraphicsLibrary::Instance().SetDXModel2DUVData(m_pDrawingData->m_IDs.m_ModelID, currentUVRect);
		return;
	}

	if(RESULT_FALSE(rParam.m_IsFacingRight)
		&& currentUVRect.m_Left < currentUVRect.m_Right)
	{	// 右向きにする
		sl::SwapTemplate(currentUVRect.m_Left, currentUVRect.m_Right);
		sl::DX11GraphicsLibrary::Instance().SetDXModel2DUVData(m_pDrawingData->m_IDs.m_ModelID, currentUVRect);
	}
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
