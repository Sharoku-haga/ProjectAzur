//==================================================================================================================================//
//!< @file		paColliderManager.h
//!< @brief		pa::ColliderManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/05	更新履歴：2018/01/06
//==================================================================================================================================//

#ifndef PA_COLLIDER_MANAGER_H
#define PA_COLLIDER_MANAGER_H

#include <vector>
#include "sl/Library/Utility/slRect.h"
#include "sl/Library/Singleton/slUserManualSingleton.h"
#include "sl/Library/SmartPointer/SharedPtr/slSharedPtr.h"
#include "paColliderBase.h"

namespace pa
{

//===================================================================================//
//!< Colliderクラスを管理するクラス
//!< Singletonクラス
//===================================================================================//
class ColliderManager final : public sl::UserManualSingleton<ColliderManager>
{

public:
	/** 更新関数 */
	void Update();

	/**
	* プレイヤーのColldierを登録する関数
	* @param[in] rPlayerCollider プレイヤーのColldierクラスのへのポインタ
	*/
	void RegisterPlayerCollider(sl::SharedPtr<ColliderBase> pPlayerCollider)
	{
		m_pPlayerCoolider = pPlayerCollider;
	}

	/** 
	* ステージ上のオブジェクトのColliderを登録する関数 
	* 毎フレーム呼ばれる
	* @param[in] pStageObjCollider ステージ上のオブジェクトのColliderのポインタ
	*/
	void RegisterStageObjCollider(sl::SharedPtr<ColliderBase> pStageObjCollider);

private:
	friend class sl::UserManualSingleton <ColliderManager>;

	sl::SharedPtr<ColliderBase>					m_pPlayerCoolider;			//!< プレイヤーのColldierクラスのへのポインタ
	std::vector<sl::SharedPtr<ColliderBase>>	m_pStageObjColliders;		//!< ステージ上のオブジェクトのColliderへのポインタの動的配列

	/** Constructor */
	ColliderManager() = default;

	/** Destructor */
	virtual ~ColliderManager() = default;

	/** プレイヤーとの衝突判定を行う関数 */
	void CheckCollisionPlayer();

	/**
	* 2つの矩形の衝突判定を行う関数.
	* @param[in] rRectA 判定したい矩形の1つ 
	* @param[in] rRectB  判定したい矩形の1つ
	* @return 衝突しているかどうか true→衝突している false→衝突していない
	*/
	bool CheckRectCollision(const sl::fRect& rRectA, const sl::fRect& rRectB);

	/** 現在登録しているColliderポインタをリセットする関数 */
	void ResetColliderPointer();

};	// class ColliderManager

}	// namespace pa

#endif	// PA_COLLIDER_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
