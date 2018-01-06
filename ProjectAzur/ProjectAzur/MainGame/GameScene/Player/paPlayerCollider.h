//==================================================================================================================================//
//!< @file		paPlayerCollider.h
//!< @brief		pa::PlayerColliderクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/05	更新履歴：2018/01/06
//==================================================================================================================================//

#ifndef PA_PLAYER_COLLIDER_H
#define PA_PLAYER_COLLIDER_H

#include "sl/Library/Utility/slRect.h"
#include "../Collider/paColliderBase.h"
#include "paPlayerCommonDeclaration.h"

namespace pa
{

class Player;

//===================================================================================//
//!< プレイヤーの衝突を管理するクラス
//===================================================================================//
class PlayerCollider final : public ColliderBase
{

public:
	/** 
	* Constructor 
	* @param[in] rSize			サイズ
	* @param[in] pPlayer		Playerクラスのインスタンスへのポインタ
	* @param[in] rParam			プレイヤーのパラメータ
	*/
	PlayerCollider(const sl::fRect& rSize
				, Player* pPlayer
				, const PlayerParam& rParam);

	/** Destructor */
	virtual~PlayerCollider();

	/** 初期化関数 */
	virtual void Initialize()override;

	/** 
	* 衝突処理を行う関数
	* 衝突した際に呼ばれる
	* @param[in] rCollider	衝突したCollider
	*/
	virtual void ProcessCollision(ColliderBase& rCollider)override;

	/** 
	* 更新関数
	* @param[in] rParam	プレイヤーのパラメータ
	*/
	void Update(const PlayerParam&	rParam);

	/** 
	* プレイヤーのパラメータを調整する関数
	* @param[out] rParam	プレイヤーのパラメータ
	*/
	void AdjustPlayerParam(PlayerParam&	rParam);

private:
	Player*						m_pOwner;				//!< オーナーのポインタ
	D3DXVECTOR2					m_DiffPos;				//!< 差分座標

	/** 
	* 衝突時における差分の値を計算する関数 
	* @param[in] rCollider	衝突したCollider
	*/
	void CalculateDiffVal(ColliderBase& rCollider);

};	// class PlayerCollider

}	// namespace pa

#endif	// PA_PLAYER_COLLIDER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
