#include "manager.h"

Manager::Manager(string name, int wId, int depId)
{
	this->name = name;
	this->workerId = wId;
	this->departmentId = depId;
}

void Manager::showInfo()
{
	cout << "ְ����ţ� " << this->workerId
		<< "\tְ�������� " << this->name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ������ϰ彻��������,���·������Ա��" << endl;
}

string Manager::getDeptName()
{
	return string("����");
}