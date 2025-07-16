# Queue Management System

This C++ project implements a queue management system for a fictional government office ("urząd"). It simulates operations on multiple queues (one per service window) and models the behavior of clients ("interesanci") arriving, being served, switching queues, or being fast-tracked.

## Features

- **Initialization**: Open an office with `n` service windows. **`O(n)`**
- **Client Handling**:
  - Add new clients to a queue. **`O(1)`**
  - Serve the first client in a queue. **`O(1)`**
  - Move a client to a different queue. **`O(1)`**
  - Fast-track a range of `k` clients for immediate service. **`O(k)`**
- **Queue Operations**:
  - Reverse the order of a queue. **`O(1)`**
  - Merge two queues. **`O(1)`**
  - Transfer `k` clients between queues when a window closes. **`O(k)`**
- **Shutdown**: Close the office and retrieve all remaining `k` clients in order. **`O(k)`**

## Key Structures

- `interesant`: Represents a single client with unique number and pointers to neighbors.
- `Okienko`: Internal representation of a service window queue using double-linked list
