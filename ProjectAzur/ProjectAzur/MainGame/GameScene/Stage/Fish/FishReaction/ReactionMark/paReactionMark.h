//==================================================================================================================================//
//!< @file		paReactionMark.h
//!< @brief		pa::ReactionMarkクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/22	更新履歴：
//==================================================================================================================================//

#ifndef PA_REACTION_MARK_H
#define PA_REACTION_MARK_H

#include <string>
#include <D3DX11.h>
#include <D3DX10.h>
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "../../paFishParam.h"
#include "../../../../../paObjDrawingData.h"
#include "../../../../../DrawingResrcDataFile/paDrawingResrcDataFile.h"

namespace pa
{

//===================================================================================//
//!< 魚のリアクションのマークのクラス
//===================================================================================//
class ReactionMark
{

public:
	/** Constructor */
	ReactionMark(const sl::DrawingID& rIDs
				, const DrawingResrcData& rResrc
				, const std::string& rMarkName);

	/** Destructor */
	~ReactionMark();

	/**
	* 更新関数 
	* @param[in] rParam 魚のパラメータ
	*/
	void Update(const FishParam& rParam);

	/**
	* 描画関数
	* @param[in] rBasePointPos ベースポイントの座標
	*/
	void Draw(const D3DXVECTOR2& rBasePointPos);

	/** 
	* 描画するデータを調整する関数.
	* 主に衝突判定処理後にデータが変わったらよぶ
	* @param[in] rParam					魚のパラメータ
	*/
	void AdjustDrawingData(const FishParam&	rParam);

	/**
	* Getter
	* @return リアクションマークの名前
	*/
	inline const std::string& GetName() { return m_Name; }

private:
	sl::DX11GraphicsLibrary&			m_rLibrary;				//!< グラフィックスライブラリのインスタンスへの参照
	sl::UniquePtr<ObjDrawingData>		m_pDrawingData;			//!< 描画データのユニークポインタ
	std::string							m_Name;					//!< リアクションマークの名前
	bool								m_IsFacingRight;		//!< 右を向いているかどうか true→ 右を向いている false→向いていない

	/** 画像反転処理を行う関数 */
	void ProcessImageReversal();

};	// class ReactionMark

}	// namespace pa

#endif	// PA_REACTION_MARK_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
