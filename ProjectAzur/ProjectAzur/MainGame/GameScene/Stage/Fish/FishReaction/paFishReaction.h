//==================================================================================================================================//
//!< @file		paFishReaction.h
//!< @brief		pa::FishReactionクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/09	更新履歴：2018/01/23
//==================================================================================================================================//

#ifndef PA_FISH_REACTION_H
#define PA_FISH_REACTION_H

#include <string>
#include "sl/Library/Graphics/slGraphicsID.h"
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "../paFishCommonDeclaration.h"

namespace pa
{

class Balloon;
class ReactionMarkManager;

//===================================================================================//
//!< 魚のリアクションクラス
//===================================================================================//
class FishReaction
{

public:
	/** 
	* Constructor 
	* @param[in] rIDs					描画データID群
	* @param[in] rResrcDataFilePath		リソースデータファイルへのパス
	*/
	FishReaction(const sl::DrawingID&	rIDs
				 , const std::string&	rResrcDataFilePath);

	/** Destructor */
	~FishReaction();

	/** 
	* 初期化関数 
	* @param[in] rParam 魚のパラメータ
	*/
	void Initialize(const FishParam& rParam);

	/** 
	* 更新関数 
	* @param[in] rParam 魚のパラメータ
	*/
	void Upadte(const FishParam& rParam);

	/** 
	* 描画関数 
	* @param[in] rParam			魚のパラメータ 
	* @param[in] rBasePointPos	ベースポイントの座標
	*/
	void Draw(const FishParam& rParam, const D3DXVECTOR2& rBasePointPos);

private:
	sl::UniquePtr<Balloon, sl::DefaultDeleter<Balloon>>		m_pBalloon;						//!< Balloonクラスのインスタンスへのユニークポインタ
	sl::UniquePtr<ReactionMarkManager
				, sl::DefaultDeleter<ReactionMarkManager>>	m_pReactionMarkManager;			//!< ReactionMarkManagerクラスのインスタンスへのユニークポインタ

};	// class FishReaction

}	// namespace pa

#endif	// PA_FISH_REACTION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
