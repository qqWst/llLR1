#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include <iostream>

struct TreeNode{
    int data;
    bool red = true;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;
};

void AddTree(TreeNode*& root, int value);
TreeNode* removeTree(TreeNode* root, int value);
bool searchTree(TreeNode* root, int target);
void PrintTree(TreeNode* root);

#endif