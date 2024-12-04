#include "bst.h"

// Insert a tenant into the BST
bool TenantBST::insert(Tenant tenant) {
    return insertNode(root, tenant);
}

bool TenantBST::insertNode(TenantNode*& node, Tenant tenant) {
    if (node == nullptr) {
        node = new TenantNode(tenant);  // Create and assign the new node
        return true;  // Insertion successful
    }

    if (tenant.tenantID < node->data.tenantID) {
        return insertNode(node->left, tenant);  // Go left
    } else if (tenant.tenantID > node->data.tenantID) {
        return insertNode(node->right, tenant);  // Go right
    } else {
        //std::cout << "Duplicate tenantID: " << tenant.tenantID << ". Insertion skipped.\n";
        return false;  // Duplicate found, insertion skipped
    }
}

// Search for a tenant by ID
Tenant* TenantBST::search(int tenantID) {
    TenantNode* result = searchNode(root, tenantID);
    if (result) {
        return &result->data;
    }
    return nullptr;
}

TenantBST::TenantNode* TenantBST::searchNode(TenantNode* node, int tenantID) {
    if (node == nullptr || node->data.tenantID == tenantID) {
        return node;
    }

    if (tenantID < node->data.tenantID) {
        return searchNode(node->left, tenantID);
    } else {
        return searchNode(node->right, tenantID);
    }
}

// Delete a tenant by ID
void TenantBST::remove(int tenantID) {
    root = deleteNode(root, tenantID);
}

TenantBST::TenantNode* TenantBST::deleteNode(TenantNode* node, int tenantID) {
    if (node == nullptr) return nullptr;

    if (tenantID < node->data.tenantID) {
        node->left = deleteNode(node->left, tenantID);
    } else if (tenantID > node->data.tenantID) {
        node->right = deleteNode(node->right, tenantID);
    } else {
        // Node to delete found
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        } else if (node->left == nullptr) {
            TenantNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            TenantNode* temp = node->left;
            delete node;
            return temp;
        } else {
            // Node with two children
            TenantNode* minNode = findMinNode(node->right);
            node->data = minNode->data;
            node->right = deleteNode(node->right, minNode->data.tenantID);
        }
    }
    return node;
}

TenantBST::TenantNode* TenantBST::findMinNode(TenantNode* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

// Get all tenant with have a ordering traversal
std::vector<Tenant> TenantBST::getTraversal() {
    std::vector<Tenant> tenants;
    traversal(root, tenants);
    return tenants;
}

void TenantBST::traversal(TenantNode* node, std::vector<Tenant>& tenants) {
    if (node) {
        traversal(node->left, tenants);
        tenants.push_back(node->data);
        traversal(node->right, tenants);
    }
}