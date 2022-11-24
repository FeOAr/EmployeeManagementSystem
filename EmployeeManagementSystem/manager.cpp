#include "manager.h"

Manager::Manager(string name, int wId, int depId)
{
	this->name = name;
	this->workerId = wId;
	this->departmentId = depId;
}

void Manager::showInfo()
{
	cout << "职工编号： " << this->workerId
		<< "\t职工姓名： " << this->name
		<< "\t岗位：" << this->getDeptName()
		<< "\t岗位职责：完成老板交给的任务,并下发任务给员工" << endl;
}

string Manager::getDeptName()
{
	return string("经理");
}