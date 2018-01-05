﻿//==================================================================================================================================//
//!< @file		paPlayerCollider.h
//!< @brief		pa::PlayerColliderクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/05	更新履歴：
//==================================================================================================================================//

#ifndef PA_PLAYER_COLLIDER_H
#define PA_PLAYER_COLLIDER_H

#include "paColliderBase.h"

namespace pa
{

//===================================================================================//
//!< プレイヤーの衝突を管理するクラス
//===================================================================================//
class PlayerCollider : public ColliderBase
{

public:
	/** Constructor */
	PlayerCollider();

	/** Destructor */
	virtual~PlayerCollider();

};	// class PlayerCollider

}	// namespace pa

#endif	// PA_PLAYER_COLLIDER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
