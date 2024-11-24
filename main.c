#include <stdio.h>  // Biblioteca padrão para entrada e saída
#include <stdlib.h> // Biblioteca padrão para funções gerais, como alocação de memória e conversões
#include <string.h> // Biblioteca para manipulação de strings
#include <locale.h> // Biblioteca para configurar a localidade, usada aqui para suportar caracteres acentuados
#include <conio.h>  // Biblioteca usada para entrada de dados no modo de console, como getch()


// Estrutura para Cadastro de Emissões e Indústrias
typedef struct {
    char nome[50];
    float valor;
} Emissao;

typedef struct {
    char nome[50];
    char cnpj[20];
    char endereco[100];
    float insumosTrabalhados[6];
    float gastosMensais[6];
} Industria;

// Estrutura para Cadastro de Funcionários
typedef struct {
    char nome[50];
    char telefone[15];
    char cpf[15];
    char endereco[100];
} Funcionario;

// Função para limpar o buffer do teclado
void limparBuffer() {
    while (getchar() != '\n');
}

// Função para salvar os dados dos funcionários em arquivos TXT, CSV e XLS
void salvarFuncionariosEmArquivos(Funcionario *funcionarios, int totalFuncionarios) {
    // Salvando em TXT
    FILE *arquivoTXT = fopen("funcionarios.txt", "w");
    if (arquivoTXT == NULL) {
        printf("Erro ao criar o arquivo TXT.\n");
        return;
    }
    fprintf(arquivoTXT, "Lista de Funcionários\n");
    fprintf(arquivoTXT, "---------------------\n");
    for (int i = 0; i < totalFuncionarios; i++) {
        fprintf(arquivoTXT, "Nome: %s\n", funcionarios[i].nome);
        fprintf(arquivoTXT, "Telefone: %s\n", funcionarios[i].telefone);
        fprintf(arquivoTXT, "CPF: %s\n", funcionarios[i].cpf);
        fprintf(arquivoTXT, "Endereço: %s\n\n", funcionarios[i].endereco);
    }
    fclose(arquivoTXT);

    // Salvando em CSV
    FILE *arquivoCSV = fopen("funcionarios.csv", "w");
    if (arquivoCSV == NULL) {
        printf("Erro ao criar o arquivo CSV.\n");
        return;
    }
    fprintf(arquivoCSV, "Nome,Telefone,CPF,Endereco\n");
    for (int i = 0; i < totalFuncionarios; i++) {
        fprintf(arquivoCSV, "\"%s\",\"%s\",\"%s\",\"%s\"\n",
                funcionarios[i].nome,
                funcionarios[i].telefone,
                funcionarios[i].cpf,
                funcionarios[i].endereco);
    }
    fclose(arquivoCSV);

    // Salvando em XLS (simulado como um arquivo tabulado)
    FILE *arquivoXLS = fopen("funcionarios.xls", "w");
    if (arquivoXLS == NULL) {
        printf("Erro ao criar o arquivo XLS.\n");
        return;
    }
    fprintf(arquivoXLS, "Nome\tTelefone\tCPF\tEndereço\n");
    for (int i = 0; i < totalFuncionarios; i++) {
        fprintf(arquivoXLS, "%s\t%s\t%s\t%s\n",
                funcionarios[i].nome,
                funcionarios[i].telefone,
                funcionarios[i].cpf,
                funcionarios[i].endereco);
    }
    fclose(arquivoXLS);

    printf("Dados dos funcionários salvos em 'funcionarios.txt', 'funcionarios.csv' e 'funcionarios.xls'.\n");
}

// Função para adicionar uma nova emissão
void adicionarEmissao(Emissao *emissoes, int *count) {
    printf("\n--- Adicionar Nova Emissão ---\n");
    printf("Digite o nome da emissão: ");
    limparBuffer();
    fgets(emissoes[*count].nome, 50, stdin);
    emissoes[*count].nome[strcspn(emissoes[*count].nome, "\n")] = 0;

    printf("Digite o valor da emissão tratada: ");
    while (scanf("%f", &emissoes[*count].valor) != 1) {
        printf("Valor inválido! Tente novamente: ");
        limparBuffer();
    }

    (*count)++;
    printf("Emissão adicionada com sucesso!\n");
}

// Função para cadastrar uma nova indústria
void cadastrarIndustria(Industria *industrias, int *totalIndustrias) {
    printf("\n--- Cadastrar Nova Indústria ---\n");
    printf("Digite o nome da indústria: ");
    limparBuffer();
    fgets(industrias[*totalIndustrias].nome, 50, stdin);
    industrias[*totalIndustrias].nome[strcspn(industrias[*totalIndustrias].nome, "\n")] = 0;

    printf("Digite o CNPJ da indústria: ");
    fgets(industrias[*totalIndustrias].cnpj, 20, stdin);
    industrias[*totalIndustrias].cnpj[strcspn(industrias[*totalIndustrias].cnpj, "\n")] = 0;

    printf("Digite o endereço da indústria: ");
    fgets(industrias[*totalIndustrias].endereco, 100, stdin);
    industrias[*totalIndustrias].endereco[strcspn(industrias[*totalIndustrias].endereco, "\n")] = 0;

    for (int i = 0; i < 6; i++) {
        printf("Digite o total de insumos tratados no mês %d: ", i + 1);
        while (scanf("%f", &industrias[*totalIndustrias].insumosTrabalhados[i]) != 1) {
            printf("Valor inválido! Tente novamente: ");
            limparBuffer();
        }
    }

    for (int i = 0; i < 6; i++) {
        printf("Digite o total de gastos no mês %d: ", i + 1);
        while (scanf("%f", &industrias[*totalIndustrias].gastosMensais[i]) != 1) {
            printf("Valor inválido! Tente novamente: ");
            limparBuffer();
        }
    }

    (*totalIndustrias)++;
    printf("Indústria cadastrada com sucesso!\n");
}

// Função para gerar relatório individual
void gerarRelatorioIndividual(Industria *industrias, int totalIndustrias) {
    char nomeIndustria[50];
    printf("\n--- Gerar Relatório Individual ---\n");
    printf("Digite o nome da indústria: ");
    limparBuffer();
    fgets(nomeIndustria, 50, stdin);
    nomeIndustria[strcspn(nomeIndustria, "\n")] = 0;

    for (int i = 0; i < totalIndustrias; i++) {
        if (strcmp(industrias[i].nome, nomeIndustria) == 0) {
            float totalInsumos = 0, totalGastos = 0;
            for (int j = 0; j < 6; j++) {
                totalInsumos += industrias[i].insumosTrabalhados[j];
                totalGastos += industrias[i].gastosMensais[j];
            }
            printf("\nRelatório da Indústria %s:\n", industrias[i].nome);
            printf("Total de insumos tratados (semestral): %.2f\n", totalInsumos);
            printf("Gastos mensais médios: %.2f\n", totalGastos / 6);
            return;
        }
    }
    printf("Indústria não encontrada.\n");
}

// Função para gerar relatório global
void gerarRelatorioGlobal(Industria *industrias, int totalIndustrias) {
    float totalInsumos = 0;
    Industria *menorProdutora = NULL;
    float totalGastos = 0;

    for (int i = 0; i < totalIndustrias; i++) {
        float insumosIndustria = 0;
        for (int j = 0; j < 6; j++) {
            insumosIndustria += industrias[i].insumosTrabalhados[j];
            totalGastos += industrias[i].gastosMensais[j];
        }
        totalInsumos += insumosIndustria;

        if (menorProdutora == NULL || insumosIndustria < menorProdutora->insumosTrabalhados[0]) {
            menorProdutora = &industrias[i];
        }
    }

    printf("\n--- Relatório Global ---\n");
    printf("Total de insumos tratados: %.2f\n", totalInsumos);
    if (menorProdutora != NULL) {
        printf("Indústria com menor produção: %s\n", menorProdutora->nome);
    }
    printf("Gasto financeiro total: %.2f\n", totalGastos);
}

// Função de login com senha protegida
int login(const char *usuario, const char *senha) {
    char inputUsuario[50], inputSenha[50];
    int i = 0;

    printf("\nDigite o nome de usuário: ");
    fgets(inputUsuario, 50, stdin);
    inputUsuario[strcspn(inputUsuario, "\n")] = 0;

    printf("Digite a senha: ");
    while (1) {
        char ch = getch();

        if (ch == 13) break;
        if (ch == 8 && i > 0) {
            i--;
            printf("\b \b");
        } else if (ch != 8) {
            inputSenha[i++] = ch;
            printf("*");
        }
    }
    inputSenha[i] = '\0';
    printf("\n");

    return (strcmp(inputUsuario, usuario) == 0 && strcmp(inputSenha, senha) == 0);
}

// Função para cadastrar um novo funcionário
void cadastrarFuncionario(Funcionario *funcionarios, int *totalFuncionarios) {
    printf("\n--- Cadastrar Novo Funcionário ---\n");
    printf("Digite o nome do funcionário: ");
    limparBuffer();
    fgets(funcionarios[*totalFuncionarios].nome, 50, stdin);
    funcionarios[*totalFuncionarios].nome[strcspn(funcionarios[*totalFuncionarios].nome, "\n")] = 0;

    printf("Digite o telefone do funcionário: ");
    fgets(funcionarios[*totalFuncionarios].telefone, 15, stdin);
    funcionarios[*totalFuncionarios].telefone[strcspn(funcionarios[*totalFuncionarios].telefone, "\n")] = 0;

    printf("Digite o CPF do funcionário: ");
    fgets(funcionarios[*totalFuncionarios].cpf, 15, stdin);
    funcionarios[*totalFuncionarios].cpf[strcspn(funcionarios[*totalFuncionarios].cpf, "\n")] = 0;

    printf("Digite o endereço do funcionário: ");
    fgets(funcionarios[*totalFuncionarios].endereco, 100, stdin);
    funcionarios[*totalFuncionarios].endereco[strcspn(funcionarios[*totalFuncionarios].endereco, "\n")] = 0;

    (*totalFuncionarios)++;
    printf("Funcionário cadastrado com sucesso!\n");

    // Salvar automaticamente em arquivos
    salvarFuncionariosEmArquivos(funcionarios, *totalFuncionarios);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    Emissao emissoes[100];
    Industria industrias[100];
    Funcionario funcionarios[100];
    int totalEmissoes = 0, totalIndustrias = 0, totalFuncionarios = 0;

    char usuario[50] = "wilson";
    char senha[50] = "teste1234";

    printf("--- Bem-vindoSistema de Gestão EcoSphere Solutions --- \n \n");
    if (!login(usuario, senha)) {
        printf("Login ou senha incorretos.\n");
        return 1;
    }

    int opcao;
    do {
        printf("\n--- Menu Principal ---\n");
        printf("1. Cadastrar Nova Emissão\n");
        printf("2. Cadastrar Nova Indústria\n");
        printf("3. Gerar Relatório Individual\n");
        printf("4. Gerar Relatório Global\n");
        printf("5. Cadastrar Novo Funcionário\n");
        printf("6. Sair\n");
        printf("Digite sua opção: ");

        while (scanf("%d", &opcao) != 1) {
            printf("Opção inválida! Tente novamente: ");
            limparBuffer();
        }

        switch (opcao) {
            case 1:
                adicionarEmissao(emissoes, &totalEmissoes);
                break;
            case 2:
                cadastrarIndustria(industrias, &totalIndustrias);
                break;
            case 3:
                gerarRelatorioIndividual(industrias, totalIndustrias);
                break;
            case 4:
                gerarRelatorioGlobal(industrias, totalIndustrias);
                break;
            case 5:
                cadastrarFuncionario(funcionarios, &totalFuncionarios);
                break;
            case 6:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}
