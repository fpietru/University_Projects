/*
    Author: Franciszek Pietrusiak
    Code Review: Hubert Fafara    
*/
#include <bits/stdc++.h>
#include "prev.h"
using namespace std;
using ll = long long;

struct Node {
    shared_ptr<Node> left, right;
    int val;
    Node(int x) : left(nullptr), right(nullptr), val(x) {}
    ~Node() = default;
};

/**
 * @brief Create new tree rooted at v1 using tree rooted at v2.
 * 
 * @param v1 root of new tree
 * @param v2 root of already existing tree we want to update
 *           If v2 == nullptr then v1 is created from scratch
 * @param L, R range that node v1 is responsible for
 * @param pos position that we want to update
 * @param x value to set in desired position
*/
void update(shared_ptr<Node> v1, shared_ptr<Node> v2, ll L, ll R, ll pos, int x) {
    if (L == R) {
        assert(v1);
        v1->val = x;
        return;
    }
    ll M = (L + R) / 2;
    if (pos <= M) {
        if (!v1->left) v1->left = make_shared<Node>(-1);
        if (v2) v1->right = v2->right;
        shared_ptr<Node> v2_next = (v2 ? v2->left : nullptr);
        update(v1->left, v2_next, L, M, pos, x);
    } else {
        if (!v1->right) v1->right = make_shared<Node>(-1);
        if (v2) v1->left = v2->left;
        shared_ptr<Node> v2_next = (v2 ? v2->right : nullptr);
        update(v1->right, v2_next, M+1, R, pos, x);
    }
    if (v1->left) v1->val = max(v1->val, v1->left->val);
    if (v1->right) v1->val = max(v1->val, v1->right->val);
}


/**
 * @brief Find maximum in range [st, ed]: max{x_i : st <= i <= ed}.
 * 
 * @param v pointer to the node in segment tree
 * @param L, R range that node v is responsible for
 * @param st, ed range that we are interested in
*/
int query(shared_ptr<Node> v, ll L, ll R, ll st, ll ed) {
    if (!v || R < st || ed < L) return -1;
    if (st <= L && R <= ed) {
        return v->val;
    }
    ll M = (L + R) / 2;
    int l_son = query(v->left, L, M, st, ed);
    int r_son = query(v->right, M+1, R, st, ed);
    return max(l_son, r_son);
}

vector<shared_ptr<Node>> roots;
int global_N; // number of leafs in all trees
// maximum range of values in trees
ll global_L = 0;
ll global_R = 1LL*INT_MAX-INT_MIN;

/**
 * @brief Translate x by -INT_MIN.
 *        Translation is used in order to have only
 *        non-negative positions in trees.
*/
ll translate(int x) {
    return 1LL * x - INT_MIN;
}

/**
 * @brief Add new value at the end of sequence of integers. 
*/
void pushBack(int value) {
    shared_ptr<Node> root = make_shared<Node>(-1);
    shared_ptr<Node> prev = (global_N == 0 ? nullptr : roots[global_N-1]);
    update(root, prev, global_L, global_R, translate(value), global_N++);
    roots.push_back(root);
}

/**
 * @brief Initialize trees with sequence of integers,
 *        k-th tree stores k first elements of seq, k>=1.
*/
void init(const std::vector<int> &seq) {
    for (int val : seq) {
        pushBack(val);
    }
}

/** 
 * @brief Find max{j : 0 <= j <= i && lo <= seq[j] <= hi}
 *        or else return -1.
*/
int prevInRange(int i, int lo, int hi) {
    int j = min(i, global_N-1); // if there are less roots than i take the last one
    if (j < 0) return -1; // if there are no trees 
    return query(roots[j], global_L, global_R, translate(lo), translate(hi));
}

/**
 * @brief Free memory.
*/
void done() {
    roots.clear();
}