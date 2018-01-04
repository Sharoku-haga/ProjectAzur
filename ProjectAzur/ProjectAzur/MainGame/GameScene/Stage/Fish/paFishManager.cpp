//==================================================================================================================================//
//!< @file		paFishManager.cpp
//!< @brief		pa::FishManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/23	更新履歴：2018/01/04
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paFishManager.h"
#include"../../../DrawingResrcDataFile/paDrawingResrcDataFile.h"
#include "FishCreator/paFishCreator.h"
#include "paFish.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

FishManager::FishManager(const sl::DrawingID&	rIDs
						, const std::string&	rResrcDataFilePath)
	: m_DrawingID(rIDs)
	, m_ResrcDataFilePath(rResrcDataFilePath)
{}

FishManager::~FishManager()
{
	Finalize();
}

void FishManager::Initialize()
{
	// データの読み込み
	DrawingResrcDataFile::Instance().LoadDataFile(m_ResrcDataFilePath);

	// FishCreatorクラスの生成と初期化
	m_pCreator.Reset(new FishCreator(m_DrawingID, m_ResrcDataFilePath.c_str()));

	// 魚クラスの生成
	/** @todo 現在仮実装 */

	m_pFishes.emplace_back(m_pCreator->CreateFish(D3DXVECTOR2(200.f, 200.f)));

	// Fishクラスの初期化
	for(auto& pfish : m_pFishes)
	{
		pfish->Initialize();
	}	
}

void FishManager::Update()
{
	for(auto& pfish : m_pFishes)
	{
		pfish->Update();
	}
}

void FishManager::Finalize()
{
	for(auto& pfish : m_pFishes)
	{
		pfish->Finalize();
	}	

	std::vector<sl::UniquePtr<Fish
		, sl::DefaultDeleter<Fish>>>().swap(m_pFishes);
}

}	// namespace pa
//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
