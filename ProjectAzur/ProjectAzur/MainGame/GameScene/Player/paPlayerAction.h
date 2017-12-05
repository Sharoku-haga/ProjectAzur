//==================================================================================================================================//
//!< @file		paPlayerAction.h
//!< @brief		pa::PlayerActionクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/05	更新履歴：2017/12/07
//==================================================================================================================================//

#ifndef PA_PLAYER_ACTION_H
#define PA_PLAYER_ACTION_H

#include <D3DX10.h>
#include "paPlayerCommonDeclaration.h"

namespace sl
{

class IInputDeviceLibrary;

}

namespace pa
{

//===================================================================================//
//!< プレイヤーの動作を管理するクラス
//===================================================================================//
class PlayerAction final
{

public:
	/** Constructor */
	PlayerAction();

	/** Destructor */
	~PlayerAction() = default;

	/** 初期化関数 */
	void Initialize();

	/**
	* 更新関数
	* @param[out] rParam プレイヤーパラメータ 
	*/
	void Update(PlayerParam& rParam);

	/** 破棄関数 */
	void Finalize();

private:
	sl::IInputDeviceLibrary&	m_rInputLibrary;					//!< sl::IInputDeviceLibraryクラスのインスタンスへのポインタ
	float						m_SpeedMinVal;						//!< スピードの最小値
	float						m_SpeedMaxVal;						//!< スピードの最大値
	float						m_CurrentVerticalSpeed;				//!< 現在の縦のスピード
	float						m_CurrentHorizontalSpeed;			//!< 現在の横のスピード

	/** 
	* 横に移動する関数 
	* @param[out] rParam プレイヤーパラメータ
	*/
	void MoveHorizontally(PlayerParam& rParam);
	
	/** 
	* 縦に移動する関数 
	* @param[out] rParam プレイヤーパラメータ
	*/
	void MoveVertically(PlayerParam& rParam);

	/** 
	* 回転する関数
	* @param[out] rParam プレイヤーパラメータ
	*/
	void Rotate(PlayerParam& rParam);

};	// namespace pa

}
#endif	// PA_PLAYER_ACTION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
