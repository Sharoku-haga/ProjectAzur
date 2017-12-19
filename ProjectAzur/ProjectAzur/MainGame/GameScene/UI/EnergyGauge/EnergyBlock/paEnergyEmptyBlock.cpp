//==================================================================================================================================//
//!< @file		paEnergyEmptyBlock.cpp
//!< @brief		pa::EnergyEmptyBlockクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/19	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "sl/Library/Graphics/slGraphicsDeclaration.h"
#include "sl/Library/Utility/Calculation/slCalculationFunc.h"
#include "paEnergyEmptyBlock.h"
#include "../../../../paObjDrawingData.h"
#include "../../../../DrawingResrcDataFile/paDrawingResrcDataFile.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

EnergyEmptyBlock::EnergyEmptyBlock(const sl::DrawingID& rIDs
								, const std::string& rResrcDataFilePath
								, const D3DXVECTOR2& rGaugePosDiff
								, int oneEnergyBlockTime)
	: m_rGraphicsLibrary(sl::DX11GraphicsLibrary::Instance())
	, m_pDrawingData(new ObjDrawingData())
	, m_GaugeDiffPos(rGaugePosDiff)
{
	m_pDrawingData->m_IDs = rIDs;
	DrawingResrcDataFile::Instance().LoadDataFile(rResrcDataFilePath);

	int	resrcDataID = 10;		// リソースID
	DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, resrcDataID);
	
	// 元の横の大きさは保持し、値は0.0fを入れてモデル作成
	m_OriginalWidth = rResrc.m_Width;
	m_OriginalHeight = rResrc.m_Height;
	m_CurrentWidth = 0.0f;
	sl::Model2DCreationData data(m_CurrentWidth, rResrc.m_Height, rResrc.m_UVRect, false);
	m_pDrawingData->m_IDs.m_ModelID = m_rGraphicsLibrary.CreateDXModel2D(data);

	//* 色変更 @todo 画像がきたらここのソースは除去
	std::vector<D3DXCOLOR> color(m_rGraphicsLibrary.GetModel2DVertexCount()
								, 0xff000000);
	m_rGraphicsLibrary.SetDXModel2DColorData(m_pDrawingData->m_IDs.m_ModelID
															, color);
	//*/

	// スクロールスピードの計算
	CalculateGaugeScrollSpeed(oneEnergyBlockTime);
}

EnergyEmptyBlock::~EnergyEmptyBlock()
{}

bool EnergyEmptyBlock::UpdateWidthSize(int elapsedTime)
{
	m_CurrentWidth = m_GaugeScrollSpeed * elapsedTime;

	if(m_CurrentWidth >= m_OriginalWidth)
	{
		m_rGraphicsLibrary.SetDXModel2DSizeData(m_pDrawingData->m_IDs.m_ModelID
												, m_OriginalWidth, m_OriginalHeight);
		return true;
	}

	m_rGraphicsLibrary.SetDXModel2DSizeData(m_pDrawingData->m_IDs.m_ModelID
												, m_CurrentWidth, m_OriginalHeight);
	return false;
}

void EnergyEmptyBlock::UpdateWidthSizeAll()
{
	m_rGraphicsLibrary.SetDXModel2DSizeData(m_pDrawingData->m_IDs.m_ModelID
											, m_OriginalWidth, m_OriginalHeight);
}

void EnergyEmptyBlock::Draw(const D3DXVECTOR2& rGaugePos)
{
	// 座標を更新 ゲージの座標に差分を足して表示
	m_pDrawingData->m_Pos = (rGaugePos + m_GaugeDiffPos);

	D3DXMATRIX matWorld;
	sl::calculation::Calculate2DMatWorld(&matWorld, m_pDrawingData->m_Pos);

	sl::Basic2DConstantBuffer constantBuffer;
	constantBuffer.m_MatWorld = matWorld;
	D3DXMatrixTranspose(&constantBuffer.m_MatWorld, &constantBuffer.m_MatWorld);

	sl::fRect bufferSize = m_rGraphicsLibrary.GetBackBufferSize();
	constantBuffer.m_WindowSize.x = bufferSize.m_Right - bufferSize.m_Left;
	constantBuffer.m_WindowSize.y = bufferSize.m_Bottom - bufferSize.m_Top;
	m_rGraphicsLibrary.DrawModel2D(m_pDrawingData->m_IDs, &constantBuffer);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void EnergyEmptyBlock::CalculateGaugeScrollSpeed(int oneEnergyBlockTime)
{
	m_GaugeScrollSpeed = m_OriginalWidth / oneEnergyBlockTime;
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
