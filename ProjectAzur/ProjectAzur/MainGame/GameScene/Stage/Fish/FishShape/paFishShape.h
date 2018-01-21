//==================================================================================================================================//
//!< @file		paFishShape.h
//!< @brief		pa::FishShapeクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/23	更新履歴：2017/12/26
//==================================================================================================================================//

#ifndef PA_FISH_SHAPE_H
#define PA_FISH_SHAPE_H

#include <vector>
#include <D3DX11.h>
#include <D3DX10.h>
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "sl/Library/SmartPointer/SharedPtr/slSharedPtr.h"
#include "../paFishParam.h"
#include "../../../../paObjDrawingData.h"

namespace pa
{

//===================================================================================//
//!< 魚の形状を管理するクラス
//===================================================================================//
class FishShape final
{

public:
	/** 
	* Constructor
	* @param[in] rIDs					描画のID群
	* @param[in] rModelIDs				モデルIDを格納したvector
	* @param[in] rUVAnimeIDs			UVアニメIDを格納したvector
	*/
	FishShape(const sl::DrawingID&	rIDs
			, std::vector<sl::ModelID>&	rModelIDs
			, std::vector<sl::UVAnimeID>&	rUVAnimeIDs);

	/** Destructor */
	~FishShape();

	/**
	* 初期化関数
 	* @param[in] rParam	パラメータ
	*/
	void Initialize(const FishParam& rParam);

	/**
	* 更新関数
	* @param[in] rParam パラメータ
	*/
	void Update(const FishParam& rParam);

	/** 破棄関数 */
	void Finalize();

	/**
	* Getter 
	* @return 形状のサイズ 
	*/
	const sl::fRect& GetCurrentRectSize();


	/**
	* Getter
	* @return 描画する為のデータ
	*/
	sl::SharedPtr<ObjDrawingData> GetpDrawingData()
	{
		return m_pDrawingData;
	}

	/**
	* 右を向いているかどうか確認する関数
	* @return ture→右を向いている false→右を向いていない
	*/
	bool IsFacingRight()
	{
		return m_IsFacingRight;
	}

	/** 
	* 描画するデータを調整する関数.
	* 主に衝突判定処理後にデータが変わったらよぶ
	* @param[in] rParam		プレイヤーのパラメータ
	*/
	void AdjustDrawingData(const FishParam& rParam);

	/** 描画関数 */
	void Draw();

private:
	sl::DX11GraphicsLibrary&			m_rLibrary;				//!< グラフィックスライブラリのインスタンスへの参照
	sl::SharedPtr<ObjDrawingData>		m_pDrawingData;			//!< 描画する為のデータ
	std::vector<sl::ModelID>			m_ModelIDs;				//!< モデルIDの動的配列(vector)
	std::vector<sl::UVAnimeID>			m_UVAnimeIDs;			//!< UVアニメIDの動的配列(vector)
	sl::fRect							m_CurrentRectSize;		//!< 現在の矩形サイズ
	bool								m_IsFacingRight;		//!< 右を向いているかどうか true→ 右を向いている false→向いていない
	
	/** 
	* 画像反転処理を行う関数 
	* @param[in] rParam					パラメータ
	*/
	void ProcessImageReversal(const FishParam& rParam);

};	// class FishShape

}	// namespace pa

#endif	// PA_FISH_SHAPE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
