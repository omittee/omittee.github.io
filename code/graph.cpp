#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <queue>
#include <stack>


#define NOTIN 0
#define IN 1
#define OUT 2

#define LEN 3//�ڽӾ������
using namespace std;
class graph{
public:
	int value;
	int pos;
	vector <int> next;//�����ڽӵ������ţ�size()��Ϊ����    �ڽӱ�
	int state=NOTIN;//��¼�Ƿ�������
	int indeg=0;//��¼���
};

struct matrix{
	int connect[LEN][LEN];
}m;


//�ڽӱ�ʵ������ͼ��
graph create_graph1(graph *node,int n){
	for(int i=0;i<n;i++){
		cout<<"�������"<<i<<"������ֵ��";
		cin>>node[i].value;
		node[i].pos=i;
	}
	for(int i=0;i<n;i++){
		cout<<"�������"<<i<<"��������ڽӵ������ţ���Ӣ�Ķ���,����"
		<<endl<<"����������Ϊ0��"<<n-1<<",û���ڽӵ�������-1��"<<endl;
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
			node[ (node[i].next[j]) ].indeg++;//��¼���
		}
	}
}
//�ڽӾ���ʵ������ͼ��
int* create_graph2(graph *node,int n){
	for(int i=0;i<n;i++){
		cout<<"�������"<<i<<"������ֵ��";
		cin>>node[i].value;
		node[i].pos=i;
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			m.connect[i][j]=0;
		}
	}
	for(int i=0;i<n;i++){
		cout<<"�������"<<i<<"��������ڽӵ������ź���ӦȨ�أ���ʽΪ num1:weight1,num2:weight2,��������ΪӢ�ķ�"
		<<endl<<"����������Ϊ0��"<<n-1<<",û���ڽӵ�������-1:0 "<<endl;
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
			node[ (node[i].next[j]) ].indeg++;//��¼���
		}
	}
	
//  ��ӡ�ڽӾ���
//	for(int i=0;i<n;i++){
//		for(int j=0;j<n;j++){
//			cout<<m.connect[i][j]<<" ";
//		}
//		cout<<endl;
//	}

}


//�����ڽӱ�ʵ�ֱ���
void BFS(graph *n,int k){
	queue <graph*> q;
	int select;
	cout<<"��������ʼ�ڵ�������";
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
		if(n[i].state==NOTIN){//��û�б�����ֵ�Ž�ȥ����
			q.push(&n[i]);
			goto FLAG1;
		}
	}
	for(int i=0;i<k;i++){
		n[i].state=NOTIN;//��ʼ��״̬�����´��ܼ������±���
	}
}

void DFS(graph *n,int k){
	stack <graph*> s;
	int select;
	bool flag=true;
	cout<<"��������ʼ�ڵ�������";
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
					flag=true;//����ܼ���������Ϊtrue
					break;
				}
				else{
					flag=false;//����Ϊfalse
				}
			}
			
			cur=s.top();
			if(!flag){//flagΪfalseʱ���������ˣ������ֵ���߳�ȥ
				s.pop();
				cout<<cur->value<<" ";
				n[cur->pos].state=OUT;
				if(s.size()){//ջ�вŸ�ֵ������ֱ���˳�ѭ��
					cur=s.top();//������жϵĻ��ḳֵ������
				}
				else{
					break;
				}
				flag=true;
			}
				
		}
	}
	for(int i=0;i<k;i++){
		if(n[i].state==NOTIN){//��û�б�����ֵ�Ž�ȥ����
			s.push(&n[i]);
			flag=true;//�޸�flagʹ���ܲ������
			goto FLAG2;
		}
	}
	for(int i=0;i<k;i++){
		n[i].state=NOTIN;//��ʼ��״̬�����´��ܼ������±���
	}
}


//��������

void TP_sort(graph n[],int k){
	for(int i=0;i<k;i++){
		if(n[i].indeg==0){
			n[i].indeg--;
			cout<<n[i].value<<" ";
			n[i].state=OUT;//����״̬
			for(int j=0;j<n[i].next.size();j++){
				n[ (n[i].next[j]) ].indeg--;//�������
			}
			i=0;//����ȫ������
		}
	}
	for(int i=0;i<k;i++){
		if(n[i].state==NOTIN){//�����������û�б�������˵��һ���л�
			cout<<endl<<"��ͼ���ڻ���"<<endl;
		}
	}
}


//�����ڽӾ���ʵ����С������
int main(){
//  �ڽӱ�ʵ������ͼ
// 	int n;
//	cout<<"�����붥����:";
//	cin>>n;
//	graph node[n];
//	create_graph1(node,n);

//	BFS(node,n);
//	DFS(node,n);
//	TP_sort(node,n);




//  �ڽӾ���ʵ������ͼ
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
