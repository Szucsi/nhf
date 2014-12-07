#include <stdio.h>
#include <ctype.h>
#include <string.h>

//neveknek tároló:
typedef struct nev{char nev[30];} nev;
//induloknak a tipusa
typedef struct lista{char nevek[30]; double eredmeny;} lista;
//a futamkban résztvevők neveit tárolja:
typedef struct futam{nev nevek[8];} futam;
//beolvassa az indulok neveit:
void nevolvas(lista *indulok, int meret){				//sztringet olvasok be
	int i;
    for (i = 0; i != meret; ++i){
		scanf("%s ", indulok[i].nevek);                        //%s -sel olvassa be és írja ki!!!
	}
}
//beolvassa az indulok eredményeit:
void eredolvas(lista *indulok, int meret){
	int i;
    for (i = 0; i != meret; ++i){
		scanf("%lf ", indulok[i].eredmeny);
	}
}
//növekvő sorrendbe rendezei az indulókat eredmény szerint:
void rendezes(lista *indulok, int meret){
	int i, j;
	double csak;
	char csak2[30];
	for(i = 0; i < meret; ++i){
		for(j = 0; j < meret; ++j){
			if (indulok[i].eredmeny > indulok[j].eredmeny){
				csak = indulok[j].eredmeny;
				csak2[30] = indulok[j].nevek[30];
				indulok[j].eredmeny = indulok[i].eredmeny;
				indulok[j].nevek[30] = indulok[i].nevek[30];
				indulok[i].eredmeny = csak;
				indulok[i].nevek[30] = csak2[30];
			}
		}
	}
}
//indulok szetosztasa futamokba
nev szetosztas(lista indulok, nev *nevek, int meret, int fszam, int eppfszam){			//eppfszam az az egesz szam amely megmondja hanyadik futamot osztjuk be
	int i;
	for(i = fszam - eppfszam; i < meret; i = i + fszam){
		nevek[i] = indulok[i].nevek;
	}
	return *nevek;
}

int main(int argc, char *argv[3]){
	
	//indulok neveik és az eredményeik:
	lista *indulok;
	//futok száma és futamok száma:
	int meret, fszam;
	//futó indexek:
	int i, j;
	nev *nevek;
	char nev;
	futam *futam;

	FILE *fp; /* fájl mutató (file pointer/handle) */
 
	fp = fopen("szoveg.txt", "wrt"); 
	
	//futok számának bekérése:
	printf("ird be mennyien indulnak");
	scanf("%d", meret);

	nevolvas(indulok, meret);
	eredolvas(indulok, meret);
	rendezes(indulok, meret);

	//futambeosztas 8 palya
	fszam = meret / 8;
	for(i = 0; i <= fszam; i++){
		szetosztas(*indulok, nevek, meret, fszam, i);
		futam[i] = nevek;
		nevek = [];
	}
	
	for(i = 0; i < fszam; i++){
		fprintf(fp, "%d-edik futam résztvevői:\n", i);
		for(j = 0; j < 8; j++){
			fprintf(fp, "%d. %s\n", j, futam[j]);
		}
	}
	fclose(fp);

	return 0;

}
