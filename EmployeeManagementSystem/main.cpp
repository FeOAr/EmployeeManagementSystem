#include <iostream>
#include "employee_management.h"

using namespace std;

int main()
{
	EmployeeManage object;
	int choice;
	while (true)
	{
		object.showMenu();
		cout << "������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			object.exitSystem();
			break; //�˳�
		case 1:	   //���ְ��
			object.addEmployee();
			break;
		case 2: //��ʾְ��
			object.showEmployee();
			break;
		case 3: //ɾ��ְ��
			object.deleteEmployee();
			break;
		case 4: //�޸�ְ��
			object.editEmlpoyeeInfo();
			break;
		case 5: //����ְ��
			object.findEmployee();
			break;
		case 6: //����ְ��
			object.sortEmployee();
			break;
		case 7: //����ļ�
			object.cleanFile();
			break;
		default:
			system("cls");
		}
	}
	return 0;
}
