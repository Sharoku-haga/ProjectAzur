﻿//==================================================================================================================================//
//!< @file		paFishManager.h
//!< @brief		pa::FishManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/23	更新履歴：2017/12/24
//==================================================================================================================================//

#ifndef PA_FISH_MANAGER_H
#define PA_FISH_MANAGER_H

#include "../paIStageObjManager.h"

namespace pa
{

//===================================================================================//
//!< Fishクラスを管理するクラス
//===================================================================================//
class FishManager : public IStageObjManager
{

public:
	/** Constructor */
	FishManager();

	/** Destructor */
	virtual ~FishManager();

};	// class FishManager

}	// namespace pa

#endif	// PA_FISH_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//