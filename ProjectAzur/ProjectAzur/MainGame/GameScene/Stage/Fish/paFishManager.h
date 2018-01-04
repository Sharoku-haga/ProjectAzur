//==================================================================================================================================//
//!< @file		paFishManager.h
//!< @brief		pa::FishManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/23	更新履歴：2018/01/04
//==================================================================================================================================//

#ifndef PA_FISH_MANAGER_H
#define PA_FISH_MANAGER_H

#include <vector>
#include <string>
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "sl/Library/Graphics/slGraphicsID.h"
#include "../paIStageObjManager.h"

namespace pa
{

class FishCreator;
class Fish;

//===================================================================================//
//!< Fishクラスを管理するクラス
//===================================================================================//
class FishManager final : public IStageObjManager
{

public:
	/** 
	* Constructor
	* @param[in] rIDs					描画のID群
	* @param[in] rResrcDataFilePath		リソースデータのファイルパス
	*/
	FishManager(const sl::DrawingID&	rIDs
				, const std::string&	rResrcDataFilePath);

	/** Destructor */
	virtual ~FishManager();

	/** 初期関数 */
	virtual void Initialize()override;

	/** 更新関数 */
	virtual void Update()override;

	/** 破棄関数 */
	virtual void Finalize()override;

private:
	sl::UniquePtr<FishCreator
		, sl::DefaultDeleter<FishCreator>>	m_pCreator;				//!< FishCreatorクラスのインスタンスへのユニークポインタ
	std::vector<sl::UniquePtr<Fish
		, sl::DefaultDeleter<Fish>>>		m_pFishes;				//!< Fishクラスのインスタンスへのユニークポインタの動的配列
	sl::DrawingID							m_DrawingID;			//!< 基本形状の描画ID
	std::string								m_ResrcDataFilePath;	//!< リソースデータファイルへのパス

};	// class FishManager

}	// namespace pa

#endif	// PA_FISH_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
