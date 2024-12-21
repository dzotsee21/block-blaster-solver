from flask import render_template, url_for, flash, redirect, request
from src.mainfolder import app
from src.mainfolder.constants import grid, figure1, figure2, figure3, figure_labels, grid_lst, figures_indexes_lst, blast_template, figures_indexes_lst_int, figures_indexes_lst_int_copy, figures_indexes_lst_int_copy2, blast_template_copy, blast_template_copy2, blast_template_copy3, best_template, prev_best_point, blast_template_const
import src.mainfolder.solver as solver
import src.mainfolder.vstr_to_vint as vstr_to_vint



@app.route('/')
def home():
    return render_template('home.html', title="Home", grid=grid, figure1=figure1, figure2=figure2, figure3=figure3)

@app.route('/toggle', methods=['POST'])
def toggle():
    try:
        x = int(request.form['gx'])
        y = int(request.form['gy'])
        block = f"r{x}c{y}"
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
    global blast_template
    global blast_template_const
    global figures_indexes_lst_int
    figures_indexes_lst_int = vstr_to_vint.vstrToVint(figures_indexes_lst)
    for block in grid_lst:
        for r_idx, row in enumerate(blast_template):
            for c_idx, col in enumerate(row):
                if block == col:
                    blast_template[r_idx][c_idx] += 'o'

    print(blast_template)
    print(solver.mainAlgorithm(blast_template, figures_indexes_lst, figures_indexes_lst_int,
                               figures_indexes_lst_int_copy, figures_indexes_lst_int_copy2,
                               blast_template_copy, blast_template_copy2, 
                               blast_template_copy3, best_template,
                               prev_best_point))
    
    blast_template = blast_template_const

    return redirect(url_for('home'))