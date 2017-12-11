//==================================================================================================================================//
//!< @file		paStageBackgroundManager.h
//!< @brief		pa::StageBackgroundManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/11	更新履歴：
//==================================================================================================================================//

#ifndef PA_STAGE_BACKGROUND_MANAGER_H
#define PA_STAGE_BACKGROUND_MANAGER_H

#include "../paIStageObjManager.h"

namespace pa
{

//===================================================================================//
//!< StageBAckgroundクラスを管理するクラス
//===================================================================================//
class StageBackgroundManager : public IStageObjManager
{

public:
	/** Constructor */
	StageBackgroundManager();

	/** Destructor */
	virtual ~StageBackgroundManager();

	/** 初期関数 */
	virtual void Initialize()override;

	/** 更新関数 */
	virtual void Update()override;

	/** 破棄関数 */
	virtual void Finalize()override;

};	// class StageBackgroundManager

}	// namespace pa

#endif	// PA_STAGE_BACKGROUND_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
