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
    int alturaMaxima;
};

Alunos arvore;

void inicializa(){
    arvore.raiz = NULL;
    arvore.quantidade = 0;
    arvore.alturaMaxima = -1;
}

int altura(Aluno *no){
	if (no == NULL)
		return -1; 
	else {
		return no->altura;
	}
}

void atualizaAltura(Aluno *no){
    if (no->esq == NULL && no->dir == NULL){
        no->altura = 0;
    } else {
        if (altura(no->esq) > altura(no->dir)){
            no->altura = altura(no->esq) + 1;
        } else {
            no->altura = altura(no->dir) + 1;
        }
    }
}

Aluno* rotacaoSimplesEsquerda(Aluno *raizAtual) {
    Aluno *novaRaiz = raizAtual->dir;
    Aluno *filho = novaRaiz->esq;

    novaRaiz->esq = raizAtual;
    raizAtual->dir = filho;

    atualizaAltura(raizAtual);
    atualizaAltura(novaRaiz);

    return novaRaiz;
}


Aluno* rotacaoSimplesDireita(Aluno *raizAtual) {
    Aluno *novaRaiz = raizAtual->esq;
    Aluno *filho = novaRaiz->dir;

    novaRaiz->dir = raizAtual;
    raizAtual->esq = filho;

    atualizaAltura(raizAtual);
    atualizaAltura(novaRaiz);

    return novaRaiz;
}



Aluno* rotacaoDuplaEsqDir(Aluno *raizAtual) {
    raizAtual->esq = rotacaoSimplesEsquerda(raizAtual->esq);

    return rotacaoSimplesDireita(raizAtual);
}


Aluno* rotacaoDuplaDirEsq(Aluno *raizAtual) {
    raizAtual->dir = rotacaoSimplesDireita(raizAtual->dir);

    return rotacaoSimplesEsquerda(raizAtual);
}



Aluno* adicionarAluno(Aluno *no, Aluno *aluno) {
    int ladoInserido; //1 - direita; 0 - esquerda

    if(no == NULL){
        no = aluno;
        no->dir = NULL;
        no->esq = NULL;
        arvore.quantidade++;
    } else {
        if(strcmp(aluno->nome, no->nome) >= 0){
            no->dir = adicionarAluno(no->dir, aluno);
            ladoInserido = 1;
        }
        else{
            no->esq = adicionarAluno(no->esq, aluno);
            ladoInserido = 0;
        }
    }

    atualizaAltura(no);
    if (no->altura > arvore.alturaMaxima) {
        arvore.alturaMaxima = no->altura;
    }

    int balanceamento = altura(no->esq) - altura(no->dir);

    int balanceamento2 = 0;
    if (ladoInserido == 1 && no->dir != NULL) {
        balanceamento2 = altura(no->dir->esq) - altura(no->dir->dir);
    } else if (ladoInserido == 0 && no->esq != NULL) {
        balanceamento2 = altura(no->esq->esq) - altura(no->esq->dir);
    }

    if(balanceamento > 1 && balanceamento2 > 0) {
        return rotacaoSimplesDireita(no);  
    }
    if(balanceamento < -1 && balanceamento2 < 0) {
        return rotacaoSimplesEsquerda(no);            
    }
    if(balanceamento > 1 && balanceamento2 < 0) {
        return rotacaoDuplaEsqDir(no);
    }
    if(balanceamento < -1 && balanceamento2 > 0) {
        return rotacaoDuplaDirEsq(no);
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

Aluno* busca(Aluno *no, const char *nome){

    if (no == NULL) {
        return NULL;
    }

    if (strcmp(nome, no->nome) == 0) {
        return no;
    } else if(strcmp(nome, no->nome) > 0){
        return busca(no->dir, nome);
    } else {
        return busca(no->esq, nome);
    }
}

void lerArqBusca(const char* nomeArquivo){
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    char nome[50];

    while (fscanf(arquivo, "%49[^\n]\n", nome) == 1) {
    Aluno* pos = busca(arvore.raiz, nome);
    if (pos != NULL){
        std::cout << "Achei!" << "\n";
    } else {
        std::cout << "Não achei :(\n";
        }
    }
}

Aluno* exclusao(Aluno* raiz, const char* nome) {
    if (raiz == NULL) {
        printf("Valor não encontrado!\n");
        return NULL;
    }

    // Desce na árvore até achar
    if (strcmp(nome, raiz->nome) < 0) {
        raiz->esq = exclusao(raiz->esq, nome);
    } else if (strcmp(nome, raiz->nome) > 0) {
        raiz->dir = exclusao(raiz->dir, nome);
    } else {
        // Nó encontrado
        if (raiz->esq == NULL) {
            Aluno* temp = raiz->dir;
            delete raiz;   // você usa new, então use delete
            return temp;
        } else if (raiz->dir == NULL) {
            Aluno* temp = raiz->esq;
            delete raiz;
            return temp;
        }

        // Nó com dois filhos: pega o menor da subárvore direita
        Aluno* temp = raiz->dir;
        while (temp->esq != NULL) {
            temp = temp->esq;
        }

        // Copia todos os dados do sucessor
        strcpy(raiz->matricula, temp->matricula);
        strcpy(raiz->cpf, temp->cpf);
        strcpy(raiz->nome, temp->nome);
        raiz->nota = temp->nota;
        raiz->idade = temp->idade;
        strcpy(raiz->curso, temp->curso);
        strcpy(raiz->cidade, temp->cidade);

        // Remove o sucessor
        raiz->dir = exclusao(raiz->dir, temp->nome);
    }

    //Atualiza altura
    atualizaAltura(raiz);

    //Balanceamento
    int balanceamento = altura(raiz->esq) - altura(raiz->dir);

    if (balanceamento > 1 && (altura(raiz->esq->esq) >= altura(raiz->esq->dir)))
        return rotacaoSimplesDireita(raiz);

    if (balanceamento > 1 && (altura(raiz->esq->esq) < altura(raiz->esq->dir)))
        return rotacaoDuplaEsqDir(raiz);

    if (balanceamento < -1 && (altura(raiz->dir->dir) >= altura(raiz->dir->esq)))
        return rotacaoSimplesEsquerda(raiz);

    if (balanceamento < -1 && (altura(raiz->dir->dir) < altura(raiz->dir->esq)))
        return rotacaoDuplaDirEsq(raiz);

    return raiz;
}

void lerArqExclusao(const char* nomeArquivo){
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return;
    }

    char nome[50];

    while (fscanf(arquivo, "%49[^\n]\n", nome) == 1) {
    Aluno* pos = exclusao(arvore.raiz, nome);
    if (pos != NULL){
        std::cout << "Excluí!" << "\n";
    } else {
        std::cout << "Não achei para excluir :(\n";
        }
    }
}

int main(){
    inicializa();
    printf("=== SISTEMA DE LEITURA DE ALUNOS CSV ===\n\n");
    
    int inicio, fim;
    inicio = clock();
    lerArquivoCSV("..\\alunos_completosV2.csv");
    fim = clock();
    printf("Tempo de leitura: %d milissegundos\n", fim - inicio); //10 segundos
    printf("Total de alunos lidos: %d\n", arvore.quantidade);
    system("pause");

    int inicio2, fim2;
    inicio2 = clock();
    lerArqBusca("..\\alunos_busca.txt");
    fim2 = clock();
    printf("Tempo de leitura: %d milissegundos\n", fim2 - inicio2); //150 milisegundos
    printf("Altura máxima da árvore: %d\n", arvore.alturaMaxima); //23

    int inicio3, fim3;
    inicio3 = clock();
    lerArqExclusao("..\\alunos_excluir.txt");
    fim3 = clock();
    printf("Tempo de leitura: %d milissegundos\n", fim3 - inicio3); //200 milisegundos

    return 0;
}
