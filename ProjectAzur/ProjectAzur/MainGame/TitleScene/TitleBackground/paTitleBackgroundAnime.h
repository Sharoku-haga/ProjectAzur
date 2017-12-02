//==================================================================================================================================//
//!< @file		paTitleBackgroundAnime.h
//!< @brief		pa::TitleBackgroundAnimeクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/30	更新履歴：2017/12/02
//==================================================================================================================================//

#ifndef PA_TITLE_BACKGROUND_ANIME_H
#define PA_TITLE_BACKGROUND_ANIME_H

#include <vector>
#include "sl/Library/Graphics/slGraphicsID.h"

namespace pa
{

//===================================================================================//
//!< タイトルの背景のアニメーションを管理するクラス
//===================================================================================//
class TitleBackgroundAnime final
{

public:
	/** Constructor */
	TitleBackgroundAnime();

	/** Destructor */
	~TitleBackgroundAnime();

	/** 初期化関数 */
	void Initialize();

	/** 
	* 更新関数
	* @return  結果 true→更新された false 
	*/
	bool Update();

	/** 破棄関数 */
	void Finalize();

	/**
	* 現在のテクスチャーのIDを取得する関数
	* @return 現在のテクスチャーのID
	*/
	inline const sl::TextureID& GetCurrentTextureID() { return m_TextureIDs[m_CurrentIndex]; }

private:
	int								m_CurrentIndex;						//!< 現在のインデックス番号
	int								m_AnimeWaitingTimeCount;			//!< アニメーションの待機時間カウント数
	std::vector<sl::TextureID>		m_TextureIDs;						//!< テクスチャーのIDを格納する動的配列

	/** アニメーションを準備する関数 */
	void StandbyAnimation();

};	// class TitleBackgroundAnime

}	// namespace pa

#endif	// PA_TITLE_BACKGROUND_ANIME_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
