#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void sortArray(int *Pstr, int Number, int flag){
	int i, j, temp;	

	for(i = 0; i < Number; i++){
		for(j = 0; j < Number; j++){
			if(Pstr[i] > Pstr[j]){
				temp = Pstr[i];
				Pstr[i] = Pstr[j];
				Pstr[j] = temp;
			}
		}
	}
	if (!flag){
		for(i = Number - 1; i >= 0; i--){
			printf("%d", Pstr[i]);
			//注意空格的要求
			if(i > 0)
               printf(" ");
		}		
		printf("\n");
	} else {
		for(i = 0; i < Number; i++){
			printf("%d ", Pstr[i]);
			//注意空格的要求
			if(i < (Number - 1))
               printf(" ");
		}		
		printf("\n");

	}
}

int main(){
	int Number, flag;
	int str[1000];
	int i;

	scanf("%d", &Number);

	for(i = 0; i < Number; i++){
		scanf("%d", &str[i]);
	}

	scanf("%d", &flag);
	
	sortArray(str, Number, flag);	

	return 0;
}
