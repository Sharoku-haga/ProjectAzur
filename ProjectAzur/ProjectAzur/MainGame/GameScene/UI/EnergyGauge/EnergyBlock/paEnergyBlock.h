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
class EnergyEmptyBlock;

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
	* @param[in] oneEnergyBlockTime		1つ分エネルギーブロックの時間
	*/
	EnergyBlock(const sl::DrawingID& rIDs
				, const std::string& rResrcDataFilePath
				, const D3DXVECTOR2& rGaugePosDiff
				, int oneEnergyBlockTime);

	/** Destructor */
	~EnergyBlock();

	/**
	* エネルギーを減らす関数
	* @param[in] elapsedTime 経過時間
	* @return エネルギーがなくなったかどうか true→なくなった false→なくなっていない
	*/
	bool DecreaseEnergy(int elapsedTime);

	/** エネルギーを空にする関数 */
	void EmptyEnergy();

	/** ブロックの色を赤に変える関数 */
	void ChangeColorRed();

	/** 
	* 描画関数.
	* この関数はEnergyGaugeクラスのDraw関数内でよぶ 
	* @param[in] rGaugePos ゲージの座標
	*/
	void Draw(const D3DXVECTOR2& rGaugePos);

private:
	sl::UniquePtr<ObjDrawingData
				, sl::DefaultDeleter<ObjDrawingData>>	m_pDrawingData;				//!< 描画データ構造体のインスタンスへのユニークポインタ
	sl::UniquePtr<EnergyEmptyBlock
				, sl::DefaultDeleter<EnergyEmptyBlock>>	m_pEmptyBlock;				//!< EnergyEmptyBlockクラスのインスタンスへのユニークポインタ
	D3DXVECTOR2											m_GaugeDiffPos;				//!< ゲージ座標との座標の差分

};	// class EnergyBlock

}	// namespace pa

#endif	// PA_ENERGY_BLOCK_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
