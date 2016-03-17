#pragma once
#include "sqlite3.h"
#include "iostream"
#include <vector>
#include <map>
#include "cocos2d.h"
#include "TableDetail.h"
USING_NS_CC;

 
class DBUtil {
     
private:
     
    //���ݿ�
    sqlite3* m_pDataBase;
     
private:
     
     
    DBUtil();
     
    virtual ~DBUtil();
     
    public :
     
     
    static DBUtil* getInstance();
     
    static void destoryInstance();
     
     
    /**
     *  �����ݿ�(����)
     *
     *  @param aDataBaseName ���ݿ���
     */
    void openDBWithName(std::string aDataBaseName);
     
    /**
     *  �ر����ݿ�
     */
    void closeDB();
     
    /**
     *  �������ݱ�
     *
     *  @param aSql       ����sql���
     *  @param aTableName ����
     */
    void createTable(std::string aSql, std::string aTableName);
     
    /**
     *  ͨ��������ѯ�ñ��Ƿ����
     *
     *  @param aTabelName ����
     *
     *  @return true: ���� false: ������
     */
    bool isExistTableByName(std::string aTabelName);
     
    /**
     *  ɾ�����ݱ�
     *
     *  @param aSql       ɾ��sql���
     *  @param aTableName ����
     */
    void deleteTable(std::string aSql, std::string aTableName);
     
    /**
     *  �����¼
     *
     *  @param aSql ��������sql���
     */
    void insertData(std::string aSql);
     
    /**
     *  ɾ����¼
     *
     *  @param aSql ɾ������sql���
     */
    void deleteData(std::string aSql);
     
    /**
     *  �޸ļ�¼
     *
     *  @param aSql �޸�����sql���
     */
    void updateData(std::string aSql);
     
    /**
     *  ��ѯ��¼
     *
     *  @param aSql     �޸�����sql���
     */
    std::vector<std::map<std::string, std::string> >searchData(std::string aSql);
     
    /**
     *  ��ѯ��¼������
     *
     *  @param sql ��ѯ��¼sql���
     *
     *  @return ��¼����
     */
    int searchDataCount(std::string aSql);
     
    /**
     *  ��ʼ����
     *
     *  @return �������(sqlite3�ṩ�ĺ�)
     */
    int beginTransaction();
     
    /**
     *  �ύ����(ʧ�ܻع�)
     *
     *  @param aResult       �������
     *
     *  @return �������(sqlite3�ṩ�ĺ�)
     */
    int comitTransaction(int aResult);
	/**
     *  ������
     *
     *  @param tablename ����
     *  @param tableDetail ��ṹ Vector<TableDetail*>
     *  
     */
	void CreateTable(std::string tablename , std::vector<TableDetail*> tableDetail);
     
};
