#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <locale.h>
//#include <conio2.h>
#include <windows.h>
#include "conio.c"
/***********************************************/
/* Definição das Estruturas                    */
/***********************************************/
typedef struct jogo{
	char cor;
	struct jogo* prox;
}LISTA;

typedef struct score{
	char nome[50];
	int pontos;
	struct score* prox;
}PONTUACAO;

/***********************************************/
/* Definição das Funções                       */
/***********************************************/
void cria_lista(LISTA** l);
void cria_pontos(PONTUACAO** po);
void genius(LISTA** l, PONTUACAO** po);
void gera_cor(LISTA* aux);
void instrucoes(void);
void recordes(PONTUACAO* auxi);
void salva_pontos(PONTUACAO** po,int pontoatual);
void desenha(void);
void azul(void);
void piscaazul(void);
void verde(void);
void piscaverde(void);
void amarelo(void);
void piscaamarelo(void);
void vermelho(void);
void piscavermelho(void);

int primeiro = 0;

main(){
	
	system("title GENIUS - SUPER LEGAL"); //Dá título a tela
    system("MODE con cols=75 lines=29"); //Redimensiona a tela	
	setlocale(LC_ALL,"PORTUGUESE"); //troca a linguagem do programa para a padrão do windows
	
	int menu; //opção do menu
	LISTA* l; // declaração da estrutura principal
	PONTUACAO* po; //declaração da estrutura de pontuação
	if(primeiro == 0){
		cria_pontos(&po); //cria a lista de pontuação
		primeiro++;
	}
	do{
		printf("JOGO SUPERLEGAL GENIUS\n\n");
		printf("1 - NOVO JOGO \n2 - PLACAR DE RECORDES \n3 - COMO JOGAR\n0 - SAIR DO JOGO \nDigite a opção desejada: ");
		scanf("%d",&menu);
		
		switch(menu){
			case 1: //inicia um novo jogo
				system("cls");
				cria_lista(&l);
				genius(&l,&po);
			break;
			case 2: //apresenta o placar do jogo
				system("cls");
				recordes(po);
			break;
			case 3:
				instrucoes(); //chama a função para mostrar as instruções
			break;
			case 0: //sair do jogo
				system("cls");
				printf("JOGO SENDO ENCERRADO! \nOBRIGADO POR JOGAR\n\n");
			break;
			default: //numero inválido
				system("cls");
				printf("NUMERO INVÁLIDO \nSELECIONE UMA OPÇÃO VALIDA");
		}
	}while(menu != 0);
}

void cria_lista(LISTA** l){
    *l = NULL; // lista criada
}

void cria_pontos(PONTUACAO** po){
	*po = NULL; // lista criada
}

void genius(LISTA** l,PONTUACAO** po){
	int continua = 1, pontoatual = -1;
	char x;
	LISTA* p;
		
	printf("INCIANDO O JOGO!\n\n");
	do{
		//CRIAÇÃO DE ORDEM COMPUTADOR
		LISTA* no =  (LISTA *) malloc (sizeof(LISTA)); // aloca novo espaco em memoria
		if( no != NULL ){ // verifica se conseguiu alocar memoria para o novo registro
			gera_cor(no);
			if(*l == NULL) // lista vazia
            	*l= no; // insere o primeiro registro
            else{
                p = *l;                        // percorre a lista até encontrar o ultimo registro
                while( p->prox != NULL )
                	p = p->prox;
                p->prox = no;                  // ultimo aponta para o novo registro
            }
		}
		pontoatual++;
		
		//IMPRIME TUDO
		p = *l;
		system("cls");
		//printf("ORDEM: \n");
		desenha();
		while(p != NULL){    // ponteiro auxiliar para a lista
			Sleep(500);
            switch(p->cor){
        		case 'W':
        			piscaazul();
           		break;
	            case 'A':
	            	piscaamarelo();
	            break;
	            case 'S':
	            	piscavermelho();
	            break;
	            case 'D':
	            	piscaverde();
	            break;
			}
            p = p->prox;  // aponta para o proximo registro da lista
		 }
		
		//JOGADA USUÁRIO E VERIFICA SE JOGADA ESTA CERTA ATÉ O FINAL DA LISTA
		p = *l;
		while(p != NULL){
			textbackground(BLACK);
			gotoxy(60,20);
			printf("\n\nDigite a sua jogada: ");
			fflush(stdin);
			x = toupper(getch());
			
			if(p->cor == x){
				printf("\nCor correta!\n");
				p = p->prox;
			}
			else{
				system("cls");
				printf("Infelizmente você perdeu :/ \n\n\n");
				system("pause");				
				salva_pontos(po,pontoatual);
				system("cls");
				main();
			}
		}
		printf("\nOrdem correta!\n\n");
		system("pause");
		system("cls");
	}while(continua != 0);
}

void recordes(PONTUACAO* auxi){	
	int count = 0;
	system("cls");
	if(auxi == NULL)
        printf( "\n Lista vazia!\n\n\n" );
	else {
	     printf("\n\n ---- PLACAR DE RECORDES ---- ");
         while(auxi != NULL){    // ponteiro auxiliar para a lista
                printf( "\n Nome: %s", auxi->nome,"\n Pontuacao: %d\n", auxi->pontos);
                auxi = auxi->prox;  // aponta para o proximo registro da lista
                count++;
                if(count > 5)
                	break;
		 } // fim while( aux != NULL )
	} 
	system("pause");
	system("cls");
}

void gera_cor(LISTA* aux){
	srand(time(NULL)); //novo seed para gerar os numeros randomicos
	
	switch(rand()%4){
		case 0://amarelo
			aux->cor = 'W';
		break;
		case 1://verde
			aux->cor = 'A';
		break;
		case 2://azul
			aux->cor = 'S';
		break;
		case 3://vermelho
			aux->cor = 'D';
		break;
	}
	aux->prox = NULL; // não aponta
}

void salva_pontos(PONTUACAO** po,int pontoatual){
	
	PONTUACAO* pp;
	PONTUACAO* ant;           // ponteiros auxiliares para percorrer a lista
	
	/*PONTUACAO* np =  (PONTUACAO*) malloc (sizeof(PONTUACAO)); // aloca novo espaco em memoria
		if( pp != NULL ){ // verifica se conseguiu alocar memoria para o novo registro
			np->pontos = pontoatual;
			system("cls");
			printf("Digite seu nome: ");
			fflush(stdin);
			gets(np->nome);
			if(* po== NULL) // lista vazia
            	*po= np; // insere o primeiro registro
            else{
                pp = *po;                        // percorre a lista até encontrar o ultimo registro
                while( pp->prox != NULL )
                	pp = pp->prox;
                pp->prox = np;                  // ultimo aponta para o novo registro
            }
		}*/
			
	PONTUACAO* np = (PONTUACAO*) malloc(sizeof(PONTUACAO)); // aloca novo espaco em memoria
	if(np != NULL){                                    // verifica se conseguiu alocar memoria para o novo registro
		np->pontos = pontoatual;
		system("cls");
		printf("Digite seu nome: ");
		fflush(stdin);
		gets(np->nome);
		pp = *po;                                      // possiciona ponteiro auxiliar no inicio para percorrer a lista
		
		while((pp != NULL) && (np->pontos > pp->pontos)){ //faz o laco ate achar a posicao ou o final da lista (no caso em que e a maior codigo)
			ant = pp;                         // guarda a posicao do anterior, para fazer ajuste dos ponteiros ao final
			pp = pp->prox;                   // percorre a lista
		}
		if(pp == *po)      // verifica se auxiliar aponta para o inicio da lista
			*po = np;       // inicio da lista aponta para novo registro
		else
			ant->prox = np;// ajuste de ponteiro para inserir na posicao ordenada
		np->prox = pp;      // ajuste de ponteiro, inserido de forma ordenada por codigo
	}
}

void desenha(void){
	azul();
	amarelo();
	verde();
	vermelho();
	
  	/*printxy(32, 2, "                "); //DÊ 16 ESPAÇOS ENTRE AS ASPAS
  	printxy(32, 3, "                "); 
  	printxy(32, 4, "                ");   
 	printxy(32, 5, "                ");
  	printxy(32, 6, "                ");
  	printxy(32, 7, "                ");*/
}

void instrucoes(void){
	system("cls");
	printf("INSTRUÇÕES PARA JOGAR: \n");
	printf("Cada cor corresponde a uma tecla do teclado [W, A, S, D], conforme ela está disposta na tela de jogo, pressione as setas seguindo a mesma ordem do computador para fazer mais pontos!\n\n\n");
	system("pause");
	system("cls");
}

void azul(void){
	textbackground(BLUE);               //FUNÇÃO QUE PINTA DE AZUL
	gotoxy(32,2);
	printf("                ");
	gotoxy(32,3);
	printf("                ");
	gotoxy(32,4);
	printf("        W       ");
	gotoxy(32,5);
	printf("                ");
	gotoxy(32,6);
	printf("                ");
	gotoxy(32,7);
	printf("                ");
}

void piscaazul(void){
	textbackground(LIGHTBLUE);               //FUNÇÃO QUE PISCA AZUL
	gotoxy(32,2);
	printf("                ");
	gotoxy(32,3);
	printf("                ");
	gotoxy(32,4);
	printf("                ");
	gotoxy(32,5);
	printf("                ");
	gotoxy(32,6);
	printf("                ");
	gotoxy(32,7);
	printf("                ");
	Beep(1396,100);Sleep(1000);
	azul();
}

void amarelo(void){
	textbackground(BROWN);               //FUNÇÃO QUE PINTA DE AMARELO
	gotoxy(16,8);
	printf("                ");
	gotoxy(16,9);
	printf("                ");
	gotoxy(16,10);
	printf("        A       ");
	gotoxy(16,11);
	printf("                ");
	gotoxy(16,12);
	printf("                ");
	gotoxy(16,13);
	printf("                ");
}

void piscaamarelo(void){
	textbackground(YELLOW);               //FUNÇÃO QUE PISCA AMARELO
	gotoxy(16,8);
	printf("                ");
	gotoxy(16,9);
	printf("                ");
	gotoxy(16,10);
	printf("                ");
	gotoxy(16,11);
	printf("                ");
	gotoxy(16,12);
	printf("                ");
	gotoxy(16,13);
	printf("                ");
	Beep(1318,100);Sleep(1000);
	amarelo();
}

void verde(void){
	textbackground(GREEN);               //FUNÇÃO QUE PINTA DE VERDE
	gotoxy(48,8);
	printf("                ");
	gotoxy(48,9);
	printf("                ");
	gotoxy(48,10);
	printf("        D       ");
	gotoxy(48,11);
	printf("                ");
	gotoxy(48,12);
	printf("                ");
	gotoxy(48,13);
	printf("                ");
}

void piscaverde(void){
	textbackground(LIGHTGREEN);               //FUNÇÃO QUE PISCA VERDE
	gotoxy(48,8);
	printf("                ");
	gotoxy(48,9);
	printf("                ");
	gotoxy(48,10);
	printf("                ");
	gotoxy(48,11);
	printf("                ");
	gotoxy(48,12);
	printf("                ");
	gotoxy(48,13);
	printf("                ");
	Beep(1174,100);Sleep(1000);
	verde();
}

void vermelho(void){
	textbackground(RED);               //FUNÇÃO QUE PINTA DE VERMELHO
	gotoxy(32,14);
	printf("                ");
	gotoxy(32,15);
	printf("                ");
	gotoxy(32,16);
	printf("        S       ");
	gotoxy(32,17);
	printf("                ");
	gotoxy(32,18);
	printf("                ");
	gotoxy(32,19);
	printf("                ");
}

void piscavermelho(void){
	textbackground(LIGHTRED);               //FUNÇÃO QUE PISCA VERMELHO
	gotoxy(32,14);
	printf("                ");
	gotoxy(32,15);
	printf("                ");
	gotoxy(32,16);
	printf("                ");
	gotoxy(32,17);
	printf("                ");
	gotoxy(32,18);
	printf("                ");
	gotoxy(32,19);
	printf("                ");
	Beep(1046,100);Sleep(1000);
	vermelho();
}

