//==================================================================================================================================//
//!< @file		slDXConstantBufferManager.cpp		
//!< @brief		sl::DXConstantBufferManagerクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/10/04	更新履歴：2017/10/06
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "slDXConstantBufferManager.h"
#include "../../../../Utility/slTemplateFunction.h"
#include "../../../../Debugger/slDebugFunction.h"

namespace sl
{

/* Public Functions ------------------------------------------------------------------------------------------- */

DXConstantBufferManager::DXConstantBufferManager(ID3D11Device*	pDevice, ID3D11DeviceContext*		pDeviceContext)
	: m_pDevice(pDevice)
	, m_pDeviceContext(pDeviceContext)
{}

DXConstantBufferManager::~DXConstantBufferManager()
{
	ReleaseALL();
}

ConstantBufferID DXConstantBufferManager::CreateConstantBuffer(unsigned int constantBufferSize)
{
	int bufferID = INT_MAX;
	ID3D11Buffer* pConstantBuffer;
	D3D11_BUFFER_DESC ConstantBufferDesc;
	ZeroMemory(&ConstantBufferDesc, sizeof(D3D11_BUFFER_DESC));
	ConstantBufferDesc.ByteWidth			= constantBufferSize;
	ConstantBufferDesc.Usage				= D3D11_USAGE_DYNAMIC;
	ConstantBufferDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
	ConstantBufferDesc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
	ConstantBufferDesc.MiscFlags			= 0;
	ConstantBufferDesc.StructureByteStride	= 0;

	if (FAILED(m_pDevice->CreateBuffer(&ConstantBufferDesc, NULL, &pConstantBuffer)))
	{
		slOutputDebugString("コンスタントバッファの生成に失敗しました");
		return ConstantBufferID(bufferID);
	}

	bufferID = m_pConstantBufferData.size();
	m_pConstantBufferData.emplace_back(new ConstantBufferData(pConstantBuffer, constantBufferSize));

	return ConstantBufferID(bufferID);
}

void DXConstantBufferManager::WriteConstantBuffer(const ConstantBufferID& rID, void*	pConstantBufferInfo)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBufferData[rID.m_Num]->m_pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)))
	{
		memcpy_s(mappedResource.pData, mappedResource.RowPitch, pConstantBufferInfo, m_pConstantBufferData[rID.m_Num]->m_BufferSize);
		m_pDeviceContext->Unmap(m_pConstantBufferData[rID.m_Num]->m_pBuffer, 0);
	}
}

void DXConstantBufferManager::Release(const ConstantBufferID& rID)
{
	SafeReleaseDX(m_pConstantBufferData[rID.m_Num]->m_pBuffer);
	SafeDelete(m_pConstantBufferData[rID.m_Num]);
}

void DXConstantBufferManager::ReleaseALL()
{
	for(auto& pConstantBufferData : m_pConstantBufferData)
	{
		SafeReleaseDX(pConstantBufferData->m_pBuffer);
		SafeDelete(pConstantBufferData);
	}
	std::vector<ConstantBufferData*>().swap(m_pConstantBufferData);
}


}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
