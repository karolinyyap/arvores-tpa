//KAROLINY ANDRISEN DO PRADO NEPPEL
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string.h>

using namespace std;

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
    Aluno **raiz;
    int tamanho;
};

Alunos listaSeq;

void inicializa(){
    listaSeq.raiz = new Aluno*[MAXIMO];
    listaSeq.tamanho = 0;

    for(int i = 0; i < MAXIMO; i++){
        listaSeq.raiz[i] = NULL;
    }
}

bool adicionarAluno(Aluno *aluno, int indice) {

    if (indice >= MAXIMO){
        cout << indice << endl;
        return false;
    }

    if (listaSeq.raiz[indice] == NULL){
        listaSeq.raiz[indice] = aluno;
        listaSeq.tamanho++;

        return true;
    } else {
        int comparacao = strcmp(aluno->nome, listaSeq.raiz[indice]->nome);
        if (comparacao <= 0){
            return adicionarAluno(aluno, (2 * indice) + 1);
        } else {
            return adicionarAluno(aluno, (2 * indice) + 2);
        }
    }

    
    return true;
    
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

            opc = adicionarAluno(novo, 0);
            if (opc == false){
                printf("\nVetor cheio!!!\n");
                break;
            }
            contador++;

            // Mostrar a cada 50 mil registros
            if (contador % 50000 == 0) {
                cout << contador << " registros lidos...\n";
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
    printf("Total de alunos inseridos: %d\n", listaSeq.tamanho);
    fim = clock();
    printf("Tempo de leitura: %d milissegundos\n", fim - inicio);
    system("pause");


    return 0;
}
