//KAROLINY ANDRISEN DO PRADO NEPPEL
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <string.h>

//1.048.576

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
};


struct Alunos{
    Aluno *raiz;
    int temp;
    int tamanho;
};

Alunos arvore;

void inicializa(){
    arvore.raiz = NULL;
    arvore.temp = 0;
    arvore.tamanho = 0;
}

//Na primeira iteração pega a raiz
Aluno* adicionarAluno(Aluno *no, Aluno *aluno) {
    aluno->esq = NULL;
    aluno->dir = NULL;
    
    if (no == NULL){
        no = aluno;
        arvore.temp++;
        if(arvore.temp > arvore.tamanho){
            arvore.tamanho = arvore.temp;
        }
    } else {
        arvore.temp++;
        if (strcmp(aluno->nome, no->nome) >= 0){
            no->dir = adicionarAluno(no->dir, aluno);
        } else {
            no->esq = adicionarAluno(no->esq, aluno);
        }
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
            arvore.temp=0;
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
    lerArquivoCSV("..\\alunos_teste.txt");
    fim = clock();
    printf("Tempo de leitura: %d milissegundos\n", fim - inicio);
    system("pause");
    printf("%d", arvore.tamanho);

    return 0;
}
