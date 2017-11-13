//==================================================================================================================================//
//!< @file		slDX11GraphicsLibrary.cpp
//!< @brief		sl::DX11GraphicsLibraryクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/11/07	更新履歴：2017/11/12
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <memory>
#include "slDX11GraphicsLibrary.h"
#include "../../Window/slWindowDeclaration.h"
#include "../../SmartPointer/slSmartPointer.h"
#include "../../Utility/slTemplateFunction.h"
#include "slDX11Graphics.h"

namespace sl
{

/* Class ------------------------------------------------------------------------------------------------------ */

class DX11GraphicsLibrary::Impl
{

public:
	UniquePtr<DXDeviceManager>				m_pDeviceManager;
	UniquePtr<DXGISwapChainManager>			m_pSwapChainManager;
	UniquePtr<DXViewManager>				m_pViewManager;
	UniquePtr<DXBlendStateManager>			m_pBlendStateManager;
	UniquePtr<DXRasterizerStateManager>		m_pRasterizerSatateManager;
	UniquePtr<DXDrawingCommander>			m_pDrawingCommander;
	UniquePtr<DXTextureManager>				m_pTextureManager;
	UniquePtr<DXSamplerStateManager>		m_pSampleStateManager;
	UniquePtr<DXModel2DStorage>				m_pModel2DStorage;
	UniquePtr<UVAnimationManager>			m_pUVAnimationManager;
	UniquePtr<DXVertexShaderManager>		m_pVertexShaderManager;
	UniquePtr<DXPixelShaderManager>			m_pPixelShaderManager;
	UniquePtr<DXInputLayoutManager>			m_pInputLayoutManager;
	UniquePtr<DXConstantBufferManager>		m_pConstantBufferManager;

};	// class DX11GraphicsLibrary::Impl

/* Public Functions ------------------------------------------------------------------------------------------- */

void DX11GraphicsLibrary::Init(const WindowHandle& rHandle, const fRect& rBackBufferSize)
{
	m_pImpl = new Impl();

	// デバイス関連の生成
	m_pImpl->m_pDeviceManager.Reset(new DXDeviceManager());
	m_pImpl->m_pDeviceManager->CreateDevice();

	//スワップチェインの生成
	m_pImpl->m_pSwapChainManager.Reset(new DXGISwapChainManager());
	m_pImpl->m_pSwapChainManager->CreateDXGISwapChain(rHandle, m_pImpl->m_pDeviceManager->GetDevice(), rBackBufferSize);

	// ビュー関連の生成
	m_pImpl->m_pViewManager.Reset(new DXViewManager());
	m_pImpl->m_pViewManager->CreateRenderTargetView(m_pImpl->m_pDeviceManager->GetDevice()
													, m_pImpl->m_pSwapChainManager->GetDXGISwapChain());
	m_pImpl->m_pViewManager->CreateDepthStencilView(m_pImpl->m_pDeviceManager->GetDevice()
													, m_pImpl->m_pSwapChainManager->GetDXGISwapChain());

	// ブレンドステートの設定を生成
	m_pImpl->m_pBlendStateManager.Reset(new DXBlendStateManager());
	m_pImpl->m_pBlendStateManager->CreateDefaultBlendState(m_pImpl->m_pDeviceManager->GetDevice());

	// ラスタライザの設定を生成
	m_pImpl->m_pRasterizerSatateManager.Reset(new DXRasterizerStateManager());
	m_pImpl->m_pRasterizerSatateManager->CreateDefaultRasterizerState(m_pImpl->m_pDeviceManager->GetDevice());

	// 描画コマンドの生成と設定
	m_pImpl->m_pDrawingCommander.Reset(new DXDrawingCommander(m_pImpl->m_pDeviceManager->GetDeviceContext()
															, m_pImpl->m_pSwapChainManager->GetDXGISwapChain()
															, m_pImpl->m_pViewManager->GetRenderTargetView()
															, m_pImpl->m_pViewManager->GetDepthStencilView()));
	m_pImpl->m_pDrawingCommander->Initialize();
	m_pImpl->m_pDrawingCommander->SetUpBlendState(m_pImpl->m_pBlendStateManager->GetDefaultBlendState());
	m_pImpl->m_pDrawingCommander->SetUpRasterizerState(m_pImpl->m_pRasterizerSatateManager->GetDefaultRasterizerState());

	// テクスチャー関連の生成
	m_pImpl->m_pTextureManager.Reset(new DXTextureManager(m_pImpl->m_pDeviceManager->GetDevice()));
	m_pImpl->m_pSampleStateManager.Reset(new DXSamplerStateManager());
	m_pImpl->m_pSampleStateManager->CreateDefaultSamplerState(m_pImpl->m_pDeviceManager->GetDevice());

	// モデル関連の生成
	m_pImpl->m_pModel2DStorage.Reset(new DXModel2DStorage());

	// UVアニメーション関連の生成
	m_pImpl->m_pUVAnimationManager.Reset(new UVAnimationManager());

	// シェーダー関連の生成
	m_pImpl->m_pVertexShaderManager.Reset(new DXVertexShaderManager(m_pImpl->m_pDeviceManager->GetDevice()));
	m_pImpl->m_pInputLayoutManager.Reset(new DXInputLayoutManager(m_pImpl->m_pDeviceManager->GetDevice()));
	m_pImpl->m_pPixelShaderManager.Reset(new DXPixelShaderManager(m_pImpl->m_pDeviceManager->GetDevice()));
	m_pImpl->m_pConstantBufferManager.Reset(new DXConstantBufferManager(m_pImpl->m_pDeviceManager->GetDevice(), m_pImpl->m_pDeviceManager->GetDeviceContext()));
}

void DX11GraphicsLibrary::ChangeScreenMode(bool isFullScreen)
{
	m_pImpl->m_pSwapChainManager->ChangeScreenMode(isFullScreen);
}

const fRect& DX11GraphicsLibrary::GetBackBufferSize()
{
	return m_pImpl->m_pSwapChainManager->GetBackBufferSize();
}

TextureID DX11GraphicsLibrary::LoadTexture(const t_char* pFileName)
{
	return m_pImpl->m_pTextureManager->LoadTexture(pFileName);
}

void DX11GraphicsLibrary::ReleaseTexture(const TextureID& rID)
{
	m_pImpl->m_pTextureManager->Release(rID);
}

void DX11GraphicsLibrary::ReleaseTextureALL()
{
	m_pImpl->m_pTextureManager->ReleaseALL();
}

VertexShaderID DX11GraphicsLibrary::CreateVertexShader(const t_char* pFilePath, const t_char* pShaderFuncName)
{
	return m_pImpl->m_pVertexShaderManager->CreateVertexShader(pFilePath, pShaderFuncName);
}

InputLayoutID DX11GraphicsLibrary::CreateInputLayout(const t_char* pVertexShaderFilePath
								, const t_char* pVertexShaderFuncName
								, D3D11_INPUT_ELEMENT_DESC* pInputElementDesc
								, unsigned int elementDescSize)
{
	return m_pImpl->m_pInputLayoutManager->CreateInputLayout(pVertexShaderFilePath
															, pVertexShaderFuncName
															, pInputElementDesc
															, elementDescSize);
}

PixelShaderID DX11GraphicsLibrary::CreatePixelShader(const t_char* pFilePath, const t_char* pShaderFuncName)
{
	return m_pImpl->m_pPixelShaderManager->CreatePixelShader(pFilePath, pShaderFuncName);
}

ConstantBufferID DX11GraphicsLibrary::CreateConstantBuffer(unsigned int constantBufferSize)
{
	return m_pImpl->m_pConstantBufferManager->CreateConstantBuffer(constantBufferSize);
}

void DX11GraphicsLibrary::ReleaseVertexShader(const VertexShaderID & rID)
{
	m_pImpl->m_pVertexShaderManager->Release(rID);
}

void DX11GraphicsLibrary::ReleaseInputLayout(const InputLayoutID & rID)
{
	m_pImpl->m_pInputLayoutManager->Release(rID);
}

void DX11GraphicsLibrary::ReleasePixelShader(const PixelShaderID& rID)
{
	m_pImpl->m_pPixelShaderManager->Release(rID);
}

void DX11GraphicsLibrary::ReleaseConstantBuffer(const ConstantBufferID& rID)
{
	m_pImpl->m_pConstantBufferManager->Release(rID);
}

void DX11GraphicsLibrary::ReleaseVertexShaderALL()
{
	m_pImpl->m_pVertexShaderManager->ReleaseALL();
}

void DX11GraphicsLibrary::ReleaseInputLayoutALL()
{
	m_pImpl->m_pInputLayoutManager->ReleaseALL();
}

void DX11GraphicsLibrary::ReleasePixelShaderALL()
{
	m_pImpl->m_pPixelShaderManager->ReleaseALL();
}

void DX11GraphicsLibrary::ReleaseConstantBufferALL()
{
	m_pImpl->m_pConstantBufferManager->ReleaseALL();
}

int DX11GraphicsLibrary::GetModel2DVertexCount()
{
	return DXModel2D::GetVertecCount();
}

ModelID DX11GraphicsLibrary::CreateDXModel2D(const Model2DCreationData& rData)
{
	DXModel2D*	pModel = new DXModel2D(m_pImpl->m_pDeviceManager->GetDevice()
										, m_pImpl->m_pDeviceManager->GetDeviceContext()
										, rData);
	return m_pImpl->m_pModel2DStorage->AddDXModel2D(pModel);
}

void DX11GraphicsLibrary::SetDXModel2DSizeData(const ModelID& rID, float widthSize, float heightSize)
{
	m_pImpl->m_pModel2DStorage->GetModel2DData(rID)->SetSizeData(widthSize, heightSize);
}

void DX11GraphicsLibrary::SetDXModel2DUVData(const ModelID& rID, const fRect& rUv)
{
	m_pImpl->m_pModel2DStorage->GetModel2DData(rID)->SetUVData(rUv);
}

void DX11GraphicsLibrary::SetDXModel2DColorData(const ModelID& rID, const std::vector<D3DXCOLOR>& rColor)
{
	m_pImpl->m_pModel2DStorage->GetModel2DData(rID)->SetColorData(rColor);
}

void DX11GraphicsLibrary::ReleaseDXModel2D(const ModelID& rID)
{
	m_pImpl->m_pModel2DStorage->ReleaseDXModel2D(rID);
}

void DX11GraphicsLibrary::ReleaseDXModel2DALL()
{
	m_pImpl->m_pModel2DStorage->ReleaseALL();
}

UVAnimeID DX11GraphicsLibrary::CreateAnimatoin(const UVAnimeCreationData& rData)
{
	return m_pImpl->m_pUVAnimationManager->CreateAnimatoin(rData);
}

bool DX11GraphicsLibrary::UpdateUVAnime(const UVAnimeID& rID, bool isLoop)
{
	return m_pImpl->m_pUVAnimationManager->UpdateUVAnime(rID, isLoop);
}

void DX11GraphicsLibrary::InitUVAnime(const UVAnimeID& rID)
{
	m_pImpl->m_pUVAnimationManager->InitUVAnime(rID);
}

bool DX11GraphicsLibrary::IsEndUVAnimation(const UVAnimeID& rID)
{
	return m_pImpl->m_pUVAnimationManager->IsEndUVAnimation(rID);
}

void DX11GraphicsLibrary::ReleaseUVAnimation(const UVAnimeID& rID)
{
	m_pImpl->m_pUVAnimationManager->ReleaseUVAnime(rID);
}

void DX11GraphicsLibrary::ReleaseUVAnimationALL()
{
	m_pImpl->m_pUVAnimationManager->ReleaseALL();
}

void DX11GraphicsLibrary::StartRender(void)
{
	m_pImpl->m_pDrawingCommander->StartRender();
}

void DX11GraphicsLibrary::EndRender(void)
{
	m_pImpl->m_pDrawingCommander->EndRender();
}

void DX11GraphicsLibrary::DrawModel2D(const DrawingID& rID, void* pConstantBufferInfo)
{
	m_pImpl->m_pDrawingCommander->SetUpShader(m_pImpl->m_pVertexShaderManager->GetVertexShader(rID.m_VertexShaderID)
											, m_pImpl->m_pPixelShaderManager->GetPixelShader(rID.m_PixelShaderID));
	m_pImpl->m_pDrawingCommander->SetUpInputLayout(m_pImpl->m_pInputLayoutManager->GetInputLayout(rID.m_InputLayoutID));
	m_pImpl->m_pDrawingCommander->SetUpPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_pImpl->m_pConstantBufferManager->WriteConstantBuffer(rID.m_ConstantBufferID, pConstantBufferInfo);
	m_pImpl->m_pDrawingCommander->SetUpConstantBuffer(m_pImpl->m_pConstantBufferManager->GetConstantBuffer(rID.m_ConstantBufferID));
	m_pImpl->m_pDrawingCommander->SetUpSamplerState(m_pImpl->m_pSampleStateManager->GetDefaultSamplerState());
	m_pImpl->m_pDrawingCommander->SetUpTexture(m_pImpl->m_pTextureManager->GetTextureRV(rID.m_TextureID));
	m_pImpl->m_pModel2DStorage->GetModel2DData(rID.m_ModelID)->Draw();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

DX11GraphicsLibrary::DX11GraphicsLibrary()
	: m_pImpl(nullptr)
{}

DX11GraphicsLibrary::~DX11GraphicsLibrary()
{
	SafeDelete(m_pImpl);
}

}	// namespace sl

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
