//==================================================================================================================================//
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
	~PlayerOriginalAction();

	/** 初期化関数 */
	virtual void Initialize()override;

	/**
	* 更新関数
	* @param[out] rParam プレイヤーパラメータ 
	*/
	virtual void Update(PlayerParam& rParam)override;

	/** 破棄関数 */
	virtual void Finalize()override;

};	// class PlayerOriginalAction

}	// namespace pa

#endif	// PA_PLAYER_ORIGINAL_ACTION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
