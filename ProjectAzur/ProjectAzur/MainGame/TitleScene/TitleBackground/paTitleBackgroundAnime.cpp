//==================================================================================================================================//
//!< @file		paTitleBackgroundAnime.cpp
//!< @brief		pa::TitleBackgroundAnimeクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/11/30	更新履歴：2017/12/02
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <string>
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "paTitleBackgroundAnime.h"

namespace pa
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const int	AnimeindexMax = 90;				// アニメーションのインデックス
const int	AnimeWaitingTime = 1;			// アニメーションの待機時間

}

/* Public Functions ------------------------------------------------------------------------------------------- */

TitleBackgroundAnime::TitleBackgroundAnime()
	: m_CurrentIndex(0)
	, m_AnimeWaitingTimeCount(0)
{}

TitleBackgroundAnime::~TitleBackgroundAnime()
{
	Finalize();
}

void TitleBackgroundAnime::Initialize()
{
	using namespace std;

	// テクスチャー読み込み処理 -------------- //

	sl::DX11GraphicsLibrary& library = sl::DX11GraphicsLibrary::Instance();

	string fileDirectory = "../Resource/Texture/Title/TitleBG/titile_";
	string fileFormat = ".png";

	string filePath;

	// 0～9までの連番処理
	for(int i = 0; i < 10 ; ++i)
	{
		filePath = fileDirectory + "00" + to_string(i) + fileFormat;
		m_TextureIDs.emplace_back(library.LoadTexture(filePath.c_str()));
	}

	// 10～最大値まで
	for(int i = 10; i <  AnimeindexMax; ++i)
	{
		filePath = fileDirectory + "0" + to_string(i) + fileFormat;
		m_TextureIDs.emplace_back(library.LoadTexture(filePath.c_str()));
	}

	StandbyAnimation();
}

bool TitleBackgroundAnime::Update()
{
	if(m_AnimeWaitingTimeCount == AnimeWaitingTime)
	{
		if(m_CurrentIndex == (m_TextureIDs.size() - 1))
		{
			StandbyAnimation();
		}
		else
		{
			++m_CurrentIndex;
			m_AnimeWaitingTimeCount = 0;
		}

		return true;
	}

	++m_AnimeWaitingTimeCount;

	return false;
}

void TitleBackgroundAnime::Finalize()
{
	if(m_TextureIDs.size() == 0)
	{
		return;
	}

	for(auto& id : m_TextureIDs)
	{
		sl::DX11GraphicsLibrary::Instance().ReleaseTexture(id);
	}

	m_TextureIDs.clear();
	std::vector<sl::TextureID>().swap(m_TextureIDs);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void TitleBackgroundAnime::StandbyAnimation()
{
	m_CurrentIndex = 0;
	m_AnimeWaitingTimeCount = 0;
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
