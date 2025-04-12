#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import subprocess
import os
from pathlib import Path

# Caminhos base
ROOT_DIR = Path(__file__).resolve().parents[1]  # polygons/
IN_DIR = ROOT_DIR / "tests" / "in"
OUT_DIR = ROOT_DIR / "tests" / "out"
EXECUTABLE = ROOT_DIR / "polygons"

# 1. Executa make em polygons/
print("🔧 Executando make em", ROOT_DIR)
make_proc = subprocess.run(["make"], cwd=ROOT_DIR, capture_output=True, text=True)

if make_proc.returncode != 0:
    print("❌ Erro ao executar make:")
    print(make_proc.stderr)
    exit(1)
else:
    print("✅ Make concluído com sucesso")

# 2. Garante que a pasta de saída exista
OUT_DIR.mkdir(parents=True, exist_ok=True)

# 3. Processa todos os arquivos *.txt em polygons/test/in/
for entrada_path in IN_DIR.glob("*.txt"):
    print(entrada_path)
    nome_base = entrada_path.stem
    saida_path = OUT_DIR / f"{nome_base}.txt"

    print(f"🚀 Executando teste: {entrada_path.name}")

    with open(entrada_path, "r") as infile, open(saida_path, "w") as outfile:
        proc = subprocess.run([str(EXECUTABLE)], stdin=infile, stdout=outfile)

    if proc.returncode != 0:
        print(f"⚠️ Erro ao processar {entrada_path.name}")
    else:
        print(f"✅ Saída salva em {saida_path.name}")
