//==================================================================================================================================//
//!< @file		paTitleBackground.cpp
//!< @brief		pa::TitleBackgroundクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/11/30	更新履歴：2017/12/02
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "sl/Library/Graphics/slGraphicsDeclaration.h"
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "sl/Library/Utility/Calculation/slCalculationFunc.h"
#include "paTitleBackground.h"
#include "../../DrawingResrcDataFile/paDrawingResrcDataFile.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

TitleBackground::TitleBackground(const sl::DrawingID& rID)
	: m_pDrawingData(new ObjDrawingData())
{
	m_pDrawingData->m_IDs = rID;
}

TitleBackground::~TitleBackground()
{
	Finalize();
}

void TitleBackground::Initialize()
{
	m_pDrawingData->m_Pos.x = 0.0f;
	m_pDrawingData->m_Pos.y = 0.0f;

	// 2Dモデルを生成
	DrawingResrcDataFile::Instance().LoadDataFile("TitleBG.vtxd");
	DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData("TitleBG.vtxd", 1);
	sl::Model2DCreationData data(rResrc.m_Width, rResrc.m_Height, rResrc.m_UVRect, false);
	m_pDrawingData->m_IDs.m_ModelID = sl::DX11GraphicsLibrary::Instance().CreateDXModel2D(data);

	int	 drawTaskPriority = 0;		// 描画タスクの優先度
	m_pDrawingData->m_pTask.Reset(new DrawTask(drawTaskPriority, std::bind(&pa::TitleBackground::Draw, this)));

	m_pBackgroundAnime.Reset(new TitleBackgroundAnime());
	m_pBackgroundAnime->Initialize();

	// テクスチャーデータを取得
	m_pDrawingData->m_IDs.m_TextureID = m_pBackgroundAnime->GetCurrentTextureID();
}

void TitleBackground::Update()
{
	if(m_pBackgroundAnime->Update())
	{	// アニメーションを更新
		m_pDrawingData->m_IDs.m_TextureID = m_pBackgroundAnime->GetCurrentTextureID();
	}
}

void TitleBackground::Finalize()
{
	m_pBackgroundAnime->Finalize();
	//sl::DX11GraphicsLibrary::Instance().ReleaseDXModel2D(m_pDrawingData->m_IDs.m_ModelID);
	DrawingResrcDataFile::Instance().ReleaseData("TitleBG.vtxd");
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void TitleBackground::Draw()
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
