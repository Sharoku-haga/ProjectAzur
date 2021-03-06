﻿//==================================================================================================================================//
//!< @file		paPlayerOriginalAction.h		
//!< @brief		pa::PlayerOriginalActionクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/26	更新履歴：
//==================================================================================================================================//

#ifndef PA_PLAYER_ORIGINAL_ACTION_H
#define PA_PLAYER_ORIGINAL_ACTION_H

#include "paPlayerActionImplBase.h"

namespace pa
{

//===================================================================================//
//!< プレイヤーのオリジナルの形状の際のアクションクラス
//===================================================================================//
class PlayerOriginalAction final : public PlayerActionImplBase
{

public:
	/** Constructor */
	PlayerOriginalAction();

	/** Destructor */
	virtual ~PlayerOriginalAction();

	/** 初期化関数 */
	virtual void Initialize()override;

	/**
	* 更新関数
	* @param[out] rParam プレイヤーパラメータ 
	*/
	virtual void Update(PlayerParam& rParam)override;

	/** 破棄関数 */
	virtual void Finalize()override;

private:
	/** 
	* 横に移動する関数 
	* @param[out] rParam プレイヤーパラメータ
	*/
	virtual void MoveHorizontally(PlayerParam& rParam)override;
	
	/** 
	* 縦に移動する関数 
	* @param[out] rParam プレイヤーパラメータ
	*/
	virtual void MoveVertically(PlayerParam& rParam)override;

};	// class PlayerOriginalAction

}	// namespace pa

#endif	// PA_PLAYER_ORIGINAL_ACTION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
