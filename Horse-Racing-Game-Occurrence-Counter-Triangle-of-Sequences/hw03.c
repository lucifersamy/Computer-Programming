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

void menu(){               //switch-case kullanýlarak menünün oluþturulduðu fonksiyon
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

void triangleOfSequences(){		//üçgenin oluþturulduðu fonksiyon
	int triangle=0,i,a=0,j;
	srand(time(NULL));

	triangle = 2 + rand()%9;	//2 ile 10 arasýnda random bir deðer generate atanar
	printf("\n\n");
	for(i=1; i<=triangle; i++){		//her satýr bir önceki satýrda yazan sayýnýn bir fazlasý olarak baþlar
		for(a=i; a<=i*i; a=a+i){   //ve her seferinde kendi kadar katlanarak karesine kadar yazdýrýlýr.
			printf("%d ",a);
		}
		printf("\n");
	}
}
void horseRacingGame(){
	int minHorseNumber=3,maxHorseNumber=3,guess=0,i=1,j=1,winner=0,speed=0,temp=0,minSpeed=10,maxSpeed=11,min=100,max=5,horseNumber=0;

	printf("\nNumber of Horse:");
	horseNumber = numberGeneratorBetweenRange(minHorseNumber,maxHorseNumber); //fonksiyon kullanýlarak random bir at sayýsý belirlenir
	printf("%d\n",horseNumber);

	guess = getInt(minHorseNumber,horseNumber); //fonksiyonla kullanýcýdan doðru aralýkta bir at numarasý alýnýr
	printf("Racing starts...\n");

	//her at için random bir gidiþ hýzý belirlenir ve en hýzlý giden elde tutulur.
	for(i=1; i<=horseNumber; i++){		
		printf("Horse %d:",i); 
		speed = numberGeneratorBetweenRange(minSpeed,maxSpeed);
		for(j=1; j<=speed; j++){
			printf("-");
			if(min > speed){
				min = speed;
				winner = i;
			}
			if(i != winner){	//en düþük deðeri alan (yani hýzlý gitmiþ) olanla eþit deðere sahip biri daha olursa ayrý bir tempte tutulur
				if(min == speed){
					temp = speed;
				}
			}
		}
	printf("\n");
	}
	printf("\n");
	if(temp == min){			// en son bulunmuþ olunan en hýzlý atýn önceden elde tutulan varsa onunla ayný olmasý halinde 2 veya daha fazla atýn
		printf("No winner!");	//berebere kalmasý durumunda kazananýn olmadýðý ekrana basýlýr
	}
	else if(guess == winner){
		printf("You Win!");
	}
	else if(guess != winner){
		printf("You Lose!Winner is Horse %d.",winner);
	}
}

int numberGeneratorBetweenRange(int min,int max){	//fonksiyona gönderilen deðerler sayesinde istenilen aralýkta random bir deðer bulunur
	int random=0;
	random = min + rand()%max;

	return random;
}

int getInt(int mini, int maxi){		//kullanýcýdan doðru aralýkta sayý girene kadar deðer istenir ve alýnýr
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
	//digitSum fonksiyonuyla iki sayýnýn da toplam basamak sayýsý bulunur
	big_number_digit = digitSum(bigNumber);	
	search_number_digit = digitSum(searchNumber);
	sum = compare(bigNumber,searchNumber);
	printf("Occurrence: %d\n\n",sum);
}

int digitSum(int number){	//basamak sayýlarýnýn hesaplandýðý fonksiyon
	int i=0,numberOfDigit=0,a=0,flag=0;

	if(number < 10){ //girilen sayýnýn tek basamak olmasý durumunda 1 return edilir
		return 1;
	}
	else{	
		while(!flag){ 			//sayýnýn tüm basamaklarý bitene kadar 10'a göre modu alýnýp ardýndan 10'a bölünmesiyle 
			a = number%10;		//elde edilen her basamak adýna numberOfDigit counterýna 1 eklenir
			number = (number-a)/10;
			numberOfDigit++;
			if(number<=9){
				numberOfDigit++;	//son basamak için sayý 10dan küçük olduðunda countera 1 eklenir ve iþlem durdurulur
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
	for(j = 0; j<digit2; j++){	//mod alýnýrken kullanmak için aranan sayýnýn basamak sayýsýna uygun hale gelene kadar 
		temp2 = temp2 * 10;		//her basamak için temp2 10 ile çarpýlýr
	} 
	//eðer aranan sayý 1 basamaklý deðilse 
	if(digit2 != 1){					
		for(i = 0; i<digit1-1; i++){	//büyük basamaklý sayýda sona gelene kadar sayýnýn kendi basamak sayýsýna uygun olarak hesaplanan
			temp = target % temp2;		//temp2 deðerine göre modu alýnýr ve bu deðer aranan sayýya eþitse sum deðerine 1 eklenir ve 10'a bölünerek 
			if(temp == seek){			//bir hane soldaki deðerin kontrolü saðlanýr
				sum++;
			}
			target /= 10;
		}
	}
	//eðer aranan sayý 1 basamaklý ise ayný iþlemler kontrol son basamaða kadar yapýlýr
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
