#include"employee_management.h"
#include"worker.h"
#include"boss.h"
#include"employee.h"
#include"manager.h"
#include<string>

EmployeeManage::EmployeeManage() {

	fileEmpty();

	this->empNum = 0;
	this->empHead.next = NULL;  //头节点初始化
	this->empHead.prior = NULL;

	if (this->fileEmptyFlag) {
		int num = this->getEmpNum();
		cout << "已读取职工个数为：" << num << endl;
		this->empNum = num;  //更新成员属性
		this->initEmployee();
	}
}

EmployeeManage::~EmployeeManage() {}

void EmployeeManage::showMenu() {
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void EmployeeManage::addEmployee() {

	string name; //职工姓名
	int workerId; //职工编号(局域)
	int depSelect; //所选部门名称编号

	//填充数据
	cout << "输入职工编号: ";
	cin >> workerId;
	cout << "输入职工姓名：";
	cin >> name;
	cout << "请选择该职工的岗位：" << endl;
	cout << "1.普通职工" << "\t2.经理" << "\t3.老板" << endl;
	cin >> depSelect;

	this->addEmployeeCore(name, workerId, depSelect);
	cout << "成功添加" << endl;
	this->save();
	this->fileEmptyFlag = true;
	system("pause");
}

void EmployeeManage::addEmployeeCore(string name, int workerId, int depSelect) {

	DLinklist tempNode = new DNode;
	tempNode->next = NULL;
	tempNode->prior = NULL;
	if (tempNode == NULL)
	{
		cout << "节点新建失败!" << endl;
		exit(0);
	}

	//如果头节点后没有节点
	if (this->empHead.next == NULL) {
		this->empHead.next = tempNode;
		tempNode->prior = &this->empHead;
	}
	else {//头插法
		tempNode->next = this->empHead.next;
		this->empHead.next->prior = tempNode;
		tempNode->prior = &this->empHead;
		this->empHead.next = tempNode;
	}

	switch (depSelect)
	{
	case 1: //普通员工
		tempNode->data = new Employee(name, workerId, 1);  //注意多态
		break;
	case 2: //经理
		tempNode->data = new Manager(name, workerId, 2);
		break;
	case 3:  //老板
		tempNode->data = new Boss(name, workerId, 3);
		break;
	default:
		break;
	}
	tempNode = nullptr;
}

void EmployeeManage::save() {

	DLinklist tempOut;  //输出用
	tempOut = &this->empHead;
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	while (tempOut->next != NULL) {
		tempOut = tempOut->next;
		ofs << tempOut->data->name << " "
			<< tempOut->data->workerId << " "
			<< tempOut->data->departmentId << endl;
	}
	ofs.close();
	cout << "本地文件更新完毕" << endl;
}

int EmployeeManage::getEmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string name;
	int workerId;
	int departmentId;

	int num = 0;

	while (ifs >> name && ifs >> workerId && ifs >> departmentId)//一行一个人
	{
		//记录人数
		num++;
	}
	ifs.close();
	return num;
}

void EmployeeManage::initEmployee() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string name;
	int workerId;
	int departmentId;

	while (ifs >> name && ifs >> workerId && ifs >> departmentId)
	{
		this->addEmployeeCore(name, workerId, departmentId);
	}
}

void EmployeeManage::showEmployee() {

	DLinklist tempNode = NULL;
	tempNode = &this->empHead;
	this->fileEmpty();
	if (this->fileEmptyFlag)
	{
		while (tempNode->next != NULL)
		{
			//遍历输出，正向，顺next
			tempNode = tempNode->next;
			tempNode->data->showInfo();
		}
	}
	else {
		cout << "文件不存在或记录为空！" << endl;
	}
	system("pause");
	system("cls");
}

void EmployeeManage::fileEmpty() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//文件存在，并且没有记录
	char ch;
	ifs >> ch; //先只读一个字符，然后判断这个字符是不是EOF
	if (ifs.eof())
	{
		cout << "文件为空!!" << endl;
		this->empNum = 0;
		this->fileEmptyFlag = false;
		ifs.close();
	}
	//文件不存在情况
	else if (!ifs.is_open())
	{
		cout << "文件不存在!!" << endl; //测试输出
		this->empNum = 0;  //初始化人数
		this->fileEmptyFlag = false; //初始化文件为空标志
		ifs.close(); //关闭文件
	}
	else
	{
		fileEmptyFlag = true;
	}
}

DLinklist EmployeeManage::searchEmployeeCore(int workerId = -1, string name = "null") {

	DLinklist tempSearchNode = &this->empHead;  //遍历用的指针
	DLinklist retResultList = new DNode;  //结果串成链返回
	DLinklist operateTool = nullptr;

	retResultList->next = nullptr;
	retResultList->prior = nullptr;

	while (tempSearchNode->next != nullptr) //nullptr
	{
		tempSearchNode = tempSearchNode->next;
		if ((tempSearchNode->data->workerId == workerId) || (tempSearchNode->data->name == name)) {
			operateTool = new DNode;
			operateTool->prior = nullptr;
			operateTool->next = nullptr;

			if ((retResultList->next == NULL) && (operateTool != NULL)) {
				//空链表
				retResultList->next = operateTool;
			}
			else {//头插法
				operateTool->next = retResultList->next;
				retResultList->next = operateTool;
			}
			operateTool->prior = tempSearchNode;
			/*
			注意此结果链表中的data弃用，将prior指针改用来指向目标结果应注意
			的是此时仍操作的是主链，全程没有所需的值的拷贝，纯粹的指针操作。
			*/
		}
	}
	if (retResultList->next == NULL) {
		return NULL;
	}
	tempSearchNode = nullptr;
	operateTool = nullptr;

	return retResultList;
}

void EmployeeManage::deleteEmployee() {
	if (!this->fileEmptyFlag) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		int workId = 0;
		DLinklist tempNode = NULL;
		DLinklist operateTool = nullptr;
		char deleteChoice = 'n';  //默认不删除
		cout << "请输入想要删除的职工号：" << endl;  //偷个懒，排除按姓名删除的方式
		cin >> workId;

		tempNode = this->searchEmployeeCore(workId);

		if (tempNode->next != NULL) {
			operateTool = tempNode->next;
			operateTool->prior->data->showInfo();
			cout << "是否删除？(y/n)";
			cin >> deleteChoice;
			if (deleteChoice == 'y') {
				operateTool->prior->prior->next = operateTool->prior->next;
				operateTool->prior->next->prior = operateTool->prior->prior;
				delete operateTool->prior;
				delete operateTool;
				operateTool = nullptr;
				tempNode = nullptr;
				this->save();
				cout << "删除成功" << endl;
			}
			else {
				cout << "已取消" << endl;
			}
		}
		else {
			cout << "查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}

void EmployeeManage::findEmployee() {

	string searchKeyWord = "";
	DLinklist tempNode = nullptr;  //用来接收结果链表
	DLinklist operateTool = nullptr;  //用来操作结果链表
	DLinklist deleteTool = nullptr;  //用来清除结果链表
	cout << "请输入职员编号或姓名：";
	cin >> searchKeyWord;
	if (((int)searchKeyWord[0] >= 48) && ((int)searchKeyWord[0] <= 57)) {
		//输入为编号
		tempNode = this->searchEmployeeCore(stoi(searchKeyWord));
	}
	else {
		//输入为姓名
		tempNode = this->searchEmployeeCore(-1, searchKeyWord);
	}

	if (tempNode->next != NULL) {
		operateTool = tempNode->next;  /*这里稍微封装了一下*/
		deleteTool = tempNode;
		while (operateTool != NULL)
		{
			operateTool->prior->data->showInfo();
			deleteTool = operateTool;
			operateTool = operateTool->next;
			delete deleteTool;
		}
		deleteTool = nullptr;
		operateTool = nullptr;
		tempNode = nullptr;
	}
	else {
		cout << "未找到此人" << endl;
	}
	system("pause");
	system("cls");
}

void EmployeeManage::editEmlpoyeeInfo() {
	if (!this->fileEmptyFlag) {
		cout << "文件不存在或记录为空！" << endl;
	}
	else {
		int workId = 0;
		DLinklist tempNode = nullptr;
		cout << "请输入想要编辑的职工号：" << endl;
		cin >> workId;

		tempNode = this->searchEmployeeCore(workId);

		if (tempNode->next != NULL) {
			int newWorkerId = 0;
			string newName = "";
			int newDepartmentId = 0;

			cout << "查到： " << workId << " 号职工，" << endl;
			tempNode->next->prior->data->showInfo();
			cout << "请输入新职工号： " << endl;
			cin >> newWorkerId;
			cout << "请输入新姓名： " << endl;
			cin >> newName;
			cout << "请选择该职工的岗位：" << endl;
			cout << "1.普通职工" << "\t2.经理" << "\t3.老板" << endl;
			cin >> newDepartmentId;

			//因为不同职位有相应子类，所以重新创建，复用增加功能核心
			this->addEmployeeCore(newName, newWorkerId, newDepartmentId);

			//删除旧节点
			tempNode->next->prior->prior->next = tempNode->next->prior->next;
			tempNode->next->prior->next->prior = tempNode->next->prior->prior;
			delete tempNode->next;
			delete tempNode;
			tempNode = nullptr;

			this->save();
		}
		else {
			cout << "查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}

void EmployeeManage::sortEmployee() {
	DLinklist tail = this->empHead.next;
	while (tail->next != NULL)
	{
		tail = tail->next;
	}
	this->sortEmployeeCore(this->empHead.next, tail);
	cout << "排序完成" << endl;
	this->save();
	system("pause");
	system("cls");
}

void EmployeeManage::sortEmployeeCore(DLinklist head, DLinklist tail) {

	DLinklist left = nullptr;
	DLinklist right = nullptr;
	Worker* pivotWorkId;

	if ((head != tail) && (head != tail->next))
	{
		pivotWorkId = head->data; //最左侧为枢轴元素
		left = head;
		right = tail;
		while ((left != right) && (left != right->next)) /*左右一起完成全部遍历*/
		{
			/*枢轴留出空位，挖坑法*/
			while (right != left)
			{
				if (right->data->workerId < pivotWorkId->workerId)
				{
					/*暂不考虑等于，因为员工编号不会一样*/
					left->data = right->data;
					left = left->next;
					break;
				}
				right = right->prior;
			}
			while (right != left)
			{
				if (left->data->workerId > pivotWorkId->workerId)
				{
					right->data = left->data;
					right = right->prior;
					break;
				}
				left = left->next;
			}
			left->data = pivotWorkId;
		}
		this->sortEmployeeCore(head, left);
		this->sortEmployeeCore(left->next, tail);
	}
}


/*前向指针测试*/
void EmployeeManage::testForPrior() {
	DLinklist tempNode, endPoint = nullptr;
	tempNode = &this->empHead;
	while (tempNode->next != NULL)
	{
		//遍历输出，正向，顺next
		tempNode = tempNode->next;
		if (tempNode->data->workerId == 3)
		{
			endPoint = tempNode;  //找到最后一个节点，创建尾指针
			while (endPoint->prior != NULL)
			{
				endPoint->data->showInfo();
				endPoint = endPoint->prior;
			}
		}
	}
	system("pause");
	system("cls");
}


void EmployeeManage::cleanFile() {
	char deleteChoice = 'n';  //默认不清空
	DLinklist operateTool = this->empHead.next;
	DLinklist deleteTool = nullptr;
	cout << "是否清空？(y/n)";
	cin >> deleteChoice;
	if (deleteChoice == 'y') {

		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		while (operateTool != nullptr)
		{
			deleteTool = operateTool;
			operateTool = operateTool->next;
			delete deleteTool;
		}
		deleteTool = nullptr;
		operateTool = nullptr;
		cout << "删除完成" << endl;
		fileEmptyFlag = false;
	}
	system("pause");
	system("cls");
}

void EmployeeManage::exitSystem() {
	cout << "感谢使用，再见 (づ￣ 3￣)づ" << endl;
	system("pause");
	system("pause");
	exit(0);
}