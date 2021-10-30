#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
//#include "linklist.cpp"
class tree_node{
public:
	int value;//ֵ
	int pos;//��¼�Լ��ǵڼ����Ӵ�(������)
	tree_node* parent;//��¼���ڵ�
	vector <tree_node*> children;//��¼�ӽڵ�
	tree_node* nextbro=NULL;//��¼�ֵܽڵ�
};


void create_tree(tree_node a[],int n){
	for(int i=0;i<n;i++){
		if(i==0){
			cout<<"�������ֵ:";
			cin>>a[0].value;
			a[0].parent=NULL;
		}
		else{
			cout<<"������Ǹ��ڵ�ֵ:";
			cin>>a[i].value;
			FLAG1:
			cout<<"������ýڵ�ĸ��ڵ������ţ������������У�";
   			for(int s=0;s<i;s++){
				cout<<s<<" ";
			}
			cout<<endl;
			int temp;
			cin>>temp;
			if(temp>=0&&temp<i){
				a[i].parent=&a[temp];
				a[i].pos=a[temp].children.size();
				if(a[i].pos>0){
					a[temp].children[a[i].pos-1]->nextbro=&a[i];//����һ���ֵܵ�nextbroָ���Լ�
				}
				a[temp].children.push_back(&a[i]);//���Լ����븸�ڵ���Ӵ���
				
			}
			else{
				cout<<"������������������"<<endl;
				goto FLAG1;
			}

		}
	}
}


//�ݹ�ʵ��
//�������
/*ʱ�临�Ӷȣ�O(n)	�ռ临�Ӷ�O(n)	nΪ�ڵ���*/
void dlr_value(tree_node *p){
	cout<<p->value<<" ";
	if(p->children.empty()){//û���Ӵ��ͷ������ֵ�
	    while(p->nextbro==NULL&&p->parent!=NULL){//û�����ֵ���ָ�򸸴�
			p=p->parent;
		}
		if(p->parent==NULL){//����ʱreturn
			return;
		}
		dlr_value(p->nextbro);
	}
	else{//���Ӵ������Ӵ�
		dlr_value(p->children[0]);
	}
 	
}
void DLR(tree_node a[]){
	cout<<"�ݹ����������";
	tree_node *p=&a[0];
	dlr_value(p);
}

//�������(���ڷǶ����������Զ����������Ϊldrr����r,��ֻ��һ���Ӵ���Ϊld)
/*ʱ�临�Ӷȣ�O(n)	�ռ临�Ӷ�O(n)	nΪ�ڵ���*/
void ldr_value(tree_node *p){
	while(!p->children.empty()){//ÿ�����Ƶ����������
		p=p->children[0];
	}
	cout<<p->value<<" ";
	if(p->parent->children.size()==1){//����Լ��Ƕ������ӡ����ֵ��ָ�򸸴�
		cout<<p->parent->value<<" ";
		p=p->parent;
	}
	if(p->nextbro!=NULL){//�����ֵ���ָ���ֵ�
		if(p->pos==0){//���Լ��������ϴ����ӡ����ֵ
			cout<<p->parent->value<<" ";
		}
		ldr_value(p->nextbro);
	}
	while(p->nextbro==NULL&&p->parent->nextbro==NULL){
		p=p->parent;//�Լ�û�����ֵܣ�����Ҳû�����ֵ�(��֧���Ҷ�)��ָ�򸸴�
	}
	if(p->nextbro==NULL&&p->parent->nextbro!=NULL){//�Լ�û�����ֵܣ����������ֵ�
		if(p->parent->pos==0){//����������ϴ󣬴�ӡ�����ĸ���ֵ
			cout<<p->parent->parent->value<<" ";
		}
		p=p->parent->nextbro;//ָ�򸸴����ֵ�
	}
	if(p!=NULL){//ֻҪ����������ݹ飬ֱ�����յ�����ĸ���(����)�����ݹ�
		ldr_value(p);
	}
}
void LDR(tree_node a[]){
 	tree_node *p=&a[0];
    cout<<"�ݹ����������";
	ldr_value(p);
}

//�������
/*ʱ�临�Ӷȣ�O(n)	�ռ临�Ӷ�O(n)	nΪ�ڵ���*/
void lrd_value(tree_node *p){
	while(p->nextbro!=NULL){//�����δ�ӡ���ֵ�ֵ
		p=p->nextbro;
  		while(!p->children.empty()){//ÿ�����Ƶ����������
			p=p->children[0];
		}
		cout<<p->value<<" ";
	}
	if(p->nextbro==NULL){//û�����ֵ���ָ�򸸴�����ӡ����ֵ���ݹ�
		p=p->parent;
		cout<<p->value<<" ";
		lrd_value(p);
	}
}
void LRD(tree_node a[]){
	tree_node *p=&a[1];
	while(!p->children.empty()){
		p=p->children[0];
	}
    cout<<"�ݹ���������"<<p->value<<" ";
	lrd_value(p);
}



//�ǵݹ�ʵ��

//�������
/*ʱ�临�Ӷȣ�O(n)	�ռ临�Ӷ�O(n)	nΪ�ڵ���*/

void DLR1(tree_node *p){
	cout<<"�ǵݹ����������"<<p->value<<" ";
	while(!p->children.empty()){
		p=p->children[0];
		cout<<p->value<<" ";
	}
	while(p->nextbro!=NULL){
		p=p->nextbro;
		cout<<p->value<<" ";
		while(!p->children.empty()){
			p=p->children[0];
			cout<<p->value<<" ";
		}
		while(p->nextbro==NULL){//û�����ֵ���ָ�򸸴�
			if(p->parent==NULL){//���������˳�����
				return;
			}
			p=p->parent;
		}
	}
	
}

//�������(���ڷǶ����������Զ����������Ϊldrr����r,��ֻ��һ���Ӵ���Ϊld)
/*ʱ�临�Ӷȣ�O(n)	�ռ临�Ӷ�O(n)	nΪ�ڵ���*/
void LDR1(tree_node *p){
	cout<<"�ǵݹ����������";
    while(p!=NULL){
		while(!p->children.empty()){//ÿ�����Ƶ����������
			p=p->children[0];
		}
		cout<<p->value<<" ";
		
		if(p->parent->children.size()==1){//����Լ��Ƕ������ӡ����ֵ��ָ�򸸴�
			cout<<p->parent->value<<" ";
			p=p->parent;
		}
		if(p->nextbro!=NULL){//�����ֵ���ָ���ֵ�
			if(p->pos==0){//���Լ��������ϴ����ӡ����ֵ
				cout<<p->parent->value<<" ";
			}
			p=p->nextbro;
			continue;
		}
		while(p->nextbro==NULL&&p->parent->nextbro==NULL){
			p=p->parent;//�Լ�û�����ֵܣ�����Ҳû�����ֵ�(��֧���Ҷ�)��ָ�򸸴�
		}
		if(p->nextbro==NULL&&p->parent->nextbro!=NULL){//�Լ�û�����ֵܣ����������ֵ�
			if(p->parent->pos==0){//����������ϴ󣬴�ӡ�����ĸ���ֵ
				cout<<p->parent->parent->value<<" ";
			}
			p=p->parent->nextbro;//ָ�򸸴����ֵ�
		}
	}
}


//�������
/*ʱ�临�Ӷȣ�O(n)	�ռ临�Ӷ�O(n)	nΪ�ڵ���*/
void LRD1(tree_node *p){
	cout<<"�ǵݹ���������";
	while(!p->children.empty()){//ÿ�����Ƶ����������
		p=p->children[0];
	}
	cout<<p->value<<" ";
	while(p->nextbro!=NULL){//�����δ�ӡ���ֵ�ֵ
		p=p->nextbro;
  		while(!p->children.empty()){//ÿ�����Ƶ����������
			p=p->children[0];
		}
		cout<<p->value<<" ";
		while(p->nextbro==NULL){//û�����ֵ���ָ�򸸴�����ӡ����ֵ
			
			if(p->parent==NULL){//���������˳�����
				return;
			}
			p=p->parent;
			cout<<p->value<<" ";
		}
	}
}


//�㼶����BFS
/*ʱ�临�Ӷȣ�O(n)	��ռ临�Ӷ�O(n)	nΪ�ڵ���*/
void BFS(tree_node *p){
	queue <tree_node*> q;
	q.push(p);
	tree_node* cur=q.front();
	while(!cur->children.empty()){
		for(int i=0;i<(cur->children.size());i++){
			q.push(cur->children[i]);
		}
		cout<<cur->value<<" ";
		q.pop();
		if(q.size()){
			cur=q.front();
		}
		else{
			return;
		}
		while(cur->children.empty()){
			cout<<cur->value<<" ";
			q.pop();
			if(q.size()){
				cur=q.front();
			}
			else{
				return;
			}
		}
	}
}

//DFS
/*ʱ�临�Ӷȣ�O(n)	��ռ临�Ӷ�O(n)	nΪ�ڵ���*/
void DFS(tree_node *p){
	stack <tree_node*> s;
	s.push(p);
	tree_node* cur=s.top();
	while(!cur->children.empty()){
		s.pop();
		for(int i=(cur->children.size()-1);i>=0;i--){
			s.push(cur->children[i]);
		}
		cout<<cur->value<<" ";
		if(s.size()){
			cur=s.top();
		}
		else{
			return;
		}
		while(cur->children.empty()){
			cout<<cur->value<<" ";
			s.pop();
			if(s.size()){
				cur=s.top();
			}
			else{
				return;
			}
		}
	}
}


int main(){
	cout<<"������ڵ���:";
	int n;
	cin>>n;
	tree_node a[n];//����tree_node����
	
	create_tree(a,n);//������
	
	
//  �ݹ�ʵ�֣�

//  �������
//	DLR(a);

//  �������
//  LDR(a);

//  �������
//	LRD(a);


//�ǵݹ�ʵ�֣�

//  �������
//	DLR1(&a[0]);

//  �������
//	LDR1(&a[0]);

//  �������
//	LRD1(&a[0]);


//  �㼶����(BFS)��
//	BFS(&a[0]);

//DFS
//	DFS(&a[0]);
  	system("pause");
	return 0;
}
