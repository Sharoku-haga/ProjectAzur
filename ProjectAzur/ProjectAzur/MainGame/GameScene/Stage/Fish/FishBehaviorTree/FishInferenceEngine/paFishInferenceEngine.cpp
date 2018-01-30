//==================================================================================================================================//
//!< @file		paFishInferenceEngine.cpp
//!< @brief		pa::FishInferenceEngineクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/30	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <vector>
#include "paFishInferenceEngine.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

FishInferenceEngine::FishInferenceEngine()
{}

FishInferenceEngine::~FishInferenceEngine()
{}

bool FishInferenceEngine::InferenceNodeInference(FishParam& rParam)
{
	// 探知して前方に何かいるならtrue

	// 移動範囲を超えたらtrue
	/*
	if(rParam.m_MoveDistance > rParam.m_MoveArea)
	{
		return true;
	}

	if(!rParam.m_IsFeching
		&& rParam.m_MoveDistance < 0.0f)
	{
		return true;
	}
	//*/

	return false;
}

NodeBase* FishInferenceEngine::InferenceNode(FishParam& rParam, NodeBase* pNode)
{
	// 子ノードがなければ、自分を再度繰り返させる
	if(pNode->EmptyChildNode())
	{
		return pNode;
	}

	std::vector<NodeBase*>& pChild = pNode->GetChildNodes();

	std::map<NodeBase*, unsigned int> data;

	// 優位ポイントを取得して行く
	for(auto& pNode : pChild)
	{
		data[pNode] = pNode->GetPriorityPoint();
	}

	// 移動範囲による調整
	AdjustMovementCase(rParam, data);

	// 探知によるポイント調整(好みや)

	// 個性によるポイント調整

	// パラメータによるポイント調整

	// 優勢のセレクトを行う
	return SelectPriority(data);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

NodeBase* FishInferenceEngine::SelectPriority(std::map<NodeBase*, unsigned int>& rData)
{	 
	auto& retItr = rData.begin();
	for (auto& checkItr  = rData.begin(); checkItr != rData.end(); ++checkItr)
	{
		if ((*retItr).second < (*checkItr).second)
		{
			retItr = checkItr;
		}
	}

	if(retItr == rData.end())
	{
		return nullptr;
	}

	return (*retItr).first;
}

void FishInferenceEngine::AdjustMovementCase(FishParam& rParam, std::map<NodeBase*, unsigned int>& rData)
{
	/*
	// 移動範囲を超えたらtrue
	if(rParam.m_MoveDistance > rParam.m_MoveArea)
	{
		for(auto& data : rData)
		{
			if( data.first->GetBehaviorName() == "Turning")
			{
				data.second += 100;
				break;
			}
		}

		return;
	}

	if(!rParam.m_IsFeching
		&& rParam.m_MoveDistance < 0.0f)
	{
		for(auto& data : rData)
		{
			if(data.first->GetBehaviorName() == "Turning")
			{
				data.second += 100;
				break;
			}
		}

		return;
	}
	//*/
}

}	// namespace pa