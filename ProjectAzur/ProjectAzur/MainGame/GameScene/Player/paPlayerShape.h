//==================================================================================================================================//
//!< @file		paPlayerShape.h
//!< @brief		pa::PlayerShapeクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/05	更新履歴：
//==================================================================================================================================//

#ifndef PA_PLAYER_SHAPE_H
#define PA_PLAYER_SHAPE_H

#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "sl/Library/Utility/slRect.h"
#include "../../paObjDrawingData.h"

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
	* @param[in] rInitialPosrPos		初期座標
	* @param[in] initialAngle			初期角度
	* @param[in] pResrcDataFilePath		リソースデータのファイルパス番号
	* @param[in] rIDs					描画のID群
	*/
	void Initialize(const D3DXVECTOR2& rInitialPos
					, float initialAngle
					, const char*	pResrcDataFilePath
					, const sl::DrawingID&	rIDs);

	/** 
	* 更新関数
	* @param[in] rPos	位置座標
	* @param[in] angle	角度
	*/
	void Update(const D3DXVECTOR2& rPos, float angle);

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
	sl::fRect InformShapeSize();

	/** 破棄関数 */
	void Finalize();

private:
	sl::DX11GraphicsLibrary&			m_rLibrary;				//!< グラフィックスライブラリのインスタンスへの参照
	sl::UniquePtr<ObjDrawingData>		m_pDrawingData;			//!< 描画する為のデータ
	sl::DrawingID						m_InitialShapeID;		//!< プレイヤーの初期形状の描画ID
	
	/** 描画関数 */
	void Draw();

};	// class PlayerShape

}	// namespace pa

#endif	// PA_PLAYER_SHAPE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
