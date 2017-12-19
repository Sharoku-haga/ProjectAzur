//==================================================================================================================================//
//!< @file		paGaugeFlame.h
//!< @brief		pa::GaugeFlameクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/18	更新履歴：2017/12/19
//==================================================================================================================================//

#ifndef PA_GAUGE_FLAME_H
#define PA_GAUGE_FLAME_H

#include <D3DX11.h>
#include <D3DX10.h>
#include <string>
#include "sl/Library/Graphics/slGraphicsID.h"
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"

namespace pa
{

struct ObjDrawingData;

//===================================================================================//
//!< 電池UIのフレーム部分のクラス 
//===================================================================================//
class GaugeFlame final
{

public:
	/** 
	* Constructor 
	* @param[in] rIDs					描画データID群
	* @param[in] rResrcDataFilePath		リソースデータファイルへのパス
	*/
	GaugeFlame(const sl::DrawingID& rIDs
			, const std::string&	rResrcDataFilePath);

	/** Destructor */
	~GaugeFlame();

	/** 
	* 描画関数.
	* この関数はEnergyGaugeクラスのDraw関数内でよぶ 
	* @param[in] rGaugePos ゲージの座標
	*/
	void Draw(const D3DXVECTOR2& rGaugePos);

private:
	sl::UniquePtr<ObjDrawingData, sl::DefaultDeleter<ObjDrawingData>>	m_pDrawingData;				//!< 描画データ構造体のインスタンスへのユニークポインタ

};	// class GaugeFlame

}	// namespace pa

#endif	// PA_GAUGE_FLAME_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
