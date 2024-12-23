from flask import render_template, url_for, flash, redirect, request
from src.mainfolder import app
from src.mainfolder.constants import (grid, figure1, figure2, figure3, figure_labels, grid_lst, figures_indexes_lst, blast_template,
                                      figures_indexes_lst_int, figures_indexes_lst_int_copy, figures_indexes_lst_int_copy2,
                                      blast_template_copy, blast_template_copy2, blast_template_copy3, best_template, prev_best_point,
                                      output_grid, FIGURES_SIZE, GRID_SIZE)
import src.mainfolder.cppfuncs.solver as solver
import src.mainfolder.cppfuncs.vstr_to_vint as vstr_to_vint

clear_needed = False

@app.route('/')
def home():
    global clear_needed
    return render_template('home.html', title="Home", grid=grid, figure1=figure1, figure2=figure2, figure3=figure3, best_template=output_grid, clear_needed=clear_needed)


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
    global clear_needed
    clear_needed = True
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
    
    for ridx, row in enumerate(output):
        for cidx, col in enumerate(row):
            if "op" in col:
                output_grid[ridx][cidx] = 2
            elif "o" in col:
                output_grid[ridx][cidx] = 1
            else:
                output_grid[ridx][cidx] = 0


    return redirect(url_for('home'))


@app.route('/clear', methods=['POST'])
def clear():
    global clear_needed
    global grid, figure1, figure2, figure3, grid_lst, figures_indexes_lst, figures_indexes_lst_int, figures_indexes_lst_int_copy, figures_indexes_lst_int_copy2
    global blast_template_copy, blast_template_copy2, blast_template_copy3, best_template, output_grid, prev_best_point, blast_template

    clear_needed = False

    grid = [[0 for _ in range(GRID_SIZE)] for _ in range(GRID_SIZE)]
    figure1 = [[0 for _ in range(FIGURES_SIZE)] for _ in range(FIGURES_SIZE)]
    figure2 = [[0 for _ in range(FIGURES_SIZE)] for _ in range(FIGURES_SIZE)]
    figure3 = [[0 for _ in range(FIGURES_SIZE)] for _ in range(FIGURES_SIZE)]

    grid_lst = []
    figures_indexes_lst = [[], [], []]
    figures_indexes_lst_int = [[[]],[[]],[[]]]
    figures_indexes_lst_int_copy = [[[]],[[]],[[]]]
    figures_indexes_lst_int_copy2 = [[[]],[[]],[[]]]
    blast_template_copy = [[]]
    blast_template_copy2 = [[]]
    blast_template_copy3 = [[]]
    best_template = [[]]
    output_grid = [[0 for _ in range(FIGURES_SIZE)] for _ in range(FIGURES_SIZE)]
    prev_best_point = 0

    blast_template = [
        ["r0c0", "r0c1", "r0c2", "r0c3", "r0c4", "r0c5", "r0c6", "r0c7"],
        ["r1c0", "r1c1", "r1c2", "r1c3", "r1c4", "r1c5", "r1c6", "r1c7"],
        ["r2c0", "r2c1", "r2c2", "r2c3", "r2c4", "r2c5", "r2c6", "r2c7"],
        ["r3c0", "r3c1", "r3c2", "r3c3", "r3c4", "r3c5", "r3c6", "r3c7"],
        ["r4c0", "r4c1", "r4c2", "r4c3", "r4c4", "r4c5", "r4c6", "r4c7"],
        ["r5c0", "r5c1", "r5c2", "r5c3", "r5c4", "r5c5", "r5c6", "r5c7"],
        ["r6c0", "r6c1", "r6c2", "r6c3", "r6c4", "r6c5", "r6c6", "r6c7"],
        ["r7c0", "r7c1", "r7c2", "r7c3", "r7c4", "r7c5", "r7c6", "r7c7"]
    ]
    return redirect(url_for('home'))