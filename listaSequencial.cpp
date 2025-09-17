//KAROLINY ANDRISEN DO PRADO NEPPEL
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <string.h>

#define MAXIMO 1048576

struct Aluno{
    char matricula[9];
    char cpf[15];
    char nome[50];
    double nota;
    int idade;
    char curso[40];
    char cidade[40];
};


struct Alunos{
    Aluno aluno[MAXIMO];
    int tamanho;
};

Alunos listaSeq;

void inicializa(){
    listaSeq.tamanho = 0;
}

//Na primeira iteração pega a raiz
bool adicionarAluno(Aluno *aluno) {
    if (listaSeq.tamanho == NULL){
        return false;
    }

    
}

void lerArquivoCSV(const char* nomeArquivo) {
    bool opc;
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

            opc = adicionarAluno(novo);
            if (opc == false){
                printf("\nVetor cheio!!!\n");
                exit(EXIT_FAILURE);
            }
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
