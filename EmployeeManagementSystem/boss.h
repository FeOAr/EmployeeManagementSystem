#pragma once
#include<iostream>
#include "worker.h"

using namespace std;

//�ϰ���
class Boss :public Worker
{
public:

	Boss(string name, int wId, int depId);

	//��ʾ������Ϣ
	virtual void showInfo();

	//��ȡְ����λ����
	virtual string getDeptName();
};
