//==================================================================================================================================//
//!< @file		paNodeBase.cpp
//!< @brief		pa::NodeBaseクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/30	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paNodeBase.h"
#include "../../paFishCommonDeclaration.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

NodeBase::NodeBase(NodeBase*	pPartentNode, BehaviorBase*	 pBehaviorBase, unsigned int hierarchyNum, unsigned int	priorityPoint)
	: m_pPartentNode(pPartentNode)
	, m_pBehaviorBase(pBehaviorBase)
	, m_HierarchyNum(hierarchyNum)
	, m_PriorityPoint(priorityPoint)
{}

NodeBase::~NodeBase()
{}

void NodeBase::Finalize()
{
	for(auto& pChild : m_pChildNode)
	{
		pChild->Finalize();
		delete pChild;
	}
}

NodeBase* NodeBase::SearchNode(const std::string& rSearchName)
{
	// ノード一致
	if(m_pBehaviorBase->GetName() == rSearchName)
	{
		return this;
	}

	// 子で検索
	for(auto& pNode : m_pChildNode)
	{
		NodeBase* pRet = pNode->SearchNode(rSearchName);
		if(pRet != nullptr)
		{
			return pRet;
		}
	}

	return nullptr;
}

void NodeBase::AddChildNode(NodeBase* pNode)
{
	m_pChildNode.emplace_back(pNode);
}

bool NodeBase::UpdateBehavior(FishParam& rParam)
{
	return m_pBehaviorBase->Update(rParam);
}

} // namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
