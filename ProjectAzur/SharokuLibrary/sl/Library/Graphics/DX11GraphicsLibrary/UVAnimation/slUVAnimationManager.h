//==================================================================================================================================//
//!< @file		slUVAnimationManager.h
//!< @brief		sl::UVAnimationManagerクラスヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/07	更新履歴：
//==================================================================================================================================//

#ifndef SL_UV_ANIMATION_MANAGER_H
#define SL_UV_ANIMATION_MANAGER_H

#include <map>
#include "../../slGraphicsDeclaration.h"
#include "../../slGraphicsID.h"

namespace sl
{

class UVAnimation;

//===================================================================================//
//!< UVAnimationクラスを管理するクラス
//===================================================================================//
class UVAnimationManager
{

public:
	/** Constructor */
	UVAnimationManager();

	/** Destructor */
	~UVAnimationManager();

	/**
	* UVアニメーションを生成する関数
	* @param[in] rData 生成したいUVアニメーションデータ
	* @return UVアニメーションID
	*/
	UVAnimeID CreateAnimatoin(const UVAnimeCreationData& rData);

	/**
	* UVアニメーションを行う関数
	* @param[in] rID UVアニメーションのID
	* @param[in] isLoop	アニメーションループフラグ true→ループする false→ループしない
	* @return true→アニメーションが更新した false→更新していない
	*/
	bool UpdateUVAnime(const UVAnimeID& rID, bool isLoop);

	/**
	* UVアニメーションを初期化する関数 
	* @param[in] rID 初期化したいUVアニメーションのID
	*/
	void InitUVAnime(const UVAnimeID& rID);

	/**
	* 指定したアニメーションが終了しているかどうかを確認する関数
	* @param[in] rID  確認したいUVアニメーションのID
	* @return true→終了している false →終了していない
	*/
	bool IsEndUVAnimation(const UVAnimeID& rID);

	/**
	* 指定したUVアニメーションの現在のUV値を取得する関数
	* @param[in] rID  取得したいUVアニメーションのID
	* @return 指定したアニメーションの現在のUV値
	*/
	const fRect& GetCurrentUVData(const UVAnimeID& rID);

	/**
	* 指定したUVアニメーションを解放する関数
	* @param[in] rID 解放したいUVアニメーションのID
	*/
	void ReleaseUVAnime(const UVAnimeID& rID);

	/** 現在格納しているUVアニメーション全てを解放する関数 */
	void ReleaseALL();

private:
	std::map<int, UVAnimation*>		m_pAnimation;		//!< UVAnimationクラスを格納するmap
	int								m_IDNumCount;		//!< ID番号のカウント数

	/** 
	* 現在使用できるIDを検索する関数 
	* @return 使用できるID番号
	*/
	int SearchAvailableIDNum();

};	// class UVAnimationManager

}	//namespace sl

#endif	// SL_UV_ANIMATION_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
