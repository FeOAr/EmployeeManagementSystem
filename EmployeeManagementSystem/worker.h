#pragma once
#include<iostream>
#include<string>
using namespace std;

//ְ���������
class Worker
{
public:

	//��ʾ������Ϣ
	virtual void showInfo() = 0;
	//��ȡ��λ����
	virtual string getDeptName() = 0;

	int workerId; //ְ�����
	string name; //ְ������
	int departmentId; //ְ�����ڲ������Ʊ��
};

typedef struct DNode {
	Worker* data;  //����ָ��
	struct DNode* prior, * next;  //ǰ�����ָ��
}DNode, *DLinklist;