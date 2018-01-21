//==================================================================================================================================//
//!< @file		paPlayerShape.h
//!< @brief		pa::PlayerShapeクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/05	更新履歴：2017/12/16
//==================================================================================================================================//

#ifndef PA_PLAYER_SHAPE_H
#define PA_PLAYER_SHAPE_H

#include <string>
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "sl/Library/Utility/slRect.h"
#include "../../../DrawTask/paDrawTask.h"
#include "../../../paObjDrawingData.h"
#include "../paPlayerCommonDeclaration.h"
#include "paPlayerOriginalShape.h"
#include "paPlayerFishShell.h"

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
	* @param[in] rResrcDataFilePath		リソースデータのファイルパス
	*/
	PlayerShape(const sl::DrawingID&	rIDs
				, const std::string&	rResrcDataFilePath);

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
	* @param[in] pFishDrawingData	魚の描画データのポインタ
	*/
	void ChangeShape(ObjDrawingData* pFishDrawingData);

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
	bool IsInvisible();

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
	sl::fRect							m_CurrentRectSize;		//!< 現在の矩形サイズ
	D3DXVECTOR2							m_BasePointPos;			//!< ベースポイントの座標
	sl::DrawingID						m_IDs;					//!< 描画ID群
	std::string							m_ResrcDataFilePath;	//!< リソースデータファイルへのパス
	sl::UniquePtr<DrawTask>				m_pTask;				//!< 描画タスクのユニークポインタ
	sl::UniquePtr<PlayerFishShell>		m_pFishShell;			//!< PlayerFishShell(魚の殻)クラスのインスタンスへのポインタ
	sl::UniquePtr<PlayerOriginalShape>	m_pOriginalShape;		//!< PlayerOriginalShape(基本形状)クラスのインスタンスへのポインタ

	/** 描画関数 */
	void Draw();

};	// class PlayerShape

}	// namespace pa

#endif	// PA_PLAYER_SHAPE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
