//==================================================================================================================================//
//!< @file		slDX11GraphicsLibrary.h
//!< @brief		sl::DX11GraphicsLibraryクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/07	更新履歴：2017/11/12
//==================================================================================================================================//

#ifndef SL_DX11_GRAPHICS_LIBRARY_H
#define SL_DX11_GRAPHICS_LIBRARY_H

#include <vector>
#include <d3dx11.h>
#include <d3dx10.h>
#include "../../Utility/slDefine.h"
#include "../../Utility/slRect.h"
#include "../../Singleton/slBasicSingleton.h"
#include "../slGraphicsDeclaration.h"
#include "../slGraphicsID.h"

namespace sl
{

struct WindowHandle;

//===================================================================================//
//!< DirectX11を使用したグラフィックスライブラリ
//!< Pimplイディオムを用いる
//===================================================================================//
class DX11GraphicsLibrary : public BasicSingleton<DX11GraphicsLibrary>
{

public:
	//-----------------------------------------------------------------//
	// ライブラリ共通関連
	//-----------------------------------------------------------------//

	/** 
	* 初期化関数 
	* @param[in] rHandle			関連付けたいウィンドウハンドル
	* @param[in] rBackBufferSize	設定したいバックバッファのサイズ
	*/
	void Init(const WindowHandle& rHandle, const fRect& rBackBufferSize);

	/** 
	* 出力スクリーンモードを変更する関数
	* @param[in] isFullScreen		true→フルスクリーン, false→ウィンドウ
	*/
	void ChangeScreenMode(bool isFullScreen);

	/**
	* バックバッファサイズを取得する関数
	* @return バックバッファのサイズ
	*/
	const fRect& GetBackBufferSize();

	//-----------------------------------------------------------------//
	// テクスチャー関連
	//-----------------------------------------------------------------//

	/** 
	* テクスチャーを読み込む関数 
	* @param[in] pFileName テクスチャーのファイル名
	* @return 登録したID
	*/
	TextureID LoadTexture(const t_char* pFileName);

	/** 
	* 指定したテクスチャーを解放する関数 
	* @param[in] rID 登録したテクスチャーのID 
	*/
	void ReleaseTexture(const TextureID& rID);

	/**  全てのテクスチャーを解放する関数 */
	void ReleaseTextureALL();

	//-----------------------------------------------------------------//
	// シェーダー関連関数
	//-----------------------------------------------------------------//

	/** 
	* バーテックスシェーダーを生成する関数
	* @param[in] pFilePath			シェーダーファイルへのパス
	* @param[in] pShaderFuncName	シェーダー関数名
	* @return バーテックスシェーダーID
	*/
	VertexShaderID CreateVertexShader(const t_char* pFilePath, const t_char* pShaderFuncName);

	/** 
	* 入力頂点レイアウトを生成する関数
	* @param[in] pVertexShaderFilePath	バーテックスシェーダーファイルへのパス
	* @param[in] pVertexShaderFuncName	バーテックスシェーダーの関数名
	* @param[in] pInputElementDesc		入力頂点レイアウト構成を格納した配列の先頭ポインタ
	* @param[in] elementDescSize		入力頂点レイアウト構成を格納した配列のサイズ
	* @return 入力頂点レイアウトのID
	*/
	InputLayoutID CreateInputLayout(const t_char* pVertexShaderFilePath
								, const t_char* pVertexShaderFuncName
								, D3D11_INPUT_ELEMENT_DESC* pInputElementDesc
								, unsigned int elementDescSize);

	/** 
	* ピクセルシェーダーを生成する関数
	* @param[in] pFilePath			シェーダーファイルへのパス
	* @param[in] pShaderFuncName	シェーダーの関数名
	* @return ピクセルシェーダーID
	*/
	PixelShaderID CreatePixelShader(const t_char* pFilePath, const t_char* pShaderFuncName);

	/**
	* コンスタントバッファ生成関数
	* @param[in] constantBufferSize コンスタントバッファサイズ
	*/
	ConstantBufferID CreateConstantBuffer(unsigned int constantBufferSize);

	/** 
	* 指定したバーテックスシェーダーを解放する関数 
	* @param[in] rID 登録したバーテックスシェーダーのID 
	*/
	void ReleaseVertexShader(const VertexShaderID & rID);

	/** 
	* 指定した入力頂点レイアウトを解放する関数 
	* @param[in] rID 登録した入力頂点レイアウトのID 
	*/
	void ReleaseInputLayout(const InputLayoutID & rID);

	/** 
	* 指定したピクセルシェーダーを解放する関数 
	* @param[in] rID 登録したピクセルシェーダーのID 
	*/
	void ReleasePixelShader(const PixelShaderID& rID);

	/**
	* 指定したコンスタントバッファーを解放する関数
	* @param[in] rID 解放したいコンスタントバッファーのID
	*/
	void ReleaseConstantBuffer(const ConstantBufferID& rID);

	/**  全てのバーテックスシェーダーを解放する関数 */
	void ReleaseVertexShaderALL();

	/**  全ての入力頂点レイアウトを解放する関数 */
	void ReleaseInputLayoutALL();

	/**  全てのピクセルシェーダーを解放する関数 */
	void ReleasePixelShaderALL();

	/** 全てのコンスタントバッファーを解放する関数 */
	void ReleaseConstantBufferALL();

	//-----------------------------------------------------------------//
	// 2Dモデル関連
	//-----------------------------------------------------------------//

	/**
	* モデル2Dの頂点数を取得する関数<br>
	* モデル作成時にカラー値の配列数などに使用する
	* @return モデル2Dの頂点数
	*/
	int GetModel2DVertexCount();

	/**
	* 2Dモデルを生成する関数
	* @param[in] rData				モデルを作成するためのデータ
	* @return モデルID
	*/
	ModelID CreateDXModel2D(const Model2DCreationData& rData);

	/**
	* 指定したモデルのサイズデータを知らせる（取得する）関数 
	* @param[in] rID			指定したいモデルデータのID
	* @param[out] rSizeData		指定したモデルのサイズデータを格納する変数
	*/
	void InformSizeData(const ModelID& rID, fRect& rSizeData);

	/**
	* 指定したモデルのUVデータを知らせる（取得する）関数
	* @param[in] rID			指定したいモデルデータのID
	* @param[out] rUVData		指定したモデルのUVデータを格納する変数
	*/
	void InformUVData(const ModelID& rID, fRect& rUVData);

	/** 
	* 2Dモデルのサイズデータを設定する関数
	* @param[in] rID			モデルデータのID
	* @param[in] widthSize		設定したい横の大きさ
	* @param[in] heightSize		設定したい縦の大きさ
	*/
	void SetDXModel2DSizeData(const ModelID& rID, float widthSize, float heightSize);

	/**
	* 2DモデルのUVデータを設定する関数
	* @param[in] rID	モデルデータのID
	* @param[in] rUv	設定したいUV値
	*/
	void SetDXModel2DUVData(const ModelID& rID, const fRect& rUv);

	/**
	* 2Dモデルの色データを設定する関数
	* @param[in] rID	モデルデータのID
	* @param[in] rColor	設定したい色
	*/
	void SetDXModel2DColorData(const ModelID& rID, const std::vector<D3DXCOLOR>& rColor);

	/**
	* 指定した2Dモデルを解放する関数
	* @param[in] rID	解放したい2DモデルのID
	*/
	void ReleaseDXModel2D(const ModelID& rID);

	/** 2Dモデルデータを全て解放する関数 */
	void ReleaseDXModel2DALL();

	//-----------------------------------------------------------------//
	// UVアニメーション関連
	//-----------------------------------------------------------------//

	/**
	* UVアニメーションを生成する関数
	* @param[in] rData 生成したいUVアニメーションデータ
	* @return UVアニメーションID
	*/
	UVAnimeID CreateAnimatoin(const UVAnimeCreationData& rData);

	/**
	* UVアニメーションを行う関数
	* @param[in] rModelID		UVアニメーションに対応したモデルのID
	* @param[in] rUVAnimeID		UVアニメーションのID
	* @param[in] isLoop			アニメーションループフラグ true→ループする false→ループしない
	* @return true→アニメーションが更新した false→更新していない
	*/
	bool UpdateUVAnime(const ModelID& rModelID, const UVAnimeID& rUVAnimeID, bool isLoop);

	/**
	* UVアニメーションを初期化する関数 
	* @param[in] rModelID		UVアニメーションに対応したモデルのID
	* @param[in] rUVAnimeID		初期化したいUVアニメーションのID
	*/
	void InitUVAnime(const ModelID& rModelID, const UVAnimeID& rUVAnimeID);

	/**
	* 指定したアニメーションが終了しているかどうかを確認する関数
	* @param[in] rID  確認したいUVアニメーションのID
	* @return true→終了している false →終了していない
	*/
	bool IsEndUVAnimation(const UVAnimeID& rID);

	/**
	* 指定したUVアニメーションを解放する関数
	* @param[in] rID 解放したいUVアニメーションのID
	*/
	void ReleaseUVAnimation(const UVAnimeID& rID);

	/** 現在格納しているUVアニメーション全てを解放する関数 */
	void ReleaseUVAnimationALL();

	//-----------------------------------------------------------------//
	// 描画関連
	//-----------------------------------------------------------------//

	/** 描画開始処理 */
	void StartRender(void);

	/** 描画終了処理 */
	void EndRender(void);

	/** 
	* 2Dモデル描画関数
	* @param[in] rID					登録した頂点情報IDとテクスチャーID
	* @param[in] pConstantBufferinfo	書き込むコンスタントバッファ情報のポインタ
	*/
	void DrawModel2D(const DrawingID& rID, void* pConstantBufferInfo);

private:
	friend class StaticCreation<DX11GraphicsLibrary>;

	class Impl;
    Impl*		m_pImpl;	//!< privateな部分をまとめたもの

	/** Constructor */
	DX11GraphicsLibrary();

	/** Destructor */
	~DX11GraphicsLibrary();

	SL_DISALLOW_COPY_AND_ASSIGN(DX11GraphicsLibrary);

};	// class DX11GraphicsLibrary

}	// namespace sl

#endif	// SL_DX11_GRAPHICS_LIBRARY_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
