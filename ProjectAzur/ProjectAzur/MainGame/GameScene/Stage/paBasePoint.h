//==================================================================================================================================//
//!< @file		paBasePoint.h
//!< @brief		pa::BasePointクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/09	更新履歴：
//==================================================================================================================================//

#ifndef PA_BASE_POINT_H
#define PA_BASE_POINT_H

#include <D3DX10.h>
#include "sl/Library/Utility/slDefine.h"
#include "sl/Library/Utility/slRect.h"
#include "sl/Library/SmartPointer/slSmartPointer.h"

namespace pa
{

class EventListener;
class Player;

//===================================================================================//
//!< ステージ関連オブジェクトの移動の際にベースとなるポイント(座標)を持つクラス
//===================================================================================//
class BasePoint final
{

public:
	/** 
	* Constructor
	* @param[in] pPlayer		Playerクラスのインスタンスへのポインタ
	* @param[in] stageSize		ステージのサイズを格納したRect構造体
	*/
	BasePoint(sl::WeakPtr<Player> pPlayer, const sl::fRect& stageSize);

	/** Destructor */
	~BasePoint() = default;

	/** 初期化関数 */
	void Initialize();

private:
	/** プレイヤーの追跡を行う間隔 */
	struct PlayerTrackingInterval
	{
		float	m_WidthInterval;			//!< 横の間隔
		float	m_HeightInterval;			//!< 縦の間隔
	};	// struct PlayerTrackingInterval

	D3DXVECTOR2							m_Pos;					//!< 位置座標
	D3DXVECTOR2							m_OldPlayerPos;			//!< プレイヤーの前の位置座標
	sl::fRect							m_StageSize;			//!< ステージサイズを格納したRect構造体
	PlayerTrackingInterval				m_TrackingInterval;		//!< プレイヤーとの追跡間隔
	sl::WeakPtr<Player>					m_pPlayer;				//!< Playerクラスのインスタンスのウィークポインタ
	sl::SharedPtr<EventListener>		m_pEventListener;		//!< EventListenerクラスのインスタンスへのポインタ

	SL_DISALLOW_COPY_AND_ASSIGN(BasePoint);

	/** 
	* 移動関数
	* プレイヤーが動いたときだけ呼ばれる関数
	*/
	void Move();

	/** 
	* 横に移動する関数 
	* @param[in]	rCurrnetPlayerPos	現在のプレイヤーの座標
	*/
	void MoveHorizontally(const D3DXVECTOR2& rCurrnetPlayerPos);
	
	/** 
	* 縦に移動する関数 
	* @param[in]	rCurrnetPlayerPos	現在のプレイヤーの座標
	*/
	void MoveVertically(const D3DXVECTOR2& rCurrnetPlayerPos);

};	// class BasePoint

}	// namespace pa

#endif	// PA_BASE_POINT_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
