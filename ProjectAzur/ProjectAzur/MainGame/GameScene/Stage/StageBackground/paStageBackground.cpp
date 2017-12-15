//==================================================================================================================================//
//!< @file		paStageBackground.cpp
//!< @brief		pa::StageBackgroundクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/11	更新履歴：2017/12/15
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "sl/Library/Graphics/slGraphicsDeclaration.h"
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "sl/Library/Utility/Calculation/slCalculationFunc.h"
#include "paStageBackground.h"
#include "../../../paObjDrawingData.h"
#include "../../../DrawingResrcDataFile/paDrawingResrcDataFile.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

StageBackground::StageBackground(const sl::DrawingID& rID
								, const std::string& rResrcDataFilePath)
	: m_pDrawingData(new ObjDrawingData())
	, m_ResrcDataFilePath(rResrcDataFilePath)
{
	m_pDrawingData->m_IDs = rID;
}

StageBackground::~StageBackground()
{
	Finalize();
}

void StageBackground::Initialize()
{
	// 2Dモデルを生成
	DrawingResrcDataFile::Instance().LoadDataFile(m_ResrcDataFilePath);
	DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(m_ResrcDataFilePath, 11);
	sl::Model2DCreationData data(rResrc.m_Width, rResrc.m_Height, rResrc.m_UVRect, false);
	m_pDrawingData->m_IDs.m_ModelID = sl::DX11GraphicsLibrary::Instance().CreateDXModel2D(data);

	int	 drawTaskPriority = 0;		// 描画タスクの優先度
	m_pDrawingData->m_pTask.Reset(new DrawTask(drawTaskPriority, std::bind(&pa::StageBackground::Draw, this)));

	m_pDrawingData->m_Pos.x = 0.0f;
	m_pDrawingData->m_Pos.y = 0.0f;
}

void StageBackground::Update()
{
	// 空関数
}

void StageBackground::Finalize()
{
	// 空関数
}

void StageBackground::Draw()
{
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
