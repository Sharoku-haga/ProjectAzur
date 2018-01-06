//==================================================================================================================================//
//!< @file		paColliderBase.h
//!< @brief		pa::ColliderBaseクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2018/01/05	更新履歴：2018/01/06
//==================================================================================================================================//

#ifndef PA_COLLIDER_BASE_H
#define PA_COLLIDER_BASE_H

#include <string>
#include <D3DX11.h>
#include <D3DX10.h>
#include "sl/Library/Utility/slRect.h"

namespace pa
{

//===================================================================================//
//!< 衝突処理クラス
//!< 基底クラス
//===================================================================================//
class ColliderBase
{

public:
	/** 
	* Constructor
	* @param[in] rTypeName Colliderのタイプ名
	*/
	explicit ColliderBase(const std::string& rTypeName);

	/** Destructor */
	virtual ~ColliderBase() = default;

	/** 初期化関数 */
	virtual void Initialize() = 0;

	/** 
	* 衝突処理を行う関数
	* 衝突した際に呼ばれる
	* @param[in] rCollider	衝突したCollider
	*/
	virtual void ProcessCollision(ColliderBase& rCollider) = 0;

	/**
	* Getter 
	* @return Colliderのタイプ(継承クラスの種類)名 
	*/
	inline const std::string& GetTypeName() { return m_TypeName; }

	/**
	* Getter 
	* @return 現在の矩形データ
	*/
	inline const sl::fRect& GetCurrentRectData() { return m_CurrentRectData; }

protected:
	/**
	* Setter
	* @param[in] rPos 位置座標
	*/
	inline void SetPos(const D3DXVECTOR2&	rPos) { m_Pos = rPos; }

	/**
	* Setter
	* @param[in] rSize サイズ
	*/
	inline void SetSize(const sl::fRect& rSize) { m_Size = rSize; }

	/**
	* Setter
	* @param[in] rAngle 角度
	*/
	inline void SetAngle(const float& rAngle) { m_Angle = rAngle; }

	/** 現在の矩形データを更新する関数 */
	void UpdateCurrentRectData();

private:
	std::string		m_TypeName;				//!< Colliderのタイプ(継承クラスの種類)名
	D3DXVECTOR2		m_Pos;					//!< 位置座標
	sl::fRect		m_Size;					//!< このColliderのサイズ
	float			m_Angle;				//!< 角度
	sl::fRect		m_CurrentRectData;		//!< 現在の矩形データ(m_RectSize + Pos)

};	// class ColliderBase

}	// namespace pa

#endif	// PA_COLLIDER_BASE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
