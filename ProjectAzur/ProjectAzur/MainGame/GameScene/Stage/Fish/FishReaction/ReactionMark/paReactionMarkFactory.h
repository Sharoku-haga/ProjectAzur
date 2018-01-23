//=================================================================================================================================//
//!< @file		paReactionMarkFactory.h		
//!< @brief		pa::ReactionMarkFactoryクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/22	更新履歴：2018/01/23
//==================================================================================================================================//

#ifndef PA_REACTION_MARK_FACTORY_H
#define PA_REACTION_MARK_FACTORY_H

#include <map>
#include <vector>
#include <sl/Library/Singleton/slUserManualSingleton.h>
#include "sl/Library/SmartPointer/SharedPtr/slSharedPtr.h"
#include "paReactionMark.h"
#include "../../paFishCommonDeclaration.h"

namespace pa
{

//===================================================================================//
//!< リアクションのマーク関連の生成、管理を行うクラス
//!< Singletonクラス
//!< クラス生成、初期化などの処理はFishManager内にて行う
//===================================================================================//
class ReactionMarkFactory : public sl::UserManualSingleton<ReactionMarkFactory>
{

public:
	/**
	* 初期化関数
	* @param[in] rIDs					描画データID群
	* @param[in] rResrcDataFilePath		リソースデータファイルへのパス
	* @param[in] rFishDiffPos			魚との差異座標
	*/
	void Initialize(const sl::DrawingID&	rIDs
					, const std::string&	rResrcDataFilePath
					, const D3DXVECTOR2&	rFishDiffPos);

	/**
	* リアクションマークのvectorを生成する関数
	* @param[in] reactionMarkFlag	前のリアクションマークのフラグ
	* @param[out] rMarks			リアクションマークの種類を格納したvector							
	*/
	void CreateReactionMarks(int reactionMarkFlag
								, std::vector<REACTION_MARK_TYPE>& rMarks);

	/**
	* Getter
	* @param[in] type リアクションマークの種類
	* @return ReactionMarkクラスのインスタンスへのポインタ
	*/
	sl::SharedPtr<ReactionMark> GetMarkPointer(REACTION_MARK_TYPE type)
	{
		return m_pMark[type];
	}

	/**
	* Getter
	* @return 魚との差異座標
	*/
	const D3DXVECTOR2& GetFishDiffPos()
	{
		return m_FishDiffPos;
	}

private:
	friend class sl::UserManualSingleton <ReactionMarkFactory>;
	std::map<REACTION_MARK_TYPE, sl::SharedPtr<ReactionMark>>		m_pMark;			//!< ReactionMarkクラスのインスタンスへのポインタのmap
	D3DXVECTOR2														m_FishDiffPos;		//!< 魚との差異座標

	/** Constructor */
	ReactionMarkFactory() = default;

	/** Destructor */
	virtual ~ReactionMarkFactory() = default;

};	// class ReactionMarkFactory

}	// namespace pa

#endif	// PA_REACTION_MARK_FACTORY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
