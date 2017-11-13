//==================================================================================================================================//
//!< @file		slGraphicsDeclaration.h
//!< @brief		グラフィックス関連で共通で使用する宣言をまとめたヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/06	更新履歴：
//==================================================================================================================================//

#ifndef SL_GRAPHICS_DECLARATION_H
#define SL_GRAPHICS_DECLARATION_H

#include <d3dx11.h>
#include <d3dx10.h>
#include <vector>
#include "../Utility/slRect.h"

namespace sl
{

//===================================================================================//
//!< 基本的な2Dにおけるコンスタントバッファの構造体
//===================================================================================//

struct Basic2DConstantBuffer
{
	D3DXMATRIX  m_MatWorld;			//!< ワールド変換行列
	D3DXVECTOR4 m_WindowSize;		//!< ウィンドウの縦横サイズ
};	// Basic2DConstantBuffer

//===================================================================================//
//!< 2Dモデルを作成するためのデータ構造体 
//===================================================================================//
struct Model2DCreationData
{
	float					m_Width;			//!< 横の大きさ
	float					m_Height;			//!< 縦の大きさ
	fRect					m_UV;				//!< UV値(矩形)
	std::vector<D3DXCOLOR>	m_Color;			//!< カラー値
	bool					m_IsCenterPos;		//!< モデルの位置座標が中心かどうか true→中心座標 false →左上座標
	Model2DCreationData() {}
	Model2DCreationData(float width, float height, bool	isCenterPos)
		: m_Width(width), m_Height(height), m_UV(0.0f, 0.0f, 1.0f, 1.0f), m_IsCenterPos(isCenterPos)
	{}
	Model2DCreationData(float width, float height, const fRect& rUV, bool isCenterPos)
		: m_Width(width), m_Height(height), m_UV(rUV), m_IsCenterPos(isCenterPos)
	{}
	Model2DCreationData(float width
						, float height
						, const fRect& rUV
						, const std::vector<D3DXCOLOR>& rColor
						, bool isCenterPos)
		: m_Width(width), m_Height(height), m_UV(rUV), m_Color(rColor), m_IsCenterPos(isCenterPos)
	{}
};	// struct Model2DCreationData

//===================================================================================//
//!< UVアニメーションを作成するためのデータ構造体
//===================================================================================//
struct UVAnimeCreationData
{
	int						m_AnimePatternCount;		//!< アニメーションの数
	int						m_AnimeWaitingTime;			//!< アニメーションの待機時間
	fRect					m_StartUV;					//!< スタート時点のUV値
	float					m_ScrollTu;					//!< スクロールするTu値
	float					m_ScrollTv;					//!< スクロールするTv値
	std::vector<int>		m_AnimeOrder;				//!< アニメーションの順番を格納
};	// struct UVAnimeCreationData


}	// namespace sl

#endif	// SL_GRAPHICS_DECLARATION_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
