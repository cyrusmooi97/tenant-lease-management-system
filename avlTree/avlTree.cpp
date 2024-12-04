#include "AVLTree.h"
#include <algorithm>
#include <iostream>

// Constructor
AVLTree::AVLTree() : root(nullptr) {}

// Destructor
AVLTree::~AVLTree() {
    destroyTree(root);
}

// Destroy the tree recursively
void AVLTree::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Function to get the height of a node
int AVLTree::height(Node* node) const {
    if (node == nullptr) return 0;
    return node->height;
}

// Function to get the balance factor of a node
int AVLTree::getBalance(Node* node) const {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

// Right rotation
AVLTree::Node* AVLTree::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotation
AVLTree::Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Insert a tenant into the AVL tree
void AVLTree::insert(Tenant tenant) {
    root = insert(root, tenant);
}

// Helper function to insert a tenant into the AVL tree
AVLTree::Node* AVLTree::insert(Node* node, Tenant tenant) {
    // Step 1: Perform the normal BST insert
    if (node == nullptr) return new Node(tenant);

    if (tenant.tenantID < node->data.tenantID) {
        node->left = insert(node->left, tenant);
    } else if (tenant.tenantID > node->data.tenantID) {
        node->right = insert(node->right, tenant);
    } else {
        // Duplicate tenant IDs are not allowed
        return node;
    }

    // Step 2: Update the height of the ancestor node
    node->height = 1 + std::max(height(node->left), height(node->right));

    // Step 3: Get the balance factor and balance the tree
    int balance = getBalance(node);

    // Left Left case
    if (balance > 1 && tenant.tenantID < node->left->data.tenantID) {
        return rightRotate(node);
    }

    // Right Right case
    if (balance < -1 && tenant.tenantID > node->right->data.tenantID) {
        return leftRotate(node);
    }

    // Left Right case
    if (balance > 1 && tenant.tenantID > node->left->data.tenantID) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left case
    if (balance < -1 && tenant.tenantID < node->right->data.tenantID) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// In-order traversal of the AVL tree
void AVLTree::inorder() const {
    inorder(root);
}

// Helper function for in-order traversal
void AVLTree::inorder(Node* node) const {
    if (node == nullptr) return;
    inorder(node->left);
    std::cout << "Tenant ID: " << node->data.tenantID << ", Name: " << node->data.name << std::endl;
    inorder(node->right);
}

// Search for a tenant by ID
Tenant* AVLTree::search(int tenantID) const {
    Node* foundNode = search(root, tenantID);
    return foundNode ? &foundNode->data : nullptr;
}

// Helper function to search for a tenant by ID
AVLTree::Node* AVLTree::search(Node* node, int tenantID) const {
    if (node == nullptr || node->data.tenantID == tenantID) {
        return node;
    }

    if (tenantID < node->data.tenantID) {
        return search(node->left, tenantID);
    } else {
        return search(node->right, tenantID);
    }
}
