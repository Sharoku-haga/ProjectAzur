//==================================================================================================================================//
//!< @file		paBehaviorFactory.cpp
//!< @brief		pa::BehaviorFactoryクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/30	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "BehaviorFactory.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

BehaviorFactory::BehaviorFactory()
{}

BehaviorFactory::~BehaviorFactory()
{}

void BehaviorFactory::Initialize()
{}

BehaviorBase* BehaviorFactory::GetBehavior(const std::string& rName)
{
	return m_pBehavior[rName];
}

void BehaviorFactory::Finalize()
{
	for(auto& pBehavior : m_pBehavior)
	{
		delete pBehavior.second;
		pBehavior.second = nullptr;
	}
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
