#ifndef IX_MANAGER_H_H
#define IX_MANAGER_H_H
#include "RM_Manager.h"
#include "PF_Manager.h"
typedef struct{
	int attrLength;    //��������������ֵ�ĳ���
	int keyLength;    //B+���йؼ��ֵĳ���
	AttrType attrType;   //��������������ֵ������
	PageNum rootPage;   //B+�����ڵ��ҳ���
	int order;     //B+���Ľ���
}IX_FileSubHeader;

typedef struct{
	int is_leaf;          //�ýڵ��Ƿ�ΪҶ�ӽڵ�
	int keynum;           //�ýڵ�ʵ�ʰ����Ĺؼ��ָ���
	PageNum parent;       //ָ�򸸽ڵ����ڵ�ҳ���
	char *keys;			  //ָ��ؼ��ֵ�ָ��
	RID *rids;            //ָ���¼��ʶ����ָ��
}IX_Node;

typedef struct{
	bool bOpen;                         //���ļ�����Ƿ��Ѿ���һ���ļ�����
	PF_FileHandle pfFileHandle;         //ҳ���ļ�����
	PF_PageHandle pfPageHandle_FileHdr; //ͷҳ��Ĳ���
	PageNum pageNum_FileHdr;            //ͷҳ���ҳ���
	IX_FileSubHeader *fileSubHeader;    //�洢�ļ���ͷ�ļ����ݵĸ���
}IX_FileHandle;

typedef struct{
	bool bOpen;                                     //ɨ���Ƿ��
	IX_FileHandle *pIXIndexHandle;                  //ָ������������ָ��
	CompOp compOp;                                  //���ڱȽϵĲ�����
	char *value;                                    //������ֵ���бȽϵ�ֵ
	ClientHint pinHint;                             //���ڼ�¼�������ָ��ҳ��Ĺ̶�����
	int N;                                          // �̶��ڻ������е�ҳ����ָ����ҳ��̶������й�
	int pinnedPageCount;                            // ʵ�ʹ̶��ڻ�������ҳ����
	PF_PageHandle pfPageHandles[PF_BUFFER_SIZE];    // �̶��ڻ�����ҳ������Ӧ��ҳ��������
	int phIx;                                       //��ǰ��ɨ��ҳ���ҳ��������
	int ridIx;
	PageNum pnNext;      //��һ������д�뻺���ҳ���
}IX_IndexScan;

RC IX_CreateFile(char *fileName, AttrType attrType, int attrLength);
RC IX_OpenFile(char *fileName, IX_FileHandle *indexHandle);
RC IX_CloseFile(IX_FileHandle *indexHandle);
//���������

//ɨ��
RC OpenIndexScan(IX_IndexScan *indexScan, IX_FileHandle *indexhandle, CompOp compOp, char *value, ClientHint pinHint);
RC IX_GetNextEntry(IX_IndexScan *indexScan, RID *rid);

//������ɾ��
RC InsertEntry(IX_FileHandle *indexHandle, void *pData, RID *rid);
RC DeleteEntry(IX_FileHandle *indexHandle, void *pData, RID *rid);

//���Ѻ���
IX_FileHandle * splitPage(IX_FileHandle *indexHandle, void *pData, RID *rid);//��ҳ,ֻ�����������root��ֱ�ӹ�ϵ��

#endif