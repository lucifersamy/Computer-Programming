#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct forest{
	char **Map;
	int Width;
	int Height;
	int Flower_X;
	int Flower_Y;
}Forest;

typedef struct botanist{
	int Coord_X;
	int Coord_Y;
	int Water_Bottle_Size;
}Botanist;

void init_game(Forest *forest,Botanist *botanist);
void print_map (Forest forest);
void search(Botanist* botanist, Forest* forest, int x, int y,int water);

int main(){
	int x;
	srand(time(NULL));
	Forest forest;
	Botanist botanist;
	init_game(&forest,&botanist);
	print_map(forest);
     printf("\nSearching...\n\n");
	search(&botanist, &forest, botanist.Coord_X, botanist.Coord_Y, botanist.Water_Bottle_Size);

	free(forest.Map);   //map için oluşturulan alanın freelenmesi
	for(x=0; x<(forest.Width)+1; x++)
		free(forest.Map[x]);
	return 0;
}

void init_game(Forest *forest,Botanist *botanist){
	FILE *Fin; 
	char *control;
	int x=0, i=0, w=0, var=0 ;
	size_t d_width = 0;
	Fin = fopen("init.csv","r");
	
	fscanf(Fin,"%d ", &botanist->Water_Bottle_Size);	//dosyadan su ve ormanın boyutlarının alınması
	fscanf(Fin,"%d,%d ", &forest->Height,&forest->Width);
	
	forest->Map = (char**)calloc(forest->Height,sizeof(char *));	//calloc ile map için dinamik bir alan olusturulması
	for(x=0; x<(forest->Width); x++)
		forest->Map[x] = (char*)calloc(forest->Width,sizeof(char));
	
	d_width = (forest->Width)*2;	//virgul ve kare sayısı oranından yola cıkılarak kullanım kolaylıgı icin boyut belirlenmesi

	control = (char*)calloc(d_width,sizeof(char));
	
	while(i < forest->Height){    //dosyadan okunan height ve width degerlerine uygun olacak sekilde 
                                   //dosyanın icindeki degerler alıip kullanilacak degerler map 2d arrayinin çine atilir
		fgets(control,1000,Fin);
		do{
			if(control[w] == ','){w++;}
			else{
				forest->Map[i][var] = control[w];  //eger botanist ise konuma 'B' atanması ve botanistin koordinatlarına i ve variableın atılması
					if(forest->Map[i][var] == 'B'){
						botanist->Coord_X = i;
						botanist->Coord_Y = var;
					}
					if(forest->Map[i][var] == 'F'){   //Botanist ile aynı sekilde flower için F atanması
						forest->Flower_X = i;
						forest->Flower_Y = var;
					}
				var++;
				w++;
			}
		}while(var < forest->Width+2); //null ve \n için 2 fazlasýna kadar bir linedaki ','' haricindeki karakterler alinir
		var=0;
		w=0;
		i++;
	}
	
	free(control); 
	fclose(Fin);
}	

void print_map(Forest forest){
	int i,j;

	for(i=0; i<forest.Height; i++){    //tüm tablo nested loop içinde print edildi
		for(j=0; (j<forest.Width); j++){
			printf("%c ", forest.Map[i][j]);
		}
		printf("\n");
	}
}

void search(Botanist* botanist, Forest* forest, int x, int y, int water){
	int direction;	//1 for up, 2 for down,3 for right,4 for left
     
	if(forest->Map[x][y] == 'F'){ //flower bulunursa bitme conditionı
	     forest->Map[x][y] = 'B';
	     print_map(*forest);
	     printf("\nI have found it on(%d,%d)!\n\n",x,y);
		return;
	}
		
	else if(water == 0){    //su biterse bitme conditionı
	     forest->Map[x][y] = 'B';
		print_map(*forest);
		printf("\nHelp! I am on (%d,%d)\n\n", x, y);
		return;
	}

	direction = 1+rand()%4;
	//random olarak belirlenen her yön için gideceği konumun tablo sınırları içinde olması ve duvar olmamasını kontrol edip uygunsa botanistin hareketi 
	if(direction == 1 && x - 1 >= 0){	//sağlandı. değilse eski konum için fonksiyon tekrar çağrıldı
	     if(forest->Map[x-1][y] != '#'){    
	          forest->Map[x][y] = ' ';
		     search(botanist, forest, x-1, y, water-1);
		}else{
		     search(botanist, forest, x, y,water);
		 }
     }
     else if(direction == 2 && x + 1 < forest->Height){	//down
	     if(forest->Map[x+1][y] != '#'){
	          forest->Map[x][y] = ' ';
		     search(botanist, forest, x+1, y, water-1);
		}else{
		     search(botanist, forest, x, y,water);
	     }          
	}	
	else if(direction == 3 && y + 1 < forest->Width){	 //right
	     if(forest->Map[x][y+1] != '#'){
	          forest->Map[x][y] = ' ';
		     search(botanist, forest, x, y+1, water-1);
		}else{
		     search(botanist, forest, x, y,water);
	     }     
     }
	else if(direction == 4 && y - 1 >= 0){	//left
	     if(forest->Map[x][y-1] != '#'){
	          forest->Map[x][y] = ' ';
	          search(botanist, forest, x, y-1, water-1);
	     }else{
		     search(botanist, forest, x, y,water);
	     }	     
	}
	else{
		search(botanist, forest, x, y,water);
	}
}


