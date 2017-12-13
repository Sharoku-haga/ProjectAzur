//==================================================================================================================================//
//!< @file		paStageBackgroundManager.cpp
//!< @brief		pa::StageBackgroundManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/11	更新履歴：2017/12/13
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paStageBackgroundManager.h"
#include "paStageBackground.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

StageBackgroundManager::StageBackgroundManager(const sl::DrawingID& rIDs
											, const std::string& rResrcDataFilePath)
	: m_DrawingID(rIDs)
	, m_ResrcDataFilePath(rResrcDataFilePath)
{}

StageBackgroundManager::~StageBackgroundManager()
{
	Finalize();
}

void StageBackgroundManager::Initialize()
{
	// 背景クラスの作成
	m_pBackground.Reset(new StageBackground(m_DrawingID, m_ResrcDataFilePath));
	m_pBackground->Initialize();
}

void StageBackgroundManager::Update()
{
	m_pBackground->Update();
}

void StageBackgroundManager::Finalize()
{
	m_pBackground->Finalize();
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
