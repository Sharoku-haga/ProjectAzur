//==================================================================================================================================//
//!< @file		slUVAnimationManager.cpp
//!< @brief		sl::UVAnimationManagerクラス実装
//!< @author	T.Haga
//!< @data		作成日時：2017/11/07	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slUVAnimationManager.h"
#include "slUVAnimation.h"
#include "../../../Utility/slTemplateFunction.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

UVAnimationManager::UVAnimationManager()
	: m_IDNumCount(0)
{}

UVAnimationManager::~UVAnimationManager()
{
	ReleaseALL();
}

UVAnimeID UVAnimationManager::CreateAnimatoin(const UVAnimeCreationData& rData)
{
	UVAnimeID id;		// 戻り値のID

	if(m_IDNumCount == INT_MAX)
	{	// IDの値がMAX値なら空いているIDを検索してそこにデータ格納
		id.m_Num = SearchAvailableIDNum();
		m_pAnimation[id.m_Num] = new UVAnimation(rData);
		return id;
	}

	m_pAnimation[m_IDNumCount] = new UVAnimation(rData);
	id.m_Num = m_IDNumCount;
	++m_IDNumCount;

	return id;
}

bool UVAnimationManager::UpdateUVAnime(const UVAnimeID& rID, bool isLoop)
{
	return m_pAnimation[rID.m_Num]->Update(isLoop);
}

void UVAnimationManager::InitUVAnime(const UVAnimeID& rID)
{
	m_pAnimation[rID.m_Num]->Init();
}

bool UVAnimationManager::IsEndUVAnimation(const UVAnimeID& rID)
{
	return m_pAnimation[rID.m_Num]->IsEndAnimation();
}

const fRect& UVAnimationManager::GetCurrentUVData(const UVAnimeID& rID)
{
	return m_pAnimation[rID.m_Num]->GetCurrentUVData();
}

void UVAnimationManager::ReleaseUVAnime(const UVAnimeID& rID)
{
	SafeDelete(m_pAnimation[rID.m_Num]);
	m_pAnimation.erase(rID.m_Num);
}

void UVAnimationManager::ReleaseALL()
{
	for(auto& pAnime : m_pAnimation)
	{
		SafeDelete(pAnime.second);
	}
	m_pAnimation.clear();
	m_IDNumCount = 0;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

int UVAnimationManager::SearchAvailableIDNum()
{
	int id;

	/** @todo ここは少し見直しした方がいいかもしれない */
	for(id = 0; id < INT_MAX; ++id)
	{
		if(m_pAnimation.find(id) != m_pAnimation.end())
		{
			break;
		}
	}
	
	return id;
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
