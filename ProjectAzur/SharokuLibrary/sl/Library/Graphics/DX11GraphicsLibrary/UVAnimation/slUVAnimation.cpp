//==================================================================================================================================//
//!< @file		slUVAnimation.cpp
//!< @brief		sl::UVAnimationクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/11/06	更新履歴：2017/12/09
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slUVAnimation.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */
 
UVAnimation::UVAnimation(const UVAnimeCreationData& rData)
	: m_AnimeWaitingTimeCount(0)
	, m_CurrentAnimeOrder(0)
{
	CreateData(rData);
}

UVAnimation::~UVAnimation()
{}

bool UVAnimation::Update(bool isLoop)
{
	if(m_AnimeWaitingTimeCount == m_AnimeWaitingTime)
	{
		if(m_CurrentAnimeOrder == (m_AnimeOrder.size() - 1))
		{
			if(isLoop)
			{
				Init();
			}
			else
			{
				return false;
			}
		}
		else
		{
			++m_CurrentAnimeOrder;
			m_CurrentUVData = m_UVData[m_AnimeOrder[m_CurrentAnimeOrder]];
			m_AnimeWaitingTimeCount = 0;
		}

		return true;
	}
	else
	{
		++m_AnimeWaitingTimeCount;
	}

	return false;
}

void UVAnimation::Init()
{
	m_CurrentAnimeOrder = 0;
	m_CurrentUVData = m_UVData[m_AnimeOrder[m_CurrentAnimeOrder]];
	m_AnimeWaitingTimeCount = 0;
}

bool UVAnimation::IsEndAnimation()
{
	return m_CurrentAnimeOrder == (m_AnimeOrder.size() - 1);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void UVAnimation::CreateData(const UVAnimeCreationData& rData)
{
	// アニメ待機時間を設定
	m_AnimeWaitingTime = rData.m_AnimeWaitingTime;

	// UVデータの設定
	fRect	currentUV = {0.0f, 0.0f, 0.0f, 0.0f};
	int		animePatternCount = 0;
	int		currentTuCount = 0;
	int		currentTvCount = 0;


	while(animePatternCount <= rData.m_AnimePatternCount)
	{
		currentUV.m_Left	= rData.m_StartUV.m_Left + rData.m_ScrollTu * currentTuCount;
		currentUV.m_Right	= rData.m_StartUV.m_Right + rData.m_ScrollTu * currentTuCount;
		currentUV.m_Top		= rData.m_StartUV.m_Top + rData.m_ScrollTv * currentTvCount;
		currentUV.m_Bottom	= rData.m_StartUV.m_Bottom + rData.m_ScrollTv * currentTvCount;
		
		m_UVData.emplace_back(currentUV.m_Left, currentUV.m_Top
							, currentUV.m_Right, currentUV.m_Bottom);

		/** @todo ここは一旦この処理でいく*/
		if(currentUV.m_Right >= 1.0f
			|| (1.0f - currentUV.m_Right) < rData.m_ScrollTu)
		{
			currentTuCount = 0;
			++currentTvCount;
		}
		else
		{
			++currentTuCount;
		}

		++animePatternCount;
	}

	// アニメの順番の設定
	if(rData.m_AnimeOrder.size() != 0)
	{
		m_AnimeOrder = rData.m_AnimeOrder;
	}
	else
	{
		for(int i = 1; i < (rData.m_AnimePatternCount + 1) ; ++i)
		{
			m_AnimeOrder.emplace_back(i);
		}
	}

	// 初期状態にする
	Init();
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
