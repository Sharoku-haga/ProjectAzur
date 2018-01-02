//==================================================================================================================================//
//!< @file		paFish.h
//!< @brief		pa::Fishクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/23	更新履歴：2018/01/01
//==================================================================================================================================//

#ifndef PA_FISH_H
#define PA_FISH_H

#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "../paStageObjBase.h"
#include "FishShape/paFishShape.h"

namespace pa
{

//===================================================================================//
//!< ゲームの魚のクラス
//===================================================================================//
class Fish final : public StageObjBase
{

public:
	/** Constructor */
	Fish(const D3DXVECTOR2& rPos, sl::UniquePtr<FishShape> pShape);

	/** Destructor */
	virtual ~Fish();

	/** 初期化関数 */
	virtual void Initialize()override;

	/** 更新関数 */
	virtual void Update()override;

	/** 破棄関数 */
	virtual void Finalize()override;

};	// class Fish

}	// namespace pa

#endif	// PA_FISH_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
