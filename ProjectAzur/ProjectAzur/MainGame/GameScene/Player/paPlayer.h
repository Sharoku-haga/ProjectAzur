//==================================================================================================================================//
//!< @file		paPlayer.h
//!< @brief		pa::Playerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/05	更新履歴：2017/12/07
//==================================================================================================================================//

#ifndef PA_PLAYER_H
#define PA_PLAYER_H

#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "sl/Library/Graphics/slGraphicsID.h"
#include "../../paIObjectBase.h"

namespace pa
{

struct	PlayerParam;
class	PlayerAction;
class	PlayerShape;

//===================================================================================//
//!< ゲームにおけるプレイヤーのクラス
//===================================================================================//
class Player final : public IObjectBase
{

public:
	/** 
	* Constructor
	* @param[in] rIDs					描画ID群
	* @param[in] pResrcDataFilePath		リソースデータのファイルパス
	*/
	Player(const sl::DrawingID& rIDs
		, const char*	pResrcDataFilePath);

	/** Destructor */
	virtual ~Player() = default;

	/** 初期化関数 */
	virtual void Initialize()override;

	/** 更新関数 */
	virtual void Update()override;

	/** 破棄関数 */
	virtual void Finalize()override;

private:
	sl::UniquePtr<PlayerParam, sl::DefaultDeleter<PlayerParam>>			m_pPlayerParam;		//!< PlayerParam構造体のインスタンスへのポインタ
	sl::UniquePtr<PlayerAction, sl::DefaultDeleter<PlayerAction>>		m_pPlayerAction;	//!< PlayerActionクラスのインスタンスへのポインタ
	sl::UniquePtr<PlayerShape, sl::DefaultDeleter<PlayerShape>>			m_pPlayerShape;		//!< PlayerShapeクラスのインスタンスへのポインタ

};	// class Player

}	// namespace pa

#endif	// PA_PLAYER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
