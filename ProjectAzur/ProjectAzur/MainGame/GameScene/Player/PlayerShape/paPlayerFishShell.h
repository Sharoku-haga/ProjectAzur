//==================================================================================================================================//
//!< @file		paPlayerFishShell.h
//!< @brief		pa::PlayerFishShellクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/21	更新履歴：
//==================================================================================================================================//

#ifndef PA_PLAYER_FISH_SHELL_H
#define PA_PLAYER_FISH_SHELL_H

#include <D3DX11.h>
#include <D3DX10.h>
#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "sl/Library/SmartPointer/UniquePtr/slUniquePtr.h"
#include "sl/Library/SmartPointer/SharedPtr/slSharedPtr.h"
#include "sl/Library/Utility/slRect.h"
#include "paPlayerFishShapeLine.h"
#include "../paPlayerCommonDeclaration.h"
#include "../../../paObjDrawingData.h"

namespace pa
{

class FishShape;

//===================================================================================//
//!< プレイヤーの魚の殻のクラス 
//===================================================================================//
class PlayerFishShell final
{

public:
	/** Constructor */
	PlayerFishShell();

	/** Destructor */
	~PlayerFishShell();

	/** 
	* 初期化関数
	* @param[in] rIDs					描画のID群
	* @param[in] rResrcDataFilePath		リソースデータのファイルパス
	*/
	void Initialize(const sl::DrawingID&	rIDs
				, const std::string&	rResrcDataFilePath);

	/**
	* 魚の形を作成する関数 
	* @param[in] pFishDrawingData	魚の描画データのポインタ
	*/
	void CreateShell(ObjDrawingData* pFishDrawingData);

	/** 魚の形を破棄する関数 */
	void DestroyShell();

	/** 
	* 更新関数
	* @param[in] rParam			プレイヤーのパラメータ
	*/
	void Update(const PlayerParam&	rParam);

	/** 
	* 描画するデータを調整する関数.
	* 主に衝突判定処理後にデータが変わったらよぶ
	* @param[in] rParam					プレイヤーのパラメータ
	*/
	void AdjustDrawingData(const PlayerParam&	rParam);

	/** 
	* 描画関数 
	* @param[in] rBasePointPos ベースポイント座標
	*/
	void Draw(const D3DXVECTOR2&	rBasePointPos);

	/** 破棄関数 */
	void Finalize();

	/**
	* Getter
	* @return 現在の矩形
	*/
	inline const sl::fRect& GetRectSize()
	{
		return m_RectSize;
	}

	/**
	* 魚の殻が作成されているかどうか確認する関数
	* @return ture→作成されている false→作成されていない
	*/
	inline bool HasCreatedShaell()
	{
		return m_HasCreatedShell;
	}

private:
	sl::DX11GraphicsLibrary&			m_rLibrary;				//!< グラフィックスライブラリのインスタンスへの参照
	sl::SharedPtr<ObjDrawingData>		m_pDrawingData;			//!< 描画する為のデータのシェアードポインタ
	sl::UniquePtr<PlayerFishShapeLine>	m_pFishLine;			//!< PlayerFishShapeLineクラスのインスタンスへのポインタ
	sl::fRect							m_RectSize;				//!< 矩形サイズ
	bool								m_IsFacingRight;		//!< 右を向いているかどうか true→ 右を向いている false→向いていない
	bool								m_HasCreatedShell;		//!< 魚の殻が作成されているかどうか ture→作成されている false→作成されていない

	/** 画像反転処理を行う関数 */
	void ProcessImageReversal();

};	// class PlayerFishShell

}	// namespace pa

#endif	// PA_PLAYER_FISH_SHELL_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
