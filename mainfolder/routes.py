from flask import render_template, url_for, flash, redirect, request
from mainfolder import app

GRID_SIZE = 8
grid = [[0 for _ in range(GRID_SIZE)] for _ in range(GRID_SIZE)]
lst = []

# make it so that updated border template gets send to the cpp algorithm and an algorithm does it job and correct templates get sends to the web
# step by step.

@app.route('/')
def home():
    return render_template('home.html', title="Home", grid=grid)

@app.route('/toggle', methods=['POST'])
def toggle():
    x = int(request.form['x'])
    y = int(request.form['y'])
    block = f"r{y}c{x}"
    if block in lst:
        lst.remove(block)
    else:
        lst.append(block)

    grid[y][x] = 1 - grid[y][x]
    return redirect(url_for('home'))