//==================================================================================================================================//
//!< @file		paPlayerAction.h
//!< @brief		pa::PlayerActionクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/05	更新履歴：2018/01/28
//==================================================================================================================================//

#ifndef PA_PLAYER_ACTION_H
#define PA_PLAYER_ACTION_H

#include <vector>
#include <D3DX11.h>
#include <D3DX10.h>
#include "sl/Library/SmartPointer/slSmartPointer.h"
#include "../paPlayerCommonDeclaration.h"
#include "paPlayerActionImplBase.h"

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

	/** プレイヤーの魚アクションに変える関数 */
	void ChangeFishActionImpl();

	/** プレイヤーのオリジナルアクションに変える関数 */
	void ChangeOriginalActionimpl();

private:
	std::vector<sl::UniquePtr<PlayerActionImplBase>>			m_pActionImpl;				//!< PlayerActionImplBaseクラスのインスタンスへのユニークポインタ
	int															m_ActiveImplIndex;			//!< 現在のアクティブなm_pActionImplのインデックス

};	// class PlayerAction

} // namespace pa

#endif	// PA_PLAYER_ACTION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
