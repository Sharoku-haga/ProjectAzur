//==================================================================================================================================//
//!< @file		paFishCreator.h
//!< @brief		pa::FishCreatorクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/23	更新履歴：2018/01/01
//==================================================================================================================================//

#ifndef PA_FISH_CREATOR_H
#define PA_FISH_CREATOR_H

#include <D3DX11.h>
#include <D3DX10.h>
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "../paFish.h"

namespace pa
{

class FishShapeCreator;

class FishCreator final
{

public:
	/** 
	* Constructor
	* @param[in] rIDs					描画のID群
	* @param[in] pResrcDataFilePath		リソースデータのファイルパス
	*/
	FishCreator(const sl::DrawingID&	rIDs
				, const char*	pResrcDataFilePath);

	/** Destructor */
	~FishCreator();

	/** 初期化関数 */
	void Initialize();

	/** 
	* 魚を生成する関数 
	* @param[in] rPos 位置座標
	*/
	sl::UniquePtr<Fish> CreateFish(const D3DXVECTOR2& rPos);

private:
	sl::UniquePtr<FishShapeCreator,
		sl::DefaultDeleter<FishShapeCreator>>			m_pShapeCreator;		// 魚の形状を生成するクラス
	sl::DrawingID										m_DrawingID;			//!< 基本形状の描画ID
	const char*											m_pResrcDataFilePath;	//!< リソースデータファイルへのパス

};	// class FishCreator

}	// namespace pa

#endif

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
