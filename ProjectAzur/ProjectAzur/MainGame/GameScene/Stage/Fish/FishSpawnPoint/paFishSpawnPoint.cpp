﻿//==================================================================================================================================//
//!< @file		paFishSpawnPoint.cpp
//!< @brief		pa::FishSpawnPointクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/24	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paFishSpawnPoint.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

FishSpawnPoint::FishSpawnPoint()
	: m_CurrentPointID(0)
{}

void FishSpawnPoint::Initialize()
{
	// 座標を収納していく

	// ID = 0
	m_PointPos.emplace_back(200.f, 200.f);
	
	// ID = 1
	m_PointPos.emplace_back(600.f, 600.f);

	// ID = 2
	m_PointPos.emplace_back(600.f, 1000.f);

}

void FishSpawnPoint::UpdatePoint()
{
	++m_CurrentPointID;

	if(m_CurrentPointID >= m_PointPos.size())
	{
		m_CurrentPointID = 0;
		return;
	}
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
