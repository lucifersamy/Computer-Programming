#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu();
void triangleOfSequences();
void countOccurrence();
void horseRacingGame();
int speedHorse();
int getInt(int mini, int maxi);
int numberGeneratorBetweenRange(int min,int max);
int digit(int number);
int digitSum(int number);
int compare(int target,int seek);

int main(){
	srand(time(NULL));
	menu();
	return 0;
}

void menu(){               //switch-case kullan�larak men�n�n olu�turuldu�u fonksiyon
	int selection,a;
	a=0;
	do{
		printf("\n");
		printf("1. Horse Racing Game\n");
		printf("2. Occurrence Counter\n");
		printf("3. Triangle of Sequences\n");
		printf("0. Exit\n");
		printf("Selection:");
		scanf("%d",&selection);
		switch(selection){
			case 0:
				a=1;
				break;
			case 1:
				horseRacingGame();
				break;
			case 2:
				countOccurrence();
				break;
			case 3:
				triangleOfSequences();
				break;
			default:
				break;
		}
	}while(a == 0);
}

void triangleOfSequences(){		//��genin olu�turuldu�u fonksiyon
	int triangle=0,i,a=0,j;
	srand(time(NULL));

	triangle = 2 + rand()%9;	//2 ile 10 aras�nda random bir de�er generate atanar
	printf("\n\n");
	for(i=1; i<=triangle; i++){		//her sat�r bir �nceki sat�rda yazan say�n�n bir fazlas� olarak ba�lar
		for(a=i; a<=i*i; a=a+i){   //ve her seferinde kendi kadar katlanarak karesine kadar yazd�r�l�r.
			printf("%d ",a);
		}
		printf("\n");
	}
}
void horseRacingGame(){
	int minHorseNumber=3,maxHorseNumber=3,guess=0,i=1,j=1,winner=0,speed=0,temp=0,minSpeed=10,maxSpeed=11,min=100,max=5,horseNumber=0;

	printf("\nNumber of Horse:");
	horseNumber = numberGeneratorBetweenRange(minHorseNumber,maxHorseNumber); //fonksiyon kullan�larak random bir at say�s� belirlenir
	printf("%d\n",horseNumber);

	guess = getInt(minHorseNumber,horseNumber); //fonksiyonla kullan�c�dan do�ru aral�kta bir at numaras� al�n�r
	printf("Racing starts...\n");

	//her at i�in random bir gidi� h�z� belirlenir ve en h�zl� giden elde tutulur.
	for(i=1; i<=horseNumber; i++){		
		printf("Horse %d:",i); 
		speed = numberGeneratorBetweenRange(minSpeed,maxSpeed);
		for(j=1; j<=speed; j++){
			printf("-");
			if(min > speed){
				min = speed;
				winner = i;
			}
			if(i != winner){	//en d���k de�eri alan (yani h�zl� gitmi�) olanla e�it de�ere sahip biri daha olursa ayr� bir tempte tutulur
				if(min == speed){
					temp = speed;
				}
			}
		}
	printf("\n");
	}
	printf("\n");
	if(temp == min){			// en son bulunmu� olunan en h�zl� at�n �nceden elde tutulan varsa onunla ayn� olmas� halinde 2 veya daha fazla at�n
		printf("No winner!");	//berebere kalmas� durumunda kazanan�n olmad��� ekrana bas�l�r
	}
	else if(guess == winner){
		printf("You Win!");
	}
	else if(guess != winner){
		printf("You Lose!Winner is Horse %d.",winner);
	}
}

int numberGeneratorBetweenRange(int min,int max){	//fonksiyona g�nderilen de�erler sayesinde istenilen aral�kta random bir de�er bulunur
	int random=0;
	random = min + rand()%max;

	return random;
}

int getInt(int mini, int maxi){		//kullan�c�dan do�ru aral�kta say� girene kadar de�er istenir ve al�n�r
	int guess=0;
	do{
		printf("Horse Number:");
		scanf("%d",&guess);
	}while(guess > maxi);

	return guess;
}
void countOccurrence(){
	
	int bigNumber=0, searchNumber=0,number=0,big_number_digit=0,search_number_digit=0;
	int sum=0,i=1,a=0;
	printf("\n\nBig Number:");
	scanf("%d",&bigNumber);
	printf("Search Number:");
	scanf("%d",&searchNumber);
	//digitSum fonksiyonuyla iki say�n�n da toplam basamak say�s� bulunur
	big_number_digit = digitSum(bigNumber);	
	search_number_digit = digitSum(searchNumber);
	sum = compare(bigNumber,searchNumber);
	printf("Occurrence: %d\n\n",sum);
}

int digitSum(int number){	//basamak say�lar�n�n hesapland��� fonksiyon
	int i=0,numberOfDigit=0,a=0,flag=0;

	if(number < 10){ //girilen say�n�n tek basamak olmas� durumunda 1 return edilir
		return 1;
	}
	else{	
		while(!flag){ 			//say�n�n t�m basamaklar� bitene kadar 10'a g�re modu al�n�p ard�ndan 10'a b�l�nmesiyle 
			a = number%10;		//elde edilen her basamak ad�na numberOfDigit counter�na 1 eklenir
			number = (number-a)/10;
			numberOfDigit++;
			if(number<=9){
				numberOfDigit++;	//son basamak i�in say� 10dan k���k oldu�unda countera 1 eklenir ve i�lem durdurulur
				flag=1;
			}
		}
	}
	return numberOfDigit;
}

int compare(int target, int seek){
	int digit1 = digitSum(target);  
	int digit2 = digitSum(seek);	
	int i,j	,temp=0;
	int temp2=1;
	int sum = 0;
	for(j = 0; j<digit2; j++){	//mod al�n�rken kullanmak i�in aranan say�n�n basamak say�s�na uygun hale gelene kadar 
		temp2 = temp2 * 10;		//her basamak i�in temp2 10 ile �arp�l�r
	} 
	//e�er aranan say� 1 basamakl� de�ilse 
	if(digit2 != 1){					
		for(i = 0; i<digit1-1; i++){	//b�y�k basamakl� say�da sona gelene kadar say�n�n kendi basamak say�s�na uygun olarak hesaplanan
			temp = target % temp2;		//temp2 de�erine g�re modu al�n�r ve bu de�er aranan say�ya e�itse sum de�erine 1 eklenir ve 10'a b�l�nerek 
			if(temp == seek){			//bir hane soldaki de�erin kontrol� sa�lan�r
				sum++;
			}
			target /= 10;
		}
	}
	//e�er aranan say� 1 basamakl� ise ayn� i�lemler kontrol son basama�a kadar yap�l�r
	else{
		for(i = 0; i<digit1; i++){
			temp = target % temp2;
			if(temp == seek){
				sum++;
			}
			target /= 10;
		}
	}
	return sum;	 
}
