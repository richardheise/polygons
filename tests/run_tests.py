#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import subprocess
import os
from pathlib import Path

# Caminhos base
ROOT_DIR = Path(__file__).resolve().parents[1]  # Diretório principal (polygons/)
IN_DIR = ROOT_DIR / "tests" / "in"  # Diretório de entrada com os arquivos de teste
OUT_DIR = ROOT_DIR / "tests" / "out"  # Diretório de saída para armazenar resultados
ANSWERS_DIR = ROOT_DIR / "tests" / "answers"  # Diretório com os arquivos esperados de resposta
EXECUTABLE = ROOT_DIR / "poligonos"  # Caminho para o executável do programa

# 1. Executa make clean antes de make em polygons/
print("Executando make clean em", ROOT_DIR)
make_clean_proc = subprocess.run(["make", "clean"], cwd=ROOT_DIR, capture_output=True, text=True)

# Verifica se o comando make clean foi bem-sucedido
if make_clean_proc.returncode != 0:
    print("Erro ao executar make clean:")
    print(make_clean_proc.stderr)
    exit(1)
else:
    print("Make clean concluído com sucesso\n")  # Adiciona uma quebra de linha

# 2. Executa make
print("Executando make em", ROOT_DIR)
make_proc = subprocess.run(["make"], cwd=ROOT_DIR, capture_output=True, text=True)

# Verifica se o comando make foi bem-sucedido
if make_proc.returncode != 0:
    print("Erro ao executar make:")
    print(make_proc.stderr)
    exit(1)
else:
    print("Make concluído com sucesso\n")  # Adiciona uma quebra de linha

# 3. Garante que a pasta de saída exista
OUT_DIR.mkdir(parents=True, exist_ok=True)  # Cria o diretório de saída, se não existir

print(f"------------Começando a execução dos testes---------\n")

# 4. Processa todos os arquivos *.txt em polygons/test/in/
for entrada_path in IN_DIR.glob("*.txt"):
    print(f"Executando teste: {entrada_path.name}")
    nome_base = entrada_path.stem  # Extrai o nome base do arquivo (sem extensão)
    saida_path = OUT_DIR / f"{nome_base}.txt"  # Define o caminho de saída para o arquivo
    expected_path = ANSWERS_DIR / f"{nome_base}.txt"  # Define o caminho do arquivo esperado

    # Processa o arquivo de entrada
    with open(entrada_path, "r") as infile, open(saida_path, "w") as outfile:
        proc = subprocess.run([str(EXECUTABLE)], stdin=infile, stdout=outfile)

    # Verifica se o processamento foi bem-sucedido
    if proc.returncode != 0:
        print(f"Erro ao processar {entrada_path.name}")
    else:
        print(f"Saída salva em {saida_path.name}\n")  # Adiciona uma quebra de linha após salvar a saída

        # 5. Compara a saída com o arquivo esperado
        if expected_path.exists():
            print(f"Comparando saída com {expected_path.name}")
            diff_proc = subprocess.run(
                ["diff", "-u", str(expected_path), str(saida_path)],  # Comando diff para comparar arquivos
                capture_output=True,
                text=True
            )

            # Verifica se há diferenças entre os arquivos
            if diff_proc.returncode == 0:
                print(f"As saídas são idênticas: {saida_path.name}\n")  # Se não houver diferenças, imprime que são idênticas
                print(f"-------------------------------------------------\n")
            else:
                print(f"Diferenças encontradas em {saida_path.name}:")
                print(diff_proc.stdout)  # Imprime as diferenças encontradas
        else:
            print(f"Arquivo de resposta esperado não encontrado: {expected_path.name}\n")  # Se o arquivo de resposta não existir
