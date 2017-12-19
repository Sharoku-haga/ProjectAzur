//==================================================================================================================================//
//!< @file		paGaugeTimer.h
//!< @brief		pa::GaugeTimerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/18	更新履歴：2017/12/19
//==================================================================================================================================//

#ifndef PA_GAUGE_TIMER_H
#define PA_GAUGE_TIMER_H

namespace pa
{

//===================================================================================//
//!< 電池ゲージの経過時間をカウントするクラス
//!< ゲームのFPSは60fps
//===================================================================================//
class GaugeTimer final
{

public:
	/** 
	* Constructor 
	* @param[in] oneEnergyBlockTime エネルギーブロック1つ分の時間
	*/
	GaugeTimer(int oneEnergyBlockTime);

	/** Destructor */
	~GaugeTimer() = default;

	/** 初期化関数 */
	void Initialize();

	/** 時間カウントを開始する関数 */
	void Start();

	/** 更新関数 */
	void Update();

	/** 時間カウントをストップする関数 */
	void Stop();

	/** 
	* 現在の時間カウント数を知らせる関数 
	* @param[out] rTimeCount 現在の時間カウント数を格納する変数
	*/
	void InformCurrentTimeCount(int& rTimeCount);

	/** 
	* 現在の時間カウントから<br>
	* エネルギーブロック1つ分の時間を進める関数 
	*/
	void ProceedOneEnergyBlockTime();

private:
	int		m_CurrentTimeCount;		//!< 現在の時間のカウント数
	int		m_OneEnergyBlockTime;	//!< エネルギーブロック1つ分の時間
	bool	m_HasStartedCount;		//!< カウントを開始したかどうか true→開始している false→開始していない

};	// class GaugeTimer

}	// namespace pa

#endif // PA_GAUGE_TIMER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
