# Arithmetic Set Library (`zbior_ary`)

**Author:** Franciszek Pietrusiak

## Overview

This C library provides a compact and efficient implementation of sets defined as unions of arithmetic progressions with a fixed, positive difference `q`. The primary use case involves operations on such sets, including union, intersection, difference, and cardinality calculations.

## Key Concepts

Sets are represented as arrays of *arithmetic segments* (`trojka`), defined by:
- `poczatek` (start of the segment),
- `koniec` (end of the segment),
- `reszta` (remainder modulo `q`).

Each segment represents an arithmetic progression of the form:  
**{poczatek, poczatek + q, ..., koniec}**  
where all elements have the same modulo `q` value.

## Main Components

### Header File: `zbior_ary.h`

Defines the `zbior_ary` type and exposes the following operations:

- `zbior_ary ciag_arytmetyczny(int a, int q, int b)`  
  Create a set representing an arithmetic progression `{a, a+q, ..., b}`.

- `zbior_ary singleton(int a)`  
  Create a set containing a single element `{a}`.

- `zbior_ary suma(zbior_ary A, zbior_ary B)`  
  Return the union of sets `A` and `B`.

- `zbior_ary iloczyn(zbior_ary A, zbior_ary B)`  
  Return the intersection of sets `A` and `B`.

- `zbior_ary roznica(zbior_ary A, zbior_ary B)`  
  Return the set difference `A \ B`.

- `bool nalezy(zbior_ary A, int b)`  
  Check if element `b` belongs to set `A`.

- `unsigned moc(zbior_ary A)`  
  Return the number of elements in set `A`.

- `unsigned ary(zbior_ary A)`  
  Return the minimal number of disjoint arithmetic progressions of difference `q` needed to represent `A`.

## Implementation Details

- **Memory Management:**  
  All dynamically allocated arrays should be freed manually using `zwolnij_pamiec()`.

- **Performance Considerations:**  
  Internally, sets are stored in a normalized form with disjoint and sorted segments to optimize set operations and membership checks.

- **Assumptions:**  
  - The arithmetic difference `q` is positive and fixed for all operations during a test case.
  - `ciag_arytmetyczny()` must be called before any other function to initialize `q`.