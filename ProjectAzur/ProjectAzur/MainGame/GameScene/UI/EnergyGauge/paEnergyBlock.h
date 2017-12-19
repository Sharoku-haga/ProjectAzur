//==================================================================================================================================//
//!< @file		paEnergyBlock.h
//!< @brief		pa::EnergyBlockクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/18	更新履歴：2017/12/19
//==================================================================================================================================//

#ifndef PA_ENERGY_BLOCK_H
#define PA_ENERGY_BLOCK_H

#include <D3DX11.h>
#include <D3DX10.h>
#include <string>
#include "sl/Library/Graphics/slGraphicsID.h"
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"

namespace pa
{

struct ObjDrawingData;

//===================================================================================//
//!< 電池のエネルギーブロッククラス
//===================================================================================//
class EnergyBlock final
{

public:
	/** 
	* Constructor 
	* @param[in] rIDs					描画データID群
	* @param[in] rResrcDataFilePath		リソースデータファイルへのパス
	* @param[in] rGaugePosDiff			ゲージ座標との差分
	*/
	EnergyBlock(const sl::DrawingID& rIDs
				, const std::string& rResrcDataFilePath
				, const D3DXVECTOR2& rGaugePosDiff);

	/** Destructor */
	~EnergyBlock();

	/** 
	* 描画関数.
	* この関数はEnergyGaugeクラスのDraw関数内でよぶ 
	* @param[in] rGaugePos ゲージの座標
	*/
	void Draw(const D3DXVECTOR2& rGaugePos);

private:
	sl::UniquePtr<ObjDrawingData, sl::DefaultDeleter<ObjDrawingData>>	m_pDrawingData;				//!< 描画データ構造体のインスタンスへのユニークポインタ
	D3DXVECTOR2															m_GaugeDiffPos;				//!< ゲージ座標との座標の差分

};	// class EnergyBlock

}	// namespace pa

#endif	// PA_ENERGY_BLOCK_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
