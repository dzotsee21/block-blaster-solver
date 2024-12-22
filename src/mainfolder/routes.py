from flask import render_template, url_for, flash, redirect, request
from src.mainfolder import app
from src.mainfolder.constants import (grid, figure1, figure2, figure3, figure_labels, grid_lst, figures_indexes_lst, blast_template,
                                      figures_indexes_lst_int, figures_indexes_lst_int_copy, figures_indexes_lst_int_copy2,
                                      blast_template_copy, blast_template_copy2, blast_template_copy3, best_template, prev_best_point,
                                      blast_template_const, figure_const, figures_indexes_lst_const, grid_const, FIGURES_SIZE)
import src.mainfolder.solver as solver
import src.mainfolder.vstr_to_vint as vstr_to_vint

output_grid = [[0 for _ in range(FIGURES_SIZE)] for _ in range(FIGURES_SIZE)]

def restart():
    global grid, figure1, figure2, figure3, figure_labels, grid_lst, figures_indexes_lst, blast_template
    global figures_indexes_lst_int, figures_indexes_lst_int_copy, figures_indexes_lst_int_copy2
    global blast_template_copy, blast_template_copy2, blast_template_copy3, best_template, prev_best_point
    global blast_template_const, figure_const, figures_indexes_lst_const

    GRID_SIZE = 8
    FIGURES_SIZE = 8

    grid = [[0 for _ in range(GRID_SIZE)] for _ in range(GRID_SIZE)]
    figure_const = [[0 for _ in range(FIGURES_SIZE)] for _ in range(FIGURES_SIZE)]
    figure1 = [[0 for _ in range(FIGURES_SIZE)] for _ in range(FIGURES_SIZE)]
    figure2 = [[0 for _ in range(FIGURES_SIZE)] for _ in range(FIGURES_SIZE)]
    figure3 = [[0 for _ in range(FIGURES_SIZE)] for _ in range(FIGURES_SIZE)]

    figure_labels = [['fx0', 'fy0'], ['fx1', 'fy1'], ['fx2', 'fy2']]
    grid_lst = []

    figures_indexes_lst = [[], [], []]
    figures_indexes_lst_int = [[[]],[[]],[[]]]
    figures_indexes_lst_int_copy = [[[]],[[]],[[]]]
    figures_indexes_lst_int_copy2 = [[[]],[[]],[[]]]

    blast_template_copy = [[]]
    blast_template_copy2 = [[]]
    blast_template_copy3 = [[]]
    best_template = [[]]
    prev_best_point = 0

    blast_template = blast_template_const

@app.route('/')
def home():
    global output_grid
    return render_template('home.html', title="Home", grid=grid, figure1=figure1, figure2=figure2, figure3=figure3, best_template=output_grid)


@app.route('/toggle', methods=['POST'])
def toggle():
    try:
        x = int(request.form['gx'])
        y = int(request.form['gy'])
        block = f"r{y}c{x}"
        print(block)
        if block in grid_lst:
            grid_lst.remove(block)
        else:
            grid_lst.append(block)


        grid[y][x] = 1 - grid[y][x]
    except:
        None
    
    for idx, figure_label in enumerate(figure_labels):
        try:
            fx = int(request.form[f'{figure_label[0]}'])
            fy = int(request.form[f'{figure_label[1]}'])
            block = f"r{fy}c{fx}"
            print(block)
            if block in figures_indexes_lst[idx]:
                figures_indexes_lst[idx].remove(block)
            else:
                figures_indexes_lst[idx].append(block)

            if idx == 0:
                figure1[fy][fx] = 1 - figure1[fy][fx]
            elif idx == 1:
                figure2[fy][fx] = 1 - figure2[fy][fx]
            else:
                figure3[fy][fx] = 1 - figure3[fy][fx]
            break
        except:
            continue

    return redirect(url_for('home'))


@app.route('/solve', methods=['POST'])
def solve():
    global output_grid
    global blast_template
    global figure1, figure2, figure3
    global grid
    global grid_lst
    global figures_indexes_lst
    global figures_indexes_lst_int

    figures_indexes_lst_int = vstr_to_vint.vstrToVint(figures_indexes_lst)
    for block in grid_lst:
        for r_idx, row in enumerate(blast_template):
            for c_idx, col in enumerate(row):
                if block == col:
                    blast_template[r_idx][c_idx] += 'o'


    output = solver.mainAlgorithm(blast_template, figures_indexes_lst, figures_indexes_lst_int,
                               figures_indexes_lst_int_copy, figures_indexes_lst_int_copy2,
                               blast_template_copy, blast_template_copy2, 
                               blast_template_copy3, best_template,
                               prev_best_point)
    
    output_grid = [[0 for _ in range(FIGURES_SIZE)] for _ in range(FIGURES_SIZE)]
    for ridx, row in enumerate(output):
        for cidx, col in enumerate(row):
            if "op" in col:
                output_grid[ridx][cidx] = 2
            elif "o" in col:
                output_grid[ridx][cidx] = 1
            else:
                output_grid[ridx][cidx] = 0
    restart()

    return redirect(url_for('home'))