#pragma once
#include "worker.h"
#include <iostream>
using namespace std;

class Manager : public Worker
{
public:
	Manager(string name, int workerId, int depId);
	virtual void showInfo();	  //显示个人信息
	virtual string getDeptName(); //获取岗位名称
};