//==================================================================================================================================//
//!< @file		paTitleScene.cpp		
//!< @brief		paTitleSceneクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/11/18	更新履歴：2017/12/02
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include "sl/Library/Graphics/DX11GraphicsLibrary/slDX11GraphicsLibrary.h"
#include "sl/Library/Graphics/slGraphicsID.h"
#include "sl/Library/Graphics/slGraphicsDeclaration.h"
#include "sl/Library/InputDevice/IInputDeviceLibrary/slIInputDeviceLibrary.h"
#include "sl/Library/Scene/slSceneManager.h"
#include "paTitleScene.h"
#include "../DrawTask/paDrawTaskManager.h"
#include "TitleBackground/paTitleBackground.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

TitleScene::TitleScene()
	: m_rGraphicsLibrary(sl::DX11GraphicsLibrary::Instance())
	, m_rInputDeviceLibrary(sl::IInputDeviceLibrary::Instance())
	, m_rDrawTaskManager(DrawTaskManager::Instance())
{}

void TitleScene::Enter()
{
	using namespace sl;

	DrawingID		ids;
	// バーテックスシェーダーファイルの読み込み
	ids.m_VertexShaderID = m_rGraphicsLibrary.CreateVertexShader("../Resource/dx11CommonVS.hlsl", "VS");

	// 頂点インプットレイアウトの作成
	D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,						D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, sizeof(D3DXVECTOR3),						D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, sizeof(D3DXVECTOR3) + sizeof(D3DXCOLOR),		D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	ids.m_InputLayoutID = m_rGraphicsLibrary.CreateInputLayout("../Resource/dx11CommonVS.hlsl", "VS", InputElementDesc, 3);

	//  ピクセルシェーダーファイルの読み込み
	ids.m_PixelShaderID = m_rGraphicsLibrary.CreatePixelShader("../Resource/dx11CommonPS.hlsl", "PS");

	// コンスタントバッファの読み込み
	ids.m_ConstantBufferID = m_rGraphicsLibrary.CreateConstantBuffer(sizeof(Basic2DConstantBuffer));

	// 描画タスクの初期化
	int priorityNumMax = 5;
	m_rDrawTaskManager.Initialize(5);

	// タイトル背景の作成
	m_pObject.emplace_back(new TitleBackground(ids));

	// オブジェクトの初期化
	for(auto& pObj : m_pObject)
	{
		pObj->Initialize();
	}

}

void TitleScene::Exit()
{
	for(auto& pObj : m_pObject)
	{
		pObj->Finalize();
	}

	m_rDrawTaskManager.DeleteALL();

	m_rGraphicsLibrary.ReleaseConstantBufferALL();
	m_rGraphicsLibrary.ReleasePixelShaderALL();
	m_rGraphicsLibrary.ReleaseInputLayoutALL();
	m_rGraphicsLibrary.ReleaseVertexShaderALL();
	m_rGraphicsLibrary.ReleaseTextureALL();
	m_rGraphicsLibrary.ReleaseDXModel2DALL();
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void TitleScene::Control()
{
	m_rInputDeviceLibrary.UpdateInputDeviceState();

	for(auto& pObj : m_pObject)
	{
		pObj->Update();
	}

	if(m_rInputDeviceLibrary.CheckKeyState(sl::K_RETURN, sl::PUSH))
	{
		sl::SceneManager::Instance().End();
	}
}

void TitleScene::Draw()
{
	m_rGraphicsLibrary.StartRender();

	m_rDrawTaskManager.Run();

	m_rGraphicsLibrary.EndRender();
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
