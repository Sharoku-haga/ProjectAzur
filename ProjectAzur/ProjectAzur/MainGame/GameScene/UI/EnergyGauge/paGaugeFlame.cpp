//==================================================================================================================================//
//!< @file		paGaugeFlame.cpp
//!< @brief		pa::GaugeFlameクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/18	更新履歴：2017/12/19
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "sl/Library/Graphics/slGraphicsDeclaration.h"
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "sl/Library/Utility/Calculation/slCalculationFunc.h"
#include "paGaugeFlame.h"
#include "../../../paObjDrawingData.h"
#include ".././../../DrawingResrcDataFile/paDrawingResrcDataFile.h" 

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

GaugeFlame::GaugeFlame(const sl::DrawingID& rIDs
					, const std::string&	rResrcDataFilePath)
	: m_pDrawingData(new ObjDrawingData())
{
	m_pDrawingData->m_IDs = rIDs;
	DrawingResrcDataFile::Instance().LoadDataFile(rResrcDataFilePath);

	int	resrcDataID = 9;		// リソースID

	DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(rResrcDataFilePath, resrcDataID);
	sl::Model2DCreationData data(rResrc.m_Width, rResrc.m_Height, rResrc.m_UVRect, false);
	m_pDrawingData->m_IDs.m_ModelID = sl::DX11GraphicsLibrary::Instance().CreateDXModel2D(data);
}

GaugeFlame::~GaugeFlame()
{
	sl::DX11GraphicsLibrary::Instance().ReleaseDXModel2D(m_pDrawingData->m_IDs.m_ModelID);
}

void GaugeFlame::Draw(const D3DXVECTOR2& rGaugePos)
{
	// 座標を更新
	m_pDrawingData->m_Pos = rGaugePos;

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
