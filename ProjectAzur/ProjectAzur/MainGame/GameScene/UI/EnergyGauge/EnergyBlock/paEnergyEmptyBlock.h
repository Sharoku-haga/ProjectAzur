//==================================================================================================================================//
//!< @file		paEnergyEmptyBlock.h
//!< @brief		pa::EnergyEmptyBlockクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/19	更新履歴：
//==================================================================================================================================//

#ifndef PA_ENERGY_EMPTY_BLOCK_H
#define PA_ENERGY_EMPTY_BLOCK_H

#include <D3DX11.h>
#include <D3DX10.h>
#include <string>
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "sl/Library/Graphics/slGraphicsID.h"
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"

namespace pa
{

struct ObjDrawingData;

//===================================================================================//
//!< 電池のエネルギーが空になったブロックのクラス
//!< エネルギーブロックの上に描画して、あたかも減ってるように見せるためのクラス
//===================================================================================//
class EnergyEmptyBlock final
{

public:
	/** 
	* Constructor 
	* @param[in] rIDs					描画データID群
	* @param[in] rResrcDataFilePath		リソースデータファイルへのパス
	* @param[in] rGaugePosDiff			ゲージ座標との差分
	* @param[in] oneEnergyBlockTime		1つ分エネルギーブロックの時間
	*/
	EnergyEmptyBlock(const sl::DrawingID& rIDs
					, const std::string& rResrcDataFilePath
					, const D3DXVECTOR2& rGaugePosDiff
					, int oneEnergyBlockTime);

	/** Destructor */
	~EnergyEmptyBlock();

	/**
	* 横のサイズを更新関数
	* @param[in] elapsedTime 経過時間
	* @return ブロック全てにかぶさったかどうか true→かぶさった false→かぶさってない
	*/
	bool UpdateWidthSize(int elapsedTime);

	/** 横のサイズを全て更新(本来のサイズに)する関数 */
	void UpdateWidthSizeAll();

	/** 
	* 描画関数.
	* この関数はEnergyGaugeクラスのDraw関数内でよぶ 
	* @param[in] rGaugePos ゲージの座標
	*/
	void Draw(const D3DXVECTOR2& rGaugePos);

private:
	sl::DX11GraphicsLibrary&											m_rGraphicsLibrary;			//!< DX11GraphicsLibraryクラスのインスタンスへの参照
	sl::UniquePtr<ObjDrawingData, sl::DefaultDeleter<ObjDrawingData>>	m_pDrawingData;				//!< 描画データ構造体のインスタンスへのユニークポインタ
	D3DXVECTOR2															m_GaugeDiffPos;				//!< ゲージ座標との座標の差分
	float																m_OriginalWidth;			//!< 本来の横の長さ
	float																m_OriginalHeight;			//!< 本来の縦の長さ
	float																m_CurrentWidth;				//!< 現在の横の長さ
	float																m_GaugeScrollSpeed;			//!< ゲージのスクロールスピード

	/** 
	* ゲージのスクロールスピードを計算する関数 
	* @param[in] oneEnergyBlockTime 1つ分エネルギーブロックの時間
	*/
	void CalculateGaugeScrollSpeed(int oneEnergyBlockTime);

};	// class EnergyEmptyBlock

}	// namespace pa

#endif	// PA_ENERGY_EMPTY_BLOCK_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
