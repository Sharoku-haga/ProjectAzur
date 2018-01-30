//==================================================================================================================================//
//!< @file		paNodeBase.h
//!< @brief		pa::NodeBaseクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/30	更新履歴：
//==================================================================================================================================//

#ifndef PA_NODE_BASE_H
#define PA_NODE_BASE_H

#include <string>
#include <vector>
#include "../Behavior/paBehaviorBase.h"

namespace pa
{

struct FishParam;

//===================================================================================//
//!< BehaviorTreeで使用するノードクラス
//===================================================================================//
class NodeBase
{

public:
	/**
	* Costructor
	* @param[in] pPartentNode	親ノードのポインタ
	* @param[in] pBehaviorBase	pBehaviorBaseクラスのインスタンスへのポインタ
	* @param[in] hierarchyNum	階層番号
	* @param[in] priorityPoint	推論に使用する優先ポイント
	*/
	NodeBase(NodeBase*	pPartentNode
			, BehaviorBase*	 pBehaviorBase
			, unsigned int hierarchyNum
			, unsigned int	priorityPoint = 50);

	/** Destructor */
	~NodeBase();

	/** 破棄関数 */
	void Finalize();

	/**
	* ノードを探索する関数
	* @param[in] rSearchName 探索するノードの名前
	* @return	探索したノードのポインタ
	*/
	NodeBase* SearchNode(const std::string& rSearchName);

	/**
	* 子ノードを追加する関数
	* @param[in] pNode
	*/
	void AddChildNode(NodeBase* pNode);

	/**
	* ノードに登録している振る舞いを更新する関数
	* @param[out] rParam 魚のパラメータ
	* @retrun ture→終了した false→ 終了していない
	*/
	bool UpdateBehavior(FishParam& rParam);


	/**
	* 子ノードが空かどうかを確認する関数
	* @retrun ture→空である false→空でない
	*/
	bool EmptyChildNode()
	{
		return m_pChildNode.size() == 0;
	}

	/**
	* Getter
	* @return 親ノードのポインタ
	*/
	NodeBase* GetPartentNode()
	{
		return m_pPartentNode;
	}

	/**
	* Getter
	* @return 子ノードのvector
	*/
	std::vector<NodeBase*>& GetChildNodes()
	{
		return m_pChildNode;
	}

	/**
	* Getter
	* @return このノードがもっているBehaviorの名前
	*/
	const std::string& GetBehaviorName()
	{
		return m_pBehaviorBase->GetName();
	}

	/**
	* Getter
	* @return 優先ポイント
	*/
	const unsigned int GetPriorityPoint()
	{
		return m_PriorityPoint;
	}

	/**
	* Getter
	* @return 階層番号
	*/
	const unsigned int GetHierarchyNum()
	{
		return m_HierarchyNum;
	}

private:
	NodeBase*						m_pPartentNode;		//!< 親のポインタ
	std::vector<NodeBase*>			m_pChildNode;		//!< 子のポインタ
	BehaviorBase*					m_pBehaviorBase;	//!< 振る舞いベース
	unsigned int					m_PriorityPoint;	//!< 優先ポイント
	unsigned int					m_HierarchyNum;		//!< 階層番号

};	// class NodeBase

}	// namespace pa

#endif	// PA_NODE_BASE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
