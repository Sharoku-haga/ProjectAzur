//==================================================================================================================================//
//!< @file		paFishBehaviorTreeFactory.cpp
//!< @brief		pa::FishBehaviorTreeFactoryクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/30	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paFishBehaviorTreeFactory.h"
#include "Behavior/BehaviorFactory.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

FishBehaviorTreeFactory::FishBehaviorTreeFactory()
{}

FishBehaviorTreeFactory::~FishBehaviorTreeFactory()
{}

void FishBehaviorTreeFactory::Initialize()
{
	m_pBehaviorFactory = new BehaviorFactory();
	m_pBehaviorFactory->Initialize();

	// Normal
	{
		std::string treeName = "Normal";
		m_pBehaviorTree[treeName] = new FishBehaviorTree(treeName);
		m_pBehaviorTree[treeName]->AddNode(m_pBehaviorFactory->GetBehavior("Movement"));
		m_pBehaviorTree[treeName]->AddNode(m_pBehaviorFactory->GetBehavior("Turning"));
	}

	// Death
	{
		std::string treeName = "Death";
		m_pBehaviorTree[treeName] = new FishBehaviorTree(treeName);
		m_pBehaviorTree[treeName]->AddNode(m_pBehaviorFactory->GetBehavior("None"));
	}
}

FishBehaviorTree* FishBehaviorTreeFactory::GetBehaviorTree(const std::string& rName)
{
	return m_pBehaviorTree[rName];
}

void FishBehaviorTreeFactory::Finalize()
{
	for(auto& pBehaviorTree : m_pBehaviorTree)
	{
		delete pBehaviorTree.second;
		pBehaviorTree.second = nullptr;
	}

	// safeDelte
	if(m_pBehaviorFactory != nullptr)
	{
		m_pBehaviorFactory->Finalize();
		delete m_pBehaviorFactory;
		m_pBehaviorFactory = nullptr;
	}
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
