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
#include "FishReaction/ReactionMark/paReactionMarkFactory.h"

namespace pa
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const int		FishCount = 3;			//!< 魚の数

}

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
	m_pCreator->Initialize();

	// 魚に関連するSingletonクラスの生成と初期化
	D3DXVECTOR2 diffPos = { 80.0f, -50.0f};
	ReactionMarkFactory::Create();
	ReactionMarkFactory::Instance().Initialize(m_DrawingID, m_ResrcDataFilePath, diffPos);

	// 魚クラスの生成
	/** @todo 現在仮実装 */

	for(int i = 0; i < FishCount; ++i)
	{
		m_pFishes.emplace_back(m_pCreator->CreateFish());
	}

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

	ReactionMarkFactory::Destroy();
}

}	// namespace pa
//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
