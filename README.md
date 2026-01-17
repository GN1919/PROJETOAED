# SGDE - Sistema de Gestão de Dados Eleitorais 

Este é um sistema desenvolvido em C para o gerenciamento e organização de processos eleitorais, permitindo o controle rigoroso de Comitês de Apoio (CAPs) e Eleitores.

## 🚀 Sobre o Projeto (Fase Inicial)

O projeto está em sua fase inicial de desenvolvimento, focando na integridade dos dados e na associação lógica entre eleitores e seus respectivos comitês. 

### Regra Principal:
O sistema garante a consistência da base de dados: um eleitor **só pode ser cadastrado** se for associado a uma CAP (Comitê de Apoio) previamente existente no sistema.

## ✨ Funcionalidades

- **Gestão de CAPs:**
  - Cadastro de novos Caps.
  - Listagem completa de CAPs cadastradas.
  - Visualização de filas das CAPs.
- **Gestão de Eleitores:**
  - Cadastro de eleitores com validação de vínculo.
  - Busca detalhada de eleitores.
  - Listagem geral de eleitores registrados.
- **Associação Lógica:**
  - Vinculação de eleitores a CAPs específicas.
  - Verificação de existência de CAP antes do cadastro de eleitor.

## 📂 Estrutura do Projeto

O projeto é modularizado para facilitar a manutenção e escalabilidade:

*   `cap.h` / `cap.c`: Definições e implementações das funções relacionadas aos Comitês de Apoio.
*   `eleitor.h` / `eleitor.c`: Definições e implementações das funções relacionadas aos Eleitores e validações.
*   `sgde.c`: Arquivo principal que contém o menu e a lógica central do sistema.

## 🛠️ Como Compilar e Executar

Para rodar este projeto em sua máquina, você precisará de um compilador C (como o GCC) instalado.

1. Abra o cmd na pasta do projeto.
2. Utilize o seguinte comando para compilar:
   
   gcc sgde.c eleitor.c cap.c -o sgde.exe
