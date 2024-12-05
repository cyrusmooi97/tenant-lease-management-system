#include <iostream>
#include <vector>
#include "tenant.h"

class AVLTree {
public:
    AVLTree() : root(nullptr) {};
    ~AVLTree();
    bool insert(Tenant tenant);
    bool deleteTenant(int tenantID);
    void inorder() const;
    Tenant* search(int tenantID) const;

private:
    // Helper struct to represent a TenantNode in the AVL tree
    struct TenantNode {
        Tenant data;
        TenantNode* left;
        TenantNode* right;
        int height;

        // Constructor uses a const reference for the tenant
        TenantNode(Tenant& tenant) : data(tenant), left(nullptr), right(nullptr), height(1) {}
    };

    // Pointer to the root of the tree
    TenantNode* root;

    // Helper methods for AVL tree operations
    int height(TenantNode* TenantNode) const;
    int getBalance(TenantNode* TenantNode) const;
    TenantNode* rightRotate(TenantNode* y);
    TenantNode* leftRotate(TenantNode* x);
    TenantNode* insert(TenantNode* root, Tenant tenant, bool& success);
    void inorder(TenantNode* root) const;
    TenantNode* search(TenantNode* root, int tenantID) const;
    void destroyTree(TenantNode* TenantNode);
    TenantNode* deleteNode(TenantNode* node, int tenantID, bool& success);
    TenantNode* minValueNode(TenantNode* node);
};

