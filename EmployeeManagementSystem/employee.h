#pragma once
#include<iostream>
#include<string>
#include "worker.h"
using namespace std;

//职工抽象基类
class Employee : public Worker
{
public:
	Employee(string name, int workerId, int depId);
	virtual void showInfo();  //显示个人信息
	virtual string getDeptName();  //获取岗位名称
};