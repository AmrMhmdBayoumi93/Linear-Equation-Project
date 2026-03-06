# 🧮 Linear Equation Solver — C++ Project

> A command-line C++ application that parses, simplifies, and solves systems of linear equations using **Cramer's Rule**.

[![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue?style=flat-square&logo=cplusplus)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey?style=flat-square)]()
[![Status](https://img.shields.io/badge/Status-Completed-brightgreen?style=flat-square)]()

---

## 📑 Table of Contents

- [About](#-about)
- [Features](#-features)
- [Project Structure](#-project-structure)
- [Requirements](#-requirements)
- [How to Compile](#-how-to-compile)
- [How to Run](#-how-to-run)
- [Input Format](#-input-format)
- [Commands](#-commands)
- [Example Session](#-example-session)
- [Team Members](#-team-members)
- [License](#-license)

---

## 📖 About

This project implements a **Linear Equation Solver** in C++ as part of a university programming course. It reads a system of `n` linear equations from standard input, processes them, and supports interactive commands to display the coefficient matrix, compute its determinant, and solve the system.

The solver uses **Cramer's Rule** and supports up to **10 variables**.

---

## ✨ Features

- ✅ Parses linear equations from plain text (e.g. `3x1+2x2-x3=10`)
- ✅ Combines like terms and sorts variables alphabetically
- ✅ Builds the coefficient matrix automatically
- ✅ Computes determinant using recursive cofactor expansion
- ✅ Solves n-variable systems using Cramer's Rule
- ✅ Interactive command loop (`D`, `D_value`, `solve`, `quit`)
- ✅ Handles negative coefficients, coefficient of ±1, and constant terms

---

## 📁 Project Structure

```
Linear-Equation-Project/
│
├── LinearEquationProject/
│   └── main.cpp          # All source code (Term, Equation, Solver classes)
│
├── LinearEquationProject.slnx   # Visual Studio solution file
├── x64/Debug/                   # Compiled output (auto-generated)
└── README.md
```

---

## ⚙️ Requirements

| Tool | Version |
|------|---------|
| C++ Compiler | g++ / clang++ / MSVC (C++11 or later) |
| OS | Windows / Linux / macOS |
| IDE (optional) | Visual Studio 2022, VS Code, CLion |

---

## 🔨 How to Compile

### Using g++ (Linux / macOS / Windows with MinGW)

```bash
g++ -o solver LinearEquationProject/main.cpp -std=c++11
```

### Using Visual Studio (Windows)

1. Open `LinearEquationProject.slnx` in Visual Studio 2022
2. Press `Ctrl + Shift + B` to build
3. Run with `Ctrl + F5`

---

## ▶️ How to Run

```bash
# Linux / macOS
./solver

# Windows
solver.exe
```

Then type your input directly in the terminal (see format below).

---

## 📥 Input Format

1. First line: a single integer `n` — the number of equations
2. Next `n` lines: one equation per line, **no spaces**, in the form:

```
[terms]=[rhs]
```

**Valid equation examples:**
```
3x1+2x2-x3=10
x1-x2=5
-2x1+3x2+x3=0
```

> ⚠️ Variables must be alphanumeric strings (e.g. `x1`, `x2`, `y`, `a`).  
> ⚠️ Coefficients of `1` and `-1` can be written as `x1` or `-x1`.

---

## 💻 Commands

After entering all equations, type any of the following commands:

| Command | Description |
|---------|-------------|
| `D` | Print the **coefficient matrix** (n × n) |
| `D xi` | Print the matrix with column `xi` **replaced by the RHS vector** (used in Cramer's Rule) |
| `D_value` | Print the **determinant** of the coefficient matrix |
| `solve` | **Solve** the system and print each variable's value |
| `quit` | **Exit** the program |

---

## 🖥️ Example Session

```
Input:
3
3x1+2x2-x3=10
x1-x2+2x3=3
2x1+x2+x3=9

Commands and Output:

D
3 2 -1
1 -1 2
2 1 1

D_value
-10

solve
x1=2
x2=1
x3=3

quit
```

---

## 👥 Team Members

**Group 3 — Lab 7**

| # | Name | ID | Role |
|---|------|----|------|
| 1 | عمرو محمد بيومي سيد احمد | 11165 | `updateVarList()`, `getCoeffMatrix()`, `getCoeff()`, `determinant()`, `execute()` |
| 2 | أحمد السيد مصيلحي قطب | 11164 | `updateVarList()` (co-author), `addEq()`, `subEq()`, `substituteVar()` |
| 3 | ميار امام محمد متولي | 12254 | `parseTerm()`, `readEquations()` |
| 4 | سارة عبد السميع احمد | 12257 | `simplify()`, `toString()` |

---

## 📄 License

This project is submitted as a university academic project.  
All rights reserved © 2025 — Group 3, Lab 7.
