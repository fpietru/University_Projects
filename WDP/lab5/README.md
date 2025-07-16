# Origami-like paper folding problem

This C program simulates the folding of paper and determines how many layers of a folded sheet are pierced by a pin at a given point.

## Overview

Each sheet can be:

- A **rectangle** (`'P'`): defined by two corner points.
- A **circle** (`'K'`): defined by its center and radius.
- A **folded sheet** (`'Z'`): created by folding a previous sheet along a line.

The goal is to compute how many paper layers are pierced when a pin is inserted at a point on a (possibly folded) sheet.

## Input Format

1. Number of sheets `n` and number of queries `q`.
2. Description of each sheet:
   - `'P' x1 y1 x2 y2` — rectangle from `(x1, y1)` to `(x2, y2)`
   - `'K' x y r` — circle centered at `(x, y)` with radius `r`
   - `'Z' k x1 y1 x2 y2` — fold sheet `k` along the line through `(x1, y1)` and `(x2, y2)`
3. `q` queries of the form:
   - `k x y` — how many layers are pierced on sheet `k` at point `(x, y)`

## How It Works

- For geometric primitives, the code checks whether the point lies inside the shape.
- For folded sheets, it recursively simulates the folding and reflects the point if necessary.
- The number of layers at a point is determined by recursively traversing the fold history.
