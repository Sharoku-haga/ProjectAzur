//==================================================================================================================================//
//!< @file		paStage.h		
//!< @brief		pa::Stageクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/09	更新履歴：2017/12/11
//==================================================================================================================================//

#ifndef PA_STAGE_H
#define PA_STAGE_H

#include <vector>
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "sl/Library/SmartPointer/WeakPtr/slWeakPtr.h"
#include "../../paIObjectBase.h"

namespace pa
{

class Player;
class BasePoint;
class IStageObjManager;


//===================================================================================//
//!< ステージクラス
//!< ステージ関連を管理するクラス
//===================================================================================//
class Stage final : public IObjectBase
{

public:
	/** 
	* Constructor 
	* @param[in] pPlayer Playerクラスのインスタンスへのシェアードポインタ
	*/
	explicit Stage(const sl::SharedPtr<Player>& pPlayer);

	/** Destructor */
	virtual ~Stage();

	/** 初期化関数 */
	virtual void Initialize()override;

	/** 更新関数 */
	virtual void Update()override;

	/** 破棄関数 */
	virtual void Finalize()override;

private:
	sl::WeakPtr<Player>													m_pPlayer;					//!< Playerクラスのインスタンスへのウィークポインタ
	sl::UniquePtr<BasePoint>											m_pBasePoint;				//!< BasePointクラスのインスタンスへのユニークポインタ
	std::vector <sl::UniquePtr<IStageObjManager
							, sl::DefaultDeleter<IStageObjManager>>>	m_pIStageObjManager;		//!< IStageObjManagerクラスのインスタンスへのユニークポインタ

};	// class Stage

}	// namespace pa

#endif // PA_STAGE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
