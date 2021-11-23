#define	_CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
//二叉树的二叉链存储表示
typedef char Telemtype;
#define MAXSQIZE 100
#define MAXSIZE 100
typedef struct BiTNode {
	Telemtype data;
	struct BiTNode* lchild, * rchild;//左右孩子指针
}BiTNode,*BiTree;
//定义一个队列
typedef struct SqQueue {
	BiTree*base;
	int front;
	int rear;
}SqQueue;
////定义一个栈
//typedef struct {
//	BiTree*base;
//	BiTree*top;
//	int stacksize;
//}SqStack;
////顺序栈初始化
//void InitStack(SqStack& S) {
//	S.base = new BiTree[MAXSIZE];
//	if (!S.base) {
//		cout << "内存分配失败" << endl;
//		exit(-1);
//	}
//	S.top = S.base;
//	S.stacksize = MAXSIZE;
//}
////获取栈顶元素
//void Gettop(SqStack& S, BiTree&p) {
//	if (S.top == S.base) {
//		cout << "栈满" << endl;
//		exit(-1);
//	}
//	p = *(S.top - 1);
//}
////入栈
//void Push(SqStack& S, BiTree& T) {
//	if (S.top - S.base >= S.stacksize) {
//		cout << "栈满" << endl;
//		exit(-1);
//	}
//	*S.top = T;
//	++S.top;
//}
////出栈
//void Pop(SqStack& S, BiTree& p) {
//	if (S.base == S.top) {
//		cout << "栈空" << endl;
//		exit(-1);
//	}
//	--S.top;
//	p = *S.top;
//}
//int StackEmpty(SqStack S) {
//	if (S.base == S.top)
//		return 0;
//	else
//		return 1;
//}
//void PostOrder(BiTree T, Telemtype x)
//{
//	SqStack S;
//	InitStack(S); //初始化栈
//	BiTree p = T; //p为遍历指针
//	BiTree r = NULL; //r为辅组指针，指向最近访问过的结点。也可以在结点中增加一个标志域tag，记录是否已被访问
//	while (p || !StackEmpty(S)) //栈不空或p不空时循环
//	{
//		if (p) //一路向左
//		{
//			Push(S, p);
//			p = p->lchild; //左孩子不空，一直向左走
//		}
//		else //向右
//		{
//			Gettop(S, p); //读栈顶结点（非出栈）
//			if (p->data == x) //如果栈顶结点的值等于x
//			{
//				while (!StackEmpty(S)) //则将栈中所有元素依次出栈打印
//				{
//					Pop(S, p);
//					cout << p->data; //访问该结点
//				}
//				return; //执行完毕返回
//			}
//			if (p->rchild && p->rchild != r) //若右子树存在，且未被访问过
//			{
//				p = p->rchild; //转向右
//				Push(S, p);
//				p = p->lchild; //再走到最左
//			}
//			else //否则，弹出结点
//			{
//				Pop(S, p);
//				r = p; //记录最近访问过的结点
//				p = NULL; //结点访问完毕后，重置p指针，不然该结点又会重新入栈
//			}
//		}
//	}
//}


//二叉树初始化
void InitBiTree(BiTree& T) {
	T = NULL;
}
//队列初始化
void InitQueue(SqQueue& Q) {
	Q.base = new BiTree[MAXSQIZE];
	if (!Q.base) {
		cout << "存储分配失败" << endl;
		exit(-1);
	}
	Q.front = Q.rear = 0;
}

//按先序遍历输入二叉树中结点的值（一个字符），字符‘#’表示空树
//构造二叉链表示的二叉树T
void CreateBiTree(BiTree& T) {
	char ch;
	cin >> ch;
	if (ch == '#')//#结束递归
		T = NULL;
	else {
		T = new BiTNode;
		T->data = ch;
		cout << "请输入" << ch << "的左孩子：";
		CreateBiTree(T->lchild);
		cout << "请输入" << ch << "的右孩子：";
		CreateBiTree(T->rchild);
	}
}
//先序遍历
void PreOrderTraverse(BiTree T) {
	if (T) {
		cout << T->data;
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}
//中序遍历
void InOrderTraverse(BiTree T) {
	if (T) {
		InOrderTraverse(T->lchild);
		cout << T->data;
		InOrderTraverse(T->rchild);
	}
}
//后序遍历
void PostOrderTraverse(BiTree T) {
	if (T) {
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		cout << T->data;
	}
}
//层序遍历-数组实现
void Floorprint(BiTree T) {
	BiTree temp[100];
	int in = 0, out = 0;
	temp[in] = T;
	in++;
	while (in > out) {
		if (temp[out]) {
			cout << temp[out]->data;
			temp[in++] = temp[out]->lchild;
			temp[in++] = temp[out]->rchild;
		}
		out++;
	}
}
//层序遍历-队列实现
//入队
void EnQueue(SqQueue& Q, BiTree& T) {
	if ((Q.rear + 1) % MAXSQIZE == Q.front) {
		cout << "队满，无法入队" << endl;
		exit(-1);
	}
	Q.base[Q.rear] = T;//二叉树根节点入队
	Q.rear = (Q.rear + 1) % MAXSQIZE;
}
//出队
BiTree OutQueue(SqQueue& Q) {
	BiTree T;
	T = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXSQIZE;
	return T;
}
//队列实现层次遍历
void Floorprint2(BiTree T) {
	SqQueue Q;
	InitQueue(Q);
	EnQueue(Q, T);//将根节点入队
	while (Q.rear != Q.front) {
		BiTree root = OutQueue(Q);//新生成一个二叉树，将对头节点赋给他
		cout << root->data;//输出二叉树结点
		if (root->lchild)//如果这个二叉树结点有左孩子，将其左孩子入队
			EnQueue(Q,root->lchild);
		if (root->rchild)//如果这个结点有右孩子，将其右孩子入队
			EnQueue(Q, root->rchild);
	}
}
//在二叉树中查找值为value的结点
//递归实现
int Find(BiTree T, Telemtype e) {
	if (!T)
		return 0;
	if (T->data == e)
		return 1;
	if (Find(T->lchild, e) || Find(T->rchild, e)) {
		cout << T->data;
		return 1;
	}
	else {
		cout << "没找到值为e的结点" << endl;
		return 0;
	}	
}
//非递归实现-栈


//统计出二叉树叶子结点的个数
//如果空树，叶子节点数为0
//否则，叶子节点数为左子树叶子节点数+右子树叶子节点数
int LeafCount(BiTree T) {
	if (!T)
		return 0;
	else if (T->lchild == NULL && T->rchild == NULL)
		return 1;
	else
		return LeafCount(T->lchild) + LeafCount(T->rchild);
}

//统计出二叉树中所有结点总数
//如果空树，则结点数为0
//否则，结点数为左子树结点数+右子树结点数+1（根节点）
int NodeCount(BiTree T) {
	if (!T)
		return 0;
	else
		return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}

//统计出二叉树中非叶子结点的个数
//非叶子结点数=结点总数-叶子结点数
int UnleafCount(BiTree T) {
	return NodeCount(T) - LeafCount(T);
}

//二叉树的高度
//如果是空树，则高度为0，深度
//否则，递归计算左子树深度为m，右子树深度为n，二叉树的深度为max(m,n)+1;
int Depth(BiTree T) {
	if (!T)
		return 0;
	else {
		int m = Depth(T->lchild);
		int n = Depth(T->rchild);
		return (m > n ? m : n) + 1;
	}
}

int main() {
	BiTree T;
	InitBiTree(T);
	cout << "********************************************************************************************" << endl;
	cout << "***1.创建二叉树**2.先序遍历**3.中序遍历**4.后序遍历**5.层次遍历1**6.层次遍历2**7.查找***" << endl;
	cout << "********************************************************************************************" << endl;
	int input;
	while (1) {
		cout << "请输入您需要的操作指令：";
		cin >> input;
		switch (input) {
		case 1: {
			cout << "按先序遍历输入二叉树中结点的值（一个字符），字符‘#’表示空树" << endl;
			cout << "请输入根结点：";
			CreateBiTree(T);
			break;
		}
		case 2: {
			cout << "先序遍历：";
			PreOrderTraverse(T);
			cout << endl;
			break;
		}
		case 3: {
			cout << "中序遍历：";
			InOrderTraverse(T);
			cout << endl;
			break;
		}
		case 4: {
			cout << "后序遍历：";
			PostOrderTraverse(T);
			cout << endl;
			break;
		}
		case 5: {
			cout << "层次遍历（数组实现）：";
			Floorprint(T);
			cout << endl;
			break;
		}
		case 6: {
			cout << "层次遍历（队列实现）：";
			Floorprint2(T);
			cout << endl;
			break;
		}
		case 7: {
			Telemtype e;
			cin >> e;
			Find(T, e);
			cout << endl;
			break;
		}
		case 10: {
			cout << "退出程序" << endl;
			exit(0);
		}
		default: {
			cout << "输入错误，请重新输入" << endl;
		}
		}
	}
}