//==================================================================================================================================//
//!< @file		paStage.h		
//!< @brief		pa::Stageクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/09	更新履歴：2017/12/13
//==================================================================================================================================//

#ifndef PA_STAGE_H
#define PA_STAGE_H

#include <vector>
#include <string>
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "sl/Library/SmartPointer/WeakPtr/slWeakPtr.h"
#include "sl/Library/Graphics/slGraphicsID.h"
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
	* @param[in] rIDs					描画データID群
	* @param[in] rResrcDataFilePath		リソースデータファイルへのﾊﾟｽ
	* @param[in] pPlayer				Playerクラスのインスタンスへのシェアードポインタ
	*/
	Stage(const sl::DrawingID& rIDs
		, const std::string&	rResrcDataFilePath 
		, const sl::WeakPtr<Player>& pPlayer);

	/** Destructor */
	virtual ~Stage();

	/** 初期化関数 */
	virtual void Initialize()override;

	/** 更新関数 */
	virtual void Update()override;

	/** 破棄関数 */
	virtual void Finalize()override;

private:
	sl::DrawingID														m_DrawingID;				//!< 描画IDを格納した構造体
	std::string															m_ResrcDataFilePath;		//!< リソースデータファイルﾊﾟｽ
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
