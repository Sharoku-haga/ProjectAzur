//==================================================================================================================================//
//!< @file		paFishBehaviorTreeMachine.cpp
//!< @brief		pa::FishBehaviorTreeMachineクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/30	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paFishBehaviorTreeMachine.h"
#include "paFishBehaviorTreeFactory.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

FishBehaviorTreeMachine::FishBehaviorTreeMachine()
	: m_pCurrentBehaviorTree(nullptr)
{}

FishBehaviorTreeMachine::~FishBehaviorTreeMachine()
{}

void FishBehaviorTreeMachine::Initialize(FishParam& rParam)
{
	rParam.m_BehaviorData.m_CurrentTreeName = "Normal";
	rParam.m_BehaviorData.m_NextTreeName = "Normal";
}

void FishBehaviorTreeMachine::Update(FishParam& rParam)
{
	if(m_pCurrentBehaviorTree == nullptr)
	{
		m_pCurrentBehaviorTree = FishBehaviorTreeFactory::Instance().GetBehaviorTree(rParam.m_BehaviorData.m_NextTreeName);
		rParam.m_BehaviorData.m_CurrentTreeName = rParam.m_BehaviorData.m_NextTreeName;
		m_pCurrentBehaviorTree->Enter(rParam);
	}

	// Tree遷移はここに挿入

	// 念の為、もう一度チェック
	if(m_pCurrentBehaviorTree == nullptr)
	{
		return;
	}

	m_pCurrentBehaviorTree->Update(rParam);

	if(rParam.m_BehaviorData.m_NextTreeName != rParam.m_BehaviorData.m_CurrentTreeName)
	{
		m_pCurrentBehaviorTree->Exit(rParam);
		m_pCurrentBehaviorTree = nullptr;
	}
}

void FishBehaviorTreeMachine::Finalize()
{
	// 現状はなし
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
