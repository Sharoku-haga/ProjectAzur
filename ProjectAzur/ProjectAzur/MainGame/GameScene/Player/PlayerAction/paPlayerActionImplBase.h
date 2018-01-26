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

protected:
	sl::IInputDeviceLibrary&	m_rInputLibrary;			//!< sl::IInputDeviceLibraryクラスのインスタンスへのポインタ
	
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

private:
	float				m_SpeedMinVal;						//!< スピードの最小値
	float				m_SpeedMaxVal;						//!< スピードの最大値

};	// class PlayerActionImplBase

}	//namespace pa

#endif	// PA_PLAYER_ACTION_IMPL_BASE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
