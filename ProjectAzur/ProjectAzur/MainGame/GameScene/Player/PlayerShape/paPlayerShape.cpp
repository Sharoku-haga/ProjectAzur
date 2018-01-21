//==================================================================================================================================//
//!< @file		paPlayerShape.cpp
//!< @brief		pa::PlayerShapeクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/05	更新履歴：2017/12/16
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <vector>
#include "sl/Library/Utility/Calculation/slCalculationFunc.h"
#include "sl/Library/Utility/slTemplateFunction.h"
#include "sl/Library/Utility/slDefine.h"
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "paPlayerShape.h"
#include "../../../DrawingResrcDataFile/paDrawingResrcDataFile.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

PlayerShape::PlayerShape(const sl::DrawingID&	rIDs
						, const std::string&	rResrcDataFilePath)
	: m_rLibrary(sl::DX11GraphicsLibrary::Instance())
	, m_InitialShapeID(rIDs)
	, m_ResrcDataFilePath(rResrcDataFilePath)
	, m_IsInvisible(false)
{}

void PlayerShape::Initialize(const PlayerParam&	rParam)
{
	int	 drawTaskPriority = 2;		// 描画タスクの優先度
	m_pDrawingData->m_pTask.Reset(new DrawTask(drawTaskPriority, std::bind(&pa::PlayerShape::Draw, this)));

	m_rLibrary.InformSizeData(m_pDrawingData->m_IDs.m_ModelID, m_CurrentRectSize);
	m_IsFacingRight = rParam.m_IsFacingRight;
}

void PlayerShape::Update(const PlayerParam&	rParam)
{
	m_pDrawingData->m_Pos = rParam.m_Pos;
	m_pDrawingData->m_Angle = rParam.m_Angle;

	if(m_rLibrary.UpdateUVAnime(m_pDrawingData->m_IDs.m_ModelID, m_pDrawingData->m_IDs.m_UVAnimeID, true))
	{	// アニメーションが更新されたら反転処理を行う
		ProcessImageReversal(rParam);
		if(m_IsFacingRight != rParam.m_IsFacingRight)
		{
			m_IsFacingRight = rParam.m_IsFacingRight;
		}
	
		ProcessTransparent(rParam);
		return;
	}

	// 前の状態(右向いているかどうか)が異なっていたら反転処理を行う
	if(m_IsFacingRight != rParam.m_IsFacingRight)
	{
		ProcessImageReversal(rParam);
		m_IsFacingRight = rParam.m_IsFacingRight;
	}

	ProcessTransparent(rParam);
}

void PlayerShape::ChangeShape(const sl::DrawingID&	rIDs)
{
	m_pDrawingData->m_IDs = rIDs;
	m_rLibrary.InitUVAnime(m_pDrawingData->m_IDs.m_ModelID, m_pDrawingData->m_IDs.m_UVAnimeID);
	m_rLibrary.InformSizeData(m_pDrawingData->m_IDs.m_ModelID, m_CurrentRectSize);
	m_IsInvisible = false;		// 透明は初期形状のみの動作なので、ここでfalseにしておく
}

void PlayerShape::ChangeInitialShape()
{
	m_pDrawingData->m_IDs = m_InitialShapeID;
	m_rLibrary.InitUVAnime(m_pDrawingData->m_IDs.m_ModelID, m_pDrawingData->m_IDs.m_UVAnimeID);
	m_rLibrary.InformSizeData(m_pDrawingData->m_IDs.m_ModelID, m_CurrentRectSize);

	// 念の為、透明処理をきっておく
	std::vector<D3DXCOLOR> color(m_rLibrary.GetModel2DVertexCount(), NormalStateColorVal);
	m_rLibrary.SetDXModel2DColorData(m_pDrawingData->m_IDs.m_ModelID, color);
	m_IsInvisible = false;
}

const sl::fRect& PlayerShape::InformShapeSize()
{	/** @todo スケール処理も加えるかも知れない */
	return m_CurrentRectSize;
}

void PlayerShape::AdjustDrawingData(const PlayerParam& rParam)
{
	m_pDrawingData->m_Pos = rParam.m_Pos;
}

void PlayerShape::Finalize()
{
	m_rLibrary.ReleaseUVAnimation(m_pDrawingData->m_IDs.m_UVAnimeID);
	m_rLibrary.ReleaseDXModel2D(m_pDrawingData->m_IDs.m_ModelID);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void PlayerShape::Draw()
{

}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
