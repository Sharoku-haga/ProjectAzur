//==================================================================================================================================//
//!< @file		paReactionMark.h
//!< @brief		pa::ReactionMarkクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/22	更新履歴：2018/01/23
//==================================================================================================================================//

#ifndef PA_REACTION_MARK_H
#define PA_REACTION_MARK_H

#include <string>
#include <D3DX11.h>
#include <D3DX10.h>
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "../../paFishCommonDeclaration.h"
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
	/** 
	* Constructor
	* @param[in] rIDs		描画ID
	* @param[in] rResrc		リソースデータ
	* @param[in] rMarkType	リアクションマークの種類
	*/
	ReactionMark(const sl::DrawingID& rIDs
				, const DrawingResrcData& rResrc
				, const REACTION_MARK_TYPE& rMarkType);

	/** Destructor */
	~ReactionMark();

	/**
	* 更新関数 
	* @param[in] rParam 魚のパラメータ
	*/
	void Update(const FishParam& rParam);

	/**
	* 描画関数
	* @param[in] rParam			魚のパラメータ
	* @param[in] rBasePointPos	ベースポイントの座標
	*/
	void Draw(const FishParam& rParam, const D3DXVECTOR2& rBasePointPos);

	/**
	* Getter
	* @return リアクションマークの種類
	*/
	inline const REACTION_MARK_TYPE& GetMarkType() { return m_MarkType; }

private:
	sl::DX11GraphicsLibrary&			m_rLibrary;				//!< グラフィックスライブラリのインスタンスへの参照
	sl::UniquePtr<ObjDrawingData>		m_pDrawingData;			//!< 描画データのユニークポインタ
	REACTION_MARK_TYPE					m_MarkType;				//!< リアクションマークの種類
	bool								m_IsFacingRight;		//!< 右を向いているかどうか true→ 右を向いている false→向いていない

	/** 画像反転処理を行う関数 */
	void ProcessImageReversal();

};	// class ReactionMark

}	// namespace pa

#endif	// PA_REACTION_MARK_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
