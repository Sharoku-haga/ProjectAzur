//==================================================================================================================================//
//!< @file		paVertexDataFile.cpp
//!< @brief		pa::VertexDataFileクラスの実装
//!< @author	T.Haga
//!< @data		作成日時：2017/11/28	更新履歴：
//==================================================================================================================================//

/* Includes --------------------------------------------------------------------------------------------------- */

#include <iostream>
#include "paVertexDataFile.h"

namespace pa
{

/* Public Functions ------------------------------------------------------------------------------------------- */

void VertexDataFile::Initialize(const std::string& rFileDirectoryPath)
{
	m_FileDirectoryPath = rFileDirectoryPath;
	ReleaseDataALL();						// ここでデータを全て解放しておく
}

bool VertexDataFile::LoadDataFile(const std::string& rFileName)
{
	using namespace std;

	if(m_VertexDatas.find(rFileName) != m_VertexDatas.end())
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

	map<int, VertexData> &rDatas = m_VertexDatas[rFileName];

	int vertexID = 0;			// VertexIDを格納する変数
	for(int count = 0; count < dataCount; ++count)
	{
		std::fread(&vertexID, sizeof(int), 1, fp);
		std::fread(&rDatas[vertexID], sizeof(VertexData), 1, fp);
	}

	std::fclose(fp);
	
	return true;
}

void VertexDataFile::ReleaseData(const std::string& rFileName)
{
	m_VertexDatas[rFileName].clear();
}

void VertexDataFile::ReleaseDataALL()
{
	for(auto& datas : m_VertexDatas)
	{
		datas.second.clear();
	}
	
	m_VertexDatas.clear();
}

}	// namespace pa

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
