#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "Tenant.h"

class AVLTree {
public:
    // Constructor
    AVLTree();

    // Destructor
    ~AVLTree();

    // Insert a tenant into the AVL tree
    void insert(Tenant tenant);

    // In-order traversal of the AVL tree
    void inorder() const;

    // Search for a tenant by ID
    Tenant* search(int tenantID) const;

private:
    // Helper struct to represent a node in the AVL tree
    struct Node {
        Tenant data;
        Node* left;
        Node* right;
        int height;

        Node(Tenant tenant) : data(tenant), left(nullptr), right(nullptr), height(1) {}
    };

    // Pointer to the root of the tree
    Node* root;

    // Helper methods for AVL tree operations
    int height(Node* node) const;
    int getBalance(Node* node) const;
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* insert(Node* root, Tenant tenant);
    void inorder(Node* root) const;
    Node* search(Node* root, int tenantID) const;
    void destroyTree(Node* node);
};

#endif // AVL_TREE_H
