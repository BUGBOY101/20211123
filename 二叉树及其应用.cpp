#define	_CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
//�������Ķ������洢��ʾ
typedef char Telemtype;
#define MAXSQIZE 100
#define MAXSIZE 100
typedef struct BiTNode {
	Telemtype data;
	struct BiTNode* lchild, * rchild;//���Һ���ָ��
}BiTNode,*BiTree;
//����һ������
typedef struct SqQueue {
	BiTree*base;
	int front;
	int rear;
}SqQueue;
////����һ��ջ
//typedef struct {
//	BiTree*base;
//	BiTree*top;
//	int stacksize;
//}SqStack;
////˳��ջ��ʼ��
//void InitStack(SqStack& S) {
//	S.base = new BiTree[MAXSIZE];
//	if (!S.base) {
//		cout << "�ڴ����ʧ��" << endl;
//		exit(-1);
//	}
//	S.top = S.base;
//	S.stacksize = MAXSIZE;
//}
////��ȡջ��Ԫ��
//void Gettop(SqStack& S, BiTree&p) {
//	if (S.top == S.base) {
//		cout << "ջ��" << endl;
//		exit(-1);
//	}
//	p = *(S.top - 1);
//}
////��ջ
//void Push(SqStack& S, BiTree& T) {
//	if (S.top - S.base >= S.stacksize) {
//		cout << "ջ��" << endl;
//		exit(-1);
//	}
//	*S.top = T;
//	++S.top;
//}
////��ջ
//void Pop(SqStack& S, BiTree& p) {
//	if (S.base == S.top) {
//		cout << "ջ��" << endl;
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
//	InitStack(S); //��ʼ��ջ
//	BiTree p = T; //pΪ����ָ��
//	BiTree r = NULL; //rΪ����ָ�룬ָ��������ʹ��Ľ�㡣Ҳ�����ڽ��������һ����־��tag����¼�Ƿ��ѱ�����
//	while (p || !StackEmpty(S)) //ջ���ջ�p����ʱѭ��
//	{
//		if (p) //һ·����
//		{
//			Push(S, p);
//			p = p->lchild; //���Ӳ��գ�һֱ������
//		}
//		else //����
//		{
//			Gettop(S, p); //��ջ����㣨�ǳ�ջ��
//			if (p->data == x) //���ջ������ֵ����x
//			{
//				while (!StackEmpty(S)) //��ջ������Ԫ�����γ�ջ��ӡ
//				{
//					Pop(S, p);
//					cout << p->data; //���ʸý��
//				}
//				return; //ִ����Ϸ���
//			}
//			if (p->rchild && p->rchild != r) //�����������ڣ���δ�����ʹ�
//			{
//				p = p->rchild; //ת����
//				Push(S, p);
//				p = p->lchild; //���ߵ�����
//			}
//			else //���򣬵������
//			{
//				Pop(S, p);
//				r = p; //��¼������ʹ��Ľ��
//				p = NULL; //��������Ϻ�����pָ�룬��Ȼ�ý���ֻ�������ջ
//			}
//		}
//	}
//}


//��������ʼ��
void InitBiTree(BiTree& T) {
	T = NULL;
}
//���г�ʼ��
void InitQueue(SqQueue& Q) {
	Q.base = new BiTree[MAXSQIZE];
	if (!Q.base) {
		cout << "�洢����ʧ��" << endl;
		exit(-1);
	}
	Q.front = Q.rear = 0;
}

//�������������������н���ֵ��һ���ַ������ַ���#����ʾ����
//�����������ʾ�Ķ�����T
void CreateBiTree(BiTree& T) {
	char ch;
	cin >> ch;
	if (ch == '#')//#�����ݹ�
		T = NULL;
	else {
		T = new BiTNode;
		T->data = ch;
		cout << "������" << ch << "�����ӣ�";
		CreateBiTree(T->lchild);
		cout << "������" << ch << "���Һ��ӣ�";
		CreateBiTree(T->rchild);
	}
}
//�������
void PreOrderTraverse(BiTree T) {
	if (T) {
		cout << T->data;
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}
//�������
void InOrderTraverse(BiTree T) {
	if (T) {
		InOrderTraverse(T->lchild);
		cout << T->data;
		InOrderTraverse(T->rchild);
	}
}
//�������
void PostOrderTraverse(BiTree T) {
	if (T) {
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		cout << T->data;
	}
}
//�������-����ʵ��
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
//�������-����ʵ��
//���
void EnQueue(SqQueue& Q, BiTree& T) {
	if ((Q.rear + 1) % MAXSQIZE == Q.front) {
		cout << "�������޷����" << endl;
		exit(-1);
	}
	Q.base[Q.rear] = T;//���������ڵ����
	Q.rear = (Q.rear + 1) % MAXSQIZE;
}
//����
BiTree OutQueue(SqQueue& Q) {
	BiTree T;
	T = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXSQIZE;
	return T;
}
//����ʵ�ֲ�α���
void Floorprint2(BiTree T) {
	SqQueue Q;
	InitQueue(Q);
	EnQueue(Q, T);//�����ڵ����
	while (Q.rear != Q.front) {
		BiTree root = OutQueue(Q);//������һ��������������ͷ�ڵ㸳����
		cout << root->data;//������������
		if (root->lchild)//��������������������ӣ������������
			EnQueue(Q,root->lchild);
		if (root->rchild)//������������Һ��ӣ������Һ������
			EnQueue(Q, root->rchild);
	}
}
//�ڶ������в���ֵΪvalue�Ľ��
//�ݹ�ʵ��
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
		cout << "û�ҵ�ֵΪe�Ľ��" << endl;
		return 0;
	}	
}
//�ǵݹ�ʵ��-ջ


//ͳ�Ƴ�������Ҷ�ӽ��ĸ���
//���������Ҷ�ӽڵ���Ϊ0
//����Ҷ�ӽڵ���Ϊ������Ҷ�ӽڵ���+������Ҷ�ӽڵ���
int LeafCount(BiTree T) {
	if (!T)
		return 0;
	else if (T->lchild == NULL && T->rchild == NULL)
		return 1;
	else
		return LeafCount(T->lchild) + LeafCount(T->rchild);
}

//ͳ�Ƴ������������н������
//���������������Ϊ0
//���򣬽����Ϊ�����������+�����������+1�����ڵ㣩
int NodeCount(BiTree T) {
	if (!T)
		return 0;
	else
		return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;
}

//ͳ�Ƴ��������з�Ҷ�ӽ��ĸ���
//��Ҷ�ӽ����=�������-Ҷ�ӽ����
int UnleafCount(BiTree T) {
	return NodeCount(T) - LeafCount(T);
}

//�������ĸ߶�
//����ǿ�������߶�Ϊ0�����
//���򣬵ݹ�������������Ϊm�����������Ϊn�������������Ϊmax(m,n)+1;
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
	cout << "***1.����������**2.�������**3.�������**4.�������**5.��α���1**6.��α���2**7.����***" << endl;
	cout << "********************************************************************************************" << endl;
	int input;
	while (1) {
		cout << "����������Ҫ�Ĳ���ָ�";
		cin >> input;
		switch (input) {
		case 1: {
			cout << "�������������������н���ֵ��һ���ַ������ַ���#����ʾ����" << endl;
			cout << "���������㣺";
			CreateBiTree(T);
			break;
		}
		case 2: {
			cout << "���������";
			PreOrderTraverse(T);
			cout << endl;
			break;
		}
		case 3: {
			cout << "���������";
			InOrderTraverse(T);
			cout << endl;
			break;
		}
		case 4: {
			cout << "���������";
			PostOrderTraverse(T);
			cout << endl;
			break;
		}
		case 5: {
			cout << "��α���������ʵ�֣���";
			Floorprint(T);
			cout << endl;
			break;
		}
		case 6: {
			cout << "��α���������ʵ�֣���";
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
			cout << "�˳�����" << endl;
			exit(0);
		}
		default: {
			cout << "�����������������" << endl;
		}
		}
	}
}