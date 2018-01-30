//==================================================================================================================================//
//!< @file		paFishBehaviorTreeFactory.h
//!< @brief		pa::FishBehaviorTreeFactoryクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/30	更新履歴：
//==================================================================================================================================//

#ifndef PA_FISH_BEHAVIOR_TREE_FACTORY_H
#define PA_FISH_BEHAVIOR_TREE_FACTORY_H

#include <map>
#include <string>
#include "paFishBehaviorTree.h"

namespace pa
{

/*
TypeString
・Normal
・Death
・
//*/

class BehaviorFactory;

//===================================================================================//
//!< 魚のBehaviorTreeのファクトリークラス
//===================================================================================//
class FishBehaviorTreeFactory
{

public:
	/** Constructor */
	FishBehaviorTreeFactory();

	/** Destructor */
	~FishBehaviorTreeFactory();

	/** 仮実装*/
	static FishBehaviorTreeFactory& Instance()
	{
		static FishBehaviorTreeFactory treeFactory;

		return treeFactory;
	}

	/** 初期化関数 */
	void Initialize();

	FishBehaviorTree* GetBehaviorTree(const std::string& rName);

	/** 破棄関数 */
	void Finalize();

private:
	std::map<std::string, FishBehaviorTree*> m_pBehaviorTree;				//!< FishBehaviorTreeクラスのインスタンスへのポインタを格納したmap
	BehaviorFactory*						 m_pBehaviorFactory;			//!< BehaviorFactoryクラスのインスタンスへのポインタ

};	// class FishBehaviorTreeFactory

}	// namespace pa

#endif // PA_FISH_BEHAVIOR_TREE_FACTORY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
