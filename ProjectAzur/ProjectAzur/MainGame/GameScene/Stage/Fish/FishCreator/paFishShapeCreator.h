//==================================================================================================================================//
//!< @file		paFishShapeCreator.h
//!< @brief		pa::FishShapeCreatorクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/28	更新履歴：2017/12/29
//==================================================================================================================================//

#ifndef PA_FISH_SHAPE_CREATOR_H
#define PA_FISH_SHAPE_CREATOR_H

#include <vector>
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "../FishShape/paFishShape.h"

namespace pa
{

//===================================================================================//
//!< FishShapeクラスを作成するクラス
//===================================================================================//
class FishShapeCreator
{

public:
	/** 
	* Constructor
	* @param[in] rIDs					描画のID群
	* @param[in] pResrcDataFilePath		リソースデータのファイルパス
	*/
	FishShapeCreator(const sl::DrawingID&	rIDs
					, const char*	pResrcDataFilePath);

	/** Destructor */
	~FishShapeCreator();

	/** 
	* FishShapeクラスを生成する関数 
	* @todo 現在は引数はないが、後に実装する予定
	*/
	sl::UniquePtr<FishShape> CreateFishShape();

private:
	sl::DX11GraphicsLibrary&			m_rLibrary;				//!< グラフィックスライブラリのインスタンスへの参照
	sl::DrawingID						m_BaseShapeID;			//!< 基本形状の描画ID
	const char*							m_pResrcDataFilePath;	//!< リソースデータファイルへのパス

	/**
	* モデルを生成する関数 
	* @todo 後に引数に個性を追加する予定
	* @param[out] rModelIDs 生成したモデルIDを格納する動的配列
	*/
	void CreateModel(std::vector<sl::ModelID>& rModelIDs);

	/**
	* UVアニメを生成する関数 
	* @todo 後に引数に個性を追加する予定
	* @param[out] rUVanimeIDs 生成したUVアニメIDを格納する動的配列
	*/
	void CreateUVAnime(std::vector<sl::UVAnimeID>& rUVAnimeIDs);

};	// class FishShapeCreator

}	// namespace pa

#endif	// PA_FISH_SHAPE_CREATOR_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
