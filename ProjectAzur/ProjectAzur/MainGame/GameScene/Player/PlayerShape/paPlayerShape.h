//==================================================================================================================================//
//!< @file		paPlayerShape.h
//!< @brief		pa::PlayerShapeクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/05	更新履歴：2017/12/16
//==================================================================================================================================//

#ifndef PA_PLAYER_SHAPE_H
#define PA_PLAYER_SHAPE_H

#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "sl/Library/Utility/slRect.h"
#include "../../../paObjDrawingData.h"
#include "../paPlayerCommonDeclaration.h"

namespace sl
{

class DX11GraphicsLibrary;

}

namespace pa
{

//===================================================================================//
//!< プレイヤーの形状(描画する形)のクラス
//===================================================================================//
class PlayerShape final
{

public:
	/** 
	* Constructor
	* @param[in] rIDs					描画のID群
	* @param[in] pResrcDataFilePath		リソースデータのファイルパス
	*/
	PlayerShape(const sl::DrawingID&	rIDs
				, const char*	pResrcDataFilePath);

	/** Destrcutor */
	~PlayerShape() = default;

	/**
	* 初期化関数
	* @param[in] rParam			プレイヤーのパラメータ
	*/
	void Initialize(const PlayerParam&	rParam);

	/** 
	* 更新関数
	* @param[in] rParam			プレイヤーのパラメータ
	*/
	void Update(const PlayerParam&	rParam);

	/** 
	* 描画する形状を変える関数
	* @param[in] rIDs		変えたい形状の描画のID群
	*/
	void ChangeShape(const sl::DrawingID&	rIDs);

	/** 初期の形状に変える関数 */
	void ChangeInitialShape();

	/**
	* 形状のサイズを知らせてくれる関数   
	* @return サイズ 
	*/
	const sl::fRect& InformShapeSize();

	/**
	* 形状が透明(ゲーム中の表現は半透明)かどうか
	* @attention この透明という状態は初期形状のみの状態である
	* @retrun true→ 透明である false→透明でない
	*/
	bool IsInvisible() { return m_IsInvisible; }

	/** 
	* 描画するデータを調整する関数.
	* 主に衝突判定処理後にデータが変わったらよぶ
	* @param[in] rParam					プレイヤーのパラメータ
	*/
	void AdjustDrawingData(const PlayerParam&	rParam);

	/** 破棄関数 */
	void Finalize();

	/**
	* Setter
	* @param[in] rBasePointPos ベースポイントの座標
	*/
	inline void SetBasePointPos(const D3DXVECTOR2& rBasePointPos)
	{ 
		m_BasePointPos = rBasePointPos; 
	}

private:
	sl::DX11GraphicsLibrary&			m_rLibrary;				//!< グラフィックスライブラリのインスタンスへの参照
	sl::UniquePtr<ObjDrawingData>		m_pDrawingData;			//!< 描画する為のデータ
	sl::DrawingID						m_InitialShapeID;		//!< プレイヤーの初期形状の描画ID
	sl::fRect							m_CurrentRectSize;		//!< 現在の矩形サイズ
	D3DXVECTOR2							m_BasePointPos;			//!< ベースポイントの座標
	const char*							m_pResrcDataFilePath;	//!< リソースデータファイルへのパス
	bool								m_IsInvisible;			//!< 透明(ゲーム中の表現は半透明)どうか true→ 透明である false→透明でない
	bool								m_IsFacingRight;		//!< 右を向いているかどうか true→ 右を向いている false→向いていない

	/** 描画関数 */
	void Draw();

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

};	// class PlayerShape

}	// namespace pa

#endif	// PA_PLAYER_SHAPE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
