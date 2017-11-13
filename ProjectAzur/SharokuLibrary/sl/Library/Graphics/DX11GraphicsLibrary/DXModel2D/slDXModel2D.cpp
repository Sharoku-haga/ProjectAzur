//==================================================================================================================================//
//!< @file		slDXModel2D.cpp	
//!< @brief		sl::DXModel2Dクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/11/02	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDXModel2D.h"
#include "../../../Utility/slDefine.h"
#include "../../../Utility/slTemplateFunction.h"
#include "../../../Debugger/slDebugFunction.h"
#include "../../../Debugger/slDebugDefine.h"

namespace sl
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const D3DXCOLOR  DefaultColor = 0xffffffff;				// デフォルトのカラーの値

}

/* Static Variable -------------------------------------------------------------------------------------------- */

const int		DXModel2D::m_VertexCount;

/* Public Functions ------------------------------------------------------------------------------------------- */

DXModel2D::DXModel2D(ID3D11Device* pDevice, ID3D11DeviceContext*	pDeviceContext
					, const Model2DCreationData& rData)
	: m_pDevice(pDevice)
	, m_pDeviceContext(pDeviceContext)
	, m_pVertexBuffer(NULL)
{
	CreateData(rData);
}

DXModel2D::~DXModel2D()
{
	ReleaseBuffer();
}

void DXModel2D::Draw()
{
	UINT stride = sizeof(VertexData);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pDeviceContext->Draw(m_VertexCount, 0);
}

void DXModel2D::SetSizeData(float width, float height)
{
	fRect size;							//!< サイズを格納する変数
	CalculateRectData(&size, width, height);

	m_Vertexs[0].m_Pos = D3DXVECTOR3( size.m_Left,		size.m_Top, 0.0f);
	m_Vertexs[1].m_Pos = D3DXVECTOR3( size.m_Right,		size.m_Top, 0.0f);
	m_Vertexs[2].m_Pos = D3DXVECTOR3( size.m_Left,		size.m_Bottom, 0.0f);
	m_Vertexs[3].m_Pos = D3DXVECTOR3( size.m_Right,		size.m_Bottom, 0.0f);

	if(RESULT_FALSE(RewriteVertexBuffer()))
	{
		slOutputDebugString("サイズにおける頂点バッファの再書き込みに失敗しました");
	}
}

void DXModel2D::SetUVData(const fRect& rUv)
{
	m_Vertexs[0].m_UV = D3DXVECTOR2( rUv.m_Left,	rUv.m_Top);
	m_Vertexs[1].m_UV = D3DXVECTOR2( rUv.m_Right,	rUv.m_Top);
	m_Vertexs[2].m_UV = D3DXVECTOR2( rUv.m_Left,	rUv.m_Bottom);
	m_Vertexs[3].m_UV = D3DXVECTOR2( rUv.m_Right,	rUv.m_Bottom);

	if(RESULT_FALSE(RewriteVertexBuffer()))
	{
		slOutputDebugString("UVにおける頂点バッファの再書き込みに失敗しました");
	}
}

void DXModel2D::SetColorData(const std::vector<D3DXCOLOR>& rColor)
{
	for(int i = 0; i < m_VertexCount; ++i)
	{
		m_Vertexs[i].m_Color = rColor[i];
	}

	if(RESULT_FALSE(RewriteVertexBuffer()))
	{
		slOutputDebugString("カラーにおける頂点バッファの再書き込みに失敗しました");
	}
}

void DXModel2D::InformSizeData(fRect& rSizeData)
{
	rSizeData.m_Left	= m_Vertexs[0].m_Pos.x;
	rSizeData.m_Top		= m_Vertexs[0].m_Pos.y;
	rSizeData.m_Right	= m_Vertexs[1].m_Pos.x;
	rSizeData.m_Bottom	= m_Vertexs[2].m_Pos.y;
}

void DXModel2D::InformUVData(fRect& rUVData)
{
	rUVData.m_Left		= m_Vertexs[0].m_UV.x;
	rUVData.m_Top		= m_Vertexs[0].m_UV.y;
	rUVData.m_Right		= m_Vertexs[1].m_UV.x;
	rUVData.m_Bottom	= m_Vertexs[2].m_UV.y;
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void DXModel2D::CreateData(const Model2DCreationData& rData)
{
	m_IsCenterPos = rData.m_IsCenterPos;

	std::vector<D3DXCOLOR>	color;			//!< カラー値を格納するvector
	if(rData.m_Color.size() == 0)
	{
		for(int i = 0; i < m_VertexCount; ++i)
		{
			color.emplace_back(DefaultColor);
		}
	}
	else
	{
		color = rData.m_Color;
	}

	fRect size;							//!< サイズを格納する変数
	CalculateRectData(&size, rData.m_Width, rData.m_Height);

	std::array<VertexData, m_VertexCount>	vertexs{
		VertexData(D3DXVECTOR3(size.m_Left,		size.m_Top,		0.0f),	color[0], D3DXVECTOR2(rData.m_UV.m_Left,	rData.m_UV.m_Top)),
		VertexData(D3DXVECTOR3(size.m_Right,	size.m_Top,		0.0f),	color[1], D3DXVECTOR2(rData.m_UV.m_Right,	rData.m_UV.m_Top)),
		VertexData(D3DXVECTOR3(size.m_Left,		size.m_Bottom,	0.0f),	color[2], D3DXVECTOR2(rData.m_UV.m_Left,	rData.m_UV.m_Bottom)),
		VertexData(D3DXVECTOR3(size.m_Right,	size.m_Bottom,	0.0f),	color[3], D3DXVECTOR2(rData.m_UV.m_Right,	rData.m_UV.m_Bottom))
	};

	for(int i = 0; i < m_VertexCount; ++i)
	{
		m_Vertexs[i].m_Pos		= vertexs[i].m_Pos;
		m_Vertexs[i].m_Color	= vertexs[i].m_Color;
		m_Vertexs[i].m_UV		= vertexs[i].m_UV;
	}

	if(RESULT_FALSE(CreateBuffer()))
	{
		slOutputDebugString("モデルのバッファ作成に失敗しました");
	}
}

bool DXModel2D::CreateBuffer()
{
	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
	bufferDesc.ByteWidth			= sizeof(VertexData) * m_VertexCount;				// バッファーのサイズ (バイト単位)
	bufferDesc.Usage				= D3D11_USAGE_DYNAMIC;								// バッファーで想定されている読み込みおよび書き込みの方法
	bufferDesc.BindFlags			= D3D11_BIND_VERTEX_BUFFER;							// バッファーをどのようにパイプラインにバインドするかの識別
	bufferDesc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;							// CPU アクセスのフラグ
	bufferDesc.MiscFlags			= 0;												// リソースに使用される、あまり一般的でないその他のオプションのフラグ
	bufferDesc.StructureByteStride	= 0;												// 構造体が構造化バッファーを表す場合のその構造体のサイズ 

	D3D11_SUBRESOURCE_DATA initVertexData;
	ZeroMemory(&initVertexData, sizeof(D3D11_SUBRESOURCE_DATA));
	initVertexData.pSysMem = m_Vertexs.data();

	if(FAILED(m_pDevice->CreateBuffer(&bufferDesc, &initVertexData, &m_pVertexBuffer)))
	{
		slOutputDebugString("頂点バッファの作成に失敗しました");
		return false;
	}
	return true;
}

bool DXModel2D::RewriteVertexBuffer()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;	// サブリソースデータにアクセスできるようにするための構造体
	if(SUCCEEDED(m_pDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)))
	{
		memcpy_s(mappedResource.pData,
				mappedResource.RowPitch,
				m_Vertexs.data(),
				sizeof(VertexData) * m_VertexCount);

		m_pDeviceContext->Unmap(m_pVertexBuffer, 0);

		return true;
	}

	slOutputDebugString("頂点バッファの再書きこみに失敗しました");
	return false;
}

void DXModel2D::ReleaseBuffer()
{
	SafeReleaseDX(m_pVertexBuffer);
}

void DXModel2D::CalculateRectData(fRect* pRect, float width, float height)
{
	if(m_IsCenterPos)
	{
		pRect->m_Left		= -(width / 2);
		pRect->m_Top		= -(height / 2);
		pRect->m_Right		= (width / 2);
		pRect->m_Bottom		= (height / 2);
	}
	else
	{
		pRect->m_Left		= 0.0f;
		pRect->m_Top		= 0.0f;
		pRect->m_Right		= width;
		pRect->m_Bottom		= height;
	}
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
