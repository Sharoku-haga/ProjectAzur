//==================================================================================================================================//
//!< @file		paFishBehaviorTree.cpp
//!< @brief		pa::FishBehaviorTreeクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/30	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paFishBehaviorTree.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

FishBehaviorTree::FishBehaviorTree(const std::string& rTreeName)
	: m_TreeName(rTreeName)
	, m_pRootNode(nullptr)
{}

FishBehaviorTree::~FishBehaviorTree()
{
	if(m_pRootNode != nullptr)
	{
		m_pRootNode->Finalize();
		delete m_pRootNode;
	}
}

void FishBehaviorTree::AddNode(BehaviorBase*	pBehaviorBase
	, unsigned int	priorityPoint
	, const std::string& rSearchName)
{
	if(rSearchName != "")
	{
		AddChildNode(pBehaviorBase, priorityPoint, rSearchName);
		return;
	}

	if(m_pRootNode == nullptr)
	{
		m_pRootNode = new NodeBase(nullptr, &m_RootBehavior, 1, priorityPoint);
	}

	AddChildNode(pBehaviorBase, priorityPoint, "Root");
}

void FishBehaviorTree::Enter(FishParam& rParam)
{}

void FishBehaviorTree::Update(FishParam& rParam)
{
	//*
	// 更新開始一発目にしか呼ばれないブロック
	if(rParam.m_BehaviorData.m_pAvtiveNode == nullptr)
	{
		if(m_pRootNode == nullptr)
		{	// そもそもRootNodeがないなら即return
			return;
		}

		rParam.m_BehaviorData.m_pAvtiveNode = m_InferenceEngine.InferenceNode(rParam, m_pRootNode);
		rParam.m_BehaviorData.m_IsEndBehavior = false;
		rParam.m_BehaviorData.m_IsEndBehavior = rParam.m_BehaviorData.m_pAvtiveNode->UpdateBehavior(rParam);
		return;
	}

	if(rParam.m_BehaviorData.m_IsEndBehavior)
	{
		InferenceActiveNode(rParam);
		rParam.m_BehaviorData.m_IsEndBehavior = false;
	}
	else
	{
		if(m_InferenceEngine.InferenceNodeInference(rParam))
		{
			InferenceActiveNode(rParam);
		}
	}

	rParam.m_BehaviorData.m_IsEndBehavior = rParam.m_BehaviorData.m_pAvtiveNode->UpdateBehavior(rParam);
	//*/
}

void FishBehaviorTree::Exit(FishParam& rParam)
{}

/* Private Functions ------------------------------------------------------------------------------------------ */

void FishBehaviorTree::AddChildNode(BehaviorBase*	pBehaviorBase
	, unsigned int	priorityPoint
	, const std::string& rSearchName)
{
	NodeBase* pSelectNode = m_pRootNode->SearchNode(rSearchName);
	if(pSelectNode != nullptr)
	{
		NodeBase* pAddNode = new NodeBase(pSelectNode, pBehaviorBase, pSelectNode->GetHierarchyNum() + 1, priorityPoint);
		pSelectNode->AddChildNode(pAddNode);
	}
}

void FishBehaviorTree::InferenceActiveNode(FishParam& rParam)
{
	//*
	if(rParam.m_BehaviorData.m_pAvtiveNode->EmptyChildNode())
	{
		rParam.m_BehaviorData.m_pAvtiveNode = m_InferenceEngine.InferenceNode(rParam, m_pRootNode);
	}
	else
	{
		rParam.m_BehaviorData.m_pAvtiveNode = m_InferenceEngine.InferenceNode(rParam, rParam.m_BehaviorData.m_pAvtiveNode);
	}
	//*/
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//


