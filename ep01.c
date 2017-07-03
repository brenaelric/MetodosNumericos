#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* Defini??es */
#define epsilon 0.0000001

/* Prot?tipo das fun??es */
int menuPrincipal();
void convBinario(float num);
void convOctal(float num);
void convHexa(float num);
float convBase();
void imprimeMatriz(double **m, int l, int c);
double **criaMatriz(int l, int c);
void metJordan(double **m, int n);
void leMatriz(double **m, int l , int c);
int sretro(double**m, int n, double x[]);
int sistemaLinear();
void cabecalho();
/* Fim do prot?tipo de fun??es */


int main (int argc, char *argv[]){
	FILE *fp;
	char nomeArquivo[255];
	double **A, *x;
	double *num, *flag;
	int tipo,i, ordem, numTermos, cont = 0, j;
	char opcao;
	int opcao2;
    float num2;

    do{
		opcao = menuPrincipal();

        switch (opcao){
            case 'C':
            case 'c':
                    system("cls");
                    cabecalho();
                    num2 = convBase();
                    convBinario(num2);
                    convOctal(num2);
                    convHexa(num2);
					break;

            case 'S':
            case 's':
                system("cls");
                cabecalho();
				printf("\n\n**** Op%c%co 'S' - Sistema linear ****\n", 135, 198);
				printf("\n1 - Sistema linear com entrada da matriz");
				printf("\n2 - Sistema linear (arquivo)");
				printf("\nDigite uma op%c%co: ", 135, 198);
				scanf("%d", &opcao2);

				switch (opcao2){
					case 1:
			            ordem = sistemaLinear();
			            x = malloc(sizeof(double)*ordem);
         			    A = criaMatriz(ordem, ordem + 1);

                		if (A == NULL || x == NULL){
                			printf("\nMem%cria insuficiente! Por favor, tente novamente.\n", 162);
                			return 1;
                		}

                		leMatriz(A, ordem, ordem + 1);
						break;

                	case 2:
                	    printf("Digite o nome do arquivo a ser aberto: \n");
                	    scanf("%s", &nomeArquivo);
                	    strcat(nomeArquivo, ".txt");
						fp = fopen(nomeArquivo, "r");

						if (!fp){
							printf("Erro na leitura! Imposs%cvel abrir o arquivo.", 161);
							exit(1);
						}
						fscanf(fp, "%d", &ordem);
						A = criaMatriz(ordem, ordem + 1);
						x = malloc(sizeof(double)*ordem);

						for (i = 0; i < ordem; i++){
							for (j = 0; j <= ordem; j++){
								double aux;
								fscanf(fp, "%lf,", &aux);
								A[i][j] = aux;
							}
						}
						fclose(fp);
						imprimeMatriz(A, ordem, ordem + 1);
						break;
				}

                metJordan(A, ordem);
                printf("\nAplicando o m%ctodo de Jordan: \n\n", 130);
                imprimeMatriz(A, ordem, ordem + 1);
                tipo = sretro(A, ordem, x);

                if (tipo == 2)
                    printf("\nCaracter%cstica do sistema linear: Sistema incompat%cvel\n\n", 161, 161);
  	            else{
                    printf("\nCaracteristica do sistema linear: %s\n", tipo?"Sistema indeterminado\n\n":"Sistema determinado\n\n");

                    for(i = 0; i < ordem; i++){
                        printf("x[%d] = %8.5lf\n", i + 1, x[i]);
                    }
                }
				free(A);
				free(x);
                break;

            case 'F':
            case 'f':
                printf("\n\n**** Op%c%co - Finalizar programa ****\n\n", 135, 198);
                return 0;

            default:
                printf("\n\n**** Op%c%co inv%clida - pressione qualquer tecla para voltar ao menu ****\n\n", 135, 198, 160);
                getch();
                system("cls");
                break;
        }
    }

    while(opcao != 'F' || opcao != 'f');
	system("pause");
	return 0;
} /* fim main */

int menuPrincipal (void){
    /* Imprime na tela o menu do programa */
    char opcao;
    cabecalho();
    printf("\n* 'C' - Convers%co", 198);
    printf("\n* 'S' - Sistema linear");
    printf("\n* 'F' - Finalizar programa");
    printf("\n* Digite uma op%c%co: ", 135, 198);
    opcao = getche();
    return opcao;
}/* Fim menuPrincipal */

int sistemaLinear(){
    int N;
    printf("\n**** Op%c%co 'S' - Sistema Linear ****\n\n", 135, 198);
    printf("Digite a ordem: ");
    scanf("%d", &N);
    return N;
} /* Fim sistemaLinear */

float convBase(){
    float num;
    printf("\n******** Op%c%co C - Convers%co de Base ********\n", 135, 198, 198);
    printf("Digite um n%cmero (decimal): ", 163);
    scanf("%f", &num);
    printf("\nDecimal: %f\n", num);
    return num;
} /* Fim convBase */

void convBinario(float dec){
    int num;
    char bin[33];
    char buffer[33];
    num = (int)dec;
    dec = dec - num;
    strcpy(bin,"");

    do{
        sprintf(buffer, "%d", num%2);
        strcat(bin, buffer);
        num = num/2;
    }
    while(num >= 2);

    sprintf(buffer, "%d", num);
    strcat(bin, buffer);
    strcpy(bin, strrev(bin));

    if(dec > 0){
        strcat(bin,",");
        int cont = 0;

        do{
            cont++;
            dec = dec*2;
            num = (int)dec;
            sprintf(buffer, "%d", num);
            strcat(bin, buffer);
            dec = dec - num;
        }
		while (dec > 0 && cont < 20);
    }

    printf("Bin%crio: %.16s\n", 160, bin);
} /* Fim convBinario */

void convOctal(float dec){
    int num;
    char octal[33];
    char buffer[33];
    num = (int)dec;
    dec = dec - num;
    strcpy(octal,"");

    do{
        sprintf(buffer,"%d", num % 8);
        strcat(octal, buffer);
        num = num/8;
    }
	while(num >= 8);

    sprintf(buffer,"%d", num);
    strcat(octal, buffer);
    strcpy(octal, strrev(octal));

    if(dec > 0){
        strcat(octal,",");
        int cont = 0;

        do{
            cont++;
            dec = dec*8;
            num = (int)dec;
            sprintf(buffer,"%d", num);
            strcat(octal, buffer);
            dec = dec - num;
        }
		while(dec > 0 && cont < 20);
    }

    printf("Octal: %s\n", octal);
} /* Fim convOctal */

void convHexa (float dec){
    int num;
    char tabelaHexa[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'A', 'B', 'C', 'D', 'E', 'F'};
    char hexa[33];
    char buffer[33];
    num = (int)dec;
    dec = dec - num;
    strcpy(hexa,"");

    do{
        sprintf(buffer, "%c", tabelaHexa[(num % 16)]);
        strcat(hexa, buffer);
        num = num/16;
    }
	while (num >= 16);

    sprintf(buffer, "%c", tabelaHexa[num]);
    strcat(hexa, buffer);
    strcpy(hexa, strrev(hexa));

    if (dec > 0){
        strcat(hexa,",");
        int cont = 0;

        do{
            cont++;
            dec = dec*16;
            num = (int)dec;
            sprintf(buffer,"%c", tabelaHexa[num]);
            strcat(hexa, buffer);
            dec = dec - num;
        }
		while (dec > 0 && cont < 20);
    }

    printf("Hexadecimal: %s\n", hexa);
} /* Fim convHexa */

/*O metodo de Jordan não foi concluido*/
void metJordan(double **m, int n){
/*
* Recebe m, a matriz aumentada de um sistema linear com n
* vari?veis, e transforma m numa matriz diagonal
* usando o m?todo de Jordan.
*/

	int i, j, k;
	double *aux, mult;

	for(i=0; i<n-1; i++){
		if(m[i][i]==0){
			j=1+1;
			while(j<n && m[i][j]==0){
				j++;
			}

			if(j<n){
					for(k=0; k<n; k++){
						*aux = m[i][k];
						m[i][k] = m[i][j];
						m[i][j] = *aux;
					}
			}
			else{
				for(i=0; i<n; i++){
					m[i][j]=0;
				}
			}
		}
		if(m[i][i] != 0){
			for(j=i+1; j<n; j++){
				mult = -m[j][i]/m[i][i];
				//m[j][i] = 0;
				for(i = 0; i<=n; i++){
					m[i][j] += mult*m[i][j];
				}
			}
		}
	}
} /* Fim metJordan */

void imprimeMatriz (double **m,int l, int c){
	/* Imprime a matriz m,com l linhas e c colunas */
    int i = 0, j = 0;
    for(i = 0; i < l; i++){
        for(j = 0; j < c; j++){
            printf("%8.3lf ",m[i][j]);
        }
        printf("\n");
    }
} /* Fim imprimeMatriz */

double **criaMatriz (int l, int c){
    /*
    * Se houver mem?ria dispon?vel,
    * aloca dinamicamente uma matriz com l linha e c colunas e
    * devolve um ponteiro para essa matriz;
    * Caso contr?rio, devolve nulo
    */

     int i, j;
     double **m;
     m = malloc(sizeof(double *));
     if (m != NULL){
        for (i = 0; i < l; i++){
                m[i] = malloc(sizeof(double)*c);
                if (m[i] == NULL){
                    for (j = 0; j < i;j++){
                        free(m[j]);
                    }
                    free(m);
                    return NULL;
                }
            }
        }
    return m;
} /* Fim criaMatriz */

void leMatriz (double **m, int l , int c){
    /*
    * L? valores para a matriz m,
    * que deve ter 'L' linhas e 'C' colunas
    */

    int i, j;
    for (i = 0; i < l; i++)
    {
        for(j = 0; j < c; j++)
        {
            printf("m[%d][%d]: ", i + 1, j + 1);
            scanf("%lf", &m[i][j]);
        }
    }
} /*Fim leMatriz*/

int sretro (double **m, int n, double x[]){
    /*
    * Recebe m, a matriz de um sistema linear com n vari?veis
    * sendo que o sistema linear tem que ser triangular superior.
    * Se o sistema linear for determinado, coloca em x a solu??o
    * do sistema linear e devolve 0 (zero). Se o sistema linear
    * for indeterminado, coloca em x uma solu??o do sistema linear
    * e devolve 1 (um). Se o sistema linear for imcompat?vel,
    * devolve 2 (dois).
    */

    int i, j, tipo = 0;
	double soma;
    for (i = n - 1; i >= 0; i--){
		soma = 0;
        for (j = i + 1; j < n; j++){
            soma = soma + m[i][j]*x[j];
	    }
        if (m[i][i] == 0){
            if(fabs(soma - m[i][n]) < epsilon)
			{
                x[i] = 0;
                tipo = 1;
			}
            else{
                return 2;
			}
        }
		else{
			x[i] = (m[i][n] - soma)/(m[i][i]);
		}
    }
     return tipo;
} /* Fim sretro */


void cabecalho (){
	/*
	* Fun??o com fins meramentente est?ticos,
	* serve apenas para deixar o menu mais estiloso
	*/

    int i;
    printf("%c", 201);
    for (i = 0; i <= 75; i++){
        printf("%c", 205);
    }
    printf("%c", 187);
    printf("\n%c\tCONVERSOR DE BASE NUM%cRICA E CALCULADORA DE SISTEMAS LINEARES\t     %c\n", 186, 144, 186);
    printf("%c", 200);
    for (i = 0; i <= 75; i++){
        printf("%c", 205);
    }
    printf("%c", 188);
    printf("\nM%cTODOS NUM%cRICOS 2017.1", 144, 144);
    printf("\nEQUIPE:\n");
    printf("Brena Kesia\nFabio Lima\nFilipe de Lima\nIan do Amaral\n\n");
} /* Fim cabecalho */
