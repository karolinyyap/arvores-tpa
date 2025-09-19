//KAROLINY ANDRISEN DO PRADO NEPPEL
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <string.h>

struct Aluno{
    char matricula[9];
    char cpf[15];
    char nome[50];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
    Aluno *dir;
    Aluno *esq;
    int altura;
};


struct Alunos{
    Aluno *raiz;
    int quantidade;
    int tamanhoAtual;
};

Alunos arvore;

void inicializa(){
    arvore.raiz = NULL;
    arvore.quantidade = 0;
    arvore.tamanhoAtual = 0;
}

void atualizaAltura(Aluno *no){
    ///.....
    ;
}

Aluno* rotacaoSimplesEsquerda(Aluno *raizAtual) {
    Aluno *novaRaiz = raizAtual->dir;
    Aluno *filho = novaRaiz->esq;

    // Executa a rotação
    novaRaiz->esq = raizAtual->dir;
    raizAtual->dir = filho;

    // Atualiza alturas
    atualizaAltura(novaRaiz);
    atualizaAltura(raizAtual);

    // Novo nó raiz
    return novaRaiz;
}

Aluno* rotacaoSimplesDireita(Aluno *raizAtual) {
    Aluno *novaRaiz = raizAtual->esq;
    Aluno *filho = novaRaiz->dir;

    // Executa a rotação
    novaRaiz->dir = raizAtual->esq;
    raizAtual->esq = filho;

    // Atualiza alturas
    atualizaAltura(novaRaiz);
    atualizaAltura(raizAtual);

    // Novo nó raiz
    return novaRaiz;
}

Aluno* rotacaoDuplaEsqDir(Aluno *raizAtual) {
    raizAtual->esq = rotacaoSimplesEsquerda(raizAtual);

    return rotacaoSimplesDireita(raizAtual);
}

Aluno* rotacaoDuplaDirEsq(Aluno *raizAtual) {
    raizAtual->esq = rotacaoSimplesDireita(raizAtual);

    return rotacaoSimplesEsquerda(raizAtual);
}

int altura(Aluno *no){
	if (no == NULL)
		return -1; 
	else {
		return no->altura;
	}
}

Aluno* adicionarAluno(Aluno *no, Aluno *aluno) {
    if(no == NULL)
        return no = aluno;

    if(strcmp(aluno->nome, no->nome)){
        no->dir = adicionarAluno(no->dir, aluno);
    }
    else{
        no->esq = adicionarAluno(no->esq, aluno);
    }

    atualizaAltura(no);

    int balanceamento = altura(no->esq) - altura(no->dir);

    if(balanceamento > 1 && /*condicao para rotação SimplesDireita*/0) {
        ///....
    }
    if(balanceamento < -1 &&  0) {
        return rotacaoSimplesEsquerda(no);            
    }
    if(balanceamento > 1 && /*condicao para rotação DuplaDireita*/0) {
        ///....
    }
    if(balanceamento < -1 && /*condição para rotação DuplaEsquerda*/0) {
        ///....
    }

    return no;
}

void lerArquivoCSV(const char* nomeArquivo) {
    int contador = 0;
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }
    char linha[300];
    
    printf("Iniciando leitura do arquivo CSV...\n");
    
    //Tirando a primeira linha
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        printf("Arquivo vazio ou erro na leitura\n");
        fclose(arquivo);
        return;
    }

    
    while (!feof(arquivo)) {
        Aluno* novo = new Aluno;
        if (fscanf(arquivo, "%8[^,],%14[^,],%39[^,],%lf,%d,%39[^,],%39[^\n]\n", 
                   novo->matricula, novo->cpf, novo->nome, &novo->nota, &novo->idade, novo->curso, novo->cidade) == 7) {

            arvore.raiz = adicionarAluno(arvore.raiz, novo);
            contador++;

            // Mostrar a cada 50 mil registros
            if (contador % 50000 == 0) {
                std::cout << contador << " registros lidos...\n";
            }

        } else {
            printf("Erro ao ler linha: %s\n", linha);
            delete novo;
            continue;
        }
    }
    
    fclose(arquivo);
}


int main(){
    inicializa();
    printf("=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n");
    
    int inicio, fim;
    inicio = clock();
    lerArquivoCSV("..\\alunos_completosV2.csv");
    fim = clock();
    printf("Tempo de leitura: %d milissegundos\n", fim - inicio);
    system("pause");

    return 0;
}
