﻿//==================================================================================================================================//
//!< @file		paColliderBase.cpp
//!< @brief		pa::ColliderBaseクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/05	更新履歴：2018/01/06
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paColliderBase.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

ColliderBase::ColliderBase(const std::string& rTypeName)
	: m_TypeName(rTypeName)
{}

/* Protected Functions ---------------------------------------------------------------------------------------- */

void ColliderBase::UpdateCurrentRectData()
{
	m_CurrentRectData.m_Left	= m_Pos.x + m_Size.m_Left; 
	m_CurrentRectData.m_Top		= m_Pos.y + m_Size.m_Top;
	m_CurrentRectData.m_Right	= m_Pos.x + m_Size.m_Right;
	m_CurrentRectData.m_Bottom	= m_Pos.y + m_Size.m_Bottom;
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
