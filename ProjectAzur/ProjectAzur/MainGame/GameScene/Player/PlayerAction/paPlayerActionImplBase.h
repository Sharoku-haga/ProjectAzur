//==================================================================================================================================//
//!< @file		paPlayerActionImplBase.h
//!< @brief		pa::PlayerActionImplBaseクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/26	更新履歴：
//==================================================================================================================================//

#ifndef PA_PLAYER_ACTION_IMPL_BASE_H
#define PA_PLAYER_ACTION_IMPL_BASE_H

#include "sl/Library/InputDevice/IInputDeviceLibrary/slIInputDeviceLibrary.h"
#include "../paPlayerCommonDeclaration.h"

namespace pa
{

//===================================================================================//
//!< プレイヤーアクションの実装の基底クラス
//===================================================================================//
class PlayerActionImplBase
{

public:
	/** アクション実装の種類 */
	enum TYPE 
	{
		ORIGINAL_ACTION,	//!< オリジナルアクション
		FISH_ACTION,		//!< 魚のアクション
		ACTION_MAX,			
	};	// enum TYPE

	/** Constructor */
	PlayerActionImplBase();

	/** Destructor */
	virtual ~PlayerActionImplBase();

	/** 初期化関数 */
	virtual void Initialize() = 0;

	/**
	* 更新関数
	* @param[out] rParam プレイヤーパラメータ 
	*/
	virtual void Update(PlayerParam& rParam) = 0;

	/** 破棄関数 */
	virtual void Finalize() = 0;

	/**
	* Getter
	* @return speedMinVal スピードの最小値
	*/
	inline float GetSpeedMinVal() { return m_SpeedMinVal; }

	/**
	* Getter
	* @return speedMaxVal スピードの最大値
	*/
	inline float GetSpeedMaxVal() { return m_SpeedMaxVal; }

protected:
	sl::IInputDeviceLibrary&	m_rInputLibrary;			//!< sl::IInputDeviceLibraryクラスのインスタンスへのポインタ
	
	/** 
	* 横に移動する関数 
	* @param[out] rParam プレイヤーパラメータ
	*/
	virtual void MoveHorizontally(PlayerParam& rParam) = 0;
	
	/** 
	* 縦に移動する関数 
	* @param[out] rParam プレイヤーパラメータ
	*/
	virtual void MoveVertically(PlayerParam& rParam) = 0;

	/** 
	* スピードを最大値と最小値の間に調整する
	* @param[in] speed 調整したいスピード
	* @return 調整したスピード
	*/
	float AdjustSpeedBetweenMaxandMinVal(float speed);

	/**
	* Setter
	* @param[in] speedMinVal スピードの最小値
	*/
	inline void SetSpeedMinVal(float speedMinVal) { m_SpeedMinVal = speedMinVal;  }

	/**
	* Setter
	* @param[in] speedMaxVal スピードの最大値
	*/
	inline void SetSpeedMaxVal(float speedMaxVal) { m_SpeedMaxVal = speedMaxVal;  }

private:
	float				m_SpeedMinVal;						//!< スピードの最小値
	float				m_SpeedMaxVal;						//!< スピードの最大値

};	// class PlayerActionImplBase

}	//namespace pa

#endif	// PA_PLAYER_ACTION_IMPL_BASE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
