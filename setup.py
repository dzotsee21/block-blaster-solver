from setuptools import setup, Extension
from pybind11.setup_helpers import Pybind11Extension

ext_modules = [
    Pybind11Extension("vstr_to_vint", ["src/blast_solver/solver.cpp"]),
]

setup(
    name="vstr_to_vint",
    ext_modules=ext_modules,
    zip_safe=False,
)