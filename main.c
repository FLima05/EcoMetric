#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição de fatores de emissão (Kg de CO2 por unidade)
#define FATOR_ELETRICIDADE 0.13    // Kg CO2 por kWh
#define FATOR_GAS_COZINHA  2.98    // Kg CO2 por Kg de GLP
#define FATOR_GASOLINA     2.31    // Kg CO2 por Litro
#define FATOR_DIESEL        2.68    // Kg CO2 por Litro
#define FATOR_PLASTICO     2.00    // Kg CO2 por Kg de plástico virgem
#define FATOR_PAPEL        0.90    // Kg CO2 por Kg de papel/papelão
#define FATOR_AGUA         0.0003  // Kg CO2 por Litro de água tratada/consumida

// Estrutura para armazenar os dados de entrada do usuário
typedef struct {
    char nome_empresa[100];
    float eletricidade_kwh;
    float gas_cozinha_kg;
    float gasolina_litros;
    float diesel_litros;
    float plastico_kg;
    float papel_kg;
    float agua_litros; // Nova métrica!
} DadosConsumo;

// Estrutura para armazenar os resultados do impacto ambiental
typedef struct {
    float co2_eletricidade;
    float co2_gas_cozinha;
    float co2_gasolina;
    float co2_diesel;
    float co2_plastico;
    float co2_papel;
    float co2_agua;
    float co2_total_kg;
    float arvores_necessarias;
} RelatorioImpacto;

// Função para limpar o buffer do teclado
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função auxiliar para ler float positivo com validação
float ler_float_positivo(const char *mensagem) {
    float valor;
    do {
        printf("%s", mensagem);
        if (scanf("%f", &valor) != 1 || valor < 0) {
            printf("⚠️ Por favor, insira um valor numérico válido e positivo.\n");
            limpar_buffer();
        } else {
            return valor;
        }
    } while (1);
}

void coletar_dados(DadosConsumo *dados) {
    printf("==================================================\n");
    printf("         COLETA DE DADOS DE CONSUMO MENSAL        \n");
    printf("==================================================\n");
    
    printf("Digite o nome da empresa ou indivíduo: ");
    fgets(dados->nome_empresa, sizeof(dados->nome_empresa), stdin);
    dados->nome_empresa[strcspn(dados->nome_empresa, "\n")] = 0; 

    dados->eletricidade_kwh = ler_float_positivo("Consumo de eletricidade (kWh): ");
    dados->gas_cozinha_kg   = ler_float_positivo("Consumo de Gás de Cozinha / GLP (Kg): ");
    dados->gasolina_litros  = ler_float_positivo("Consumo de Gasolina (Litros): ");
    dados->diesel_litros    = ler_float_positivo("Consumo de Diesel (Litros): ");
    dados->plastico_kg      = ler_float_positivo("Uso/Descarte de Plásticos de uso único (Kg): ");
    dados->papel_kg         = ler_float_positivo("Consumo de Papel e Papelão (Kg): ");
    dados->agua_litros      = ler_float_positivo("Consumo de Água Encanada (Litros): ");
}

void calcular_impacto(const DadosConsumo *dados, RelatorioImpacto *relatorio) {
    relatorio->co2_eletricidade = dados->eletricidade_kwh * FATOR_ELETRICIDADE;
    relatorio->co2_gas_cozinha  = dados->gas_cozinha_kg * FATOR_GAS_COZINHA;
    relatorio->co2_gasolina     = dados->gasolina_litros * FATOR_GASOLINA;
    relatorio->co2_diesel       = dados->diesel_litros * FATOR_DIESEL;
    relatorio->co2_plastico     = dados->plastico_kg * FATOR_PLASTICO;
    relatorio->co2_papel        = dados->papel_kg * FATOR_PAPEL;
    relatorio->co2_agua         = dados->agua_litros * FATOR_AGUA;
    
    relatorio->co2_total_kg = relatorio->co2_eletricidade + 
                              relatorio->co2_gas_cozinha + 
                              relatorio->co2_gasolina + 
                              relatorio->co2_diesel + 
                              relatorio->co2_plastico + 
                              relatorio->co2_papel +
                              relatorio->co2_agua;
    
    // Estimativa: Uma árvore absorve ~7.5kg de CO2 por ano.
    relatorio->arvores_necessarias = (relatorio->co2_total_kg * 12.0) / 7.5;
}

// Salva o relatório gerado em um arquivo TXT persistente
void salvar_em_arquivo(const DadosConsumo *dados, const RelatorioImpacto *relatorio) {
    FILE *arquivo = fopen("historico_sustentabilidade.txt", "a"); // "a" adiciona ao final do arquivo sem apagar o anterior
    if (arquivo == NULL) {
        printf("⚠️ Erro ao salvar o relatório em arquivo.\n");
        return;
    }

    fprintf(arquivo, "==================================================\n");
    fprintf(arquivo, "EMPRESA/USUÁRIO: %s\n", dados->nome_empresa);
    fprintf(arquivo, "TOTAL EMITIDO: %.2f Kg CO2 (%.2f Toneladas)\n", relatorio->co2_total_kg, relatorio->co2_total_kg / 1000.0);
    fprintf(arquivo, "Compensação: %.0f árvores necessárias.\n", relatorio->arvores_necessarias);
    fprintf(arquivo, "==================================================\n\n");

    fclose(arquivo);
    printf("\n💾 Relatório salvo com sucesso em 'historico_sustentabilidade.txt'!\n");
}

void exibir_relatorio(const DadosConsumo *dados, const RelatorioImpacto *relatorio) {
    printf("\n==================================================\n");
    printf("      RELATÓRIO DE PEGADA DE CARBONO MENSAL       \n");
    printf("==================================================\n");
    printf("Empresa/Usuário: %s\n\n", dados->nome_empresa);
    
    printf("Desdobramento das Emissões (em Kg de CO2):\n");
    printf("  - Eletricidade:    %10.2f Kg CO2\n", relatorio->co2_eletricidade);
    printf("  - Gás de Cozinha:  %10.2f Kg CO2\n", relatorio->co2_gas_cozinha);
    printf("  - Gasolina:        %10.2f Kg CO2\n", relatorio->co2_gasolina);
    printf("  - Diesel:          %10.2f Kg CO2\n", relatorio->co2_diesel);
    printf("  - Plásticos:       %10.2f Kg CO2\n", relatorio->co2_plastico);
    printf("  - Papel/Papelão:   %10.2f Kg CO2\n", relatorio->co2_papel);
    printf("  - Água Encanada:   %10.2f Kg CO2\n", relatorio->co2_agua);
    
    printf("--------------------------------------------------\n");
    printf("TOTAL EMITIDO:       %10.2f Kg CO2 (%.2f Toneladas)\n", 
            relatorio->co2_total_kg, relatorio->co2_total_kg / 1000.0);
    printf("Compensação Anual:   Mínimo de %.0f árvores plantadas para neutralização.\n", 
            relatorio->arvores_necessarias);
    
    printf("\n==================================================\n");
    printf("         PLANO DE METAS E SUGESTÕES DE REDUÇÃO    \n");
    printf("==================================================\n");
    
    int possui_sugestao = 0;
    float economia_total_co2 = 0;
    
    if (relatorio->co2_eletricidade > 50.0) {
        float economia = relatorio->co2_eletricidade * 0.10;
        printf("[ ] Energia: Reduzir 10%% desligando aparelhos em stand-by. Meta: -%.2f Kg CO2.\n", economia);
        economia_total_co2 += economia;
        possui_sugestao = 1;
    }
    if ((relatorio->co2_gasolina + relatorio->co2_diesel) > 100.0) {
        float economia = (relatorio->co2_gasolina + relatorio->co2_diesel) * 0.15;
        printf("[ ] Mobilidade: Otimizar rotas de entrega ou caronas. Meta: -%.2f Kg CO2.\n", economia);
        economia_total_co2 += economia;
        possui_sugestao = 1;
    }
    if (relatorio->co2_plastico > 20.0) {
        float economia = relatorio->co2_plastico * 0.50;
        printf("[ ] Resíduos: Substituir copos descartáveis por reutilizáveis. Meta: -%.2f Kg CO2.\n", economia);
        economia_total_co2 += economia;
        possui_sugestao = 1;
    }
    if (relatorio->co2_agua > 5.0) {
        float economia = relatorio->co2_agua * 0.20;
        printf("[ ] Água: Captar água da chuva ou ajustar descargas. Meta: -%.2f Kg CO2.\n", economia);
        economia_total_co2 += economia;
        possui_sugestao = 1;
    }
    
    if (possui_sugestao) {
        float arvores_economizadas = (economia_total_co2 * 12.0) / 7.5;
        printf("--------------------------------------------------\n");
        printf("🌱 IMPACTO DAS METAS: Economia potencial de %.2f Kg CO2/mês.\n", economia_total_co2);
        printf("   Isso evita a necessidade de plantar %.0f árvores por ano!\n", arvores_economizadas);
    } else {
        printf("Parabéns! Suas emissões atuais já estão ótimas. Continue assim!\n");
    }
    printf("==================================================\n");
}

int main() {
    DadosConsumo dados_usuario;
    RelatorioImpacto relatorio_usuario;
    int opcao;

    do {
        printf("\n==================================================\n");
        printf("    CALCULADORA DE PEGADA DE CARBONO COMERCIAL     \n");
        printf("==================================================\n");
        printf("1. Executar Nova Análise\n");
        printf("2. Sair do Programa\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            printf("Opção inválida! Digite um número.\n");
            limpar_buffer();
            continue;
        }
        limpar_buffer();

        switch(opcao) {
            case 1:
                coletar_dados(&dados_usuario);
                limpar_buffer(); 
                calcular_impacto(&dados_usuario, &relatorio_usuario);
                exibir_relatorio(&dados_usuario, &relatorio_usuario);
                salvar_em_arquivo(&dados_usuario, &relatorio_usuario);
                break;
            case 2:
                printf("Encerrando o programa. Obrigado por cuidar do planeta!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while(opcao != 2);

    return 0;
}