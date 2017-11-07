//==================================================================================================================================//
//!< @file		slDXConstantBufferManager.h		
//!< @brief		sl::DXConstantBufferManagerクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/10/04	更新履歴：
//==================================================================================================================================//

#ifndef SL_DX_CONSTANT_BUFFER_MANAGER_H
#define SL_DX_CONSTANT_BUFFER_MANAGER_H

#include <d3dx11.h>
#include <d3dx10.h>
#include <vector>
#include <functional>
#include "../../../../Utility/slTypes.h"
#include "../../../slGraphicsID.h"

namespace sl
{

//===================================================================================//
//!< DirectXのコンスタントバッファーを管理するクラス
//===================================================================================//
class DXConstantBufferManager
{

public:
	/** 
	* Constructor 
	* @param[in] pDevice		DirectXのデバイス
	* @param[in] pDeviceContext DirectXのデバイスコンテキスト
	*/
	DXConstantBufferManager(ID3D11Device*	pDevice, ID3D11DeviceContext*	pDeviceContext);

	/** Destructor */
	~DXConstantBufferManager();

	/**
	* コンスタントバッファ生成関数
	* @param[in] constantBufferSize コンスタントバッファサイズ
	* @param[in] func				コンスタントバッファに情報を書き込む関数のポインタ
	*/
	ConstantBufferID CreateConstantBuffer(unsigned int constantBufferSize);

	/**
	* 指定したコンスタントバッファーに情報を書き込む関数
	* @param[in] rID					情報を書き込みたいコンスタントバッファのID
	* @param[in] pConstantBufferinfo	書き込むコンスタントバッファ情報のポインタ
	*/
	void WriteConstantBuffer(const ConstantBufferID& rID, void*	pConstantBufferInfo);

	/**
	* 指定したコンスタントバッファを取得する関数
	* @param[in] riD 取得したいコンスタントバッファのID
	* @return 指定したコンスタントバッファ
	*/
	ID3D11Buffer*	GetConstantBuffer(const ConstantBufferID& rID) 
	{ 
		return m_pConstantBufferData[rID.m_Num]->m_pBuffer; 
	}

	/**
	* 指定したコンスタントバッファーを解放する関数
	* @param[in] rID 解放したいコンスタントバッファーのID
	*/
	void Release(const ConstantBufferID& rID);

	/** 全てのコンスタントバッファーを解放する関数 */
	void ReleaseALL();

private:
	struct ConstantBufferData
	{
		ID3D11Buffer*		m_pBuffer;						//!< コンスタントバッファ
		unsigned int		m_BufferSize;					//!< バッファサイズ 

		ConstantBufferData(ID3D11Buffer* pConstntBuffer
							, unsigned int constantBufferSize)
			: m_pBuffer(pConstntBuffer)
			, m_BufferSize(constantBufferSize)
		{}

	};	//  struct ConstantBufferData
	ID3D11Device*								m_pDevice;					//!< DirectXのデバイス
	ID3D11DeviceContext*						m_pDeviceContext;			//!< DirectXのデバイスコンテキスト
	std::vector<ConstantBufferData*>			m_pConstantBufferData;		//!< コンスタントバッファを格納したvector

};	// class DXConstantBufferManager

}	// namespace sl

#endif	// SL_DX_CONSTANT_BUFFER_MANAGER_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
