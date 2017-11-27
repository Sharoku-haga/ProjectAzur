//==================================================================================================================================//
//!< @file		paVeretxDataFile.h
//!< @brief		pa::VertexDataFileクラスのヘッダ
//!< @author	T.Haga
//!< @data		作成日時：2017/11/28	更新履歴：
//==================================================================================================================================//

#ifndef PA_VERTEX_DATA_FILE_H
#define PA_VERTEX_DATA_FILE_H

#include <string>
#include <map>

namespace pa
{

struct VertexData
{

};	// struct VertexData

//===================================================================================//
//!< ツールが作成するVertexに関するデータファイルを管理するクラス 
//===================================================================================//
class VertexDataFile
{

public:
	/** Contructor */
	VertexDataFile();

	/** Destructor */
	~VertexDataFile();

	/**
	* データファイルをロードする関数
	* @param[in] rFilePath データファイルのパス
	* @return 結果 true→成功 false→失敗
	*/
	bool LoadDataFile(const std::string& rFilePath);

	VertexData& GetVertexData(const std::string& rFilePath, int id);

	void ReleaseDataFile(const std::string& rFilePath);

	void ReleaseDataFileALL();

private:
	std::map< std::string, std::map<int, VertexData> > m_VertexDatas;			//!< VertexDataを格納しているmap.intはID

};	// class VertexDataFile

}	// namespace pa

#endif // PA_VERTEX_DATA_FILE_H

//==================================================================================================================================//
// END OF FILE
//==================================================================================================================================//
