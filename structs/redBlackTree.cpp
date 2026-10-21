#include "redBlackTree.h"
using namespace std;

bool IsRed(TreeNode* root){
    return root != nullptr && root->red;
}

void RotateLeft(TreeNode*& root){
    TreeNode* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    root = newRoot;
}

void RotateRight(TreeNode*& root){
    TreeNode* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    root = newRoot;
}

void Balance(TreeNode*& root){
    if (root == nullptr || IsRed(root)){
        return;
    }
    if (IsRed(root->left) && (IsRed(root->left->left) || IsRed(root->left->right))){
        if (IsRed(root->right)){
            root->left->red = false;
            root->right->red = false;
            root->red = true;
        } else {
            if (IsRed(root->left->right)){
                RotateLeft(root->left);
            }
            RotateRight(root);
            root->red = false;
            root->right->red = true;
        }
    }
    else if (IsRed(root->right) && (IsRed(root->right->left) || IsRed(root->right->right))) {
        if (IsRed(root->left)){
            root->left->red = false;
            root->right->red = false;
            root->red = true;
        } else {
            if (IsRed(root->right->left)){
                RotateRight(root->right);
            }
            RotateLeft(root);
            root->red = false;
            root->left->red = true;
        }
    }
}

void AddRecursion(TreeNode*& root, int value){
    if (value < root->data){
        if (root->left == nullptr){
            root->left = new TreeNode{value, true, nullptr, nullptr};
        }else{
            AddRecursion(root->left, value);
        }
    }else if (value > root->data){
        if (root->right == nullptr){
            root->right = new TreeNode{value, true, nullptr, nullptr};
        }else{
            AddRecursion(root->right, value);
        }
    }else {
        return;
    }
    Balance(root);
}

void AddTree(TreeNode*& root, int value) {
    if (root == nullptr) {
        root = new TreeNode{value, false, nullptr, nullptr};
        return;
    }
    AddRecursion(root, value);
    root->red = false;
}

TreeNode* findMin(TreeNode* root) {
    while (root != nullptr && root->left != nullptr) {
        root = root->left;
    }
    return root;
}


TreeNode* removeTree(TreeNode* root, int value) {
    if (root == nullptr) return nullptr;

    if (value < root->data) {
        root->left = removeTree(root->left, value);
    } else if (value > root->data) {
        root->right = removeTree(root->right, value);
    } else {

        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = removeTree(root->right, temp->data);
    }
    return root;
}

bool searchTree(TreeNode* root, int target) {
    if (root == nullptr) return false;
    if (root->data == target) return true;

    if (target < root->data)
        return searchTree(root->left, target);
    else
        return searchTree(root->right, target);
}

void PrintPreorder(TreeNode* root){
    if (root == nullptr) {return;}
    cout << root->data;
    if (root->red){
        cout << " К ";
    } else {
        cout << " Ч ";
    }
    PrintPreorder(root->left);
    PrintPreorder(root->right);
}

void PrintInorder(TreeNode* root){
    if (root == nullptr) return;
    PrintInorder(root->left);
    cout << root->data;
    if (root->red){
        cout << " К ";
    } else {
        cout << " Ч ";
    }
    PrintInorder(root->right);
}

void PrintPostorder(TreeNode* root){
    if (root == nullptr) return;
    PrintPostorder(root->left);
    PrintPostorder(root->right);
    cout << root->data;
    if (root->red){
        cout << " К ";
    } else {
        cout << " Ч ";
    }
}

void PrintTree(TreeNode* root) {
    if (root == nullptr) {
        cout << "Дерево пусто." << endl;
        return;
    }
    cout << "Прямой обход: ";
    PrintPreorder(root); 
    cout << endl;
    cout << "Симметричный обход: ";
    PrintInorder(root); 
    cout << endl;
    cout << "Обратный обход: ";
    PrintPostorder(root); 
    cout << endl;
}