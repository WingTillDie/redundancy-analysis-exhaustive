#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstdint>
#include <sstream>
#include <fstream>
#include "subsequence.hh"
//#define debug

/*
void mem_print(int rdim, int cdim; bool mem[rdim][cdim], int rdim, int cdim){
	for(int i=0; i<rdim; i++){
		for(int j=0; j<cdim; j++)
			printf("%d ", mem[i][j]);
		printf("\n");
	}
}
void mem_init(int rdim, int cdim; bool mem[rdim][cdim], int rdim, int cdim){
	for(int i=0; i<rdim; i++){
		for(int j=0; j<cdim; j++)
			mem[i][j]=0;
	}
}
*/

/*
void giveup_test(int rdim, int cdim){//Give up lowest numbers but harder to create r and c of point
	int r=(RAND_MAX+1U)%(rdim*cdim);
	if(random()<r)
		printf("%d ", 1);//giveup
	else
		printf("%d ", 0);
}
*/

struct Point{
	int r;
	int c;
	Point(){};
	Point(int rIn, int cIn) : r(rIn), c(cIn){
	}
	int operator==(Point p){
		if(r==p.r && c==p.c)
			return 1;
		else
			return 0;
	}
	int operator>(Point p){//Just sort by r
		return r>p.r;
	}
	int operator<(Point p){//Just sort by r
		return r<p.r;
	}
	string repr_compact(){
		ostringstream buffer;
		buffer << r << ',' << c;
		return buffer.str();
	}
};

ostream& operator<<(ostream& os, Point p){
	cout << '(' << p.r << ',' << p.c << ")";
	return os;
}

template <typename T>
struct List{
	T data;//What is default value
	struct List *next=NULL;
};

struct cList{//Column list
	int c=-1;
	struct cList *next=NULL;
};

	struct cStack;
struct rList{//Row list///TODO Need c size?
	int r=-1;
	struct rList *next=NULL;
	cStack *child=NULL;
};

//Templatelize? data as struct? Only insertion is somewaht different?
//Check data type to determine action? Inheritance with override?
//Just overloading with single and 2 parameters?
/*
struct Tree_old{//More like stack for cList
	rList *head=NULL;
	int size=0;
	//Print tree, insert, free
	~Tree_old(){//TODO implement free c
		clear();
	}
	void clear(){//TODO implement free c
		rList *current=head;
		for(int i=0; i<size; i++){
			rList *next=current->next;
			delete current;
			current=next;
		}
		head=NULL;
		size=0;
	}
	int insert(Point p){//Return if there's duplication then higher function call again
		int r=p.r;
		int c=p.c;//Related features not implemented
		if(head==NULL){
			head=new rList;//Lack destructor
			head->r=r;
			//Lack c
			size++;
			return 0;//Success
		}else{//TODO: Duplication is determined by both r and c//Insert c datas
			rList *previous=NULL;
			rList *current=head;
			while(current && (r > current->r)){
				//Check if next is NULL
				previous=current;
				current=current->next;
			}
			if(!current){//Is largest
				rList *newNode=new rList;
				newNode->r=r;
				//TODO: implement c
				previous->next=newNode;
				size++;
				return 0;
			}
			if(current->r == r){
#ifdef debug
				printf("Duplicate!\n");
#endif
				return 1;//TODO: also check for c
			} else {
				rList *newNode=new rList;
				newNode->r=r;
				//TODO: implement c
				previous->next=newNode;
				newNode->next=current;
				size++;
				return 0;
			}
		}
	}
	void print_rList(){
		rList *current=head;
		if(current==NULL){
			printf("rList is empty.\n");
			return;
		}
		for(int i=0; i<size; i++){
			printf("%d ", current->r);
			current=current->next;
		}
		printf("\n");
	}
};
*/

template <typename T>
struct Stack{
	List<T> *head=NULL;
	int size=0;
	//Print tree, insert, free
	Stack(){}
	Stack(T c){
		insert(c);
	}
	~Stack(){//TODO implement free c
		clear();
	}
	void clear(){//TODO implement free c
		List<T> *current=head;
		for(int i=0; i<size; i++){
			List<T> *next=current->next;
			delete current;
			current=next;
		}
		head=NULL;
		size=0;
	}
	//TODO data type T
	int insert(T data){//Return if there's duplication then higher function call again
		//c Related features not implemented
		if(head==NULL){
			head=new List<T>;//Lack destructor
			head->data=data;
			//Lack c
			
			size++;
			return 0;//Success
		}else{//TODO: Duplication is determined by both r and c//Insert c datas
			List<T> *previous=NULL;
			List<T> *current=head;
			while(current && (data > current->data)){
				//Check if next is NULL
				previous=current;
				current=current->next;
			}
			if(!current){//Is largest
				List<T> *newNode=new List<T>;
				newNode->data=data;
				//TODO: implement c
				previous->next=newNode;
				size++;
				return 0;
			}
			if(current->data == data){
#ifdef debug
				printf("Duplicate!\n");
#endif
				return 1;//TODO: also check for c
			}else if(previous == NULL){//Is smallest
				List<T> *newNode=new List<T>;
				newNode->data=data;
				newNode->next=head;
				head=newNode;
				size++;
				return 0;
			} else {
				List<T> *newNode=new List<T>;
				newNode->data=data;
				//TODO: implement c
				previous->next=newNode;
				newNode->next=current;
				size++;
				return 0;
			}
		}
	}
	void print_List(){
		List<T> *current=head;
		if(current==NULL){
			cout << typeid(this).name() << " is empty.\n";
			//printf("List<T> is empty.\n");
			return;
		}
		for(int i=0; i<size; i++){
			//printf("%d ", current->data);
			cout << current->data << ' ';
			current=current->next;
		}
		printf("\n");
	}
	void print(){print_List();}
};

struct cStack{
	cList *head=NULL;
	int size=0;
	//Print tree, insert, free
	cStack(){}
	cStack(int c){
		insert(c);
	}
	cStack(cStack &s){//How to const cStack
		/*
		for(int i=0; i<s.size; i++)
			this->insert(s[i]); //Can be faster by manipulating cList
		*/
		insert(s);//Small problem not copy but is insert actually
	}
	~cStack(){//TODO implement free c
		clear();
	}
	void insert(cStack &s){
		for(int i=0; i<s.size; i++)
			insert(s[i]); //Can be faster by manipulating cList
	}
	operator()(cStack &s){
		clear();
		insert(s);
	}
	int& operator[](int n){
		cList *current=head;
		for(int i=0; i<n; i++)
			current=current->next;
		return current->c;
	}
	void clear(){//TODO implement free c
		cList *current=head;
		for(int i=0; i<size; i++){
			cList *next=current->next;
			delete current;
			current=next;
		}
		head=NULL;
		size=0;
	}
	int insert(int c){//Return if there's duplication then higher function call again
		//c Related features not implemented
		if(head==NULL){
			head=new cList;//Lack destructor
			head->c=c;
			//Lack c
			
			size++;
			return 0;//Success
		}else{//TODO: Duplication is determined by both r and c//Insert c datas
			cList *previous=NULL;
			cList *current=head;
			while(current && (c > current->c)){
				//Check if next is NULL
				previous=current;
				current=current->next;
			}
			if(!current){//Is largest
				cList *newNode=new cList;
				newNode->c=c;
				//TODO: implement c
				previous->next=newNode;
				size++;
				return 0;
			}
			if(current->c == c){
#ifdef debug
				printf("Duplicate!\n");
#endif
				return 1;//TODO: also check for c
			}else if(previous == NULL){//Is smallest
				cList *newNode=new cList;
				newNode->c=c;
				newNode->next=head;
				head=newNode;
				size++;
				return 0;
			} else {
				cList *newNode=new cList;
				newNode->c=c;
				//TODO: implement c
				previous->next=newNode;
				newNode->next=current;
				size++;
				return 0;
			}
		}
	}
	void print_cList(){
		cList *current=head;
		if(current==NULL){
			printf("cList is empty.\n");
			return;
		}
		for(int i=0; i<size; i++){
			printf("%d ", current->c);
			current=current->next;
		}
		printf("\n");
	}
	void print(){print_cList();}
};


struct Tree{
	//TODO Should be child rather than new cStk
	rList *head=NULL;
	int size=0;
	//Print tree, insert, free
	virtual ~Tree(){//TODO implement free c
		clear();
	}
	void clear(){//TODO implement free c
		rList *current=head;
		for(int i=0; i<size; i++){
			rList *next=current->next;
			delete current->child;
			delete current;
			current=next;
		}
		head=NULL;
		size=0;
	}
	cStack& operator[](int n){
		rList *current=head;
		for(int i=0; i<n; i++)
			current=current->next;
		return *current->child;
	}
	int sol(array& arr){
		cStack s;
		for(int i=0; i<arr.n; i++)
			s.insert((*this)[arr[i]]);
                return s.size;
	}
	int C(int n){//C r get n in combinatorics
		if(n==0) return 0;
		int r=size;
		array a(n);
		int index=n-1;
		int ret=-1;
		while(true){
			while(a[index]>r-n+index){
				if(--index<0){
#ifdef debug
					cout << '\n';
#endif
					return ret;
				}
				a.align(index);
			}
			index=n-1;
			int tmp=sol(a);
			if(tmp<ret||ret==-1)
				ret=tmp;
#ifdef debug
			a.print();
			cout << ':' << sol(a) << '\n';//Just for debugging
#endif
			a[index]++;
		}
	}
	array* C_Which(int n){//Get exactly which combination for debugging
		if(n==0) return NULL;
		int r=size;
		array a(n);
		int index=n-1;
		int ret=-1;
		array *arr_r=new array(n);//Lack destructor
		while(true){
			while(a[index]>r-n+index){
				if(--index<0){
#ifdef debug
					cout << '\n';
#endif
					return arr_r;//TODO problem
				}
				a.align(index);
			}
			index=n-1;
			int tmp=sol(a);
			if(tmp<ret||ret==-1){
				ret=tmp;
				*arr_r=a;
			}
#ifdef debug
			a.print();
			cout << ':' << sol(a) << '\n';//Just for debugging
#endif
			a[index]++;
		}
	}
	virtual int insert(Point p){//Return if there's duplication then higher function call again
		int r=p.r;
		int c=p.c;//Related features not implemented
		if(head==NULL){
			head=new rList;//Lack destructor
			head->r=r;
			//Lack c
			head->child=new cStack;//Lack destructor
			size++;
			head->child->insert(c);
			return 0;//Success
		}else{//TODO: Duplication is determined by both r and c//Insert c datas
			rList *previous=NULL;
			rList *current=head;
			while(current && (r > current->r)){
				//Check if next is NULL
				previous=current;
				current=current->next;
			}
			if(!current){//Is largest
				rList *newNode=new rList;
				newNode->r=r;
				//TODO: implement c
				previous->next=newNode;
				size++;
				newNode->child=new cStack;
				newNode->child->insert(c);
				return 0;
			}
			if(current->r == r){
				if(!current->child)
					current->child=new cStack;
				if(current->child->insert(c)){
					return 1;
				} else {
					return 0;
				}//Also check for c
			} else if(previous == NULL){//Is smallest
				rList *newNode=new rList;
				newNode->r=r;
				newNode->next=head;
				head=newNode;
				size++;
				newNode->child=new cStack;
				newNode->child->insert(c);
				return 0;
			} else {
				rList *newNode=new rList;
				newNode->r=r;
				//TODO: implement c
				previous->next=newNode;
				newNode->next=current;
				size++;
				newNode->child=new cStack;
				newNode->child->insert(c);
				return 0;
			}
		}
	}
	void print_rList(){
		rList *current=head;
		if(current==NULL){
			printf("rList is empty.\n");
			return;
		}
		for(int i=0; i<size; i++){
			printf("%d ", current->r);
			current=current->next;
		}
		printf("\n");
	}
	void print_tree(){
		rList *current=head;
		if(current==NULL){
			printf("Tree is empty.\n");
			return;
		}
		for(int i=0; i<size; i++){
			printf("%d: ", current->r);
			current->child->print_cList();
			current=current->next;
		}
		cout << '\n'; 
	}
	void print(){print_tree();}
};

struct STree : Tree{//Solution list//TODO Don't insert if larger
	int insert(Point p) override{//Return if there's duplication then higher function call again
		int r=p.r;
		int c=p.c;//Related features not implemented
		if(head==NULL){
			head=new rList;//Lack destructor
			head->r=r;
			//Lack c
			head->child=new cStack;//Lack destructor
			size++;
			head->child->insert(c);
			return 0;//Success
		}else{//TODO: Duplication is determined by both r and c//Insert c datas
			rList *previous=NULL;
			rList *current=head;
			while(current && (r > current->r)){
				//Check if next is NULL
				previous=current;
				current=current->next;
			}
			if(!current){//Is largest
				rList *newNode=new rList;
				newNode->r=r;
				//TODO: implement c
				previous->next=newNode;
				size++;
				newNode->child=new cStack;
				newNode->child->insert(c);
				return 0;
			}
			if(current->r == r){
				if(!current->child)
					current->child=new cStack;
				if(current->child->insert(c)){
					return 1;
				} else {
					return 0;
				}//Also check for c
			} else if(previous == NULL){//Is smallest
				rList *newNode=new rList;
				newNode->r=r;
				newNode->next=head;
				head=newNode;
				size++;
				newNode->child=new cStack;
				newNode->child->insert(c);
				return 0;
			} else {
				rList *newNode=new rList;
				newNode->r=r;
				//TODO: implement c
				previous->next=newNode;
				newNode->next=current;
				size++;
				newNode->child=new cStack;
				newNode->child->insert(c);
				return 0;
			}
		}
	}
};

Point point_gen(int rdim, int cdim){
	int r/*remainder*/=(RAND_MAX+1U)%(rdim*cdim);
	int tmp=random();
	while(tmp>RAND_MAX-r){
		tmp=random();
	}
	tmp%=rdim*cdim;
	Point p;
	p.c=tmp%cdim;
	p.r=tmp/cdim;
	return p;
}

Tree points_gen(int n, int rdim, int cdim){//n: faults
	Tree a;
	for(int i=0; i<n; i++){
		int r;
		do {
			r=a.insert(point_gen(rdim, cdim));
		} while (r);
	}
	return a;
}


Tree points_gen_print(int n, int rdim, int cdim){//n: faults
	Tree a;
	for(int i=0; i<n; i++){
		int r;
		Point p;
		do {
			p=point_gen(rdim, cdim);
			r=a.insert(p);
		} while (r);
		cout << p.repr_compact() << ',';
	}
	return a;
}

Tree points_gen_fprint(ofstream& fout, int n, int rdim, int cdim){//n: faults
	Tree a;
	for(int i=0; i<n; i++){
		int r;
		Point p;
		do {
			p=point_gen(rdim, cdim);
			r=a.insert(p);
		} while (r);
		fout << p.repr_compact() << ',';
	}
	return a;
}

//TODO A function that return solution list(multiple (nRow, nCol))//Not finished
Point* solution_list(Tree& t){//Don't insert if used is larger than previous record//Need tree?
	//int i=1;//TODO change to for loop
	//sub(i, t.size);
	Point *sol=new Point[t.size];//TODO: Need destructor
	sol[0]={t.size, 0};
	//Try select 2 index and solve//Get all children of index and put it into stack to remove duplicate
	
	return sol;//Change to tree?
}

void print_sol(int n, int rdim, int cdim){//n: faults
	Stack<Point>* sol=new Stack<Point>;
	Tree a=points_gen(n, rdim, cdim);
	cout << "Tree:\n";
	a.print();
	cout << "Sol:\n";
	cStack s;
	for(int i=0; i<=a.size; i++){
		sol->insert({a.size-i, a.C(i)});
		cout << a.size-i << ' ' << a.C(i) << ": ";
		array *arr=a.C_Which(i);
		if(arr!=NULL){
			arr->print();
			for(int i=0; i<arr->n; i++)
				s.insert(a[(*arr)[i]]);
			cout << ": ";
			s.print();
		}
		cout << '\n';
	}
	sol->print();
	delete sol;
}

Stack<Point>& return_sol(int n, int rdim, int cdim){//n: faults
	Stack<Point>* sol=new Stack<Point>;
	Tree a=points_gen(n, rdim, cdim);
	cout << "Tree:\n";
	a.print();
	cout << "Sol:\n";
	cStack s;
	for(int i=0; i<=a.size; i++){
		sol->insert({a.size-i, a.C(i)});
		cout << a.size-i << ' ' << a.C(i) << ": ";
		array *arr=a.C_Which(i);
		if(arr!=NULL){
			arr->print();
			for(int i=0; i<arr->n; i++)
				s.insert(a[(*arr)[i]]);
			cout << ": ";
			s.print();
		}
		cout << '\n';
	}
	sol->print();
	return *sol;
}

int print_repairable(int sr, int sc, int n, int rdim, int cdim){//1 is reparable, 0 is not reparable//n:faults sr:spare row sc:spare column	
	int ret=0;
	Tree a=points_gen(n, rdim, cdim);
	cout << "Tree:\n";
	a.print();
	cout << "Sol:\n";
	cStack s;
	for(int i=0; i<=a.size; i++){//Can check lesser?
		int row=a.size-i;
		int col=a.C(i);
		//sol->insert({row, col});
		cout << row << ' ' << col;
		if(row<=sr && col<=sc)
			cout << "Repairable\n";
		/*
		array *arr=a.C_Which(i);
		if(arr!=NULL){
			arr->print();
			for(int i=0; i<arr->n; i++)
				s.insert(a[(*arr)[i]]);
			cout << ": ";
			s.print();
		}
		*/
		cout << '\n';
	}
}

//Remove solutions in solution list that are bad than other solution? But it will be slower than direct comparison?
int repairable_brief(int sr, int sc, int n, int rdim, int cdim){//1 is reparable, 0 is not reparable//n:faults sr:spare row sc:spare column//Brieft output
	int ret=0;
	Tree a=points_gen(n, rdim, cdim);
	//cout << "Tree:\n";
	a.print();
	//cout << "Sol:\n";
	//cStack s;
	for(int i=0; i<=a.size; i++){//Can check lesser?
		int row=a.size-i;
		int col=a.C(i);
		//sol->insert({row, col});
		if(row<=sr && col<=sc){
			cout << "Repairable\n";
			ret=1;
			return ret;
		}
		/*
		array *arr=a.C_Which(i);
		if(arr!=NULL){
			arr->print();
			for(int i=0; i<arr->n; i++)
				s.insert(a[(*arr)[i]]);
			cout << ": ";
			s.print();
		}
		*/
	}
	cout << "NOT repairable\n";
	return ret;
}

int  repairable_brief_fprint(ofstream& points, ofstream& label, int sr, int sc, int n, int rdim, int cdim){//1 is reparable, 0 is not reparable//n:faults sr:spare row sc:spare column//Brieft output
	int ret=0;
	Tree a=points_gen_fprint(points, n, rdim, cdim);
	//cout << "Tree:\n";
	//a.print();
	//cout << "Sol:\n";
	//cStack s;
	for(int i=0; i<=a.size; i++){//Can check lesser?
		int row=a.size-i;
		int col=a.C(i);
		//sol->insert({row, col});
		if(row<=sr && col<=sc){
			ret=1;
			label << ret << ',';
			return ret;
		}
		/*
		array *arr=a.C_Which(i);
		if(arr!=NULL){
			arr->print();
			for(int i=0; i<arr->n; i++)
				s.insert(a[(*arr)[i]]);
			cout << ": ";
			s.print();
		}
		*/
	}
	label << ret << ',';
	return ret;
}

namespace test{
	void insert2cStack(){
		cStack s;
		s.insert(1);
		s.insert(2);
		s.insert(3);
		cStack s2;
		s2.insert(2);
		s2.insert(3);
		s2.insert(4);
		s2.insert(5);
		cStack s3;
		s3.insert(s);
		s3.insert(s2);
		s.print();
		s2.print();
		s3.print();
	}
	void gen_nPoints(int n){
		for(int i=0; i<n; i++)
			points_gen(4, 10, 10).print_tree();
	}
	void tree(){
		Tree a;
		a.print_tree();
		a.insert({3,7}); a.print_tree();
		a.insert({3,7}); a.print_tree();
		a.insert({3,8}); a.print_tree();
		a.insert({2,4}); a.print_tree();
		a.insert({0,4}); a.print_tree();
		a.insert({0,9}); a.print_tree();
		a.insert({26,-3}); a.print_tree();
	}
	void tree_new(){
		Tree a;
		a.print_rList();
		a.insert({3,7}); a.print_rList();
		a.insert({3,7}); a.print_rList();
		a.insert({5,7}); a.print_rList();
		a.insert({4,7}); a.print_rList();
		a.insert({4,7}); a.print_rList();
		a.insert({4,8}); a.print_rList();
		a.print_tree();
		a.~Tree(); a.print_rList();
		a.insert({4,7}); a.print_rList();
	}
	void cstack(){
		cStack b;
		b.print_cList();
		b.insert(3); b.print_cList();
		b.insert(3); b.print_cList();
		b.insert(5); b.print_cList();
		b.insert(4); b.print_cList();
		b.insert(4); b.print_cList();
		b.insert(1); b.print_cList();
		b.~cStack(); b.print_cList();
		b.insert(4); b.print_cList();
	}
	void PointDirectInint(){
		List<Point> a={.data={3,7}};
		cout << a.data;
	}
	void giveUpTest(){//2**30
		for(int i=0; i<1000; i++)
			point_gen(812825, 1321);//812825 and 1321
	}
	void oldTest(){
		//mem_init(mem, rdim, cdim);
		//mem_print(mem, rdim, cdim);
	}
	void smallTree(){//Correctly solved the tree
		Stack<Point> sol;
		Tree a;
		a.insert({3,7});
		a.insert({3,5});
		a.insert({2,1});
		a.insert({1,7});
		a.insert({1,8});
		a.print();
		cStack s;
		for(int i=0; i<=a.size; i++){
			sol.insert({a.size-i, a.C(i)});
			cout << a.size-i << ' ' << a.C(i) << ": ";
			array *arr=a.C_Which(i);
			if(arr!=NULL){
				arr->print();
				for(int i=0; i<arr->n; i++)
					s.insert(a[(*arr)[i]]);
				cout << ": ";
				s.print();
			}
			cout << '\n';
		}
	}
	void stackPoint(){
		Stack<Point> a; a.print_List();
		a.insert(Point(3,4)); a.print_List();
		a.insert(Point(4,4)); a.print_List();
	}
	void arr(){
		int i=3;
		array a(i);
		a.print();
		array *arr_r=new array(i);
		a.print();
		*arr_r=a;
		a[0]=99;
		arr_r->print();
		a.print();
	}
}

void fprint_property(ofstream& points, ofstream& label, int sr, int sc, int n, int rdim, int cdim){
	points << n << ',';
	points << rdim << ',';
	points << cdim << ',';

	label << sr << ',';
	label << sc << ',';
	label << n << ',';
	label << rdim << ',';
	label << cdim << ',';
}

void fsolve_create(int n, string filename_points, string filename_label, int sr, int sc, int n_faults, int rdim, int cdim){
	ofstream points(filename_points), label(filename_label);
	fprint_property(points, label, sr, sc, n_faults, rdim, cdim);
	for(int i=0; i<n; i++){
		repairable_brief_fprint(points, label, sr, sc, n_faults, rdim, cdim);
		cout << '\r' << i << flush;
	}
	points.close();
	label.close();
}
void fsolve_append(int n, string filename_points, string filename_label, int sr, int sc, int n_faults, int rdim, int cdim){//TODO change mode to append
	ofstream points(filename_points, ios_base::app), label(filename_label, ios_base::app);
	for(int i=0; i<n; i++){
		repairable_brief_fprint(points, label, sr, sc, n_faults, rdim, cdim);
		cout << '\r' << i << flush;
	}
	points.close();
	label.close();
}

int main(){
	int common_dim=10;//Change to 1024
	int rdim=common_dim, cdim=common_dim;
	int sr=1, sc=2, n_faults=5;
	//bool mem[rdim][cdim];
	srandom(time(NULL));
	//test::gen_nPoints(5);
	//test::insert2cStack();
	//test::smallTree();
	//test::arr();
	/*
	ofstream points("points"), label("label");
	fprint_property(points, label, sr, sc, n_faults, rdim, cdim);
	for(int i=0; i<3; i++){//5, 5, 17, 1024, 1024
		//print_sol(n_faults, rdim, cdim);
		//points_gen_fprint(points, n_faults, rdim, cdim);
		//print_repairable(sr, sc, n_faults, rdim, cdim);
		//repairable_brief(sr, sc, n_faults, rdim, cdim);
		repairable_brief_fprint(points, label, sr, sc, n_faults, rdim, cdim);
	}
	points.close();
	label.close();
	*/
	fsolve_append(70000, "points", "label", sr, sc, n_faults, rdim, cdim);
}
