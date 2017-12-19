//==================================================================================================================================//
//!< @file		paGaugeTimer.cpp
//!< @brief		pa::GaugeTimerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/18	更新履歴：2017/12/19
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "sl/Library/Utility/slDefine.h"
#include "paGaugeTimer.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

GaugeTimer::GaugeTimer(int oneEnergyBlockTime)
	: m_CurrentTimeCount(0)
	, m_OneEnergyBlockTime(oneEnergyBlockTime)
	, m_HasStartedCount(false)
{}

void GaugeTimer::Initialize()
{
	m_CurrentTimeCount = 0;
	m_HasStartedCount = false;
}

void GaugeTimer::Start()
{
	m_HasStartedCount = true;
}

void GaugeTimer::Update()
{
	if(RESULT_FALSE(m_HasStartedCount))
	{
		return;
	}

	++m_CurrentTimeCount;
}

void GaugeTimer::Stop()
{
	m_HasStartedCount = false;
}

void GaugeTimer::InformCurrentTimeCount(int& rTimeCount)
{
	rTimeCount = m_CurrentTimeCount;
}

void GaugeTimer::ProceedOneEnergyBlockTime()
{
	m_CurrentTimeCount += m_OneEnergyBlockTime;
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
