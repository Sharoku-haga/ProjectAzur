//==================================================================================================================================//
//!< @file		paBasePoint.cpp
//!< @brief		pa::BasePointクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/09	更新履歴：2017/12/16
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "paBasePoint.h"
#include "../../EventManager/paEventListener.h"
#include "../../EventManager/paEventManager.h"
#include "../Player/paPlayer.h"
#include "paStageObjBase.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

BasePoint::BasePoint(sl::WeakPtr<Player> pPlayer, const sl::fRect& stageSize)
	: m_Pos({0.0f, 0.0f})
	, m_OldPlayerPos({0.0f, 0.0f})
	, m_StageSize(stageSize)
	, m_pPlayer(pPlayer)
	, m_pEventListener(new EventListener())
{}

void BasePoint::Initialize()
{	
	// 同期イベントの登録
	m_pEventListener->RegisterSynEventFunc("player_move", std::bind(&pa::BasePoint::Move, this));
	EventManager::Instance().RegisterEventListener("player_move", m_pEventListener);

	// 追跡間隔の設定
	sl::fRect buckBufferSize = sl::DX11GraphicsLibrary::Instance().GetBackBufferSize();
	m_TrackingInterval.m_WidthInterval = (buckBufferSize.m_Right - buckBufferSize.m_Left) / 2;
	m_TrackingInterval.m_HeightInterval = (buckBufferSize.m_Bottom - buckBufferSize.m_Top) / 2;

	// 初期位置へ移動する
	Move();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void BasePoint::Move()
{
	if(m_pPlayer.IsExpired())
	{	// Playerクラスのインスタンスポインタが
		// 無効ならば即Return
		return;
	}
	sl::SharedPtr<Player> pPlayer = m_pPlayer.Lock();
	const D3DXVECTOR2& rCurrnetPlayerPos = pPlayer->GetPos();

	/** @todo 縦移動も横移動も基本的なアルゴリズムは一緒なので、まとめてみるのあり */
	MoveHorizontally(rCurrnetPlayerPos);
	MoveVertically(rCurrnetPlayerPos);

	// StageObjBaseのベースポイントの座標を更新する 
	StageObjBase::SetBasePointPos(m_Pos);

	// プレイヤーの保持しているベースポイントの座標も更新する
	pPlayer->SetBasePointPos(m_Pos);

	// プレイヤーの座標を更新する
	m_OldPlayerPos = rCurrnetPlayerPos;
}

void BasePoint::MoveHorizontally(const D3DXVECTOR2& rCurrnetPlayerPos)
{
	if(rCurrnetPlayerPos.x < (m_StageSize.m_Left + m_TrackingInterval.m_WidthInterval))
	{	// 左端付近処理
		if(m_Pos.x > m_StageSize.m_Left)
		{
			m_Pos.x = m_StageSize.m_Left;
		}
		return;
	}
	else if	(rCurrnetPlayerPos.x > (m_StageSize.m_Right - m_TrackingInterval.m_WidthInterval))
	{	// 右端付近処理
		if(m_Pos.x <  (m_StageSize.m_Right - (m_TrackingInterval.m_WidthInterval * 2)))
		{
			m_Pos.x = (m_StageSize.m_Right - (m_TrackingInterval.m_WidthInterval * 2));
		}
		return;
	}

	// プレイヤーと離れている分移動する
	m_Pos.x += (rCurrnetPlayerPos.x - m_OldPlayerPos.x);

	// プレイヤーとの間が追跡間隔より離れすぎていたら調整する
	if((rCurrnetPlayerPos.x - m_Pos.x) >  m_TrackingInterval.m_WidthInterval)
	{	
		m_Pos.x += ((rCurrnetPlayerPos.x - m_Pos.x) - m_TrackingInterval.m_WidthInterval);
	}
	else if((rCurrnetPlayerPos.x - m_Pos.x) <  m_TrackingInterval.m_WidthInterval)
	{	
		m_Pos.x -= (m_TrackingInterval.m_WidthInterval - (rCurrnetPlayerPos.x - m_Pos.x));
	}
}

void BasePoint::MoveVertically(const D3DXVECTOR2& rCurrnetPlayerPos)
{
	if(rCurrnetPlayerPos.y < (m_StageSize.m_Top + m_TrackingInterval.m_HeightInterval))
	{	// 上端付近処理
		if(m_Pos.y > m_StageSize.m_Top)
		{
			m_Pos.y = m_StageSize.m_Top;
		}
		return;
	}
	else if	(rCurrnetPlayerPos.y > (m_StageSize.m_Bottom - m_TrackingInterval.m_HeightInterval))
	{	// 下端付近処理
		if(m_Pos.y <  (m_StageSize.m_Bottom - (m_TrackingInterval.m_HeightInterval * 2)))
		{
			m_Pos.y = (m_StageSize.m_Bottom - (m_TrackingInterval.m_HeightInterval * 2));
		}
		return;
	}

	// プレイヤーと離れている分移動する
	m_Pos.y += (rCurrnetPlayerPos.y - m_OldPlayerPos.y);

	// プレイヤーとの間が追跡間隔より離れすぎていたら調整する
	if((rCurrnetPlayerPos.y - m_Pos.y) >  m_TrackingInterval.m_HeightInterval)
	{
		m_Pos.y += ((rCurrnetPlayerPos.y - m_Pos.y) - m_TrackingInterval.m_HeightInterval);
	}
	else if((rCurrnetPlayerPos.y - m_Pos.y) <  m_TrackingInterval.m_HeightInterval)
	{	
		m_Pos.y -= (m_TrackingInterval.m_HeightInterval - (rCurrnetPlayerPos.y - m_Pos.y));
	}
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
