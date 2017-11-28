//==================================================================================================================================//
//!< @file		paDrawingDataFile.cpp
//!< @brief		pa::DrawingDataFileクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/11/28	更新履歴：2017/11/29
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <iostream>
#include "paDrawingDataFile.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

void DrawingDataFile::Initialize(const std::string& rFileDirectoryPath)
{
	m_FileDirectoryPath = rFileDirectoryPath;
	ReleaseDataALL();						// ここでデータを全て解放しておく
}

bool DrawingDataFile::LoadDataFile(const std::string& rFileName)
{
	using namespace std;

	if(m_DrawingDatas.find(rFileName) != m_DrawingDatas.end())
	{	// すでにファイルをロードしているならtrueを返す
		return true;
	}

	// ファイルﾊﾟｽを作成する
	string filePath = m_FileDirectoryPath + string("/");
	filePath = filePath + rFileName;

	FILE* fp;
	fopen_s(&fp, filePath.c_str(), "rb");

	if(fp == nullptr)
	{	// ファイル読み込み失敗したらfalse
		return false;
	}

	//	データ数を読み込む
	short dataCount = 0;
	std::fread(&dataCount, sizeof(short), 1, fp);
	if(dataCount == 0)
	{	// データ数が0なら失敗
		return false;
	}

	map<int, DrawingData> &rDatas = m_DrawingDatas[rFileName];

	int drawingDataID = 0;			// 描画データIDを格納する変数
	for(int count = 0; count < dataCount; ++count)
	{
		std::fread(&drawingDataID, sizeof(int), 1, fp);
		std::fread(&rDatas[drawingDataID], sizeof(DrawingData), 1, fp);
	}

	std::fclose(fp);
	
	return true;
}

void DrawingDataFile::ReleaseData(const std::string& rFileName)
{
	m_DrawingDatas[rFileName].clear();
	m_DrawingDatas.erase(rFileName);
}

void DrawingDataFile::ReleaseDataALL()
{
	for(auto& datas : m_DrawingDatas)
	{
		datas.second.clear();
	}
	
	m_DrawingDatas.clear();
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
