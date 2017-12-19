//==================================================================================================================================//
//!< @file		paEnergyBlock.cpp
//!< @brief		pa::EnergyBlockクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/18	更新履歴：2017/12/19
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "sl/Library/Graphics/slGraphicsDeclaration.h"
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "sl/Library/Utility/Calculation/slCalculationFunc.h"
#include "paEnergyBlock.h"
#include "../../../paObjDrawingData.h"
#include ".././../../DrawingResrcDataFile/paDrawingResrcDataFile.h" 

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

EnergyBlock::EnergyBlock(const sl::DrawingID& rIDs
						, const std::string&  rResrcDataFilePath
						, const D3DXVECTOR2&  rGaugePosDiff)
	: m_pDrawingData(new ObjDrawingData())
	, m_GaugeDiffPos(rGaugePosDiff)
{
	m_pDrawingData->m_IDs = rIDs;
	DrawingResrcDataFile::Instance().LoadDataFile(rResrcDataFilePath);

	int	resrcDataID = 10;		// リソースID
	DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, resrcDataID);
	sl::Model2DCreationData data(rResrc.m_Width, rResrc.m_Height, rResrc.m_UVRect, false);
	m_pDrawingData->m_IDs.m_ModelID = sl::DX11GraphicsLibrary::Instance().CreateDXModel2D(data);
}

EnergyBlock::~EnergyBlock()
{
	sl::DX11GraphicsLibrary::Instance().ReleaseDXModel2D(m_pDrawingData->m_IDs.m_ModelID);
}

void EnergyBlock::Draw(const D3DXVECTOR2& rGaugePos)
{
	// 座標を更新 ゲージの座標に差分を足して表示
	m_pDrawingData->m_Pos = (rGaugePos + m_GaugeDiffPos);

	D3DXMATRIX matWorld;
	sl::calculation::Calculate2DMatWorld(&matWorld, m_pDrawingData->m_Pos);

	sl::Basic2DConstantBuffer constantBuffer;
	constantBuffer.m_MatWorld = matWorld;
	D3DXMatrixTranspose(&constantBuffer.m_MatWorld, &constantBuffer.m_MatWorld);

	sl::fRect bufferSize = sl::DX11GraphicsLibrary::Instance().GetBackBufferSize();
	constantBuffer.m_WindowSize.x = bufferSize.m_Right - bufferSize.m_Left;
	constantBuffer.m_WindowSize.y = bufferSize.m_Bottom - bufferSize.m_Top;
	sl::DX11GraphicsLibrary::Instance().DrawModel2D(m_pDrawingData->m_IDs, &constantBuffer);
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
