//==================================================================================================================================//
//!< @file		paReactionMarkManager.cpp		
//!< @brief		pa::ReactionMarkManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2018/01/22	更新履歴：2018/01/23
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "paReactionMarkManager.h"
#include "paReactionMarkFactory.h"

namespace pa
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const int	DispTime = 80;				//!< 表示時間

}

/* Public Functions ------------------------------------------------------------------------------------------- */

ReactionMarkManager::ReactionMarkManager()
	: m_CurrentMarkOrderIndex(0)
	, m_PrevReactionMarkFlag(0)
	, m_DispTimeCount(0)
{}

ReactionMarkManager::~ReactionMarkManager()
{}

void ReactionMarkManager::Initialize(const FishParam& rParam)
{
	UpdateMark(rParam);
	m_pDisplayingMark.Reset(nullptr);
}

void ReactionMarkManager::Update(const FishParam& rParam)
{
	if(m_PrevReactionMarkFlag != rParam.m_ReactionMarkFlag)
	{
		UpdateMark(rParam);
		/** @todo ここに現在表示しているマークが適切かどうかの処理をいれるべきか検討 */
	}

	++m_DispTimeCount;

	if(m_DispTimeCount == DispTime)
	{
		ChangeDispMark();
		m_DispTimeCount = 0;
	}

	if(m_pDisplayingMark.Get() == nullptr)
	{
		return;
	}

	m_pDisplayingMark->Update(rParam);
}

void ReactionMarkManager::Draw(const FishParam& rParam, const D3DXVECTOR2& rBasePointPos)
{
	if(m_pDisplayingMark.Get() == nullptr)
	{
		return;
	}

	m_pDisplayingMark->Draw(rParam, rBasePointPos);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void ReactionMarkManager::ChangeDispMark()
{
	if(m_DispMarks.size() == 0)
	{
		return;
	}

	++m_CurrentMarkOrderIndex;

	if(m_DispMarks.size() == 1)
	{
		if(m_pDisplayingMark.Get() == nullptr)
		{
			m_CurrentMarkOrderIndex = 0;
			m_pDisplayingMark = ReactionMarkFactory::Instance().GetMarkPointer(m_DispMarks[m_CurrentMarkOrderIndex]);
			return;
		}

		m_pDisplayingMark.Reset(nullptr);
		return;
	}

	if(m_CurrentMarkOrderIndex == m_DispMarks.size())
	{
		m_CurrentMarkOrderIndex = 0;
		m_pDisplayingMark = ReactionMarkFactory::Instance().GetMarkPointer(m_DispMarks[m_CurrentMarkOrderIndex]);
		return;
	}

	m_pDisplayingMark = ReactionMarkFactory::Instance().GetMarkPointer(m_DispMarks[m_CurrentMarkOrderIndex]);
}

void ReactionMarkManager::UpdateMark(const FishParam& rParam)
{
	ReactionMarkFactory::Instance().CreateReactionMarks( rParam.m_ReactionMarkFlag, m_DispMarks);
	m_PrevReactionMarkFlag = rParam.m_ReactionMarkFlag;
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
