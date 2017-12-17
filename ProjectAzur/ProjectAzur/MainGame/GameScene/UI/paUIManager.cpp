//==================================================================================================================================//
//!< @file		paUIManager.cpp
//!< @brief		pa::UIManagerクラス実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/17	更新履歴：2017/12/18
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paUIManager.h"
#include "paIUI.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

UIManager::UIManager(const sl::DrawingID& rIDs
					, const std::string& rResrcDataFilePath)
	: m_DrawingID(rIDs)
	, m_ResrcDataFilePath(rResrcDataFilePath)
{}

UIManager::~UIManager()
{
	Finalize();
}

void UIManager::Initialize()
{
	for(auto& pUI : m_pUI)
	{
		pUI->Initialize();;
	}
}

void UIManager::Update()
{

}

void UIManager::Finalize()
{
	for(auto& pUI : m_pUI)
	{
		pUI->Finalize();
	}

	std::vector<sl::UniquePtr<IUI, sl::DefaultDeleter<IUI>>>().swap(m_pUI);
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
