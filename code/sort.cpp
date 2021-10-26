#include <iostream>

#define LEN 10
using namespace std;
//直接插入排序
/*最坏时间复杂度：1+2+...+n-1=n(n-1)/2	O(n^2)	空间复杂度O(1) 	稳定*/
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
/*最坏时间复杂度：O(n^2)	空间复杂度O(1) 	稳定*/
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
/*最坏时间复杂度：O(n^2)	空间复杂度O(n) 	稳定*/
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

//希尔排序
/*最坏时间复杂度：O(n^2)（采用希尔增量）	空间复杂度O(1) 	不稳定*/
void XE_sort(int a[],int n){
	int i,j,temp;
	for(int gap=n/2;gap>0;gap/=2){//取希尔增量
		for(i=gap;i<n;i++){
			j=i;
			temp=a[j];//保存a[j]值
			while(j-gap>=0&&temp<a[j-gap]){//子序列进行直接插入排序
				a[j]=a[j-gap];
				j-=gap;
			}
			a[j]=temp;
		}
	}

}


//快速排序
/*最坏时间复杂度：O(n^2)	平均时间复杂度O(nlogn)	最坏空间复杂度O(n)	平均空间复杂度O(logn) 	不稳定*/
void Q_sort(int a[],int begin,int end){
	if(begin<end){
		int i=end,j=begin,temp=a[begin];
		while(i>j){
			while(i>j&&a[i]>temp){
				i--;
			}
			if(i>j){
				a[j]=a[i];//交换
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
		a[j]=temp;//最后一个交换的进行赋值
		Q_sort(a,begin,i-1);//递归
		Q_sort(a,i+1,end);
	}
}

//归并排序
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

	//希尔排序
//  XE_sort(arr,LEN);

	//快速排序
//	Q_sort(arr,0,LEN);

	//归并排序
	M_sort(arr,LEN);
	for(int i=0;i<LEN;i++){
		cout<<arr[i]<<" ";
	}
	return 0;
}
