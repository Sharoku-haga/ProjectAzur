//==================================================================================================================================//
//!< @file		slUVAnimation.h
//!< @brief		sl::UVAnimationクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/06	更新履歴：
//==================================================================================================================================//

#ifndef SL_UV_ANIMATION_H
#define SL_UV_ANIMATION_H

#include <vector>
#include "../../../Utility/slRect.h"
#include "../../slGraphicsDeclaration.h"

namespace sl
{

//===================================================================================//
//!< UVアニメーションのクラス
//===================================================================================//
class UVAnimation
{

public:
	/** 
	* Constructor
	* @param[in] rData	作成したいアニメーションのデータ
	*/
	UVAnimation(const UVAnimeCreationData& rData);

	/** Destructor */
	~UVAnimation();

	/**
	* アニメーション更新関数
	* @param[in] isLoop ループするかどうかのフラグ true→成功 false→失敗
	* @return true→更新 false→更新していない
	*/
	bool Update(bool isLoop);

	/** 初期化関数 */
	void Init();

	/**
	* アニメーションが終了しているかどうかを確認する関数
	* @return true→終了している false→終了していない
	*/
	bool IsEndAnimation();

	/**
	* 現在のUVデータを取得する関数
	* @return UVデータ
	*/
	const fRect& GetCurrentUVData(){ return m_CurrentUVData; }

private:
	std::vector<fRect>		m_UVData;						//!< 各アニメーションのUVデータを格納するvector
	std::vector<int>		m_AnimeOrder;					//!< アニメーションの順番を格納するvector
	int						m_AnimeWaitingTime;				//!< アニメーションの待機時間
	int						m_AnimeWaitingTimeCount;		//!< アニメーションの待機時間のカウント数
	fRect					m_CurrentUVData;				//!< 現在のUVデータ
	int						m_CurrentAnimeOrder;			//!< 現在のアニメーションの順番

	/** 
	* アニメーションのデータを作成する関数
	* @param[in] rData	作成したいアニメーションのデータ
	*/
	void CreateData(const UVAnimeCreationData& rData);

};	// class UVAnimation

}	// namespace sl

#endif	// SL_UV_ANIMATION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
