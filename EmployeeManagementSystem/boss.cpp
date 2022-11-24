#include "boss.h"

Boss::Boss(string name, int wId, int depId)
{
	this->name = name;
	this->workerId = wId;
	this->departmentId = depId;
}

void Boss::showInfo()
{
	cout << "职工编号： " << this->workerId
		<< "\t职工姓名： " << this->name
		<< "\t岗位：" << this->getDeptName()
		<< "\t岗位职责：管理公司所有事务" << endl;
}

string Boss::getDeptName()
{
	return string("总裁");
}