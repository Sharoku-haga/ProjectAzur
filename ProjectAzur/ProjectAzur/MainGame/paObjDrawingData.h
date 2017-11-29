//==================================================================================================================================//
//!< @file		paObjDrawingData.h
//!< @brief		pa::ObjDrawingData構造体のヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/29	更新履歴：
//==================================================================================================================================//

#ifndef PA_OBJ_DRAWING_DATA_H
#define PA_OBJ_DRAWING_DATA_H

#include <D3DX10.h>
#include "sl/Library/Graphics/slGraphicsID.h"
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "DrawTask/paDrawTask.h"

namespace pa
{

//===================================================================================//
//!< オブジェクトの描画に関するデータ
//===================================================================================//
struct ObjDrawingData
{
	D3DXVECTOR2					m_Pos;				//!< 位置座標
	float						m_Angle;			//!< 角度(デフォルト値は0.0ｆ)
	D3DXVECTOR3					m_Scale;			//!< スケール値(デフォルト値は1.0ｆ, 1.0ｆ, 1.0ｆ)
	sl::DrawingID				m_IDs;				//!< 描画に関するID群 
	sl::UniquePtr<DrawTask>		m_pTask;			//!< DrawTaskクラスのインスタンスへのポインタ

	ObjDrawingData() 
		: m_Angle(0.0f)
		, m_Scale({1.0f, 1.0f, 1.0f})
	{}

};	// struct ObjDrawingData

}	// namespace pa

#endif	// PA_OBJ_DRAWING_DATA_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
