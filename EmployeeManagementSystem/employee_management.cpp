#include"employee_management.h"
#include"worker.h"
#include"boss.h"
#include"employee.h"
#include"manager.h"
#include<string>


EmployeeManage::EmployeeManage() {

	fileEmpty();

	this->empNum = 0;
	this->empHead.next = NULL;  /*ͷ�ڵ��ʼ��*/
	this->empHead.prior = NULL;

	if (this->fileEmptyFlag) {
		int num = this->getEmpNum();
		cout << "�Ѷ�ȡְ������Ϊ��" << num << endl;
		this->empNum = num;  /*���³�Ա����*/
		this->initEmployee();
	}
}

EmployeeManage::~EmployeeManage() {}

void EmployeeManage::showMenu() {
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

void EmployeeManage::addEmployee() {

	string name; /*ְ������*/
	int workerId; /*ְ�����(����)*/
	int depSelect; /*��ѡ�������Ʊ��*/

	/*�������*/
	cout << "����ְ�����: ";
	cin >> workerId;
	cout << "����ְ��������";
	cin >> name;
	cout << "��ѡ���ְ���ĸ�λ��" << endl;
	cout << "1.��ְͨ��" << "\t2.����" << "\t3.�ϰ�" << endl;
	cin >> depSelect;

	this->addEmployeeCore(name, workerId, depSelect);
	cout << "�ɹ����" << endl;
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
		cout << "�ڵ��½�ʧ��!" << endl;
		exit(0);
	}

	/*���ͷ�ڵ��û�нڵ�*/
	if (this->empHead.next == NULL) {
		this->empHead.next = tempNode;
		tempNode->prior = &this->empHead;
	}
	else {/*ͷ�巨*/
		tempNode->next = this->empHead.next;
		this->empHead.next->prior = tempNode;
		tempNode->prior = &this->empHead;
		this->empHead.next = tempNode;
	}

	switch (depSelect)
	{
	case 1: /*��ͨԱ��*/
		tempNode->data = new Employee(name, workerId, 1);  /*ע���̬*/
		break;
	case 2: /*����*/
		tempNode->data = new Manager(name, workerId, 2);
		break;
	case 3:  /*�ϰ�*/
		tempNode->data = new Boss(name, workerId, 3);
		break;
	default:
		break;
	}
	tempNode = nullptr;
}

void EmployeeManage::save() {

	DLinklist tempOut;  /*�����*/
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
	cout << "�����ļ��������" << endl;
}

int EmployeeManage::getEmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string name;
	int workerId;
	int departmentId;

	int num = 0;

	while (ifs >> name && ifs >> workerId && ifs >> departmentId)  /*һ��һ����*/
	{
		/*��¼����*/
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
			/*�������������˳next*/
			tempNode = tempNode->next;
			tempNode->data->showInfo();
		}
	}
	else {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	system("pause");
	system("cls");
}

void EmployeeManage::fileEmpty() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	/*�ļ����ڣ�����û�м�¼*/
	char ch;
	ifs >> ch; /*��ֻ��һ���ַ���Ȼ���ж�����ַ��ǲ���EOF*/
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��!!" << endl;
		this->empNum = 0;
		this->fileEmptyFlag = false;
		ifs.close();
	}
	/*�ļ����������*/
	else if (!ifs.is_open())
	{
		cout << "�ļ�������!!" << endl; /*�������*/
		this->empNum = 0;  /*��ʼ������*/
		this->fileEmptyFlag = false; /*��ʼ���ļ�Ϊ�ձ�־*/
		ifs.close(); /*�ر��ļ�*/
	}
	else
	{
		fileEmptyFlag = true;
	}
}

DLinklist EmployeeManage::searchEmployeeCore(int workerId = -1, string name = "null") {

	DLinklist tempSearchNode = &this->empHead;  /*�����õ�ָ��*/
	DLinklist retResultList = new DNode;  /*�������������*/
	DLinklist operateTool = nullptr;

	retResultList->next = nullptr;
	retResultList->prior = nullptr;

	while (tempSearchNode->next != nullptr) /*nullptr*/
	{
		tempSearchNode = tempSearchNode->next;
		if ((tempSearchNode->data->workerId == workerId) || (tempSearchNode->data->name == name)) {
			operateTool = new DNode;
			operateTool->prior = nullptr;
			operateTool->next = nullptr;

			if ((retResultList->next == NULL) && (operateTool != NULL)) {
				/*������*/
				retResultList->next = operateTool;
			}
			else {/*ͷ�巨*/
				operateTool->next = retResultList->next;
				retResultList->next = operateTool;
			}
			operateTool->prior = tempSearchNode;
			/*
			ע��˽�������е�data���ã���priorָ�������ָ��Ŀ����Ӧע��
			���Ǵ�ʱ�Բ�������������ȫ��û�������ֵ�Ŀ����������ָ�������
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
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		int workId = 0;
		DLinklist tempNode = NULL;
		DLinklist operateTool = nullptr;
		char deleteChoice = 'n';  /*Ĭ�ϲ�ɾ��*/
		cout << "��������Ҫɾ����ְ���ţ�" << endl;
		cin >> workId;

		tempNode = this->searchEmployeeCore(workId);

		if (tempNode->next != NULL) {
			operateTool = tempNode->next;
			operateTool->prior->data->showInfo();
			cout << "�Ƿ�ɾ����(y/n)";
			cin >> deleteChoice;
			if (deleteChoice == 'y') {
				operateTool->prior->prior->next = operateTool->prior->next;
				operateTool->prior->next->prior = operateTool->prior->prior;
				delete operateTool->prior;
				delete operateTool;
				operateTool = nullptr;
				tempNode = nullptr;
				this->save();
				cout << "ɾ���ɹ�" << endl;
			}
			else {
				cout << "��ȡ��" << endl;
			}
		}
		else {
			cout << "���޴���" << endl;
		}
	}
	system("pause");
	system("cls");
}

void EmployeeManage::findEmployee() {

	string searchKeyWord = "";
	DLinklist tempNode = nullptr;  /*�������ս������*/
	DLinklist operateTool = nullptr;  /*���������������*/
	DLinklist deleteTool = nullptr;  /*��������������*/
	cout << "������ְԱ��Ż�������";
	cin >> searchKeyWord;
	if (((int)searchKeyWord[0] >= 48) && ((int)searchKeyWord[0] <= 57)) {
		/*����Ϊ���*/
		tempNode = this->searchEmployeeCore(stoi(searchKeyWord));
	}
	else {
		/*����Ϊ����*/
		tempNode = this->searchEmployeeCore(-1, searchKeyWord);
	}

	if (tempNode->next != NULL) {
		operateTool = tempNode->next;  /*������΢��װ��һ��*/
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
		cout << "δ�ҵ�����" << endl;
	}
	system("pause");
	system("cls");
}

void EmployeeManage::editEmlpoyeeInfo() {
	if (!this->fileEmptyFlag) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
		int workId = 0;
		DLinklist tempNode = nullptr;
		cout << "��������Ҫ�༭��ְ���ţ�" << endl;
		cin >> workId;

		tempNode = this->searchEmployeeCore(workId);

		if (tempNode->next != NULL) {
			int newWorkerId = 0;
			string newName = "";
			int newDepartmentId = 0;

			cout << "�鵽�� " << workId << " ��ְ����" << endl;
			tempNode->next->prior->data->showInfo();
			cout << "��������ְ���ţ� " << endl;
			cin >> newWorkerId;
			cout << "�������������� " << endl;
			cin >> newName;
			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "1.��ְͨ��" << "\t2.����" << "\t3.�ϰ�" << endl;
			cin >> newDepartmentId;

			/*��Ϊ��ְͬλ����Ӧ���࣬�������´������������ӹ��ܺ���*/
			this->addEmployeeCore(newName, newWorkerId, newDepartmentId);

			/*ɾ���ɽڵ�*/
			tempNode->next->prior->prior->next = tempNode->next->prior->next;
			tempNode->next->prior->next->prior = tempNode->next->prior->prior;
			delete tempNode->next;
			delete tempNode;
			tempNode = nullptr;

			this->save();
		}
		else {
			cout << "���޴���" << endl;
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
	cout << "�������" << endl;
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
		pivotWorkId = head->data;  /*�����Ϊ����Ԫ��*/
		left = head;
		right = tail;
		while ((left != right) && (left != right->next)) /*����һ�����ȫ������*/
		{
			/*����������λ���ڿӷ�*/
			while (right != left)
			{
				if (right->data->workerId < pivotWorkId->workerId)  /*�޸Ĵ˴����·��Ĺ�ϵ���ſɵ���������*/
				{
					/*�ݲ����ǵ��ڣ���ΪԱ����Ų���һ��*/
					left->data = right->data;
					left = left->next;
					break;
				}
				right = right->prior;
			}
			while (right != left)
			{
				if (left->data->workerId > pivotWorkId->workerId)  /*����������*/
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


/*ǰ��ָ�����*/
void EmployeeManage::testForPrior() {
	DLinklist tempNode, endPoint = nullptr;
	tempNode = &this->empHead;
	while (tempNode->next != NULL)
	{
		/*�������������˳next*/
		tempNode = tempNode->next;
		if (tempNode->data->workerId == 3)
		{
			endPoint = tempNode;  /*�ҵ����һ���ڵ㣬����βָ��*/
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
	char deleteChoice = 'n';  /*Ĭ�ϲ����*/
	DLinklist operateTool = this->empHead.next;
	DLinklist deleteTool = nullptr;
	cout << "�Ƿ���գ�(y/n)";
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
		cout << "ɾ�����" << endl;
		fileEmptyFlag = false;
	}
	system("pause");
	system("cls");
}

void EmployeeManage::exitSystem() {
	cout << "��лʹ�ã��ټ� (�ţ� 3��)��" << endl;
	system("pause");
	exit(0);
}