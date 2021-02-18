#include <stdio.h>

void menu();
void encrypt_open_msg();
void decrypt_secret_msg();
int find_size_of_line(char line[]);
void reverse_line(char line[], int line_lenght);

int main(){
	menu();
	return 1;
}
void menu(){
	int selection=1;
	do{
		printf("1. Encrypt\n");
		printf("2. Decrypt\n");
		printf("0. Exit\n");
		printf("Choice:");
		scanf("%d",&selection);
		switch(selection){
			case 1:
				encrypt_open_msg();
				break;
			case 2: 
				 decrypt_secret_msg();
				break;
			case 0:
				break;
			default:
				break;
		}
	}while(selection != 0);
}
void encrypt_open_msg(){
	int i=0,key,x,temp,size;
	char message[1023],a;
	FILE *fin,*fwr;
	fin = fopen("open_msg.txt","r");
	fwr = fopen("secret_msg.txt","w"); 
	do{
		printf("Enter the key:");
		scanf("%d",&key);
	}while(key>=26 || key<1);	//taking key from user to encrypt 
	printf("\n");
	do{
		x = fscanf(fin,"%c",&message[i]);	//reading real message from file
		i++;
	}while(x != EOF);
	i=0;
	size = find_size_of_line(message);
	reverse_line(message,size);
	a=1;
	while(a!=0){
		if(message[i]=='\n'){
			printf("\n");
			fprintf(fwr, "\n");
		}
		else if(message[i]==' '){	//if there is space it replaces _
			printf("_");
			fprintf(fwr, "_");
		}
		else if(message[i]=='.'){ //there is . it replaces * 
			printf("*");
			fprintf(fwr, "*");
		}
		else{
			if((message[i]-key)>='a'){	//karakterden girilen key çıkarıldığında ascıı tablosundaki harf aralığının dışına çıkılmıyorsa çıkarılıp direkt yazılır
				printf("%c",message[i]-key);
				fprintf(fwr, "%c",message[i]-key);
			}
			else{		//asciideki harf aralığının dışına çıkıyorsa çıkmadığı sürece geri gidip çıktığı kısım tempte tutularak 'z'den çıkarılır
				temp = key-(message[i]-'a');
				printf("%c",'z'-temp+1);
				fprintf(fwr, "%c",'z'-temp+1);
			}
		}
		i++;
		a=message[i];

	}
	printf("\n\n");
	fclose(fin);
	fclose(fwr);

}
 void decrypt_secret_msg(){
 	int i=0,key,x,temp,size;
	char message[1023],a;
	FILE *fin,*fwr;
	fin = fopen("open_msg.txt","w");
	fwr = fopen("secret_msg.txt","r"); 
	do{
		printf("Enter the key:");
		scanf("%d",&key);
	}while(key>=26|| key<1);	//taking key from user to encrypt 
	printf("\n");
	do{
		x = fscanf(fwr,"%c",&message[i]);	//reading real message from file
		i++;
	}while(x != EOF); ///dosyanın sonunakadar tüm karakterler alınır 
	i=0;
	size = find_size_of_line(message);
	reverse_line(message,size);
	a=1;
	while(a!=0){
		if(message[i]=='\n'){ 
			printf("\n");
			fprintf(fin, "\n");
		}
		else if(message[i]=='_'){	//if there is space it replaces _
			printf(" ");
			fprintf(fin," ");
		}
		else if(message[i]=='*'){ //there is . it replaces * 
			printf(".");
			fprintf(fin, ".");
		}
		else{
			if((message[i]+key)<='z'){	//karakterden girilen key çıkarıldığında ascıı tablosundaki harf aralığının dışına çıkılmıyorsa çıkarılıp direkt yazılır
				printf("%c",message[i]+key);
				fprintf(fin, "%c",message[i]+key);
			}
			else{
				temp = key-('z'-(message[i])); //key ile ilerlendiğinde harf tablodaki harfler aralığına tekabül etmiyorsa fazlalık baştan ilave edilir
				printf("%c",'a'+temp-1);
				fprintf(fin, "%c",'a'-1+temp);
			}
		}
		i++;
		a=message[i];
	}
	printf("\n\n");
	fclose(fin);
	fclose(fwr);
 }
 int find_size_of_line(char line[]){	
 	int size=0,i;
 	for(i=1; line[i]!=0; i++){
 		size++;
 	}
 	return size;
 }
void reverse_line(char line[], int line_lenght){
	int i;
	char temp;
	for(i=0; i<(line_lenght/2); i++){
		temp = line[i];
		line[i] = line[line_lenght-i-1];
		line[line_lenght-i-1]= temp;
	}
}

