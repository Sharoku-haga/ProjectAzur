//==================================================================================================================================//
//!< @file		slCalculationFunc.cpp
//!< @brief		計算関連の関数をまとめたファイルの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/11/13	更新履歴：
//==================================================================================================================================//

#include "slCalculationFunc.h"

namespace sl
{
namespace calculation
{ 

void Calculate2DMatWorld(D3DXMATRIX* pMatWorld
						, const D3DXVECTOR2& rPos
						, const D3DXVECTOR3& rScale
						, float angle)
{
	D3DXMATRIX matTranslate,matRotate;
	D3DXMatrixIdentity(pMatWorld);
	D3DXMatrixScaling(pMatWorld, rScale.x, rScale.y, 1.0f);
	D3DXMatrixRotationZ(&matRotate, angle);
	D3DXMatrixMultiply(pMatWorld, pMatWorld, &matRotate);
	D3DXMatrixTranslation(&matTranslate, rPos.x, rPos.y, 0);
	D3DXMatrixMultiply(pMatWorld, pMatWorld, &matTranslate);

}




}	// namespace calculation
}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
