#pragma once
#include<iostream>
#include<string>
#include "worker.h"
using namespace std;

//ְ���������
class Employee : public Worker
{
public:
	Employee(string name, int workerId, int depId);
	virtual void showInfo();  //��ʾ������Ϣ
	virtual string getDeptName();  //��ȡ��λ����
};