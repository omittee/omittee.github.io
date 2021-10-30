#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
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


//递归实现
//先序遍历
/*时间复杂度：O(n)	空间复杂度O(n)	n为节点数*/
void dlr_value(tree_node *p){
	cout<<p->value<<" ";
	if(p->children.empty()){//没有子代就访问右兄弟
	    while(p->nextbro==NULL&&p->parent!=NULL){//没有右兄弟则指向父代
			p=p->parent;
		}
		if(p->parent==NULL){//到根时return
			return;
		}
		dlr_value(p->nextbro);
	}
	else{//有子代访问子代
		dlr_value(p->children[0]);
	}
 	
}
void DLR(tree_node a[]){
	cout<<"递归先序遍历：";
	tree_node *p=&a[0];
	dlr_value(p);
}

//中序遍历(由于非二叉树，所以定义遍历规则为ldrr……r,若只有一个子代则为ld)
/*时间复杂度：O(n)	空间复杂度O(n)	n为节点数*/
void ldr_value(tree_node *p){
	while(!p->children.empty()){//每次先移到最左子孙代
		p=p->children[0];
	}
	cout<<p->value<<" ";
	if(p->parent->children.size()==1){//如果自己是独苗则打印父代值并指向父代
		cout<<p->parent->value<<" ";
		p=p->parent;
	}
	if(p->nextbro!=NULL){//有右兄弟则指向兄弟
		if(p->pos==0){//若自己本身是老大则打印父代值
			cout<<p->parent->value<<" ";
		}
		ldr_value(p->nextbro);
	}
	while(p->nextbro==NULL&&p->parent->nextbro==NULL){
		p=p->parent;//自己没有右兄弟，父代也没有右兄弟(分支最右端)则指向父代
	}
	if(p->nextbro==NULL&&p->parent->nextbro!=NULL){//自己没有右兄弟，父代有右兄弟
		if(p->parent->pos==0){//如果父代是老大，打印父代的父代值
			cout<<p->parent->parent->value<<" ";
		}
		p=p->parent->nextbro;//指向父代右兄弟
	}
	if(p!=NULL){//只要不空则继续递归，直到最终到达根的父代(即空)结束递归
		ldr_value(p);
	}
}
void LDR(tree_node a[]){
 	tree_node *p=&a[0];
    cout<<"递归中序遍历：";
	ldr_value(p);
}

//后序遍历
/*时间复杂度：O(n)	空间复杂度O(n)	n为节点数*/
void lrd_value(tree_node *p){
	while(p->nextbro!=NULL){//先依次打印右兄弟值
		p=p->nextbro;
  		while(!p->children.empty()){//每次先移到最左子孙代
			p=p->children[0];
		}
		cout<<p->value<<" ";
	}
	if(p->nextbro==NULL){//没有右兄弟则指向父代，打印父代值，递归
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
    cout<<"递归后序遍历："<<p->value<<" ";
	lrd_value(p);
}



//非递归实现

//先序遍历
/*时间复杂度：O(n)	空间复杂度O(n)	n为节点数*/

void DLR1(tree_node *p){
	cout<<"非递归先序遍历："<<p->value<<" ";
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
		while(p->nextbro==NULL){//没有右兄弟则指向父代
			if(p->parent==NULL){//到根部则退出函数
				return;
			}
			p=p->parent;
		}
	}
	
}

//中序遍历(由于非二叉树，所以定义遍历规则为ldrr……r,若只有一个子代则为ld)
/*时间复杂度：O(n)	空间复杂度O(n)	n为节点数*/
void LDR1(tree_node *p){
	cout<<"非递归中序遍历：";
    while(p!=NULL){
		while(!p->children.empty()){//每次先移到最左子孙代
			p=p->children[0];
		}
		cout<<p->value<<" ";
		
		if(p->parent->children.size()==1){//如果自己是独苗则打印父代值并指向父代
			cout<<p->parent->value<<" ";
			p=p->parent;
		}
		if(p->nextbro!=NULL){//有右兄弟则指向兄弟
			if(p->pos==0){//若自己本身是老大则打印父代值
				cout<<p->parent->value<<" ";
			}
			p=p->nextbro;
			continue;
		}
		while(p->nextbro==NULL&&p->parent->nextbro==NULL){
			p=p->parent;//自己没有右兄弟，父代也没有右兄弟(分支最右端)则指向父代
		}
		if(p->nextbro==NULL&&p->parent->nextbro!=NULL){//自己没有右兄弟，父代有右兄弟
			if(p->parent->pos==0){//如果父代是老大，打印父代的父代值
				cout<<p->parent->parent->value<<" ";
			}
			p=p->parent->nextbro;//指向父代右兄弟
		}
	}
}


//后序遍历
/*时间复杂度：O(n)	空间复杂度O(n)	n为节点数*/
void LRD1(tree_node *p){
	cout<<"非递归后序遍历：";
	while(!p->children.empty()){//每次先移到最左子孙代
		p=p->children[0];
	}
	cout<<p->value<<" ";
	while(p->nextbro!=NULL){//先依次打印右兄弟值
		p=p->nextbro;
  		while(!p->children.empty()){//每次先移到最左子孙代
			p=p->children[0];
		}
		cout<<p->value<<" ";
		while(p->nextbro==NULL){//没有右兄弟则指向父代，打印父代值
			
			if(p->parent==NULL){//到根部则退出函数
				return;
			}
			p=p->parent;
			cout<<p->value<<" ";
		}
	}
}


//层级遍历BFS
/*时间复杂度：O(n)	最坏空间复杂度O(n)	n为节点数*/
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
/*时间复杂度：O(n)	最坏空间复杂度O(n)	n为节点数*/
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
	cout<<"请输入节点数:";
	int n;
	cin>>n;
	tree_node a[n];//创建tree_node数组
	
	create_tree(a,n);//创建树
	
	
//  递归实现：

//  先序遍历
//	DLR(a);

//  中序遍历
//  LDR(a);

//  后序遍历
//	LRD(a);


//非递归实现：

//  先序遍历
//	DLR1(&a[0]);

//  中序遍历
//	LDR1(&a[0]);

//  后序遍历
//	LRD1(&a[0]);


//  层级遍历(BFS)：
//	BFS(&a[0]);

//DFS
//	DFS(&a[0]);
  	system("pause");
	return 0;
}
