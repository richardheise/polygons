#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
from matplotlib.pyplot import figure, savefig, get_cmap
from matplotlib.patches import Patch
from matplotlib.lines import Line2D

def le_poligono(stdin, abscissas, ordenadas, limites):
    ax, ay = [], []
    n = int(stdin.readline())
    for _ in range(n):
        x, y = map(int, stdin.readline().split())
        ax.append(x)
        ay.append(y)
        limites['maxx'] = max(limites['maxx'], x)
        limites['minx'] = min(limites['minx'], x)
        limites['maxy'] = max(limites['maxy'], y)
        limites['miny'] = min(limites['miny'], y)
    ax.append(ax[0])
    ay.append(ay[0])
    abscissas.append(ax)
    ordenadas.append(ay)

def le_entrada(stdin, abscissas, ordenadas, px, py, limites):
    n_poly, n_point = map(int, stdin.readline().split())
    for _ in range(n_poly):
        le_poligono(stdin, abscissas, ordenadas, limites)
    for _ in range(n_point):
        x, y = map(int, stdin.readline().split())
        px.append(x)
        py.append(y)
        limites['maxx'] = max(limites['maxx'], x)
        limites['minx'] = min(limites['minx'], x)
        limites['maxy'] = max(limites['maxy'], y)
        limites['miny'] = min(limites['miny'], y)

def processa_arquivo(entrada_path):
    nome_base = os.path.splitext(os.path.basename(entrada_path))[0]
    with open(entrada_path, 'r') as f:
        abscissas = []
        ordenadas = []
        px = []
        py = []
        limites = {'maxx': -99999, 'maxy': -99999, 'minx': 99999, 'miny': 99999}

        le_entrada(f, abscissas, ordenadas, px, py, limites)

        dx = limites['maxx'] - limites['minx']
        dy = limites['maxy'] - limites['miny']
        e = int(max(dx * 0.1, dy * 0.1)) + 1

        maxx = limites['maxx'] + e
        maxy = limites['maxy'] + e
        minx = limites['minx'] - e
        miny = limites['miny'] - e

        fig = figure(1, figsize=(max(dx / 1.5, 8), max(dy / 1.5, 6)))
        ax = fig.add_subplot(111, autoscale_on=False, xlim=(minx, maxx), ylim=(miny, maxy))

        cmap_polygons = get_cmap('tab20')
        cmap_points = get_cmap('tab10')

        legend_polygons = []
        legend_points = []

        for p in range(len(abscissas)):
            cor = cmap_polygons(p % cmap_polygons.N)
            ax.plot(abscissas[p], ordenadas[p], lw=2, color=cor)
            legend_polygons.append(Patch(facecolor=cor, label=f'Polígono {p+1}'))

        for p in range(len(px)):
            cor = cmap_points(p % cmap_points.N)
            ax.plot(px[p], py[p], 'o', color=cor, markersize=5)
            legend_points.append(Line2D([0], [0], marker='o', color='w',
                                        label=f'Ponto {p+1}', markerfacecolor=cor, markersize=5))

        ax.add_artist(ax.legend(handles=legend_polygons, title="Polígonos",
                                loc='upper left', bbox_to_anchor=(1.01, 1),
                                fontsize=7, title_fontsize=8))
        ax.legend(handles=legend_points, title="Pontos",
                  loc='lower left', bbox_to_anchor=(1.01, 0),
                  fontsize=7, title_fontsize=8)

        os.makedirs("imgs", exist_ok=True)
        savefig(f"imgs/{nome_base}.png", dpi=300, bbox_inches='tight')
        fig.clf()

# --- INÍCIO ---

in_dir = "in"
for arquivo in os.listdir(in_dir):
    if arquivo.endswith(".txt"):
        path = os.path.join(in_dir, arquivo)
        processa_arquivo(path)
