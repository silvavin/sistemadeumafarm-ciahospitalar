#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura principal do medicamento (Arquivo Sequencial) [cite: 34]
typedef struct {
    int id;
    char nome[50];
    char dosagem[20];
    char fabricante[50];
} Medicamento;

// Estrutura do índice (Arquivo Indexado) [cite: 24, 28]
typedef struct {
    int id;
    long offset; // Posição no arquivo original [cite: 26]
} Indice;

// Protótipos das funções
void cadastrarMedicamento();
void gerarRelatorioSequencial();
void consultaRapidaIndexada();
void limparBuffer();

int main() {
    int opcao;

    do {
        printf("\n--- SGIM - Gestao de Inventario de Medicamentos ---\n");
        printf("1. Cadastrar Medicamento (Sequencial)\n");
        printf("2. Relatorio Geral (Leitura Linear)\n");
        printf("3. Consulta Rapida (Uso de Indice)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: cadastrarMedicamento(); break;
            case 2: gerarRelatorioSequencial(); break;
            case 3: consultaRapidaIndexada(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

void cadastrarMedicamento() {
    FILE *fDados = fopen("medicamentos.dat", "ab"); // Inserção no final [cite: 19]
    FILE *fIndice = fopen("indices.idx", "ab");
    
    if (fDados == NULL || fIndice == NULL) { // Tratamento de erro [cite: 16]
        printf("Erro ao abrir arquivos!\n");
        return;
    }

    Medicamento m;
    Indice i;

    printf("ID: ");
    scanf("%d", &m.id);
    limparBuffer();
    printf("Nome: ");
    fgets(m.nome, 50, stdin);
    strtok(m.nome, "\n");
    printf("Dosagem: ");
    fgets(m.dosagem, 20, stdin);
    strtok(m.dosagem, "\n");
    printf("Fabricante: ");
    fgets(m.fabricante, 50, stdin);
    strtok(m.fabricante, "\n");

    // Captura a posição antes de gravar (Indexação) [cite: 29, 52]
    i.id = m.id;
    fseek(fDados, 0, SEEK_END); 
    i.offset = ftell(fDados); 

    fwrite(&m, sizeof(Medicamento), 1, fDados);
    fwrite(&i, sizeof(Indice), 1, fIndice);

    fclose(fDados);
    fclose(fIndice);
    printf("Medicamento cadastrado com sucesso!\n");
}

void gerarRelatorioSequencial() {
    FILE *f = fopen("medicamentos.dat", "rb");
    if (f == NULL) return;

    Medicamento m;
    int contador = 0;

    printf("\n--- Relatorio Geral (Busca Linear) ---\n");
    while (fread(&m, sizeof(Medicamento), 1, f)) {
        printf("ID: %d | Nome: %s | Fabricante: %s\n", m.id, m.nome, m.fabricante);
        contador++; // Simula o desafio da busca linear [cite: 21]
    }
    printf("Total de registros lidos sequencialmente: %d\n", contador);
    fclose(f);
}

void consultaRapidaIndexada() {
    int buscaId;
    printf("Digite o ID para busca instantanea: ");
    scanf("%d", &buscaId);

    FILE *fIndice = fopen("indices.idx", "rb");
    FILE *fDados = fopen("medicamentos.dat", "rb");

    if (!fIndice || !fDados) return;

    Indice idx;
    int encontrado = 0;

    // O sistema lê o índice para encontrar a posição exata [cite: 29]
    while (fread(&idx, sizeof(Indice), 1, fIndice)) {
        if (idx.id == buscaId) {
            // Usa o fseek para acessar o dado diretamente no arquivo principal [cite: 29, 30]
            fseek(fDados, idx.offset, SEEK_SET);
            Medicamento m;
            fread(&m, sizeof(Medicamento), 1, fDados);
            
            printf("\n--- Medicamento Encontrado ---\n");
            printf("ID: %d\nNome: %s\nDosagem: %s\nFabricante: %s\n", m.id, m.nome, m.dosagem, m.fabricante);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) printf("Medicamento nao localizado.\n");

    fclose(fIndice);
    fclose(fDados);
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
