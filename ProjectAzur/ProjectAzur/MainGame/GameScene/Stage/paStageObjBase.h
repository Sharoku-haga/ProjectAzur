//==================================================================================================================================//
//!< @file		paStageObjBase.h
//!< @brief		pa::StageObjBaseクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/12/09	更新履歴：
//==================================================================================================================================//

#ifndef PA_STAGE_OBJ_BASE_H
#define PA_STAGE_OBJ_BASE_H

#include <D3DX10.h>
#include "sl/Library/Utility/slRect.h"

namespace pa
{

//===================================================================================//
//!< ステージに関連するオブジェクトの基底クラス
//===================================================================================//
class StageObjBase
{

public:
	/** Constructor */
	StageObjBase() = default;

	/** Destructor */
	virtual ~StageObjBase()  = default;

	/** 更新関数 */
	virtual void Update() = 0;

	/** 
	* Setter 
	* @param[in] rBasePointPos ベースポイントの座標
	*/
	static void SetBasePointPos(const D3DXVECTOR2&	rBasePointPos) 
	{ 
		m_BasePointPos = rBasePointPos; 
	}

	/** 
	* Setter 
	* @param[in] rScreenSize スクリーンサイズ
	*/
	static void SetScreenSize(const sl::fRect& rScreenSize)
	{
		m_ScreenSize = rScreenSize;
	}

protected:
	/** 
	* 自身が画面範囲にあるかを確認する関数
	* @param[in] rMyPos		自身の座標
	* @param[in] rMySize	自身のサイズ
	* @return 結果 true→画面範囲内にある false→画面範囲外にある
	*/
	bool CheckScreenArea(const D3DXVECTOR2&	rMyPos, const sl::fRect& rMySize);

private:
	static D3DXVECTOR2		m_BasePointPos;		//!< ベースポイントの座標	
	static sl::fRect		m_ScreenSize;		//!< スクリーンサイズ

};	// class StageObjBase

}	// namespace pa

#endif	// PA_STAGE_OBJ_BASE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
