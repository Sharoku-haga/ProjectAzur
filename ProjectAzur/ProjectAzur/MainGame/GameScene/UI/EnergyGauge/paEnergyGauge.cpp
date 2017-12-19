//==================================================================================================================================//
//!< @file		paEnergyGauge.cpp
//!< @brief		pa::EnergyGaugeクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/12/18	更新履歴：2017/12/20
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <D3DX11.h>
#include <D3DX10.h>
#include "paEnergyGauge.h"
#include "../../../paObjDrawingData.h"
#include "paGaugeFlame.h"
#include "paGaugeTimer.h"
#include "paGaugeEffect.h"
#include "EnergyBlock/paEnergyBlock.h"
#include "../../../DrawingResrcDataFile/paDrawingResrcDataFile.h"
#include "../../../EventManager/paEventManager.h"

namespace pa
{

/* Unnamed Namespace ------------------------------------------------------------------------------------------ */

namespace
{

const		D3DXVECTOR2		InitialPos			= { 1600.0f, 0.0f };			// ゲージの初期座標(矩形の左上)	
const		int				EnergyBlockCount	= 3;							// エネルギーブロックの数
const		int				OneEnergyBlockTime	= 3600;							// エネルギーブロック1つ分の時間(3分)			

}

/* Public Functions ------------------------------------------------------------------------------------------- */

EnergyGauge::EnergyGauge(const sl::DrawingID& rIDs
						, const std::string&	rResrcDataFilePath)
	: m_pDrawingData(new ObjDrawingData())
	, m_ResrcDataFilePath(rResrcDataFilePath)
	, m_ProcessingState(NORMAL_PROCESSING)
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
	D3DXVECTOR2		energyBlockStartPos = { 35.0f, 10.0f };		// エネルギーブロック開始座標
	D3DXVECTOR2		diffPos				= { 0.0f, 0.0f };		// 差分座標を格納する変数
	float			energyBlockInterval = 10.0f;				// エネルギーブロックの間隔
	int				resrcDataID			= 10;					// エネルギーブロックリソースID

	DrawingResrcData& rResrc = DrawingResrcDataFile::Instance().GetDrawingData(m_ResrcDataFilePath, resrcDataID);

	for(int count = 0; count < EnergyBlockCount; ++ count)
	{
		diffPos.x = energyBlockStartPos.x + energyBlockInterval * count + rResrc.m_Width * count;
		diffPos.y = energyBlockStartPos.y;
		m_pEnergyBlocks.emplace_back(new EnergyBlock(m_pDrawingData->m_IDs, m_ResrcDataFilePath, diffPos, OneEnergyBlockTime));
	}
	m_CurrentEnergyBlockNum = 0;

	m_pDrawingData->m_Pos = InitialPos;

	int	 drawTaskPriority = 10;		// 描画タスクの優先度
	m_pDrawingData->m_pTask.Reset(new DrawTask(drawTaskPriority, std::bind(&pa::EnergyGauge::Draw, this)));

	// タイマーの作成
	m_pGaugeTimer.Reset(new GaugeTimer(OneEnergyBlockTime));
	m_pGaugeTimer->Initialize();

	// エフェクトの作成
	D3DXVECTOR2 effectDiffPos = {110.f, 0.0f};
	m_pGaugeEffect.Reset(new GaugeEffect(m_pDrawingData->m_IDs, m_ResrcDataFilePath, effectDiffPos));

	m_pGaugeTimer->Start();
}

void EnergyGauge::Update()
{
	switch(m_ProcessingState)
	{
	case NORMAL_PROCESSING:
		RunNormalProcessing();
		break;

	case DAMAGE_PROCESSING:
		RunDamageProcessing();
		break;

	default:
		// do nothing
		break;
	}
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

	m_pGaugeEffect->Draw(m_pDrawingData->m_Pos);
}

void EnergyGauge::RunNormalProcessing()
{
	m_pGaugeTimer->Update();
	int currentTime = 0;
	m_pGaugeTimer->InformCurrentTimeCount(currentTime);

	// 現在のブロックの位置ごとに時間を調整する
	currentTime = currentTime - OneEnergyBlockTime * m_CurrentEnergyBlockNum;

	if(m_pEnergyBlocks[m_CurrentEnergyBlockNum]->DecreaseEnergy(currentTime))
	{
		if(m_CurrentEnergyBlockNum == (EnergyBlockCount - 1))
		{
			// ゲーム終了イベントを飛ばす
			EventManager::Instance().ReceiveEvent("game_end");
			return;
		}

		++m_CurrentEnergyBlockNum;

		if(m_CurrentEnergyBlockNum == (EnergyBlockCount - 1))
		{
			m_pGaugeEffect->ActivateDrawing();
			m_pEnergyBlocks[m_CurrentEnergyBlockNum]->ChangeColorRed();
		}
	}
}

void EnergyGauge::RunDamageProcessing()
{
	m_pGaugeEffect->Update();
	m_pEnergyBlocks[m_CurrentEnergyBlockNum]->EmptyEnergy();

	// エネルギーブロックが最後の1つだったら、ゲーム終了イベントをとばす
	if(m_CurrentEnergyBlockNum == (EnergyBlockCount - 1))
	{
		EventManager::Instance().ReceiveEvent("game_end");
		return;
	}

	++m_CurrentEnergyBlockNum;

	if(m_CurrentEnergyBlockNum == (EnergyBlockCount - 1))
	{
		m_pGaugeEffect->ActivateDrawing();
		m_pEnergyBlocks[m_CurrentEnergyBlockNum]->ChangeColorRed();
	}

	m_pGaugeTimer->ProceedOneEnergyBlockTime();
	int currentTime = 0;
	m_pGaugeTimer->InformCurrentTimeCount(currentTime);
	currentTime = currentTime - OneEnergyBlockTime * m_CurrentEnergyBlockNum;
	m_pEnergyBlocks[m_CurrentEnergyBlockNum]->DecreaseEnergy(currentTime);

	m_ProcessingState = NORMAL_PROCESSING;
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
