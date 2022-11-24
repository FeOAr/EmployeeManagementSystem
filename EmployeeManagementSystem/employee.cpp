#include "employee.h"

Employee::Employee(string name, int wId, int depId)
{
	this->name = name;
	this->workerId = wId;
	this->departmentId = depId;
}

void Employee::showInfo()
{
	cout << "职工编号： " << this->workerId
		<< "\t职工姓名： " << this->name
		<< "\t岗位：" << this->getDeptName()
		<< "\t岗位职责：完成经理交给的任务" << endl;
}

string Employee::getDeptName()
{
	return string("员工");
}