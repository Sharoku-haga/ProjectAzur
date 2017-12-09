//==================================================================================================================================//
//!< @file		paStageObjBase.cpp
//!< @brief		pa::StageObjBaseクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/09	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paStageObjBase.h"

namespace pa
{

/* Protected Functions ---------------------------------------------------------------------------------------- */

bool StageObjBase::CheckScreenArea(const D3DXVECTOR2&	rMyPos, const sl::fRect& rMySize)
{
	//画面範囲内に存在しているか横と縦にわけて確認する
	// 確認際、補正値としてオブジェクトのサイズを計算にいれる
	float widthSize = rMySize.m_Right - rMySize.m_Left;

	if( rMyPos.x < (m_BasePointPos.x - widthSize)
	|| rMyPos.x > (m_BasePointPos.x + widthSize + m_ScreenSize.m_Right))
	{
		return false;
	}
 
	float heightSize = rMySize.m_Bottom - rMySize.m_Top;

	if( rMyPos.y < (m_BasePointPos.y - heightSize)
	|| rMyPos.y > (m_BasePointPos.y + heightSize + m_ScreenSize.m_Bottom))
	{
		return false;
	}
	return true;
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
