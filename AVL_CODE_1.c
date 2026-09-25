/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int key;
    char code[32];
    int height;
    struct Node *left;
    struct Node *right;
} Node;

int height(Node *n) {
    return n ? n->height : 0;
}

int max(int a, int b) {
    return a > b ? a : b;
}

Node* createNode(int key, char *code) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->key = key;
    strcpy(node->code, code);
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *t = x->right;

    x->right = y;
    y->left = t;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

int getBalance(Node *node) {
    return node ? height(node->left) - height(node->right) : 0;
}

Node* insert(Node *node, int key, char *code) {
    if (node == NULL)
        return createNode(key, code);

    if (key < node->key)
        node->left = insert(node->left, key, code);
    else if (key > node->key)
        node->right = insert(node->right, key, code);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* deleteMin(Node *root) {
    if (root == NULL)
        return NULL;

    if (root->left == NULL) {
        Node *temp = root->right;
        free(root);
        return temp;
    }

    root->left = deleteMin(root->left);

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d %s\n", root->key, root->code);
        inorder(root->right);
    }
}

void freeTree(Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    Node *root = NULL;
    int n, key;
    char code[32];

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %31s", &key, code);
        root = insert(root, key, code);
    }

    printf("In-order traversal before deletion:\n");
    inorder(root);

    root = deleteMin(root);

    printf("In-order traversal after deletion:\n");
    inorder(root);

    freeTree(root);

    return 0;
}