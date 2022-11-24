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
		cout << "请输入选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			object.exitSystem();
			break; //退出
		case 1:	   //添加职工
			object.addEmployee();
			break;
		case 2: //显示职工
			object.showEmployee();
			break;
		case 3: //删除职工
			object.deleteEmployee();
			break;
		case 4: //修改职工
			object.editEmlpoyeeInfo();
			break;
		case 5: //查找职工
			object.findEmployee();
			break;
		case 6: //排序职工
			object.sortEmployee();
			break;
		case 7: //清空文件
			object.cleanFile();
			break;
		default:
			system("cls");
		}
	}
	return 0;
}
