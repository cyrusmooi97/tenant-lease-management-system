#include "avlTree.h"
#include <algorithm>
#include <iostream>

// Destructor
AVLTree::~AVLTree() {
    destroyTree(root);
}

// Destroy the tree recursively
void AVLTree::destroyTree(TenantNode* TenantNode) {
    if (TenantNode != nullptr) {
        destroyTree(TenantNode->left);
        destroyTree(TenantNode->right);
        delete TenantNode;
    }
}

int AVLTree::height(TenantNode* TenantNode) const {
    if (TenantNode == nullptr) return 0;
    return TenantNode->height;
}

// Function to get the balance factor of a TenantNode
int AVLTree::getBalance(TenantNode* TenantNode) const {
    if (TenantNode == nullptr) return 0;
    return height(TenantNode->left) - height(TenantNode->right);
}

// Right rotation
AVLTree::TenantNode* AVLTree::rightRotate(TenantNode* y) {
    TenantNode* x = y->left;
    TenantNode* T2 = x->right;

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
AVLTree::TenantNode* AVLTree::leftRotate(TenantNode* x) {
    TenantNode* y = x->right;
    TenantNode* T2 = y->left;

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
bool AVLTree::insert(Tenant tenant) {
    bool success = false;
    root = insert(root, tenant, success);
    return success;
}

AVLTree::TenantNode* AVLTree::insert(TenantNode* node, Tenant tenant, bool& success) {
    // Step 1: Perform the normal BST insert
    if (node == nullptr) {
        // Create a new TenantNode for the new tenant
        node = new TenantNode(tenant);
        success = true;  // Insertion successful
        return node;
    }

    if (tenant.tenantID < node->data.tenantID) {
        node->left = insert(node->left, tenant, success);
    } else if (tenant.tenantID > node->data.tenantID) {
        node->right = insert(node->right, tenant, success);
    } else {
        // Duplicate tenant IDs are not allowed
        success = false;  // Insertion failed due to duplicate tenant ID
        return node;
    }

    // Step 2: Update the height of the ancestor TenantNode
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

void AVLTree::inorder(TenantNode* TenantNode) const {
    if (TenantNode == nullptr) return;
    inorder(TenantNode->left);
    std::cout << "Tenant ID: " << TenantNode->data.tenantID << ", Name: " << TenantNode->data.name << std::endl;
    inorder(TenantNode->right);
}


Tenant* AVLTree::search(int tenantID) const {
    TenantNode* foundTenantNode = search(root, tenantID);
    return foundTenantNode ? &foundTenantNode->data : nullptr;
}


AVLTree::TenantNode* AVLTree::search(TenantNode* node, int tenantID) const {
    if (node == nullptr || node->data.tenantID == tenantID) {
        return node;
    }

    if (tenantID < node->data.tenantID) {
        return search(node->left, tenantID);
    } else {
        return search(node->right, tenantID);
    }
}

bool AVLTree::deleteTenant(int tenantID) {
    bool success = false;
    root = deleteNode(root, tenantID, success);
    return success;
}

AVLTree::TenantNode* AVLTree::deleteNode(TenantNode* node, int tenantID, bool& success) {
    // Step 1: Perform the normal BST delete
    if (node == nullptr) {
        success = false;  // Tenant not found
        return node;
    }

    if (tenantID < node->data.tenantID) {
        node->left = deleteNode(node->left, tenantID, success);
    } else if (tenantID > node->data.tenantID) {
        node->right = deleteNode(node->right, tenantID, success);
    } else {
        // Node to be deleted found
        success = true;

        // Node with only one child or no child
        if (node->left == nullptr) {
            TenantNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            TenantNode* temp = node->left;
            delete node;
            return temp;
        }

        // Node with two children: Get the inorder successor
        TenantNode* temp = minValueNode(node->right);

        // Copy the inorder successor's data to this node
        node->data = temp->data;

        // Delete the inorder successor
        node->right = deleteNode(node->right, temp->data.tenantID, success);
    }

    // Step 2: Update height of the current node
    node->height = 1 + std::max(height(node->left), height(node->right));

    // Step 3: Get the balance factor of this node
    int balance = getBalance(node);

    // Balance the tree if needed

    // Left Left case
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rightRotate(node);
    }

    // Right Right case
    if (balance < -1 && getBalance(node->right) <= 0) {
        return leftRotate(node);
    }

    // Left Right case
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left case
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVLTree::TenantNode* AVLTree::minValueNode(TenantNode* node) {
    TenantNode* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}