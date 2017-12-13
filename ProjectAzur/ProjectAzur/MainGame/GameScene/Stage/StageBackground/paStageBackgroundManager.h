//==================================================================================================================================//
//!< @file		paStageBackgroundManager.h
//!< @brief		pa::StageBackgroundManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/11	更新履歴：2017/12/13
//==================================================================================================================================//

#ifndef PA_STAGE_BACKGROUND_MANAGER_H
#define PA_STAGE_BACKGROUND_MANAGER_H

#include <string>
#include "sl/Library/Graphics/slGraphicsID.h"
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "../paIStageObjManager.h"

namespace pa
{

class StageBackground;

//===================================================================================//
//!< StageBackgroundクラス関連を管理するクラス
//===================================================================================//
class StageBackgroundManager : public IStageObjManager
{

public:
	/** 
	* Constructor 
	* @param[in] rIDs				描画ID群
	* @param[in] rResrcDataFilePath 描画のリソースデータファイルのパス
	*/
	explicit StageBackgroundManager(const sl::DrawingID& rIDs
									, const std::string& rResrcDataFilePath);

	/** Destructor */
	virtual ~StageBackgroundManager();

	/** 初期関数 */
	virtual void Initialize()override;

	/** 更新関数 */
	virtual void Update()override;

	/** 破棄関数 */
	virtual void Finalize()override;

private:
	sl::UniquePtr<StageBackground
		, sl::DefaultDeleter<StageBackground>>			m_pBackground;			//!< StageBackgroundクラスのインスタンスへのユニークポインタ
	sl::DrawingID										m_DrawingID;			//!< 描画データID
	std::string											m_ResrcDataFilePath;	//!< 描画のリソースデータファイルのパス

};	// class StageBackgroundManager

}	// namespace pa

#endif	// PA_STAGE_BACKGROUND_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
