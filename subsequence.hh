#include <cstdio>
#include <iostream>

using namespace std;

struct array{
	int n;
	int *a;
	array(int in): n(in){
		a=new int[n];
		for(int i=0; i<in; i++)
			a[i]=i;
	}
	~array(){
		delete a;
	}
	void print(){
		for(int i=0; i<n; i++)
			cout << a[i] << ' ';
		cout << '\n';
	}
	void set(int x, int v){//index, value
		a[x]=v;
	}
	int get(int x){//index
		return a[x];	
	}
	void align(int x){//index
		a[x]++;
		for(int i=x+1; i<n; i++){
			a[i]=a[i-1]+1;	
		}
	}
	int& operator[](int x){//index
		return a[x];
	}
};


void sub(int n, int r){//Get num, range//Finished
	array a(n);
	int index=n-1;
	while(true){
		while(a[index]>r-n+index){
			if(--index<0)
				return;
			a.align(index);
		}
		index=n-1;
		a.print();
		a[index]++;
	}
}

