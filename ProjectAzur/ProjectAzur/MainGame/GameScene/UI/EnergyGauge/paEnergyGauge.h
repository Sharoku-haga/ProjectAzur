//==================================================================================================================================//
//!< @file		paEnergyGauge.h
//!< @brief		pa::EnergyGaugeクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/18	更新履歴：2017/12/19
//==================================================================================================================================//

#ifndef PA_ENERGY_GAUGE_H
#define PA_ENERGY_GAUGE_H

#include <vector>
#include <string>
#include "sl/Library/Graphics/slGraphicsID.h"
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "sl/Library/SmartPointer/SharedPtr/slSharedPtr.h"
#include "../paIUI.h"

namespace pa
{

struct ObjDrawingData;
class EnergyBlock;
class GaugeFlame;

//===================================================================================//
//!< 電池ゲージクラス
//!< ゲームのプレイ時間をあらわすUI
//===================================================================================//
class EnergyGauge final : public IUI
{

public:
	/** 
	* Constructor 
	* @param[in] rIDs					描画データID群
	* @param[in] rResrcDataFilePath		リソースデータファイルへのパス
	*/
	EnergyGauge(const sl::DrawingID&	rIDs
				, const std::string&	rResrcDataFilePath);

	/** Destructor */
	virtual ~EnergyGauge();

	/** 初期化関数 */
	virtual void Initialize()override;

	/** 更新関数 */
	virtual void Update()override;

	/** 破棄関数 */
	virtual void Finalize()override;

private:
	sl::UniquePtr<ObjDrawingData
				, sl::DefaultDeleter<ObjDrawingData>>			m_pDrawingData;			//!< 描画データ構造体のインスタンスへのユニークポインタ
	std::string													m_ResrcDataFilePath;	//!< リソースデータファイルパス
	sl::UniquePtr<GaugeFlame
				, sl::DefaultDeleter<GaugeFlame>>				m_pGaugeFlame;			//!< GaugeFlameクラスのインスタンスへのユニークポインタ 
	std::vector<sl::UniquePtr<EnergyBlock
						, sl::DefaultDeleter<EnergyBlock>>>		m_pEnergyBlocks;		//!< EnergyBlockクラスのインスタンスへのユニークポインタの動的配列
	
	/** 描画関数 */
	void Draw();

};	// class EnergyGauge

}	// namespace pa

#endif	// PA_ENERGY_GAUGE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
