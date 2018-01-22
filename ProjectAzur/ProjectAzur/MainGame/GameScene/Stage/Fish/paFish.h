//==================================================================================================================================//
//!< @file		paFish.h
//!< @brief		pa::Fishクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/23	更新履歴：2018/01/03
//==================================================================================================================================//

#ifndef PA_FISH_H
#define PA_FISH_H

#include <D3DX11.h>
#include <D3DX10.h>
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "../paStageObjBase.h"
#include "paFishCommonDeclaration.h"
#include "FishShape/paFishShape.h"
#include "FishReaction/paFishReaction.h"
#include "FishReaction\paFishReaction.h"

namespace pa
{

class FishCollider;
class DrawTask;

//===================================================================================//
//!< ゲームの魚のクラス
//===================================================================================//
class Fish final : public StageObjBase
{

public:
	/** 
	* Constructor 
	* @param[in] rPos		位置座標
	* @param[in] pShape		形状
	* @param[in] pReaction	リアクション
	*/
	Fish(const D3DXVECTOR2& rPos
		, sl::UniquePtr<FishShape> pShape
		, sl::UniquePtr<FishReaction> pReaction);

	/** Destructor */
	virtual ~Fish();

	/** 初期化関数 */
	virtual void Initialize()override;

	/** 更新関数 */
	virtual void Update()override;

	/** 破棄関数 */
	virtual void Finalize()override;

private:
	FishParam												m_Param;		//!< 魚のパラメータ
	sl::UniquePtr<FishShape>								m_pShape;		//!< FishShapeクラスのインスタンスへのユニークポインタ
	sl::UniquePtr<FishReaction>								m_pReaction;	//!< FishReactionクラスのインスタンスへのユニークポインタ
	sl::UniquePtr<FishCollider
				, sl::DefaultDeleter<FishCollider>>			m_pCollider;	//!< FishColliderクラスのインスタンスへのユニークポインタ
	sl::UniquePtr<DrawTask
				, sl::DefaultDeleter<DrawTask>>				m_pDrawTask;	//!< DrawTaskクラスのインスタンスへのユニークポインタ

	/** 描画関数 */
	void Draw();

};	// class Fish

}	// namespace pa

#endif	// PA_FISH_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
