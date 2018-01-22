//==================================================================================================================================//
//!< @file		paPlayerFishShapeLine.h		
//!< @brief		pa::PlayerFishShapeLineクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/22	更新履歴：
//==================================================================================================================================//

#ifndef PA_PLAYER_FISH_SHAPE_LINE_H
#define PA_PLAYER_FISH_SHAPE_LINE_H

#include <string>
#include <D3DX11.h>
#include <D3DX10.h>
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "sl/Library/Utility/slRect.h"
#include "../paPlayerCommonDeclaration.h"
#include "../../../paObjDrawingData.h"

namespace pa
{

//===================================================================================//
//!< プレイヤーが操る魚の周りを囲む線のクラス
//===================================================================================//
class PlayerFishShapeLine
{

public:
	/** 
	* Constructor
	* @param[in] rIDs					描画のID群
	* @param[in] rResrcDataFilePath		リソースデータのファイルパス
	*/
	PlayerFishShapeLine(const sl::DrawingID&	rIDs
						, const std::string&	rResrcDataFilePath);

	/** Destructor */
	~PlayerFishShapeLine();

	/**
	* ステータスを変更する関数
	* @param[in] rRectSize
	*/
	void ChangeStatus(const sl::fRect& rRectSize);

	/** 
	* 更新関数
	* @param[in] rParam			プレイヤーのパラメータ
	*/
	void Update(const PlayerParam&	rParam);

	/** 
	* 描画するデータを調整する関数.
	* 主に衝突判定処理後にデータが変わったらよぶ
	* @param[in] rParam					プレイヤーのパラメータ
	*/
	void AdjustDrawingData(const PlayerParam&	rParam);

	/** 
	* 描画関数 
	* @param[in] rBasePointPos ベースポイント座標
	*/
	void Draw(const D3DXVECTOR2&	rBasePointPos);

private:
	sl::DX11GraphicsLibrary&			m_rLibrary;				//!< グラフィックスライブラリのインスタンスへの参照
	sl::UniquePtr<ObjDrawingData>		m_pDrawingData;			//!< 描画する為のデータ
	bool								m_IsFacingRight;		//!< 右を向いているかどうか true→ 右を向いている false→向いていない

	/** 画像反転処理を行う関数 */
	void ProcessImageReversal();

};	// class PlayerFishShapeLine

}	// namespace pa

#endif	// PA_PLAYER_FISH_SHAPE_LINE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
