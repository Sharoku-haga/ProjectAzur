//==================================================================================================================================//
//!< @file		paBalloon.h
//!< @brief		pa::Balloonクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/09	更新履歴：2018/01/11
//==================================================================================================================================//

#ifndef PA_BALLOON_H
#define PA_BALLOON_H

#include <string>
#include <D3DX11.h>
#include <D3DX10.h>
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "sl/Library/Graphics/slGraphicsID.h"
#include "../paFishParam.h"


namespace pa
{

struct ObjDrawingData;

//===================================================================================//
//!< 魚のリアクションの吹き出しクラス
//===================================================================================//
class Balloon final
{

public:
	/** 
	* Constructor
	* @param[in] rIDs					描画のID群
	* @param[in] pResrcDataFilePath		リソースデータのファイルパス
	*/
	Balloon(const sl::DrawingID&	rIDs
			, const std::string&	rResrcDataFilePath);

	/** Destructor */
	~Balloon();

	/** 
	* 初期化関数
	* @param[in] rFishPosDiff			魚座標との差分
	*/
	void Initialize(const D3DXVECTOR2&	rFishPosDiff);

	/** 
	* 更新関数 
	* @param[in] rParam 魚のパラメータ
	*/
	void Update(const FishParam& rParam);

	/** 
	* 描画関数 
	* @param[in] rParam 魚のパラメータ 
	*/
	void Draw(const FishParam& rParam);

private:
	sl::UniquePtr<ObjDrawingData
				, sl::DefaultDeleter<ObjDrawingData>>	m_pDrawingData;				//!< 描画データ構造体のインスタンスへのユニークポインタ
	D3DXVECTOR2											m_GaugeDiffPos;				//!< ゲージ座標との座標の差分
	bool												m_IsFacingRight;			//!< 右を向いているかどうかのフラグ. true→向いている false→向いていない

	/** 
	* 画像を逆転する関数 
	* @param[in] rParam 魚のパラメータ
	*/
	void ProcessImageReversal(const FishParam& rParam);

};	// class Balloon

}	// namespace pa

#endif	// PA_BALLOON_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
