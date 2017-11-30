//==================================================================================================================================//
//!< @file		paTitleBackground.h
//!< @brief		pa::TitleBackgroundクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/30	更新履歴：2017/12/02
//==================================================================================================================================//

#ifndef PA_TITLE_BACKGROUND_H
#define PA_TITLE_BACKGROUND_H

#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "sl/Library/Graphics/slGraphicsID.h"
#include "../../paIObjectBase.h"
#include "../../paObjDrawingData.h"
#include "paTitleBackgroundAnime.h"

namespace pa
{

//===================================================================================//
//!< タイトルの背景クラス
//===================================================================================//
class TitleBackground final : public IObjectBase 
{

public:
	/** 
	* Constructor 
	* @param[in] rID 描画に必要なID
	*/
	explicit TitleBackground(const sl::DrawingID& rID);

	/** Destructor */
	virtual ~TitleBackground();

	/** 初期化関数 */
	virtual void Initialize()override;

	/** 更新関数 */
	virtual void Update()override;

	/** 破棄関数 */
	virtual void Finalize()override;

private:
	sl::UniquePtr<ObjDrawingData>				m_pDrawingData;			//!< ObjDrawingDataクラスのインスタンスへのポインタ 
	sl::UniquePtr<TitleBackgroundAnime>			m_pBackgroundAnime;		//!< TitleBackgroundAnimeクラスのインスタンスへのポインタ

	/** 描画関数 */
	void Draw();

};	// class TitleBackground

}	// namespace pa

#endif	// PA_TITLE_BACKGROUND_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
