#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <clocale>

// Trabalho de Construção de Algoritmo 2 do centro universtário adventsita de são paulo - UNASP - SP
// Desenvolvido pelo Ezequiel Muxito 

// struct de alunos 
struct aluno {
  int RA;
  char nome[30], curso[30], email[30];
};

void listarAlunos() {
  FILE * arqAluno = fopen ("basededados/basededadosAluno.txt","r");
  int RA;
  char nome[30], curso[30], email[30];
  
  printf("\t\t\t***********************************************\n\n");
  printf("\t\t\t********   LISTAR ALUNO ********\n\n");
  printf(" RA	 NOME \t\t	CURSO \t\t\t E-mail	\n\n");

  while(fscanf(arqAluno, "%d %s %s %s", &RA, nome, curso, email) != EOF) {
    printf("%-8d %-20s %-20s %-20s\n", RA, nome, curso, email);
  }
  printf("\n\n");
  fclose(arqAluno);
}

int excluirAluno(int RAexcl) {
  FILE * arqEnt = fopen ("basededados/basededadosAluno.txt","r");
  FILE * arqSai = fopen ("basededados/basededadosAluno_tmp.txt","w");
  
  int RA;
  char nome[30], curso[30], email[30];
  
  int alunoExcluido = 0;
  while(fscanf(arqEnt, "%s %s %s %s", &RA, nome, curso, email) != EOF) {
    if(RA != RAexcl){
    	fprintf(arqSai, "%-8d %-20s %-20s %-20s\n", RA, nome, curso, email);
	}
    else{
    	alunoExcluido = 1;
	}
  }
  fclose(arqEnt);
  fclose(arqSai);
  
  remove("basededados/basededadosAluno.txt");
  rename("basededados/basededadosAluno_tmp.txt", "basededados/basededadosAluno.txt");
  return alunoExcluido;
}

void buscarALuno() {
  FILE * arqAluno = fopen("basededados/basededadosAluno.txt","r");

  int RA, RAbusca;
  char nome[30], curso[30], email[30];
  
  printf("\t\t\t***********************************************\n\n");
  printf("\t\t\t********   PESQUISAR ALUNO ********\n\n");

  printf("Busque pelo RA: ");
  scanf("%d", &RAbusca);
  printf(" RA	 NOME \t\t	CURSO \t\t\t E-mail	\n\n");
  while(fscanf(arqAluno, "%d %s %s %s", &RA, nome, curso, email) != EOF) {
    if(RAbusca == RA)
      printf("%-8d %-20s %-20s %-20s\n", RA, nome, curso, email);
  }
  fclose(arqAluno);
}

void mostarMenuAluno(){
	printf("\n");
	
	printf("\t\t\t***********************************************\n\n");
    printf("\t\t\t********   ABA ACESSO AOS DADOS DO ALUNO ********\n\n");
  
	printf("1 - LISTAR ALUNOS\n");
 	printf("2 - PESQUISAR ALUNOS\n");
 	printf("3 - EXCLUIR ALUNOS\n");
  	printf("4 - CADASTRAR ALUNO\n");
  	printf("\n0 - Sair\n\n");
}

void cadastrarAluno() {
  FILE * arqAluno = fopen("basededados/basededadosAluno.txt",  "a");
  FILE * arqAlunoEx = fopen("basededados/basededadosAluno.txt", "r");

  int RA, RAEx;
  int i, n;
  char nome[30], curso[30], email[30];
  
  printf("\t\t\t***********************************************\n\n");
  printf("\t\t\t********   CADASTRAR ALUNO ********\n\n");

  printf("\n\n");
  printf("DIGITE NÚMERO DE ALUNOS A CADASTRAR: ");
  scanf("%d", &n);
  printf("\n\n");
  
   printf("Digite RA: ");
   scanf("%d", &RAEx);
    while(fscanf(arqAlunoEx, "%d %s %s %s", &RA, nome, curso, email) != EOF) {
    	for(i = 1; i <= n; i++){
            if(RAEx == RA){
	  	 	  printf("Aluno ja existe na base de dados.\n");
	     	}		
	        else{
		  	  printf("Digite Nome: ");
			  scanf("%s", nome);
			  printf("Digite Curso: ");
			  scanf("%s", curso);
			  printf("Digite E-mail: ");
			  scanf("%s", email);
			  
		  	  fprintf(arqAluno, "%-8d %-20s %-20s %-20s\n", RAEx, nome, curso, email);
		  	  printf("\n\n");
   	       }
		}
   	    fclose(arqAlunoEx);
	}
	  printf("\n\n");
    fclose(arqAluno);
}

void daddosAlunos(){
	
  int menu;
  do {
    mostarMenuAluno();
    printf("OPÇÃO: ");
    scanf("%d", &menu);
    
    if(menu == 1)
      listarAlunos();
    else if(menu == 2) 
      buscarALuno();
    else if(menu == 3) {
      printf("\t\t\t***********************************************\n\n");
  	  printf("\t\t\t********   EXCLUIR ALUNO ********\n\n");
      
      int RA;
      printf("Digite RA: ");
      scanf("%d", &RA);
      if(excluirAluno(RA))
        printf("Aluno excluido com sucesso.\n");
      else
        printf("Aluno nao encontrado.\n");
        
      printf("\n");
    }
    
    else if(menu == 4) {
      cadastrarAluno();
    }
  } while(menu != 0);
  
  printf("Programa encerrado\n");	
}

// dados - de livros 
void mostarMenuLvros(){
	printf("\n");
	printf("\t\t\t***********************************************\n\n");
    printf("\t\t\t********   ABA ACESSO AOS DADOS DE LIVROS ********\n\n");
    
	printf("1 - LISTAR LIVROS\n");
 	printf("2 - PESQUISAR LIVROS\n");
 	printf("3 - EXCLUIR LIVROS\n");
  	printf("4 - CADASTRAR LIVROS\n");
  	printf("\n0 - Sair\n");
}

// struct - de livros 
struct livro {
  int ano, QT; char ISBN[20];
  char titulo[50], editora[20];
};

void listarLivros() {
  
  FILE * arqLivro = fopen ("basededados/basededadosLivro.txt","r");
  int ano, codigo, QT; char ISBN[20];
  char titulo[30], editora[20];
  
  printf("\t\t\t***********************************************\n\n");
  printf("\t\t\t********   LISTAR ALUNO ********\n\n");
  printf("\nCódigo  ISBN \t\t        TÍTULO \t\t            EDITORA \t         ANO      QT. EXEMPLARES	\n\n");

  while(fscanf(arqLivro, "%d %s %s %s %d %d",&codigo, ISBN, titulo, editora, &ano, &QT) != EOF) {
    	printf("%-7d %-20s %-30s %-20s %-8d %-10d\n",codigo, ISBN, titulo, editora, ano, QT);
  }
  fclose(arqLivro);
  printf("\n\n");
}

void buscarLivros(){
  FILE * arqLivro = fopen ("basededados/basededadosLivro.txt","r");
  int ano, codigo, QT; char ISBN[20], ISBNbusca[20];
  char titulo[30], editora[20]; int i;
  
  printf("\t\t\t***********************************************\n\n");
  printf("\t\t\t********   PESQUISAR DE LIVRO ********\n\n");

  printf("Busque pelo ISBN: ");
  scanf("%s", ISBNbusca);
  
  while(fscanf(arqLivro, "%d %s %s %s %d %d", &codigo, ISBN, titulo, editora, &ano, &QT) != EOF) {
		if(ISBNbusca[i] == ISBN[i]){
		  printf("\n\n");
	      printf("%-7d %-20s %-30s %-20s %-8d %-10d\n", codigo, ISBN, titulo, editora, ano, QT);
	      printf("\n\n");
	    }
   }
  fclose(arqLivro);
	
}
int excluirLivros(char ISBNexcl[]){
  FILE * arqEnt = fopen ("basededados/basededadosLivro.txt","r");
  FILE * arqSai = fopen ("basededados/basededadosLivro_temp.txt","w");
  
  int ano, QT, codigo; char ISBN[20];
  char titulo[30], editora[20]; int i;
  
  int livroExcluido = 0;
  while(fscanf(arqEnt, "%d %s %s %s %s", &codigo, ISBN, titulo, editora, &ano, &QT) != EOF) {
    if(ISBN[i] != ISBNexcl[i]){
    	fprintf(arqSai, "%-7d %-20s %-50s %-20s %-8d %-10d\n",codigo, ISBN, titulo, editora, ano, QT);
	}
    else{
    	livroExcluido = 1;
	}
  }
  fclose(arqEnt);
  fclose(arqSai);
  
  remove("basededados/basededadosLivro.txt");
  rename("basededados/basededadosLivro_temp.txt", "basededados/basededadosLivro.txt");
  return livroExcluido;
}
void cadastrarLivros(){
  FILE * arqLivro = fopen("basededados/basededadosLivro.txt",   "a");
  FILE * arqLivroEx = fopen("basededados/basededadosLivro.txt", "r");
  
  int ano, QT, codigo; char ISBN[20], ISBNN[20];
  char titulo[30], editora[50];
  int i, n;
  
  printf("\t\t\t***********************************************\n\n");
  printf("\t\t\t********   CADASTRAR LIVRO ********\n\n");

  printf("\n\n");
  printf("DIGITE NÚMERO DE LIVROS A CADASTRAR: ");
  scanf("%d", &n);
  printf("\n\n");
 
    printf("Digite ISBN: ");
	scanf("%s", ISBNN);
	
    while(fscanf(arqLivroEx, "%d %s %s %s %d %d", &codigo, ISBN, titulo, editora, &ano, &QT) != EOF) {
    	for(i = 1; i <= n; i++){
		  	if(ISBNN[i] == ISBN[i]){
		  	  printf("Livro ja existe na base de dados.\n");
			}		
		    else{
		      printf("Digite o código: ");
		      scanf("%d", &codigo);
		  	  printf("Digite Título: ");
			  scanf("%s", titulo);
			  printf("Digite Editor: ");
			  scanf("%s", editora);
			  printf("Digite Ano: ");
			  scanf("%d", &ano);
			  printf("Digite Q. Exmplar: ");
			  scanf("%d", &QT);
			  
		  	  fprintf(arqLivro, "%-7d %-20s %-50s %-20s %-8d %-10d\n", codigo, ISBNN, titulo, editora, ano, QT);
		  	  printf("\n\n");
	   	    }
		}
   	    fclose(arqLivroEx);
	}
    printf("\n\n");
    fclose(arqLivro);
}

void dadosLivros(){
	int menu;
  do {
    mostarMenuLvros();
    printf("OPÇÃO: ");
    scanf("%d", &menu);
    
    if(menu == 1)
      listarLivros();
    else if(menu == 2) 
      buscarLivros();
   else if(menu == 3) {
      printf("\t\t\t***********************************************\n\n");
  	  printf("\t\t\t********   EXCLUIR LIVRO ********\n\n");
      
      char ISBN[20];
      printf("Digite ISBN: ");
      scanf("%s", ISBN);
      if(excluirLivros(ISBN))
        printf("Livro excluido com sucesso.\n");
      else
        printf("Livro nao encontrado.\n");
        
      printf("\n");
    }
    else if(menu == 4) 
      cadastrarLivros();
    
  } while(menu != 0);
  
  printf("Programa encerrado\n");	
	
}
// struct - de emoprestimo  
struct emprestimo {
	char numero[6];

};
// menu de emprestimo 
void mostarMenuEmprestimo(){
	printf("\n");
	printf("\t\t\t***********************************************\n\n");
    printf("\t\t\t********   ABA ACESSO AOS DADOS DE EMPRESTIMO ********\n\n");
    
	printf("1 - LISTAR LIVROS\n");
 	printf("2 - LISTAR ALUNOS\n");
  	printf("3 - LISTAR EMPRESTÍMO\n");
  	printf("4 - EXCLUIR EMPRESTÍMO\n");
  	printf("5 - CADASTRAR EMPRESTÍMO\n");
  	printf("\n0 - Sair\n");
}
// submenu de emprestimo 
void mostarSobMenueEmprestimo(){
	printf("\n");
    
	printf("1 - LISTAR TODOS EMPRESTÍMOS\n");
 	printf("2 - LISTAR EMPRESTÍSMO DE UM LIVRO\n");
  	printf("3 - LISTAR EMPRESTÍMO EM ATRASO\n");
  	printf("\n0 - Sair\n");
}


void cadastrarEmprestimo() {
  FILE * arqCadEmp = fopen("basededados/basededadosEmprestimo.txt",  "a");
  FILE * arqCadEx = fopen("basededados/basededadosEmprestimo.txt", "r");
 
  int RAEmp, RAEx, QTEm,codigo, i, n, praso; 
  char tituloEm[30], nomeEm[18];
  
   time_t t = time(NULL);   
   struct tm *tm = localtime(&t);
    // printf("%s", asctime(tm));
    
  printf("\t\t\t***********************************************\n\n");
  printf("\t\t\t********   CADASTRAR LIVRO ********\n\n");

  printf("\n\n");
  printf("DIGITE NÚMERO DE ALUNOS A CADASTRAR: ");
  scanf("%d", &n);
  printf("\n\n");
  
  	printf("Digite RA do aluno: ");
    scanf("%d", &RAEmp);
            
    while(fscanf(arqCadEx, "%d %d %s %s %d %d", &codigo, &RAEx, nomeEm, tituloEm, &QTEm, &praso) != EOF) {
    	for(i = 1; i <= n; i++){
    	
          	if(RAEx == RAEmp && praso >= 16){
          		printf("Aluno como livro em emprestímo,  praso de devolução vencido.\n");	
			}	
	        else{
		  	  printf("Digite código do livro: ");
			  scanf("%d", &codigo);
			  printf("Digite nome do aluno: ");
			  scanf("%s", nomeEm);
			  printf("Digite titulo do livro: ");
			  scanf("%s", tituloEm);
			  printf("Digite QT. livro: ");
			  scanf("%d", &QTEm);
			  printf("Digite o praso para devolução: ");
			  scanf("%d", &praso);
			  
			  fprintf(arqCadEmp, "%-4d %-8d %-18s %-30s %-8d %-4d\n", codigo, RAEmp, nomeEm, tituloEm, QTEm, praso);
   	       }
		}
   	    fclose(arqCadEx);
	}
	printf("\n\n");
    fclose(arqCadEmp);
}
int excluirEmprestimo(int codigoEx) {
  FILE * arqEnt = fopen ("basededados/basededadosEmprestimo.txt","r");
  FILE * arqSai = fopen ("basededados/basededadosEmprestimo_temp.txt","w");
  
  int RAEmp, RAEx, QTEm,codigo, i, n, praso; 
  char tituloEm[30], nomeEm[20];
  
  int EmpExcluido = 0;
  while(fscanf(arqEnt, "%d %d %s %s %d %d", &codigo, &RAEx, nomeEm, tituloEm, &QTEm, &praso) != EOF) {
    if(codigo != codigoEx){
    	 fscanf(arqSai, "%-4d %-8d %-18s %-30s %-8d %-4d", codigo, RAEmp, nomeEm, tituloEm, QTEm, praso);
	}
    else{
    	EmpExcluido = 1;
	}
  }
  fclose(arqEnt);
  fclose(arqSai);
  
  remove("basededados/basededadosEmprestimo.txt");
  rename("basededados/basededadosEmprestimo_temp.txt", "basededados/basededadosEmprestimo.txt");
  return EmpExcluido;
}
void  listarEmprestimo(){
  mostarSobMenueEmprestimo();
  FILE * arqEmp = fopen("basededados/basededadosEmprestimo.txt", "r");
  
  int RAEmp, QTEm, menu, praso; 
  char tituloEm[30], nomeEm[18], data; int codigo, codigoEx, prasoEx;
  
  printf("\t\t\t***********************************************\n\n");
  printf("\t\t\t********   LISTAR EMPRESTÍMO ********\n\n");
  //printf("\n ISBN \t\t          TÍTULO \t\t\t                EDITORA \t     ANO      QT. EXEMPLARES	\n");
	
	printf("OPÇÂO: ");
    scanf("%d", &menu);
    printf("\n\n");	
    
    if(menu == 1){
    	 while(fscanf(arqEmp, "%d %d %s %s %d %d", &codigo, &RAEmp, nomeEm, tituloEm, &QTEm, &praso) != EOF) {
	      	printf("%-4d %-8d %-18s %-30s %-8d %-4d\n", codigo, RAEmp, nomeEm, tituloEm, QTEm, praso);
		}
		fclose(arqEmp);
        printf("\n\n");	
	}
	else if (menu == 2){
		printf("Digite o código: ");
		scanf("%d", &codigoEx);
		printf("\n\n");
		while(fscanf(arqEmp, "%d %d %s %s %d %d", &codigo, &RAEmp, nomeEm, tituloEm, &QTEm, &praso) != EOF) {
			if(codigo == codigoEx){
				printf("%-4d %-8d %-18s %-30s %-8d %-4d\n", codigo, RAEmp, nomeEm, tituloEm, QTEm, praso);
			}		
		}
		fclose(arqEmp);
        printf("\n\n");
	}
	else if(menu == 3){
		printf("Digite o tempo de atraso: ");
		scanf("%d", &prasoEx);
		printf("\n\n");	
		while(fscanf(arqEmp, "%d %d %s %s %d %d", &codigo, &RAEmp, nomeEm, tituloEm, &QTEm, &praso) != EOF) {
			if(prasoEx >= 16){
				if (praso >= prasoEx){
					printf("%-4d %-8d %-18s %-30s %-8d %-4d\n", codigo, RAEmp, nomeEm, tituloEm, QTEm, praso);
				}
			}
			else 
				printf("Não existe emprestimo em atraso!");	
		}
		fclose(arqEmp);
  		printf("\n\n");
	}
   
}
void emprestimoLivro(){
	int menu;
  do {
    mostarMenuEmprestimo();
    printf("OPÇÃO: ");
    scanf("%d", &menu);
    
    if(menu == 1)
      listarLivros();
    else if(menu == 2) 
      listarAlunos();
    else if(menu == 3) 
      listarEmprestimo();
   else if(menu == 4) {
      printf("\t\t\t***********************************************\n\n");
  	  printf("\t\t\t********   EXCLUIR EMPRESTÍMO ********\n\n");
      
      int codigo;
      printf("Digite código de emprestímo: ");
      scanf("%d", codigo);
      if(excluirEmprestimo(codigo))
        printf("Emprestímo excluido com sucesso.\n");
      else
        printf("Emprestímo não encontrado.\n");
        
      printf("\n");
    }
    else if(menu == 5)
    	cadastrarEmprestimo();
    
  } while(menu != 0);
  
  printf("Programa encerrado\n");	
}

void mostrarMenuPrincipal(){

	printf("\t\t\t***********************************************\n");   
    printf("\t\t\t*       SISTEMA DA BIBLIOTÉCA UNASP - SP       *\n");
    printf("\t\t\t***********************************************\n\n");
	printf("\t\t\t********   MENÚ DE NAVEGAÇÃO DE ACESSOS ********\n\n");
	
    printf("1 - ACESSO DO ALUNO \n");
 	printf("2 - ACESSO DE LIVROS \n");
  	printf("3 - ACESSO DE EMPRESTIMO DE LIVROS\n");
  	printf("4 - ACESSO A LISTA DOS INTEGRANTES DO GRUPO\n");

  	printf("\n0 - Sair\n\n");
    
}
 
void mostarMenuListaGrupo(){
	printf("\n");
	printf("\t\t\t***********************************************\n\n");
    printf("\t\t\t********   ACESSO DE LISTA DOS INTEGRANTES DO GRUPO ********\n\n");
   
	printf("1 - LISTAR INTEGRANTES\n");
  	printf("2 - CADASTRAR INTEGRANTE\n");
  	printf("\n0 - Sair\n");
}
void dadosbonusEnviarEmail(){
    printf("\t\t\t***********************************************\n\n");
	printf("\t\t\t******** ACESSO AO  BONUS - ENVIAR E-MAIL ********\n\n");
	
}
void dadosntegrantesGroupo(){
  mostarMenuListaGrupo();
  FILE * arqGrupoLent = fopen("basededados/basededadosIntegrantes.txt",   "r");
  FILE * arqGrupoEnt = fopen("basededados/basededadosIntegrantes.txt",     "a");
  
  int RA;
  char numero[5], nome[20], sobrenome[20];
  int n;
   
   printf("OPÇÂO:  ");
   scanf("%d", &n);
   printf("\n\n");
    
    if (n ==1){
    	printf("\t\t\t********   LISTAR INTEGRANTE ********\n\n");
    	printf("\n \t NOME \t           SOBRENOME \t          RA 	\n\n");
    
		while(fscanf(arqGrupoLent, "%s %s %s %d", numero, nome, sobrenome, &RA) != EOF) {
    	  printf(" %-5s %-20s %-20s %-8d \n", numero, nome, sobrenome, RA);
    	}	
	}
	fclose(arqGrupoLent);
	printf("\n\n");
   if (n == 2){
		printf("\t\t\t********   CADASTRAR INTEGRANTE ********\n\n");
		
		printf("Digite Número: ");
	    scanf("%s", numero);
	    printf("Digite Nome: ");
	    scanf("%s", nome);
	    printf("Digite Sobrenome: ");
	    scanf("%s", sobrenome);
	    printf("Digite RA: ");
	    scanf("%d", &RA);
	  
  	     fprintf(arqGrupoEnt, "%-5s %-20s %-20s %-8d \n", numero, nome, sobrenome, RA);
	}
	fclose(arqGrupoEnt);
    printf("\n\n"); 
	
}
void bunsEnvioEmail(){
 
}
int main(void) {
  setlocale(LC_ALL, "Portuguese");
  int menu;
  
  do {
    mostrarMenuPrincipal();
    printf("OPÇÃO: ");
    scanf("%d", &menu);
    
    if(menu == 1)
      daddosAlunos();
    else if(menu == 2) 
      dadosLivros();
    else if(menu == 3) 
      emprestimoLivro();
	else if(menu == 4) 
      dadosntegrantesGroupo();
   
  } while(menu != 0);
  
  printf("Programa encerrado\n");
  printf("\n");
  return 0;
}
