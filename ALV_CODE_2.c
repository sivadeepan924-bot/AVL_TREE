/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

int height(struct Node *n) {
    if (n == NULL)
        return 0;
    return n->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct Node* createNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct Node* rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

struct Node* leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

int getBalance(struct Node *node) {
    if (node == NULL)
        return 0;

    return height(node->left) - height(node->right);
}

struct Node* insert(struct Node *node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Left Left
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

int search(struct Node *root, int key) {
    if (root == NULL)
        return 0;

    if (root->key == key)
        return 1;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

int main() {
    struct Node *root = NULL;
    int key, k;

    while (scanf("%d", &key) == 1 && key != -1) {
        root = insert(root, key);
    }

    scanf("%d", &k);

    if (search(root, k))
        printf("Key %d found in the AVL tree.", k);
    else
        printf("Key %d not found in the AVL tree.", k);

    return 0;
}