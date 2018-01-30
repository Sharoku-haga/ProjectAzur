//==================================================================================================================================//
//!< @file		paFishBehaviorTree.h
//!< @brief		pa::FishBehaviorTreeクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/30	更新履歴：
//==================================================================================================================================//

#ifndef PA_FISH_BHAVIOR_TREE_H
#define PA_FISH_BHAVIOR_TREE_H

#include <string>
#include <memory>
#include "../paFishCommonDeclaration.h"
#include "NodeBase/paNodeBase.h"
#include "Behavior/paBehaviorBase.h"
#include "FishInferenceEngine/paFishInferenceEngine.h"
#include "Behavior/BehaviorBase_Child/paRootBehavior.h"

namespace pa
{

//===================================================================================//
//!< 魚のBehaviorTreeのクラス
//===================================================================================//
class FishBehaviorTree
{

public:
	/** 
	* Constructor 
	* @param[in] rTreeName ツリーの名前
	*/
	FishBehaviorTree(const std::string& rTreeName);

	/** Destructor */
	~FishBehaviorTree();

	/** 
	* ノード追加関数 
	* 1階層につきBehaviorは同じものはない。というルール
	* 第1引数のみだと、自動的にRootノードの子に追加される
	* @param[in] pBehaviorBase		BehaviorBaseクラスのインスタンスへのポインタ		
	* @param[in] priorityPoint		優位ポイント.デフォルト50
	* @param[in] rSearchName		探索名.デフォルト探索名""
	*/
	void AddNode(BehaviorBase*	pBehaviorBase
				, unsigned int	priorityPoint = 50
				, const std::string& rSearchName = "");

	/** 
	* このTreeに入ったら呼ぶ関数 
	* @param[in] rParam 魚のパラメータ
	*/
	void Enter(FishParam& rParam);

	/** 
	* 毎フレーム呼ぶ関数 
	* @param[in] rParam 魚のパラメータ
	*/
	void Update(FishParam& rParam);

	/** 
	* このTreeを抜けるときの関数 
	* @param[in] rParam 魚のパラメータ
	*/
	void Exit(FishParam& rParam);

	/**
	* Getter
	* @return ツリー名
	*/
	inline const std::string GetTreeName()
	{
		return m_TreeName;
	}

private:
	std::string				m_TreeName;				//!< ツリーの名前
	NodeBase*				m_pRootNode;			//!< NodeBaseクラスのインスタンスへのポインタ	
	RootBehavior			m_RootBehavior;			//!< RootBehaviorクラス
	FishInferenceEngine		m_InferenceEngine;		//!< 推論エンジン

	/** 
	* 子ノード追加関数 
	* 1階層につきBehaviorは同じものはない。というルール
	* 第1引数のみだと、自動的にRootノードの子に追加される
	* @param[in] pBehaviorBase		BehaviorBaseクラスのインスタンスへのポインタ		
	* @param[in] priorityPoint		優位ポイント
	* @param[in] rSearchName		探索名
	*/
	void AddChildNode(BehaviorBase*	pBehaviorBase
					, unsigned int	priorityPoint
					, const std::string& rSearchName);

	/**
	* アクティブノードを推論する関数
	* @param[in] rParam 魚のパラメータ
	*/
	void InferenceActiveNode(FishParam& rParam);
	
};	// class FishBehaviorTree

}	// namespace pa

#endif	// PA_FISH_BHAVIOR_TREE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
