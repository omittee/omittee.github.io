#include <iostream>
#define LEN 5
using namespace std;
//直接插入排序
void SI_sort(int a[],int n){
	int i,j,temp;
	for(i=1;i<n;i++){
		if(a[i]<a[i-1]){//无序序列第一个数小于有序序列最后的数
			j=i-1;
			temp=a[i];//保存该数值，让有序序列有向后移动的空间
			for(;j>=0;j--){
				if(temp<a[j]){
					a[j+1]=a[j];//有序序列中大于temp的都后移，直到没有大于temp的则停止移动
				}
				else{
					break;
				}
			}
			a[j+1]=temp;//有序序列部分后移，前面腾出空间可以进行赋值，插入temp值
		}
	}
}
//折半插入排序
void BI_sort(int a[],int n){
	int i,start=0,end,temp;
	for(i=1;i<n;i++){
		if(a[i]<a[i-1]){//无序序列第一个数小于有序序列最后的数
			end=i-1;
			temp=a[i];//保存该数值，让有序序列有向后移动的空间
			while(start<=end){
				if(temp<a[(start+end)/2]){//与有序序列中间值比较
					end=(start+end)/2-1;//缩小范围
				}
				else{
					start=(start+end)/2+1;//缩小范围
				}
			}
			for(int s=i-1;s>=end+1;s--){
				a[s+1]=a[s];//从end+1到有序序列末都后移
			}
			a[end+1]=temp;//有序序列部分后移，前面腾出空间可以进行赋值，插入temp值
		}
	}
}
//路插入排序
void RI_sort(int a[],int n){
	int b[n];
	b[0]=a[0];
	int i,start=0,end=0,s;
	for(i=1;i<n;i++){
		if(a[i]<b[start]){//无序序列第一个数小于有序序列最小的数
            start=(start-1+n)%n;
            b[start]=a[i];
		}
		else if(a[i]>b[end]){//无序序列第一个数大于有序序列最大的数
            end=(end+1+n)%n;
            b[end]=a[i];
		}
		else{//a[i]介于有序序列最大值与最小值之间
			s=(end+1+n)%n;
			while(b[(s-1+n)%n]>a[i]){//同直接插入排序
				b[(s+n)%n]=b[(s-1+n)%n];
				s=(s-1+n)%n;
			}
			b[(s+n)%n]=a[i];
			end=(end+1+n)%n;//更新最大值
		}
	}
	for(int i=0;i<n;i++){
		a[i]=b[start];//从有序序列的最小值赋到最大值
		start=(start+1+n)%n;
	}
}



int main(){

	int arr[LEN];
	for(int i=0;i<LEN;i++){
		cin>>arr[i];
	}
	//直接插入排序
//	SI_sort(arr,LEN);
	
	
	//折半插入排序
//	BI_sort(arr,LEN);
	
	//路插入排序
//	RI_sort(arr,LEN);


	for(int i=0;i<LEN;i++){
		cout<<arr[i]<<" ";
	}
	return 0;
}
