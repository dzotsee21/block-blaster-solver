from flask import render_template, url_for, flash, redirect, request
from mainfolder import app

GRID_SIZE = 8
FIGURES_SIZE = 8
grid = [[0 for _ in range(GRID_SIZE)] for _ in range(GRID_SIZE)]
figure1 = [[0 for _ in range(FIGURES_SIZE)] for _ in range(FIGURES_SIZE)]
figure2 = [[0 for _ in range(FIGURES_SIZE)] for _ in range(FIGURES_SIZE)]
figure3 = [[0 for _ in range(FIGURES_SIZE)] for _ in range(FIGURES_SIZE)]

figure_labels = [['fx0', 'fy0'], ['fx1', 'fy1'], ['fx2', 'fy2']]
grid_lst = []
figures_indexes_lst = [[],[],[]]

# make it so that updated border template gets send to the cpp algorithm and an algorithm does it job and correct templates get sends to the web
# step by step.

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