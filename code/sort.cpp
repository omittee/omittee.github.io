#include <iostream>
#include <cstdlib>
#define LEN 10
using namespace std;
//ֱ�Ӳ�������
/*�ʱ�临�Ӷȣ�1+2+...+n-1=n(n-1)/2	O(n^2)	�ռ临�Ӷ�O(1) 	�ȶ�*/
void SI_sort(int a[],int n){
	int i,j,temp;
	for(i=1;i<n;i++){
		if(a[i]<a[i-1]){//�������е�һ����С����������������
			j=i-1;
			temp=a[i];//�������ֵ������������������ƶ��Ŀռ�
			for(;j>=0;j--){
				if(temp<a[j]){
					a[j+1]=a[j];//���������д���temp�Ķ����ƣ�ֱ��û�д���temp����ֹͣ�ƶ�
				}
				else{
					break;
				}
			}
			a[j+1]=temp;//�������в��ֺ��ƣ�ǰ���ڳ��ռ���Խ��и�ֵ������tempֵ
		}
	}
}
//�۰��������
/*�ʱ�临�Ӷȣ�O(n^2)	�ռ临�Ӷ�O(1) 	�ȶ�*/
void BI_sort(int a[],int n){
	int i,start=0,end,temp;
	for(i=1;i<n;i++){
		if(a[i]<a[i-1]){//�������е�һ����С����������������
			end=i-1;
			temp=a[i];//�������ֵ������������������ƶ��Ŀռ�
			while(start<=end){
				if(temp<a[(start+end)/2]){//�����������м�ֵ�Ƚ�
					end=(start+end)/2-1;//��С��Χ
				}
				else{
					start=(start+end)/2+1;//��С��Χ
				}
			}
			for(int s=i-1;s>=end+1;s--){
				a[s+1]=a[s];//��end+1����������ĩ������
			}
			a[end+1]=temp;//�������в��ֺ��ƣ�ǰ���ڳ��ռ���Խ��и�ֵ������tempֵ
		}
	}
}
//·��������
/*�ʱ�临�Ӷȣ�O(n^2)	�ռ临�Ӷ�O(n) 	�ȶ�*/
void RI_sort(int a[],int n){
	int b[n];
	b[0]=a[0];
	int i,start=0,end=0,s;
	for(i=1;i<n;i++){
		if(a[i]<b[start]){//�������е�һ����С������������С����
            start=(start-1+n)%n;
            b[start]=a[i];
		}
		else if(a[i]>b[end]){//�������е�һ����������������������
            end=(end+1+n)%n;
            b[end]=a[i];
		}
		else{//a[i]���������������ֵ����Сֵ֮��
			s=(end+1+n)%n;
			while(b[(s-1+n)%n]>a[i]){//ֱͬ�Ӳ�������
				b[(s+n)%n]=b[(s-1+n)%n];
				s=(s-1+n)%n;
			}
			b[(s+n)%n]=a[i];
			end=(end+1+n)%n;//�������ֵ
		}
	}
	for(int i=0;i<n;i++){
		a[i]=b[start];//���������е���Сֵ�������ֵ
		start=(start+1+n)%n;
	}
}

//ϣ������
/*�ʱ�临�Ӷȣ�O(n^2)������ϣ��������	�ռ临�Ӷ�O(1) 	���ȶ�*/
void XE_sort(int a[],int n){
	int i,j,temp;
	for(int gap=n/2;gap>0;gap/=2){//ȡϣ������
		for(i=gap;i<n;i++){
			j=i;
			temp=a[j];//����a[j]ֵ
			while(j-gap>=0&&temp<a[j-gap]){//�����н���ֱ�Ӳ�������
				a[j]=a[j-gap];
				j-=gap;
			}
			a[j]=temp;
		}
	}

}


//��������
/*�ʱ�临�Ӷȣ�O(n^2)	ƽ��ʱ�临�Ӷ�O(nlogn)	��ռ临�Ӷ�O(n)	ƽ���ռ临�Ӷ�O(logn) 	���ȶ�*/
void Q_sort(int a[],int begin,int end){
	if(begin<end){
		int i=end,j=begin,temp=a[begin];
		while(i>j){
			while(i>j&&a[i]>temp){
				i--;
			}
			if(i>j){
				a[j]=a[i];//����
				j++;
			}
			while(i>j&&a[j]<temp){
				j++;
			}
			if(i>j){
				a[i]=a[j];
				i--;
			}
		}
		a[j]=temp;//���һ�������Ľ��и�ֵ
		Q_sort(a,begin,i-1);//�ݹ�
		Q_sort(a,i+1,end);
	}
}

//�鲢����
/*�ʱ�临�Ӷȣ�O(nlogn)	�ռ临�Ӷ�O(n) 	�ȶ�*/
void M_sort(int a[],int n){
	int b[n];
	for(int unit=1;unit<n;unit*=2){
		for(int start=0;start<n;start+=unit*2){
			int down=start,mid=min(start+unit,n),up=min(start+unit*2,n);
			int k = down;
            int start1 = down, end1 = mid;
            int start2 = mid, end2 = up;
            while(start1<end1&&start2<end2){
				b[k++]=a[start1]<a[start2]?a[start1++]:a[start2++];
			}
			while (start1 < end1){
                b[k++] = a[start1++];
			}
            while (start2 < end2){
                b[k++] = a[start2++];
			}
		}
		for(int i=0;i<n;i++){
			a[i]=b[i];
			cout<<b[i]<<" ";
		}
		cout<<endl;
	}
}



//������
class list{
public:
	int value;//ֵ
	int next;//��һ��������
};
//���������
/*�ʱ�临�Ӷȣ�O(n^2)	�ռ临�Ӷ�O(n) 	�ȶ�*/
void L_sort(int n){
	list arr[n+1];//��������
	int i;
	arr[0].value=n;
	arr[0].next=1;
	arr[1].next=-1;
	for(i=1;i<=n;i++){
		cin>>arr[i].value;//������ֵ��Ͳ�������
		for(int s=0,fore;s!=-1;fore=s/*��¼������*/,s=arr[s].next/*���º����������*/){
			if(s>0&&arr[s].value>arr[i].value){
				arr[i].next=arr[fore].next;//��ǰһ����nextָ������next
				arr[fore].next=i;//�Ѳ���������Ÿ�ֵ��ǰһ����next
				break;
			}
			else if(arr[s].next==-1){
				arr[s].next=i;
				arr[i].next=-1;
			}
		}
	}
	
	for(int s=0;s!=-1;s=arr[s].next){
		if(s!=0){
			cout<<arr[s].value<<" ";
		}
	}
}


//������
/*�ʱ�临�Ӷȣ�O(nlogn)	�ռ临�Ӷ�O(1) 	���ȶ�*/
void do_Dswap(int a[],int start,int end){
	int father=start;
	int son=start*2+1;
	int temp;
	while(son<=end){
		if(son<end-1&&a[son]<a[son+1]){//�ҵ�����Ӵ�
			son++;
		}
		if(a[son]<a[father]){
			return;
		}
		else{
			temp=a[son];
			a[son]=a[father];
			a[father]=temp;
			father=son;//���������������Ӵ����Ͻ�������
			son=son*2+1;
		}
	}
}
void D_sort(int a[],int n){
	for(int i=n/2-1;i>=0;i--){
		do_Dswap(a,i,n-1);//��ʼ�����Ѵ�����Ͻ���������ֱ������
	}
	for(int i=n-1,temp;i>0;i--){
		if(a[0]>a[i]){
			temp=a[i];
			a[i]=a[0];
			a[0]=temp;//������ײ����ֵ����
		}
		do_Dswap(a,0,i-1);//�������°Ѵ�����Ͻ����������ײ����ֵ�˳�����
	}
}




int main(){

	int arr[LEN];
	for(int i=0;i<LEN;i++){
		cin>>arr[i];
	}	
	
	
	//ֱ�Ӳ�������
//	SI_sort(arr,LEN);
	
	
	//�۰��������
//	BI_sort(arr,LEN);
	
	//·��������
//	RI_sort(arr,LEN);

	//ϣ������
//  XE_sort(arr,LEN);

	//��������
//	Q_sort(arr,0,LEN);

	//�鲢����
//	M_sort(arr,LEN);

	//������
//	D_sort(arr,LEN);

	
	for(int i=0;i<LEN;i++){
		cout<<arr[i]<<" ";
	}

	//���������
//	L_sort(LEN);

	system("pause");
	return 0;
}
