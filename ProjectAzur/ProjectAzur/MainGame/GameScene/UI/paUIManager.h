//==================================================================================================================================//
//!< @file		paUIManager.h
//!< @brief		pa::UIManagerクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/17	更新履歴：2017/12/18
//==================================================================================================================================//

#ifndef PA_UI_MANAGER_H
#define PA_UI_MANAGER_H

#include <vector>
#include <string>
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "sl/Library/Graphics/slGraphicsID.h"
#include "../../paIObjectBase.h"

namespace pa
{

class IUI;

//===================================================================================//
//!< IUIクラスを管理するクラス
//===================================================================================//
class UIManager final : public IObjectBase
{

public:
	/** Constructor */
	UIManager(const sl::DrawingID& rIDs
			, const std::string&	rResrcDataFilePath);

	/** Destructor */
	virtual ~UIManager();

	/** 初期化関数 */
	virtual void Initialize()override;

	/** 更新関数 */
	virtual void Update()override;

	/** 破棄関数 */
	virtual void Finalize()override;

private:
	sl::DrawingID														m_DrawingID;				//!< 描画IDを格納した構造体
	std::string															m_ResrcDataFilePath;		//!< リソースデータファイルﾊﾟｽ
	std::vector<sl::UniquePtr<IUI, sl::DefaultDeleter<IUI>>>			m_pUI;						//!< IUIインターフェースのインスタンスへのポインタ

};	// class UIManager

}	// namespace pa

#endif	// PA_UI_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
