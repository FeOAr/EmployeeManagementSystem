#include "boss.h"

Boss::Boss(string name, int wId, int depId)
{
	this->name = name;
	this->workerId = wId;
	this->departmentId = depId;
}

void Boss::showInfo()
{
	cout << "ְ����ţ� " << this->workerId
		<< "\tְ�������� " << this->name
		<< "\t��λ��" << this->getDeptName()
		<< "\t��λְ�𣺹���˾��������" << endl;
}

string Boss::getDeptName()
{
	return string("�ܲ�");
}