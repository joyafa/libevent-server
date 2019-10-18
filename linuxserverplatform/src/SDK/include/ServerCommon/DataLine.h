#pragma once

#include "Lock.h"
#include "InternalMessageDefine.h"

/*
Struct		:ListItemData
Memo		:链表项数据结构
Parameter	:
	stDataHead	:数据包头
	pData		:每个链表项数据的指针，使用用new方式申请的内存，注意，在出队列时，要显式的delete 该内存
*/
struct ListItemData
{
	DataLineHead stDataHead;
	BYTE* pData;
};

//数据队列类
class CDataLine
{
private:
	std::list <ListItemData*> m_DataList;
	CSignedLock	m_csLock;

public:
	CDataLine();
	virtual ~CDataLine();

public:
	//获取锁
	CSignedLock* GetLock() { return &m_csLock; }
	//清理所有数据
	bool CleanLineData();
	//加入消息队列
	virtual UINT AddData(DataLineHead* pDataInfo, UINT uAddSize, UINT uDataKind, const void* pAppendData = NULL, UINT uAppendAddSize = 0);
	//提取消息数据
	virtual UINT GetData(DataLineHead** pDataBuffer);

public:
	size_t GetDataCount();
};