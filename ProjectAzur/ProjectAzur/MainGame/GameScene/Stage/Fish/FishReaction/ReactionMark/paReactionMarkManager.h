//==================================================================================================================================//
//!< @file		paReactionMarkManager.h		
//!< @brief		pa::ReactionMarkManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/22	更新履歴：2018/01/23
//==================================================================================================================================//

#ifndef PA_REACTION_MARK_MANAGER_H
#define PA_REACTION_MARK_MANAGER_H

#include <vector>
#include "sl/Library/SmartPointer/SharedPtr/slSharedPtr.h"
#include "paReactionMark.h"
#include"../../paFishCommonDeclaration.h"

namespace pa
{

//===================================================================================//
//!< 魚のリアクションのマークを管理するクラス
//===================================================================================//
class ReactionMarkManager
{

public:
	/** Constructor */
	ReactionMarkManager();

	/** Destructor */
	~ReactionMarkManager();

	/**
	* 初期化関数 
	* @param[in] rParam 魚のパラメータ
	*/
	void Initialize(const FishParam& rParam);

	/**
	* 更新関数 
	* @param[in] rParam 魚のパラメータ
	*/
	void Update(const FishParam& rParam);

	/**
	* 描画関数
	* @param[in] rParam			魚のパラメータ
	* @param[in] rBasePointPos	ベースポイントの座標
	*/
	void Draw(const FishParam& rParam, const D3DXVECTOR2& rBasePointPos);

private:
	sl::SharedPtr<ReactionMark>			m_pDisplayingMark;				//!< 表示しているマーク
	std::vector<REACTION_MARK_TYPE>		m_DispMarks;					//!< 表示するマークのvector
	int									m_CurrentMarkOrderIndex;		//!< 現在のマークの順番のインデックス
	int									m_PrevReactionMarkFlag;			//!< 前のリアクションマークのフラグ
	int									m_DispTimeCount;				//!< 表示時間カウント数

	/** 表示マークを変更する関数 */
	void ChangeDispMark();

	/**
	* マークのvectorを更新する関数
	* @param[in] rParam			魚のパラメータ
	*/
	void UpdateMark(const FishParam& rParam);

};	// class ReactionMarkManager

}	// namespace pa

#endif	// PA_REACTION_MARK_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
