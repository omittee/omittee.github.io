#include <iostream>
#include <vector>
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

//�������
void dlr_value(tree_node *p,tree_node *temp){
	if(p==NULL){//ֻ��û����һ���ֵ�ʱ�Ż����NULL
		p=temp;//������ָ��ȡ����ָ��
		dlr_value((p->parent)->nextbro,temp);//���ʸ��ڵ���ֵ�
 	}
	if(&p!=NULL&&p->parent==NULL){
		return;
	}
	if(&p!=NULL){
		temp=p;//���浱ǰ����ָ��
		cout<<p->value<<" ";
		if(p->children.empty()){//û���Ӵ��ͷ����ֵ�
			dlr_value(p->nextbro,temp);
		}
		else{//���Ӵ������Ӵ�
			dlr_value(p->children[0],temp);
		}
	}
 	
}
void DLR(tree_node a[]){
	cout<<"���������"<<a[0].value<<" ";
	tree_node *p=&a[1];
	dlr_value(p,p);
}

//�������(���ڷǶ����������Զ����������Ϊldrr����r)
void ldr_value(tree_node *p){

	cout<<p->parent->value<<" ";
	while(p->nextbro!=NULL){
		p=p->nextbro;
		while(!p->children.empty()){
			p=p->children[0];
		}
		cout<<p->value<<" ";
	}
	if(p->nextbro==NULL){
		p=p->parent;
		ldr_value(p);
	}
}
void LDR(tree_node a[]){
	tree_node *p=&a[1];
	while(!p->children.empty()){
		p=p->children[0];
	}
    cout<<"���������"<<p->value<<" ";
	ldr_value(p);
}



//�������
void lrd_value(tree_node *p){
	while(p->nextbro!=NULL){
		p=p->nextbro;
  		while(!p->children.empty()){
			p=p->children[0];
		}
		cout<<p->value<<" ";
	}
	if(p->nextbro==NULL){
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
    cout<<"���������"<<p->value<<" ";
	lrd_value(p);
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

//  �������(��BUG)
//  LDR(a);

//  �������
//	LRD(a);
	return 0;
}
