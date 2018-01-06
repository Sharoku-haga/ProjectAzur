//==================================================================================================================================//
//!< @file		paFishCollider.h
//!< @brief		pa::FishColliderクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/05	更新履歴：2018/01/06
//==================================================================================================================================//

#ifndef PA_FISH_COLLIDER_H
#define PA_FISH_COLLIDER_H

#include "sl/Library/Utility/slRect.h"
#include "../../../Collider/paColliderBase.h"
#include "../paFishParam.h"

namespace pa
{

class Fish;

//===================================================================================//
//!< 魚の衝突を管理するクラス
//===================================================================================//
class FishCollider : public ColliderBase
{

public:
	/** 
	* Constructor 
	* @param[in] rSize			サイズ
	* @param[in] pFish			Fishクラスのインスタンスへのポインタ
	* @param[in] rParam			魚のパラメータ
	*/
	FishCollider(const sl::fRect& rSize
				, Fish* pFish
				, const FishParam& rParam);

	/** Destructor */
	virtual ~FishCollider();

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
	* @param[in] rParam	魚のパラメータ
	*/
	void Update(const FishParam& rParam);

private:
	Fish*		m_pOwner;	//!< オーナーのポインタ

};	// class FishCollider

}	// namespace pa

#endif	// PA_FISH_COLLIDER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
