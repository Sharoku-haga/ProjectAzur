//==================================================================================================================================//
//!< @file		paEnergyGauge.h
//!< @brief		pa::EnergyGaugeクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/18	更新履歴：2017/12/20
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
class GaugeTimer;
class GaugeEffect;

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
	/** ゲージの処理状態*/
	enum PROCESSING_STATE
	{
		NORMAL_PROCESSING,			//!< 通常の処理. 
		DAMAGE_PROCESSING,			//!< ダメージ処理. プレイヤーが食べられた(ダメージ)ときの処理
	};

	sl::UniquePtr<ObjDrawingData
				, sl::DefaultDeleter<ObjDrawingData>>			m_pDrawingData;				//!< 描画データ構造体のインスタンスへのユニークポインタ
	std::string													m_ResrcDataFilePath;		//!< リソースデータファイルパス
		sl::UniquePtr<GaugeTimer
				, sl::DefaultDeleter<GaugeTimer>>				m_pGaugeTimer;				//!< GaugeTimerクラスのインスタンスへのユニークポインタ 
	sl::UniquePtr<GaugeFlame
				, sl::DefaultDeleter<GaugeFlame>>				m_pGaugeFlame;				//!< GaugeFlameクラスのインスタンスへのユニークポインタ 
	std::vector<sl::UniquePtr<EnergyBlock
						, sl::DefaultDeleter<EnergyBlock>>>		m_pEnergyBlocks;			//!< EnergyBlockクラスのインスタンスへのユニークポインタの動的配列
	sl::UniquePtr<GaugeEffect
				, sl::DefaultDeleter<GaugeEffect>>				m_pGaugeEffect;				//!< GaugeEffectクラスのインスタンスへのユニークポインタ
	int															m_CurrentEnergyBlockNum;	//!< 現在のエネルギーブロックの番号
	PROCESSING_STATE											m_ProcessingState;			//!< プロセスの状態

	/** 描画関数 */
	void Draw();

	/** 通常処理を行う関数 */
	void RunNormalProcessing();

	/** ダメージ処理を行う関数 */
	void RunDamageProcessing();

};	// class EnergyGauge

}	// namespace pa

#endif	// PA_ENERGY_GAUGE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
