//==================================================================================================================================//
//!< @file		paFishBehaviorTreeMachine.h
//!< @brief		pa::FishBehaviorTreeMachineクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/30	更新履歴：
//==================================================================================================================================//

#ifndef PA_FISH_BEHAVIOR_TREE_H
#define PA_FISH_BEHAVIOR_TREE_H

#include "../paFishCommonDeclaration.h"

namespace pa
{

class FishBehaviorTree;

//===================================================================================//
//!< 魚のBehaviorTreeを管理するクラス
//===================================================================================//
class FishBehaviorTreeMachine final
{

public:
	/** Constructor */
	FishBehaviorTreeMachine();

	/** Destructor */
	~FishBehaviorTreeMachine();

	/**
	* 初期化関数
	* @param[in] rParam 魚のパラメータ
	*/
	void Initialize(FishParam& rParam);

	/**
	* 更新関数
	* @param[in] rParam 魚のパラメータ
	*/
	void Update(FishParam& rParam);

	/** 破棄関数 */
	void Finalize();

private:
	FishBehaviorTree*	m_pCurrentBehaviorTree;			//!< 現在のBehaviorTreeのインスタンスへのポインタ

};	// class FishBehaviorTreeMachine

}	// namespace pa

#endif	// PA_FISH_BEHAVIOR_TREE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
