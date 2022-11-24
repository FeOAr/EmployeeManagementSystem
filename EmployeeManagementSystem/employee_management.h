#pragma once
#include<iostream>
#include"worker.h"
#include <fstream>

#define  FILENAME "emp_file.txt"
using namespace std;  //注意命名空间

class EmployeeManage {
public:
	EmployeeManage();
	void showMenu();  //菜单
	void addEmployee();  //增加人员
	void addEmployeeCore(string, int, int);  //增加人员功能核心
	void save();  //写入存储文件
	int getEmpNum();  //统计本地文件已存储人数
	void initEmployee();  //从存储文件载入数据
	void showEmployee();  //显示职员
	void fileEmpty();  //文件判空
	void deleteEmployee();  //删除职员
	//void deleteEmployeeCore();  //删除功能核心
	DLinklist searchEmployeeCore(int, string);  //查找功能核心
	void findEmployee();  //查找职员
	void editEmlpoyeeInfo();
	void sortEmployee();  //排序功能
	void sortEmployeeCore(DLinklist, DLinklist);  //排序功能核心
	void cleanFile();
	void exitSystem();  //退出
	void testForPrior();  //测试前向指针
	~EmployeeManage();
public:
	int empNum;  //统计人数
	DNode empHead;	/*链表头节点，此处感觉不需要使用头指针，因为头节点包含于对象内，不会弄丢*/
	bool fileEmptyFlag;  //false = 空 true = 非空
};