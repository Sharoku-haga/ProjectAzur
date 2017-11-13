//==================================================================================================================================//
//!< @file		slCalculationFunc.h
//!< @brief		計算関連の関数をまとめたファイルのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/13	更新履歴：
//==================================================================================================================================//

#ifndef SL_CALCULATION_HFUNC_H
#define SL_CALCULATION_HFUNC_H

#include <d3dx11.h>
#include <d3dx10.h>

namespace sl
{
namespace calculation
{


/**
* 2Dにおけるワールド座標を計算する関数
* @param[out]	pMatWorld	計算したワールド座標を格納する変数
* @param[in]	rPos		位置座標	
* @param[in]	rScale		スケール値.デフォルトが1.0倍
* @param[in]	angle		角度.デフォルト値は0.0ｆ
*/
void Calculate2DMatWorld(D3DXMATRIX* pMatWorld
						, const D3DXVECTOR2& rPos
						, const D3DXVECTOR3& rScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f)
						, float angle = 0.0f);


}	// namespace calculation
}	// namespace sl

#endif	// SL_CALCULATION_HFUNC_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//

