//==================================================================================================================================//
//!< @file		paFishCommonDeclaration.h
//!< @brief		pa::Fishクラスに関連する共通宣言をまとめたヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/23	更新履歴：2018/01/30
//==================================================================================================================================//

#ifndef PA_FISH_COMMON_DECLARATION_H
#define PA_FISH_COMMON_DECLARATION_H

#include <string>
#include <D3DX11.h>
#include <D3DX10.h>
#include "FishBehaviorTree/NodeBase/paNodeBase.h"

namespace pa
{

/** 魚のリアクションのマークの種類の列挙 */
enum REACTION_MARK_TYPE
{
	NONE = 0x00,		//!< 何もない
	HUNGER = 0x01,		//!< 空腹
	WARNING = 0x02,		//!< 警戒
	ATTACK = 0x04,		//!< 攻撃
	DISCOVERY = 0x08,	//!< 発見
	REFUGE = 0x10,		//!< 避難
	EATING = 0x20,		//!< 捕食
	TARGET = 0x40,		//!< 目標
	DETECTION = 0x80,	//!< 標的(探知)

};	// enum REACTION_MARK_TYPE


//===================================================================================//
//!< Behavior関連のデータ構造体
//===================================================================================//
struct BehaviorData
{
	NodeBase*				m_pAvtiveNode;			//!< 現在アクティブなデータノードのポインタ
	bool					m_IsEndBehavior;		//!< 振る舞いが完了したかどうかのフラグ true→処理終了 false→処理終了していない
	std::string				m_CurrentTreeName;		//!< 現在のBehaviorTreeの名
	std::string				m_NextTreeName;			//!< 次のBehaviorTreeの名

	BehaviorData() 
		: m_pAvtiveNode(nullptr), m_IsEndBehavior(false)
	{}
};

//===================================================================================//
//!< 魚のパラメータクラス。
//===================================================================================//
struct FishParam
{
	D3DXVECTOR2		m_Pos;						//!< 座標
	float			m_Angle;					//!< 角度
	BehaviorData	m_BehaviorData;				//!< Behavior関連のデータ構造体
	bool			m_IsFacingRight;			//!< 右を向いているかどうかのフラグ. true→向いている false→向いていない
	int				m_ReactionMarkFlag;			//!< 魚のリアクションマークのフラグ(ビット管理)

	FishParam()
		: m_Pos({0.0f, 0.0f})
		, m_Angle(0.0f)
		, m_IsFacingRight(true)
		, m_ReactionMarkFlag(0)
	{}

};	// struct FishParam

}	// namespace pa


#endif	// PA_FISH_COMMON_DECLARATION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
