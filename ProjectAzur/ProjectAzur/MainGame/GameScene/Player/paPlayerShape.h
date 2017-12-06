//==================================================================================================================================//
//!< @file		paPlayerShape.h
//!< @brief		pa::PlayerShapeクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/05	更新履歴：2017/12/07
//==================================================================================================================================//

#ifndef PA_PLAYER_SHAPE_H
#define PA_PLAYER_SHAPE_H

#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "sl/Library/Utility/slRect.h"
#include "../../paObjDrawingData.h"
#include "paPlayerCommonDeclaration.h"

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
	/** Constructor */
	PlayerShape();

	/** Destrcutor */
	~PlayerShape() = default;

	/**
	* 初期化関数
	* @param[in] rParam					プレイヤーのパラメータ
	* @param[in] pResrcDataFilePath		リソースデータのファイルパス番号
	* @param[in] rIDs					描画のID群
	*/
	void Initialize(const PlayerParam&	rParam
					, const char*	pResrcDataFilePath
					, const sl::DrawingID&	rIDs);

	/** 
	* 更新関数
	* @param[in] rParam					プレイヤーのパラメータ
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
	* 描画するデータを調整する関数.
	* 主に衝突判定処理後にdデータが変わったらよぶ
	* @param[in] rParam					プレイヤーのパラメータ
	*/
	void AdjustDrawingData(const PlayerParam&	rParam);

	/** 破棄関数 */
	void Finalize();

private:
	sl::DX11GraphicsLibrary&			m_rLibrary;				//!< グラフィックスライブラリのインスタンスへの参照
	sl::UniquePtr<ObjDrawingData>		m_pDrawingData;			//!< 描画する為のデータ
	sl::DrawingID						m_InitialShapeID;		//!< プレイヤーの初期形状の描画ID
	sl::fRect							m_CurrentRectSize;		//!< 現在の矩形サイズ
	bool								m_IsFacingRight;		//!< 右を向いているかどうか

	/** 描画関数 */
	void Draw();

	/** 
	* 画像反転処理を行う関数 
	* @param[in] rParam					プレイヤーのパラメータ
	*/
	void ProcessImageReversal(const PlayerParam&	rParam);

};	// class PlayerShape

}	// namespace pa

#endif	// PA_PLAYER_SHAPE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
