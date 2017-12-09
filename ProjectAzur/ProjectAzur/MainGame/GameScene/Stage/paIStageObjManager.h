//==================================================================================================================================//
//!< @file		paIStageObjManager.h		
//!< @brief		pa;;IStageObjManagerインターフェースのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/09	更新履歴：2017/12/11
//==================================================================================================================================//

#ifndef PA_ISTAGE_OBJ_MANAGER_H
#define PA_ISTAGE_OBJ_MANAGER_H

#include "sl/Library/Utility/slDefine.h"

namespace pa
{

//===================================================================================//
//!< StageObjBaseを継承したクラスを管理するManagerクラスのインターフェース
//===================================================================================//
interface IStageObjManager
{

public:
	/** Constructor */
	IStageObjManager() = default;

	/** Destructor */
	virtual ~IStageObjManager() = default;

	/** 初期関数 */
	virtual void Initialize() = 0;

	/** 更新関数 */
	virtual void Update() = 0;

	/** 破棄関数 */
	virtual void Finalize() = 0;

};	// interface IStageObjManager

}	// namespace pa

#endif	// PA_ISTAGE_OBJ_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
