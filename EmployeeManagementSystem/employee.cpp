#include "employee.h"

Employee::Employee(string name, int wId, int depId)
{
	this->name = name;
	this->workerId = wId;
	this->departmentId = depId;
}

void Employee::showInfo()
{
	cout << "ְ����ţ� " << this->workerId
		<< "\tְ�������� " << this->name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ����ɾ�����������" << endl;
}

string Employee::getDeptName()
{
	return string("Ա��");
}