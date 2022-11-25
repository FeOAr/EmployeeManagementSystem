# EmployeeManagementSystem
# 链表结构

```c++
typedef struct DNode {
	Worker* data;  //父类指针
	struct DNode* prior, * next;  //前驱后继指针
}DNode, *DLinklist;
```



![](https://imgforfeoar-1312132618.cos.ap-shanghai.myqcloud.com/markdown/202211232114213.png)

>注意此处结果链的`prior`指针，没有指向前驱节点，而是指向主链。使结果链成为单链表。以此种方式保存需要的结果，data区弃用。结果链表同样使用`DNode`结构体。 





![](https://imgforfeoar-1312132618.cos.ap-shanghai.myqcloud.com/markdown/202211232114624.png)

> 实际上在353行


![](https://imgforfeoar-1312132618.cos.ap-shanghai.myqcloud.com/markdown/202211232114262.png)



# 类与节点相关结构

三个子类全部采用全部public继承职工worker抽象类，子类中重写父类中纯虚函数。

![类结构.drawio](https://imgforfeoar-1312132618.cos.ap-shanghai.myqcloud.com/markdown/202211251505494.png)

