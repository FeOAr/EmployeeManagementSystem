#pragma once
#include<iostream>
#include"worker.h"
#include <fstream>

#define  FILENAME "emp_file.txt"
using namespace std;  //ע�������ռ�

class EmployeeManage {
public:
	EmployeeManage();
	void showMenu();  //�˵�
	void addEmployee();  //������Ա
	void addEmployeeCore(string, int, int);  //������Ա���ܺ���
	void save();  //д��洢�ļ�
	int getEmpNum();  //ͳ�Ʊ����ļ��Ѵ洢����
	void initEmployee();  //�Ӵ洢�ļ���������
	void showEmployee();  //��ʾְԱ
	void fileEmpty();  //�ļ��п�
	void deleteEmployee();  //ɾ��ְԱ
	DLinklist searchEmployeeCore(int, string);  //���ҹ��ܺ���
	void findEmployee();  //����ְԱ
	void editEmlpoyeeInfo();
	void sortEmployee();  //������
	void sortEmployeeCore(DLinklist, DLinklist);  //�����ܺ���
	void cleanFile();
	void exitSystem();  //�˳�
	void testForPrior();  //����ǰ��ָ��
	~EmployeeManage();
public:
	int empNum;  //ͳ������
	DNode empHead;	/*����ͷ�ڵ㣬�˴��о�����Ҫʹ��ͷָ�룬��Ϊͷ�ڵ�����ڶ����ڣ�����Ū��*/
	bool fileEmptyFlag;  //false = �� true = �ǿ�
};