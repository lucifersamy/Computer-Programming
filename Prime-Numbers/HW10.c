#include <time.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct Node{
	int data;
    struct Node *next;
}Node;

int read(FILE *fin);
int sizeFinder(FILE *fin);
void traverse_linked_list_show_primes(Node *head, clock_t end_init_time);
void linked_list(Node **head,int size);
int findPrime(int a);
void array(FILE *fin,int size);

int main(){
	clock_t start_link, end_link_1_million,start_array,end_array_1_million;
	clock_t end_init_time;
	FILE *fin,*dynamicArray,*linkedList;
	fin = fopen("data.txt","r");
	int size;
	Node *head = NULL;
	
	dynamicArray = fopen("output_prime_LiknedList.txt","w+");	//opening files 
	linkedList = fopen("output_prime_dynamic_array.txt","w+");

	size = sizeFinder(fin);

	start_link = clock();	//starting clock for one million for link list
	linked_list(&head,size);
	end_init_time = clock();

	traverse_linked_list_show_primes(head, end_init_time);
	end_link_1_million = clock();	//to end clock for one million for link list

	double linkl_1_million = (double)(end_link_1_million - start_link) / CLOCKS_PER_SEC;
	fprintf(linkedList,"calculating time for 1 million(second):%lf\n",linkl_1_million);
	printf("calculating time for 1 million(second):%lf\n",linkl_1_million);

	start_array = clock();		//starting clock for one million for array
	array(fin,size);
	end_array_1_million = clock();	//to end clock for one million for array
	
	double array_1_million = (double)(end_array_1_million - start_array) / CLOCKS_PER_SEC;	//calculating time for 1 million
	fprintf(dynamicArray,"calculating time for 1 million(second):%lf",array_1_million);
	printf("calculating time for 1 million(second):%lf\n",array_1_million);
	
	return 0;
}

int read(FILE *fin){	//read all numbers from data file
	int number,c;
	fscanf(fin,"%d,00\n",&number);
		return number;
}

int findPrime(int a) {		///a function for calculating prime numbers
	int i;
	if (a < 2)
		return 0;
	if (a == 2)
		return 1;
	for (i = 3; i < a ; ++i){
		if (a % i == 0)
			return 0;
	}
	return 1;
}

void traverse_linked_list_show_primes(Node *head, clock_t end_init_time){ 
	Node *current = head;				//copy the head of linked list to 'current' to protect the head while all operations
	int control=0;						//and show the prime numbers
	clock_t end_of_5hundred, end_of_7hundred,start;
	FILE *linkedList;
	linkedList = fopen("output_prime_LiknedList.txt","w+");

	start = clock();
	
	while(current!=NULL){				
		int prime = current->data;	///controling pcurrent->data is prime
		if (findPrime(prime)){
			fprintf(linkedList,"%d\n", prime);
			printf("%d\n",prime);
		}
		if(control == 1 && prime > 750000){  //when number is 750000 time is stop
			end_of_7hundred = clock();
			control = 2;
		}

		else if(control == 0 && prime > 500000){	 //when number is 500000 time is stop
			end_of_5hundred = clock();
			control = 1;
		}

		current = current->next;
	}
	double linked_5_hundred = (double)(end_of_5hundred - start + end_init_time) / CLOCKS_PER_SEC;///finding time for 500000 and 7500000
	fprintf(linkedList,"calculating time for 5 hundred(second):%lf\n",linked_5_hundred);	
	printf("calculating time for 5 hundred(second):%lf\n",linked_5_hundred);

	double linkedl_7_hundred = (double)(end_of_7hundred - start + end_init_time) / CLOCKS_PER_SEC;
	fprintf(linkedList,"calculating time for 7 hundred(second):%lf\n",linkedl_7_hundred);
	printf("calculating time for 7 hundred(second):%lf\n",linkedl_7_hundred);
}

void linked_list(Node **head,int size){	
	int number,i,a,flag=0;
	FILE *fin;
	fin = fopen("data.txt","r");

	Node *temp = NULL;
	*head = (Node*)malloc(sizeof(Node));	//get numbers and assign this numbers to temp->data
	temp = *head;
	//record all these numbers ( data.txt ) into Linked-List
	for(i=0; i<size; i++){	  	
		temp->data = read(fin);	 //temp->next should be null
		temp->next = (Node *)malloc(sizeof(Node));
		temp = temp->next;			//temp should be temp next										
	}
	
	fclose(fin);

}

void array(FILE *fin,int size){
	int *numbers,i;	
	int control = 0;
	FILE *dynamicArray;
	fin = fopen("data.txt","r");
	dynamicArray = fopen("output_prime_dynamic_array.txt","w+");
	clock_t end_of_5hundred, end_of_7hundred;
	clock_t start = clock();

	numbers = (int*)malloc(size*sizeof(int));
	for(i=0; i<size; i++){	//
		numbers[i] = read(fin);	
		if (findPrime(numbers[i])){		//if number is prime print
			fprintf(dynamicArray,"%d\n", numbers[i]);	
			printf("%d\n",numbers[i]);
		}
		if(numbers[i] > 750000 && control == 1){	//when number is 500000 time is stop
			end_of_7hundred = clock();
			control = 2;
		}
		else if(numbers[i] > 500000 && control == 0){	//when number is 500000 time is stop
			end_of_5hundred = clock();
			control = 1;
		}
				
	}
	double array_5_hundred = (double)(end_of_5hundred - start) / CLOCKS_PER_SEC;	//finding time for 500000 and 750000
	fprintf(dynamicArray,"calculating time for 5 hundred(second):%lf\n",array_5_hundred);
	printf("calculating time for 5 hundred(second):%lf\n",array_5_hundred);

	double array_7_hundred = (double)(end_of_7hundred - start) / CLOCKS_PER_SEC;
	fprintf(dynamicArray,"calculating time for 7 hundred(second):%lf\n",array_7_hundred);
	printf("calculating time for 7 hundred(second):%lf\n",array_7_hundred);

	fclose(fin);
}


int sizeFinder(FILE *fin){	 //this function calculates size for dynamic arrays and linked list 
	int size,number;	
	
	while(fscanf(fin,"%d,00\n",&number) != EOF)
		size++;
	return size;
}