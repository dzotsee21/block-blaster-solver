from flask import render_template, url_for, flash, redirect, request
from mainfolder import app
from mainfolder.constants import grid, figure1, figure2, figure3, figure_labels, grid_lst, figures_indexes_lst, blast_template


# make it so that when pressing "SOLVE" button cpp algorithm runs and nice, detailed step-by-step grid gets outputed.

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

        print(grid_lst)

        grid[y][x] = 1 - grid[y][x]
    except:
        None
    
    for idx, figure_label in enumerate(figure_labels):
        try:
            fx = int(request.form[f'{figure_label[0]}'])
            fy = int(request.form[f'{figure_label[1]}'])
            block = f"r{fx}c{fy}"
            if block in figures_indexes_lst[idx]:
                figures_indexes_lst[idx].remove(block)
            else:
                figures_indexes_lst[idx].append(block)
            print(figures_indexes_lst[idx])
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
    for block in grid_lst:
        for r_idx, row in enumerate(blast_template):
            for c_idx, col in enumerate(row):
                if block == col:
                    blast_template[r_idx][c_idx] += 'o'

    print(blast_template)

    return redirect(url_for('home'))