//==================================================================================================================================//
//!< @file		paPlayerFishAction.h	
//!< @brief		pa::PlayerFishActionクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/26	更新履歴：
//==================================================================================================================================//

#ifndef PA_PLAYER_FISH_ACTION_H
#define PA_PLAYER_FISH_ACTION_H

#include "paPlayerActionImplBase.h"

namespace pa
{

//===================================================================================//
//!< プレイヤーの魚の形状時のアクションクラス
//===================================================================================//
class PlayerFishAction final : public PlayerActionImplBase
{

public:
	/** Constructor */
	PlayerFishAction();

	/** Destructor */
	virtual ~PlayerFishAction();

	/** 初期化関数 */
	virtual void Initialize()override;

	/**
	* 更新関数
	* @param[out] rParam プレイヤーパラメータ 
	*/
	virtual void Update(PlayerParam& rParam)override;

	/** 破棄関数 */
	virtual void Finalize()override;

};	// class PlayerFishAction

}	// namespace pa

#endif	// PA_PLAYER_FISH_ACTION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
