#include <iostream>
#include <vector>
using namespace std;
//#include "linklist.cpp"
class tree_node{
public:
	int value;//值
	int pos;//记录自己是第几个子代(索引号)
	tree_node* parent;//记录父节点
	vector <tree_node*> children;//记录子节点
	tree_node* nextbro=NULL;//记录兄弟节点
};


void create_tree(tree_node a[],int n){
	for(int i=0;i<n;i++){
		if(i==0){
			cout<<"请输入根值:";
			cin>>a[0].value;
			a[0].parent=NULL;
		}
		else{
			cout<<"请输入非根节点值:";
			cin>>a[i].value;
			FLAG1:
			cout<<"请输入该节点的父节点索引号，可用索引号有：";
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
					a[temp].children[a[i].pos-1]->nextbro=&a[i];//把上一个兄弟的nextbro指向自己
				}
				a[temp].children.push_back(&a[i]);//把自己加入父节点的子代中
				
			}
			else{
				cout<<"输入有误，请重新输入"<<endl;
				goto FLAG1;
			}

		}
	}
}

//先序遍历
void dlr_value(tree_node *p,tree_node *temp){
	if(p==NULL){//只有没有下一个兄弟时才会出现NULL
		p=temp;//用正常指针取代空指针
		dlr_value((p->parent)->nextbro,temp);//访问父节点的兄弟
 	}
	if(&p!=NULL&&p->parent==NULL){
		return;
	}
	if(&p!=NULL){
		temp=p;//保存当前正常指针
		cout<<p->value<<" ";
		if(p->children.empty()){//没有子代就访问兄弟
			dlr_value(p->nextbro,temp);
		}
		else{//有子代访问子代
			dlr_value(p->children[0],temp);
		}
	}
 	
}
void DLR(tree_node a[]){
	cout<<"先序遍历："<<a[0].value<<" ";
	tree_node *p=&a[1];
	dlr_value(p,p);
}

//中序遍历(由于非二叉树，所以定义遍历规则为ldrr……r)
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
    cout<<"中序遍历："<<p->value<<" ";
	ldr_value(p);
}



//后序遍历
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
    cout<<"后序遍历："<<p->value<<" ";
	lrd_value(p);
}

int main(){
	cout<<"请输入节点数:";
	int n;
	cin>>n;
	tree_node a[n];//创建tree_node数组
	
	create_tree(a,n);//创建树
	
	
//  递归实现：

//  先序遍历
//	DLR(a);

//  中序遍历(有BUG)
//  LDR(a);

//  后序遍历
//	LRD(a);
	return 0;
}
