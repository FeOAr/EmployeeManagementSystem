#pragma once
#include "worker.h"
#include <iostream>
using namespace std;

class Manager : public Worker
{
public:
	Manager(string name, int workerId, int depId);
	virtual void showInfo();	  //��ʾ������Ϣ
	virtual string getDeptName(); //��ȡ��λ����
};