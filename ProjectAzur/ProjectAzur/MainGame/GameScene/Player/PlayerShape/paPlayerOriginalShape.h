//==================================================================================================================================//
//!< @file		paPlayerOriginalShape.h
//!< @brief		pa::PlayerOriginalShapeクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/21	更新履歴：
//==================================================================================================================================//

#ifndef PA_PLAYER_ORIGINAL_SHAPE_H
#define PA_PLAYER_ORIGINAL_SHAPE_H

#include <string>
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "sl/Library/Utility/slRect.h"
#include "../../../paObjDrawingData.h"
#include "../paPlayerCommonDeclaration.h"

namespace pa
{

//===================================================================================//
//!< プレイヤーのオリジナルの形状クラス
//===================================================================================//
class PlayerOriginalShape final
{

public:
	/** Constructor */
	PlayerOriginalShape();

	/** Destrutor */
	~PlayerOriginalShape();

	/**
	* 初期化関数
	* @param[in] rIDs					描画のID群
	* @param[in] rResrcDataFilePath		リソースデータのファイルパス
	* @param[in] rParam					プレイヤーのパラメータ
	*/
	void Initialize(const sl::DrawingID&	rIDs
					, const std::string&	rResrcDataFilePath
					, const PlayerParam&	rParam);

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

	/** 破棄関数 */
	void Finalize();

	/**
	* 形状が透明(ゲーム中の表現は半透明)かどうか
	* @attention この透明という状態は初期形状のみの状態である
	* @retrun true→ 透明である false→透明でない
	*/
	bool IsInvisible();

	/**
	* Getter
	* @return 現在の矩形
	*/
	inline const sl::fRect& GetRectSize()
	{
		return m_RectSize;
	}

private:
	sl::DX11GraphicsLibrary&			m_rLibrary;				//!< グラフィックスライブラリのインスタンスへの参照
	sl::UniquePtr<ObjDrawingData>		m_pDrawingData;			//!< 描画する為のデータ
	sl::DrawingID						m_InitialShapeID;		//!< プレイヤーの初期形状の描画ID
	sl::fRect							m_RectSize;				//!< 矩形サイズ
	bool								m_IsFacingRight;		//!< 右を向いているかどうか true→ 右を向いている false→向いていない
	bool								m_IsInvisible;			//!< 透明(ゲーム中の表現は半透明)どうか true→ 透明である false→透明でない

	/** 
	* 画像反転処理を行う関数 
	* @param[in] rParam					プレイヤーのパラメータ
	*/
	void ProcessImageReversal(const PlayerParam&	rParam);

	/**
	* 透明化処理を行う関数
	* 初期形状の場合のみ待機中透明となるため、その処理を行う
	* @param[in] rParam					プレイヤーのパラメータ
	*/
	void ProcessTransparent(const PlayerParam&	rParam);

};	// class PlayerOriginalShape

}	// namespace pa

#endif	// PA_PLAYER_ORIGINAL_SHAPE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
