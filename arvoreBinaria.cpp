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
};


struct Alunos{
    Aluno *raiz;
    int status;
};

Alunos *arvore;

void inicializa(){
    arvore->raiz = NULL;
    arvore->status = 0;
}

Aluno* adicionarAluno(Aluno *aluno) {
    aluno->esq = NULL;
    aluno->dir = NULL;

    if (arvore->raiz == NULL){
        arvore->raiz = aluno;
    } else {
        if (strcmp(aluno->nome, arvore->raiz->nome) > 0){

        } else {

        }
    }

    return arvore->raiz;
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

            adicionarAluno(novo);
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

// Função recursiva que imprime a árvore em ordem (alfabética pelo nome)
void imprimirRec(Aluno* raiz) {
    if (raiz == NULL) return;

    imprimirRec(raiz->esq);  // Visita subárvore esquerda
    std::cout << "Nome: " << raiz->nome
              << " | Matrícula: " << raiz->matricula
              << std::endl;
    imprimirRec(raiz->dir);  // Visita subárvore direita
}

// Função pública que chama a recursiva
void imprimir() {
    if (arvore->raiz == NULL) {
        std::cout << "A árvore está vazia!" << std::endl;
        return;
    }
    imprimirRec(arvore->raiz);
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

    imprimir();

    return 0;
}