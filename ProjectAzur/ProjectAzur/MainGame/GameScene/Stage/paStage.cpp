//==================================================================================================================================//
//!< @file		paStage.cpp		
//!< @brief		pa::Stageクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/09	更新履歴：2017/12/11
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paStage.h"
#include "../Player/paPlayer.h"
#include "paBasePoint.h"
#include "paIStageObjManager.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

Stage::Stage(const sl::SharedPtr<Player>& pPlayer)
	: m_pPlayer(pPlayer)
{}

Stage::~Stage()
{
	Finalize();
}

void Stage::Initialize()
{
	/** @todo ステージサイズは仮の値 */
	sl::fRect stageSize = {0.0f, 0.0f, 3940.0f, 2160.0f};

	// ベースポイントの生成と初期化
	m_pBasePoint.Reset(new BasePoint(m_pPlayer, stageSize));
	m_pBasePoint->Initialize();

	// 各IStageObjManagerを継承したクラスの生成と初期化

	for(auto& pObjectManager : m_pIStageObjManager)
	{
		pObjectManager->Initialize();
	}
}

void Stage::Update()
{
	for(auto& pObjectManager : m_pIStageObjManager)
	{
		pObjectManager->Update();
	}
}

void Stage::Finalize()
{
	for(auto& pObjectManager : m_pIStageObjManager)
	{
		pObjectManager->Finalize();
	}
	
	std::vector <sl::UniquePtr<IStageObjManager
		, sl::DefaultDeleter<IStageObjManager>>>().swap(m_pIStageObjManager);
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
