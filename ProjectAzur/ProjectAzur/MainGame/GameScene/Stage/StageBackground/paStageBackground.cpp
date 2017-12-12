//==================================================================================================================================//
//!< @file		paStageBackground.cpp
//!< @brief		pa::StageBackgroundクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/11	更新履歴：2017/12/13
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "sl/Library/Graphics/slGraphicsDeclaration.h"
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "sl/Library/Utility/Calculation/slCalculationFunc.h"
#include "paStageBackground.h"
#include "../../../paObjDrawingData.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

StageBackground::StageBackground(const std::string& rResrcDataFilePath)
	: m_ResrcDataFilePath(rResrcDataFilePath)
{}

StageBackground::~StageBackground()
{
	Finalize();
}

void StageBackground::Initialize()
{}

void StageBackground::Update()
{}

void StageBackground::Finalize()
{
	// 空関数
}

void StageBackground::Draw()
{
	// ベースポイントの現在の座標を代入する
	//m_pDrawingData->m_Pos = m_BasePointPos;

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
