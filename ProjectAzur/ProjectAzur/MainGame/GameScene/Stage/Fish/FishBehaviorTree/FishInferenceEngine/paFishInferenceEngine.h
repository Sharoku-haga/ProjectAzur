//==================================================================================================================================//
//!< @file		paFishInferenceEngine.h
//!< @brief		pa::FishInferenceEngineクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/30	更新履歴：
//==================================================================================================================================//

#ifndef FISH_INFERENCE_ENGINE_H
#define FISH_INFERENCE_ENGINE_H

#include <map>
#include <memory>
#include "../../paFishCommonDeclaration.h"
#include "../NodeBase/paNodeBase.h"

namespace pa
{

//===================================================================================//
//!< 魚の推論エンジンクラス
//===================================================================================//
class FishInferenceEngine final
{

public:
	/** Constructor */
	FishInferenceEngine();

	/** Destructor */
	~FishInferenceEngine();

	/**
	* ノード推論を行うかを推論する関数
	* @param[in] rParam 魚のパラメータ
	* @return ture→ 行う false→行わない
	*/
	bool InferenceNodeInference(FishParam& rParam);

	/**
	* ノードの推論を行う関数
	* @param[in] rParam		魚のパラメータ
	* @param[in] pNode		推論を行うノード
	* @return 推論した結果のノード
	*/
	NodeBase* InferenceNode(FishParam& rParam, NodeBase* pNode);

private:
	/**
	* 優位ポイントでノードを判断する関数
	* @param[in] rData	優位ポイントデータ
	* @return 選んだノードのポインタ
	*/
	NodeBase* SelectPriority(std::map<NodeBase*, unsigned int>& rData);

	/**
	* 移動の範囲を調整する関数
	* @param[in] rParam 魚のパラメータ
	* @param[in] rData	優位ポイントデータ
	*/
	void AdjustMovementCase(FishParam& rParam, std::map<NodeBase*, unsigned int>& rData);

};	// class FishInferenceEngine

}	// namespace pa

#endif	// FISH_INFERENCE_ENGINE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
