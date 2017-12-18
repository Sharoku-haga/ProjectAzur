//==================================================================================================================================//
//!< @file		paEnergyGauge.cpp
//!< @brief		pa::EnergyGaugeクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/18	更新履歴：2017/12/19
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <D3DX11.h>
#include <D3DX10.h>
#include "paEnergyGauge.h"
#include "../../../paObjDrawingData.h"
#include "paGaugeFlame.h"
#include "paEnergyBlock.h"
#include "../../../DrawingResrcDataFile/paDrawingResrcDataFile.h"

namespace pa
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const		D3DXVECTOR2		InitialPos			= { 1600.0f, 0.0f };			// ゲージの初期座標(矩形の左上)			

}

/* Public Functions ------------------------------------------------------------------------------------------- */

EnergyGauge::EnergyGauge(const sl::DrawingID& rIDs
						, const std::string&	rResrcDataFilePath)
	: m_pDrawingData(new ObjDrawingData())
	, m_ResrcDataFilePath(rResrcDataFilePath)
{
	m_pDrawingData->m_IDs = rIDs;
}

EnergyGauge::~EnergyGauge()
{
	Finalize();
}

void EnergyGauge::Initialize()
{
	// ゲージのフレームの作成
	m_pGaugeFlame.Reset(new GaugeFlame(m_pDrawingData->m_IDs, m_ResrcDataFilePath));

	// ゲージのエネルギーブロック部分の作成

	int				energyBlockCount	= 3;					// ブロックの数
	D3DXVECTOR2		energyBlockStartPos = { 35.0f, 10.0f };		// エネルギーブロック開始座標
	D3DXVECTOR2		diffPos				= { 0.0f, 0.0f };		// 差分座標を格納する変数
	float			energyBlockInterval = 10.0f;				// エネルギーブロックの間隔
	int				resrcDataID			= 10;					// エネルギーブロックリソースID

	DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(m_ResrcDataFilePath, resrcDataID);

	for(int count = 0; count < energyBlockCount; ++ count)
	{
		diffPos.x = energyBlockStartPos.x + energyBlockInterval * count + rResrc.m_Width * count;
		diffPos.y = energyBlockStartPos.y;
		m_pEnergyBlocks.emplace_back(new EnergyBlock(m_pDrawingData->m_IDs, m_ResrcDataFilePath, diffPos));
	}

	m_pDrawingData->m_Pos = InitialPos;

	int	 drawTaskPriority = 10;		// 描画タスクの優先度
	m_pDrawingData->m_pTask.Reset(new DrawTask(drawTaskPriority, std::bind(&pa::EnergyGauge::Draw, this)));
}

void EnergyGauge::Update()
{
	// 現在は空関数
}

void EnergyGauge::Finalize()
{
	std::vector<sl::UniquePtr<EnergyBlock
							, sl::DefaultDeleter<EnergyBlock>>>().swap(m_pEnergyBlocks);
}

/* Private Functions ------------------------------------------------------------------------------------------ */

void EnergyGauge::Draw()
{
	m_pGaugeFlame->Draw(m_pDrawingData->m_Pos);
	for(auto& pEnergyBlock : m_pEnergyBlocks)
	{
		pEnergyBlock->Draw(m_pDrawingData->m_Pos);
	}
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
