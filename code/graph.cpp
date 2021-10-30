#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <queue>
#include <stack>


#define NOTIN 0
#define IN 1
#define OUT 2

#define LEN 3//邻接矩阵阶数
using namespace std;
class graph{
public:
	int value;
	int pos;
	vector <int> next;//储存邻接点索引号，size()即为出度    邻接表
	int state=NOTIN;//记录是否放入队列
	int indeg=0;//记录入度
};

struct matrix{
	int connect[LEN][LEN];
}m;


//邻接表实现有向图版
graph create_graph1(graph *node,int n){
	for(int i=0;i<n;i++){
		cout<<"请输入第"<<i<<"个顶点值：";
		cin>>node[i].value;
		node[i].pos=i;
	}
	for(int i=0;i<n;i++){
		cout<<"请输入第"<<i<<"个顶点的邻接点索引号，用英文逗号,隔开"
		<<endl<<"可用索引号为0到"<<n-1<<",没有邻接点则输入-1。"<<endl;
		string s;
		cin>>s;
		int temp1=0,temp2;
		while(temp1!=-1){
			temp2=s.find(",",temp1);
			string stemp;
			if(temp1!=0){
				stemp=s.substr(temp1,temp2-temp1);
			}
			else{
				stemp=s.substr(temp1,temp2);
			}
			
			int c=atoi(stemp.c_str());
			if(c>=0){
				node[i].next.push_back(c);
			}
			temp1=temp2+1;
			if(temp1==0){
				break;
			}
		}
		
		if(s.find(",")==-1){
   			int c=atoi(s.c_str());
			if(c>=0){
				node[i].next.push_back(c);
			}
		}
		node[i].pos=i;
		for(int j=0;j<node[i].next.size();j++){
			node[ (node[i].next[j]) ].indeg++;//记录入度
		}
	}
}
//邻接矩阵实现无向图版
int* create_graph2(graph *node,int n){
	for(int i=0;i<n;i++){
		cout<<"请输入第"<<i<<"个顶点值：";
		cin>>node[i].value;
		node[i].pos=i;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			m.connect[i][j]=0;
		}
	}
	for(int i=0;i<n;i++){
		cout<<"请输入第"<<i<<"个顶点的邻接点索引号和相应权重，格式为 num1:weight1,num2:weight2,……符号为英文符"
		<<endl<<"可用索引号为0到"<<n-1<<",没有邻接点则输入-1:0 "<<endl;
		string s;
		cin>>s;
		int temp1=0,temp2;
		while(temp1!=-1){
			temp2=s.find(",",temp1);
			string stemp,num,weight;
			if(temp1!=0){
				stemp=s.substr(temp1,temp2-temp1);
				
			}
			else{
				stemp=s.substr(temp1,temp2);
			}

			int a=stemp.find(":");
			num=stemp.substr(0,a);
			weight=stemp.substr(a+1,stemp.size()-a-1);
			int in=atoi(num.c_str());
			int iw=atoi(weight.c_str());
			if(in>=0){
				m.connect[i][in]=iw;
				m.connect[in][i]=iw;
			}
			temp1=temp2+1;
			if(temp1==0){
				break;
			}
		}
		if(s.find(",")==-1){
	  		int a=s.find(":");
			string num=s.substr(0,a);
			string weight=s.substr(a+1,s.size()-a-1);
			int in=atoi(num.c_str());
			int iw=atoi(weight.c_str());
			if(in>=0){
				m.connect[i][in]=iw;
				m.connect[in][i]=iw;
			}
		}
		node[i].pos=i;
		for(int j=0;j<node[i].next.size();j++){
			node[ (node[i].next[j]) ].indeg++;//记录入度
		}
	}
	
//  打印邻接矩阵
//	for(int i=0;i<n;i++){
//		for(int j=0;j<n;j++){
//			cout<<m.connect[i][j]<<" ";
//		}
//		cout<<endl;
//	}

}


//基于邻接表实现遍历
void BFS(graph *n,int k){
	queue <graph*> q;
	int select;
	cout<<"请输入起始节点索引号";
	cin>>select;
	q.push(&n[select]);
	n[select].state=IN;
	cout<<"BFS:";
	graph *cur;
	FLAG1:
	while(q.size()){
		cur=q.front();
		for(int i=0;i<cur->next.size();i++){
			if(n[ (cur->next[i]) ].state==NOTIN){
				q.push(&n[ (cur->next[i]) ]);
				n[ (cur->next[i]) ].state=IN;
			}
		}
		cout<<cur->value<<" ";
		q.pop();
		n[cur->pos].state=OUT;
	}
	for(int i=0;i<k;i++){
		if(n[i].state==NOTIN){//把没有遍历的值放进去遍历
			q.push(&n[i]);
			goto FLAG1;
		}
	}
	for(int i=0;i<k;i++){
		n[i].state=NOTIN;//初始化状态，让下次能继续重新遍历
	}
}

void DFS(graph *n,int k){
	stack <graph*> s;
	int select;
	bool flag=true;
	cout<<"请输入起始节点索引号";
	cin>>select;
	s.push(&n[select]);
	n[select].state=IN;
	cout<<"DFS:";
	graph *cur;
	FLAG2:
	while(s.size()){
		cur=s.top();
		while(flag){
			for(int i=0;i<cur->next.size();i++){
				if(n[ (cur->next[i]) ].state==NOTIN){
					s.push(&n[ (cur->next[i]) ]);
					n[ (cur->next[i]) ].state=IN;
					flag=true;//如果能继续深入则为true
					break;
				}
				else{
					flag=false;//否则为false
				}
			}
			
			cur=s.top();
			if(!flag){//flag为false时不能深入了，则输出值后踢出去
				s.pop();
				cout<<cur->value<<" ";
				n[cur->pos].state=OUT;
				if(s.size()){//栈有才赋值，否则直接退出循环
					cur=s.top();//如果不判断的话会赋值而出错
				}
				else{
					break;
				}
				flag=true;
			}
				
		}
	}
	for(int i=0;i<k;i++){
		if(n[i].state==NOTIN){//把没有遍历的值放进去遍历
			s.push(&n[i]);
			flag=true;//修改flag使其能参与遍历
			goto FLAG2;
		}
	}
	for(int i=0;i<k;i++){
		n[i].state=NOTIN;//初始化状态，让下次能继续重新遍历
	}
}


//拓扑排序

void TP_sort(graph n[],int k){
	for(int i=0;i<k;i++){
		if(n[i].indeg==0){
			n[i].indeg--;
			cout<<n[i].value<<" ";
			n[i].state=OUT;//更新状态
			for(int j=0;j<n[i].next.size();j++){
				n[ (n[i].next[j]) ].indeg--;//更新入度
			}
			i=0;//重新全部遍历
		}
	}
	for(int i=0;i<k;i++){
		if(n[i].state==NOTIN){//如果还有数据没有被遍历则说明一定有环
			cout<<endl<<"此图存在环！"<<endl;
		}
	}
}


//基于邻接矩阵实现最小生成树
int main(){
//  邻接表实现有向图
// 	int n;
//	cout<<"请输入顶点数:";
//	cin>>n;
//	graph node[n];
//	create_graph1(node,n);

//	BFS(node,n);
//	DFS(node,n);
//	TP_sort(node,n);




//  邻接矩阵实现无向图
	graph node[LEN];
	create_graph2(node,LEN);
	for(int i=0;i<LEN;i++){
		for(int j=0;j<LEN;j++){
			cout<<m.connect[i][j]<<" ";
		}
		cout<<endl;
	}



	return 0;
}
