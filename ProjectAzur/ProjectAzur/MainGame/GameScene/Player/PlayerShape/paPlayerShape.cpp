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

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace 
{

const int	 DrawTaskPriority = 2;		// 描画タスクの優先度

}

/* Public Functions ------------------------------------------------------------------------------------------- */

PlayerShape::PlayerShape(const sl::DrawingID&	rIDs
						, const std::string&	rResrcDataFilePath)
	: m_rLibrary(sl::DX11GraphicsLibrary::Instance())
	, m_ResrcDataFilePath(rResrcDataFilePath)
{}

void PlayerShape::Initialize(const PlayerParam&	rParam)
{
	m_pOriginalShape.Reset(new PlayerOriginalShape());
	m_pOriginalShape->Initialize(m_IDs, m_ResrcDataFilePath, rParam);

	m_pFishShell.Reset(new PlayerFishShell());
	m_pFishShell->Initialize(m_IDs, m_ResrcDataFilePath);

	m_pTask.Reset(new DrawTask(DrawTaskPriority, std::bind(&pa::PlayerShape::Draw, this)));

	/* テストコード
	m_CurrentRectSize = m_pFishShell->GetRectSize();

	//*/
}

void PlayerShape::Update(const PlayerParam&	rParam)
{
	if(m_pFishShell->HasCreatedShaell())
	{
		m_pFishShell->Update(rParam);
		return;
	}

	m_pOriginalShape->Update(rParam);
}

void PlayerShape::ChangeShape(ObjDrawingData* pFishDrawingData)
{
	m_pFishShell->CreateShell(pFishDrawingData);
}

void PlayerShape::ChangeInitialShape()
{
	m_pFishShell->DestroyShell();
}

const sl::fRect& PlayerShape::InformShapeSize()
{	/** @todo スケール処理も加えるかも知れない */
	return m_CurrentRectSize;
}

bool PlayerShape::IsInvisible()
{
	if(m_pFishShell->HasCreatedShaell())
	{
		return false;
	}

	return m_pOriginalShape->IsInvisible();
}

void PlayerShape::AdjustDrawingData(const PlayerParam& rParam)
{
	if(m_pFishShell->HasCreatedShaell())
	{
		m_pFishShell->AdjustDrawingData(rParam);
		return;
	}

	m_pOriginalShape->AdjustDrawingData(rParam);
}

void PlayerShape::Finalize()
{
	m_pFishShell->Finalize();
	m_pOriginalShape->Finalize();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void PlayerShape::Draw()
{
	if(m_pFishShell->HasCreatedShaell())
	{
		m_pFishShell->Draw(m_BasePointPos);
		return;
	}

	m_pOriginalShape->Draw(m_BasePointPos);
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
