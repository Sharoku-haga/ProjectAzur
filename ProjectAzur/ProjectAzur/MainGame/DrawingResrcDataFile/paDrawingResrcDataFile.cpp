//==================================================================================================================================//
//!< @file		paDrawingResrcDataFile.cpp
//!< @brief		pa::DrawingResrcDataFileクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/11/28	更新履歴：2017/11/29
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <iostream>
#include "paDrawingResrcDataFile.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

void DrawingResrcDataFile::Initialize(const std::string& rFileDirectoryPath)
{
	m_FileDirectoryPath = rFileDirectoryPath;
	ReleaseDataALL();						// ここでデータを全て解放しておく
}

bool DrawingResrcDataFile::LoadDataFile(const std::string& rFileName)
{
	using namespace std;

	if(m_DrawingResrcDatas.find(rFileName) != m_DrawingResrcDatas.end())
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

	map<int, DrawingResrcData> &rDatas = m_DrawingResrcDatas[rFileName];

	int drawingDataID = 0;			// 描画データIDを格納する変数
	for(int count = 0; count < dataCount; ++count)
	{
		std::fread(&drawingDataID, sizeof(int), 1, fp);
		std::fread(&rDatas[drawingDataID], sizeof(DrawingResrcData), 1, fp);
	}

	std::fclose(fp);
	
	return true;
}

void DrawingResrcDataFile::ReleaseData(const std::string& rFileName)
{
	m_DrawingResrcDatas[rFileName].clear();
	m_DrawingResrcDatas.erase(rFileName);
}

void DrawingResrcDataFile::ReleaseDataALL()
{
	for(auto& datas : m_DrawingResrcDatas)
	{
		datas.second.clear();
	}
	
	m_DrawingResrcDatas.clear();
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
