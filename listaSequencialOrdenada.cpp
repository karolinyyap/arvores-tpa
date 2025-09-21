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
    int altura;
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

int altura(int indice){
	if (listaSeq.raiz[indice]== NULL){
		return -1; 
    } else {
		return listaSeq.raiz[indice]->altura;
	}
}

void atualizaAltura(int indice){
    int dir = (2 * indice) + 2;
    int esq = (2 * indice) + 1;

    if (listaSeq.raiz[esq] == NULL && listaSeq.raiz[dir] == NULL){
        listaSeq.raiz[indice]->altura = 0;
    } else {
        if (altura(esq) > altura(dir)){
            listaSeq.raiz[indice]->altura = altura(esq) + 1;
        } else {
            listaSeq.raiz[indice]->altura = altura(dir) + 1;
        }
    }
}

void rotacaoSimplesEsquerda(int indice) {
    int dir = (2 * indice) + 2;
    int esq = (2 * indice) + 1;

    int esqDir = 2 * esq + 2; //filho direito de esq

    if (listaSeq.raiz[esq] == NULL) return; // nada a rotacionar

    Aluno* raizAtual = listaSeq.raiz[indice];
    Aluno* novaRaiz = listaSeq.raiz[esq];
    Aluno* filho = listaSeq.raiz[esqDir];

    // Nova raiz sobe
    listaSeq.raiz[indice] = novaRaiz;

    // O antigo nó vira filho direito da nova raiz
    listaSeq.raiz[dir] = raizAtual;

    // Reorganiza filhos
    listaSeq.raiz[esq] = listaSeq.raiz[2*esq + 1]; // A fica no mesmo lugar
    listaSeq.raiz[2 * dir + 1] = filho;
    
    atualizaAltura(dir);
    atualizaAltura(indice);

}


void rotacaoSimplesDireita(int indice) {
    int dir = (2 * indice) + 2;
    int esq = (2 * indice) + 1;
    int dirEsq = 2*dir + 1; //filho esquerdo de dir

    if (listaSeq.raiz[dir] == NULL) return; // nada a rotacionar

    Aluno* raizAtual = listaSeq.raiz[indice];
    Aluno* novaRaiz = listaSeq.raiz[dir];
    Aluno* filho = listaSeq.raiz[dirEsq];

    // Nova raiz sobe
    listaSeq.raiz[indice] = novaRaiz;

    // O antigo nó vira filho esquerdo da nova raiz
    listaSeq.raiz[esq] = raizAtual;

    // Reorganiza filhos
    listaSeq.raiz[dir] = listaSeq.raiz[2 * dir + 2]; // C fica no lugar
    listaSeq.raiz[2 * esq + 2] = filho;        // B vira filho direito do antigo nó

    // Atualiza alturas
    atualizaAltura(esq);
    atualizaAltura(indice);

}

void rotacaoDuplaEsqDir(int indice) {
    rotacaoSimplesEsquerda((2 * indice) + 1);

    rotacaoSimplesDireita(indice);
}


void rotacaoDuplaDirEsq(int indice) {
    rotacaoSimplesDireita((2 * indice) + 2);

    rotacaoSimplesEsquerda(indice);
}

bool adicionarAluno(Aluno *aluno, int indice) {
    if (indice >= MAXIMO){
        return false;
    }

    printf("Comecei a inserir");
    if (listaSeq.raiz[indice] == NULL){
        listaSeq.raiz[indice] = aluno;
        listaSeq.tamanho++;

    } else {
        if (strcmp(aluno->nome, listaSeq.raiz[indice]->nome) <= 0){
            return adicionarAluno(aluno, (2 * indice) + 1);
        } else {
            return adicionarAluno(aluno, (2 * indice) + 2);
        }
    }

    atualizaAltura(indice);

    printf("Balanceando");
    int balanceamento = altura((2 * indice) + 1) - altura((2 * indice) + 2);

    if(balanceamento > 1 && strcmp(aluno->nome, listaSeq.raiz[2 * indice + 1]->nome) < 0) {
        printf("RotacioneiDireita");
        rotacaoSimplesDireita(indice);  
    }
    if(balanceamento < -1 && strcmp(aluno->nome, listaSeq.raiz[2 * indice + 2]->nome) > 0) {
        printf("RotacioneiEsquerda");
        rotacaoSimplesEsquerda(indice);            
    }
    if(balanceamento > 1 && strcmp(aluno->nome, listaSeq.raiz[2 * indice + 1]->nome) > 0) {
        printf("RotacioneiEsquerdaDireita");
        rotacaoDuplaEsqDir(indice);
    }
    if(balanceamento < -1 && strcmp(aluno->nome, listaSeq.raiz[2 * indice + 2]->nome) < 0) {
        printf("RotacioneiDireitaEsquerda");
        rotacaoDuplaDirEsq(indice);
    }
    
    printf("Terminei");
    return true;
    
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

            int opc = adicionarAluno(novo, 0);
            if(opc == false){
                printf("Vetor cheio!!");
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


void imprimirInOrder(int indice) {
    if (indice >= MAXIMO || listaSeq.raiz[indice] == NULL)
        return;

    // Imprime subárvore esquerda
    imprimirInOrder(2 * indice + 1);

    // Imprime o nó atual
    Aluno* aluno = listaSeq.raiz[indice];
    cout << "Nome: " << aluno->nome << ", Matricula: " << aluno->matricula
         << ", Nota: " << aluno->nota << ", Idade: " << aluno->idade
         << ", Curso: " << aluno->curso << ", Cidade: " << aluno->cidade
         << ", Altura: " << aluno->altura << endl;

    // Imprime subárvore direita
    imprimirInOrder(2 * indice + 2);
}


int main(){
    inicializa();
    printf("=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n");
    
    int inicio, fim;
    inicio = clock();
    lerArquivoCSV("..\\alunos_teste.txt");
    printf("Total de alunos inseridos: %d\n", listaSeq.tamanho);
    fim = clock();
    printf("Tempo de leitura: %d milissegundos\n", fim - inicio);
    system("pause");
    imprimirInOrder(0);



    return 0;
}
