# SGIM - Sistema de Gestão de Inventário de Medicamentos

## 📌 Visão Geral
O SGIM (Sistema de Gestão de Inventário de Medicamentos) é um protótipo desenvolvido como estudo de caso para a Unidade Didática IV da disciplina de Manipulação de Arquivos Sequenciais e Indexados, no curso de Análise e Desenvolvimento de Sistemas (ADS).

O projeto demonstra, de forma prática, como melhorar significativamente o desempenho de buscas em arquivos utilizando indexação.

---

## 🏥 Problema
Um hospital local enfrenta dificuldades para localizar medicamentos rapidamente em um banco de dados baseado em arquivo sequencial (texto simples).  

À medida que o volume de registros cresce, o tempo de busca aumenta linearmente, impactando diretamente a eficiência no atendimento ao paciente.

---

## 💡 Solução
O SGIM resolve esse problema adotando uma abordagem híbrida:

- Mantém os dados em um **arquivo sequencial** (`medicamentos.dat`)
- Utiliza um **arquivo de índice** (`indices.idx`) para acesso direto

Isso permite:
- Inserção simples e eficiente (append)
- Busca rápida baseada em ID

---

## 🛠️ Tecnologias e Conceitos

- **Linguagem C**
- **Manipulação de Arquivos**
  - `fopen`, `fclose`
  - `fwrite`, `fread`
- **Arquivos Sequenciais**
  - Registros armazenados em sequência
- **Arquivos Indexados**
  - Estrutura `{ID, posição}`
- **Ponteiros de Arquivo**
  - `fseek()` → movimentação no arquivo
  - `ftell()` → obtenção da posição atual

---

## 🚀 Funcionalidades

### ✔️ Cadastrar Medicamento
Armazena:
- ID
- Nome
- Dosagem
- Fabricante

Os dados são inseridos no final do arquivo (`append`).

---

### ✔️ Gerar Índice
Cria ou atualiza o arquivo `indices.idx`, contendo:
