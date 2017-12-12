//==================================================================================================================================//
//!< @file		paStageBackground.h
//!< @brief		pa::StageBackgroundクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/11	更新履歴：
//==================================================================================================================================//

#ifndef PA_STAGE_BACKGROUND_H
#define PA_STAGE_BACKGROUND_H

#include <string>
#include <sl/Library/SmartPointer/UniquePtr/slUniquePtr.h>
#include "../paStageObjBase.h"

namespace pa
{

struct ObjDrawingData;

//===================================================================================//
//!< ステージ背景クラス
//===================================================================================//
class StageBackground : public StageObjBase
{

public:
	/** 
	* Constructor
	* @param[in] rResrcDataFilePath 描画のリソースデータファイルのパス
	*/
	explicit StageBackground(const std::string& rResrcDataFilePath);

	/** Destructor */
	virtual ~StageBackground() = default;

	/** 初期化関数 */
	virtual void Initialize()override;

	/** 更新関数 */
	virtual void Update()override;

	/** 破棄関数 */
	virtual void Finalize()override;

private:
	sl::UniquePtr<ObjDrawingData
		, sl::DefaultDeleter<ObjDrawingData>>		m_pDrawingData;				//!< ObjDrawongData構造体のインスタンスへのユニークポインタ
	std::string										m_ResrcDataFilePath;		//!< 描画のリソースデータファイルのパス

	/** 描画関数 */
	void Draw();

};	// class StageBackground

}	// namespace pa

#endif	// PA_STAGE_BACKGROUND_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
