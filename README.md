OBS: O codigo possui duas versões uma com terminal interativo em C, e uma versão web em html mostrando como seria o site.

# 🌱 Eco Metric - Calculadora de Pegada de Carbono

O **Eco Metric** é um ecossistema focado em sustentabilidade e práticas ESG (*Environmental, Social, and Governance*), projetado para ajudar empresas e indivíduos a monitorar, calcular e reduzir sua pegada de carbono mensal. 

O repositório é composto por duas versões complementares da ferramenta:
1. **Versão CLI (C):** Uma aplicação robusta de terminal focada em análise detalhada, com persistência de dados em arquivo texto e métrica adicional de consumo hídrico.
2. **Versão Web (HTML):** Uma interface gráfica moderna, intuitiva e responsiva para cálculos rápidos e geração visual de relatórios ambientais.

---

## 🚀 Funcionalidades

### 💻 Aplicação em C (Terminal)
* **Entradas detalhadas:** Coleta dados de Eletricidade (kWh), Gás de Cozinha (Kg), Gasolina (L), Diesel (L), Plástico de uso único (Kg), Papel/Papelão (Kg) e Água Encanada (Litros).
* **Validação de dados:** Mecanismo contra entradas inválidas ou valores negativos.
* **Persistência de Histórico:** Cria e alimenta automaticamente um arquivo `historico_sustentabilidade.txt` para auditorias e registros futuros.
* **Plano de Metas Dinâmico:** Gera sugestões quantitativas de economia de $CO_2$ com base no nível de consumo inserido.

### 🌐 Aplicação Web (HTML/JS)
* **Design Responsivo:** Interface limpa e adaptável para dispositivos móveis e desktops baseada na identidade visual ESG.
* **KPIs em Tempo Real:** Exibição clara do total de $CO_2$ emitido (em kg e toneladas) e a quantidade necessária de árvores para compensação.
* **Geração de Relatório Visual:** Detalhamento em lista e recomendações práticas de mitigação ecológica acionadas por algoritmos em JavaScript.

---

## 📊 Fatores de Emissão Utilizados

Os cálculos utilizam coeficientes de conversão para transformar consumo em impacto ambiental ($Kg\ de\ CO_2$ por unidade):

| Recurso | Unidade | Fator de Emissão |
| :--- | :---: | :---: |
| ⚡ Eletricidade | kWh | 0.13 |
| 🔥 Gás de Cozinha (GLP) | Kg | 2.98 |
| ⛽ Gasolina | Litro | 2.31 |
| 🚛 Diesel | Litro | 2.68 |
| 🧴 Plástico Virgem | Kg | 2.00 |
| 📦 Papel / Papelão | Kg | 0.90 |
| 💧 Água Encanada * | Litro | 0.0003 |

*\*Métrica exclusiva da versão em C.*

> 📋 **Fórmula de Compensação:** O cálculo de árvores baseia-se na estimativa de que uma árvore nativa absorve aproximadamente 7.5 Kg de $CO_2$ por ano na sua fase de crescimento. O sistema calcula o impacto anual projetado $\text{Total Mensal} \times 12$ para determinar a cota de plantio necessária.

---

## 🛠️ Como Executar os Projetos

### 1. Versão Web (HTML)
Não requer instalação de dependências ou servidores.
1. Navegue até a pasta do projeto.
2. Abra o arquivo pelo live server`.html` (ex: `index.html`) diretamente em qualquer navegador moderno (Chrome, Edge, Firefox, Safari).

### 2. Versão CLI (C)
Requer um compilador C (como o `gcc`) instalado no sistema.

**Passo 1: Compilar o código**
Abra o terminal na pasta do arquivo e execute:
```bash
gcc -o ecometric calculadora.c
