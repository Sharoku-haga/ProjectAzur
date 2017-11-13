//==================================================================================================================================//
//!< @file		slDXModel2D.h	
//!< @brief		sl::DXModel2Dクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/02	更新履歴：
//==================================================================================================================================//

#ifndef SL_DX_MODEL_2D_H
#define SL_DX_MODEL_2D_H

#include <vector>
#include <array>
#include <d3dx11.h>
#include <d3dx10.h>
#include "../../../Utility/slRect.h"
#include "../../slGraphicsDeclaration.h"

namespace sl
{

//===================================================================================//
//!< DirectXにおける2Dモデルクラス
//===================================================================================//
class DXModel2D
{

public:
	/** 
	* Constructor 
	* @param[in] pDevice			Direct3Dのデバイス
	* @param[in] pDeviceContext		Direct3Dのデバイスコンテキスト
	* @param[in] rData				モデルを作成するためのデータ
	*/
	DXModel2D(ID3D11Device* pDevice, ID3D11DeviceContext*	pDeviceContext
			, const Model2DCreationData& rData);
	
	/** Destructor */
	~DXModel2D();

	/** 描画関数 */
	void Draw();

	/** 
	* サイズデータを設定する関数
	* @param[in] width		設定したい横の大きさ
	* @param[in] height		設定したい縦の大きさ
	*/
	void SetSizeData(float width, float height);

	/**
	* UVデータを設定する関数
	* @param[in] rUv	設定したいUV値
	*/
	void SetUVData(const fRect& rUv);

	/**
	* 色データを設定する関数
	* @param[in] rColor	設定したい色
	*/
	void SetColorData(const std::vector<D3DXCOLOR>& rColor);

	/**
	* サイズデータを知らせる関数 
	* @param[out] rSizeData 自身のサイズデータを格納する変数
	*/
	void InformSizeData(fRect& rSizeData);

	/**
	* UVデータを知らせる関数
	* @param[out] rUVData 自身のUVデータを格納する変数
	*/
	void InformUVData(fRect& rUVData);

	/**
	* Getter
	* @return モデルの頂点数
	*/
	static inline int GetVertecCount(){ return m_VertexCount; }

private:
	/** 頂点データ */
	struct VertexData
	{
		D3DXVECTOR3		m_Pos;			//!< 位置情報
		D3DXCOLOR		m_Color;		//!< 色情報
		D3DXVECTOR2		m_UV;			//!< テクスチャーのUV情報
		VertexData() {}
		VertexData(const D3DXVECTOR3& rPos, D3DXCOLOR rColor, D3DXVECTOR2 rUV)
			: m_Pos(rPos), m_Color(rColor), m_UV(rUV)
		{}
	};	// struct VertexData

	static const int						m_VertexCount = 4;			//!< 頂点数.2Dの為4つ
	ID3D11Device*							m_pDevice;					//!< Direct3Dのデバイス
	ID3D11DeviceContext*					m_pDeviceContext;			//!< Direct3Dのデバイスコンテキスト
	ID3D11Buffer*							m_pVertexBuffer;			//!< 頂点バッファ
	std::array<VertexData, m_VertexCount>	m_Vertexs;					//!< モデルの頂点データ
	bool									m_IsCenterPos;				//!< モデルの位置座標が中心かどうか true→中心座標 false →左上座標

	/** 
	* モデルのデータを作成する関数 
	* @param[in] rData	モデルを作成するためのデータ
	*/
	void CreateData(const Model2DCreationData& rData);

	/** 
	* 頂点バッファを作成する関数
	* @return	結果 true→成功 false→失敗
	*/
	bool CreateBuffer();

	/** 
	*  作成した頂点バッファの情報を書き換える関数
	* @return	結果 true→成功 false→失敗
	*/
	bool RewriteVertexBuffer();

	/** バッファを開放する関数 */
	void ReleaseBuffer();

	/**
	* モデルの矩形サイズを計算する関数
	* @param[out] pRect 計算した矩形データを格納する変数
	* @param[in] width		横の大きさ
	* @param[in] height		縦の大きさ
	*/
	void CalculateRectData(fRect* pRect, float width, float height);

};	// class DXModel2D

}	// namespace sl

#endif	// SL_DX_MODEL_2D_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
