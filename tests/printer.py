#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import sys
import os
from matplotlib.pyplot import figure, savefig, get_cmap
from matplotlib.patches import Patch
from matplotlib.lines import Line2D

def le_poligono(p=0):
    global abscissas, ordenadas, maxx, maxy, minx, miny
    ax = []
    ay = []
    n = int(stdin.readline())
    for _ in range(n):
        a = stdin.readline().split()
        x = int(a[0])
        y = int(a[1])
        ax.append(x)
        ay.append(y)
        maxx = max(maxx, x)
        minx = min(minx, x)
        maxy = max(maxy, y)
        miny = min(miny, y)
    ax.append(ax[0])
    ay.append(ay[0])
    abscissas.append(ax)
    ordenadas.append(ay)

def le_entrada():
    global n_poly, n_point, px, py, maxx, maxy, minx, miny
    a = stdin.readline().split()
    n_poly = int(a[0])
    n_point = int(a[1])
    for p in range(n_poly):
        le_poligono(p)
    for _ in range(n_point):
        a = stdin.readline().split()
        x = int(a[0])
        y = int(a[1])
        px.append(x)
        py.append(y)
        maxx = max(maxx, x)
        minx = min(minx, x)
        maxy = max(maxy, y)
        miny = min(miny, y)

# --- INÍCIO DO SCRIPT ---

if len(sys.argv) != 2:
    print("Uso: python3 script.py <arquivo_entrada>")
    sys.exit(1)

entrada_path = sys.argv[1]
nome_base = os.path.splitext(os.path.basename(entrada_path))[0]

with open(entrada_path, 'r') as f:
    stdin = f
    abscissas = []
    ordenadas = []
    px = []
    py = []
    maxx = -99999
    maxy = -99999
    minx = 99999
    miny = 99999

    le_entrada()
    dx = maxx - minx
    dy = maxy - miny
    ex = dx * 0.1
    ey = dy * 0.1
    e = int(max(ex, ey)) + 1

    dx += 2 * e
    dy += 2 * e
    maxx += e
    maxy += e
    minx -= e
    miny -= e

    # Aumenta o tamanho da figura
    fig = figure(1, figsize=(max(dx / 1.5, 8), max(dy / 1.5, 6)))
    ax = fig.add_subplot(111, autoscale_on=False, xlim=(minx, maxx), ylim=(miny, maxy))

    cmap_polygons = get_cmap('tab20')
    cmap_points = get_cmap('tab10')

    legend_polygons = []
    legend_points = []

    # Desenha os polígonos
    for p in range(len(abscissas)):
        cor = cmap_polygons(p % cmap_polygons.N)
        ax.plot(abscissas[p], ordenadas[p], lw=2, color=cor)
        legend_polygons.append(Patch(facecolor=cor, label=f'Polígono {p}'))

    # Desenha os pontos
    for p in range(len(px)):
        cor = cmap_points(p % cmap_points.N)
        ax.plot(px[p], py[p], 'o', color=cor, markersize=5)
        legend_points.append(Line2D([0], [0], marker='o', color='w', label=f'Ponto {p}',
                                    markerfacecolor=cor, markersize=5))

    # Adiciona as duas legendas afastadas
    ax.add_artist(ax.legend(handles=legend_polygons, title="Polígonos",
                            loc='upper left', bbox_to_anchor=(1.01, 1),
                            fontsize=7, title_fontsize=8))
    ax.legend(handles=legend_points, title="Pontos",
              loc='lower left', bbox_to_anchor=(1.01, 0),
              fontsize=7, title_fontsize=8)

    os.makedirs("imgs", exist_ok=True)
    savefig(f"imgs/{nome_base}.png", dpi=300, bbox_inches='tight')
