#include <iostream>
#include <vector>
#include "tenant.h"

class TenantBST {
private:
    struct TenantNode {
        Tenant data;
        TenantNode* left;
        TenantNode* right;

        TenantNode(Tenant tenant) : data(tenant), left(nullptr), right(nullptr) {}
    };

    TenantNode* root;

    bool insertNode(TenantNode*& node, Tenant tenant);
    TenantNode* searchNode(TenantNode* node, int tenantID);
    TenantNode* deleteNode(TenantNode* node, int tenantID);
    TenantNode* findMinNode(TenantNode* node);
    void traversal(TenantNode* node, std::vector<Tenant>& tenants);

public:
    TenantBST() : root(nullptr) {}

    bool insert(Tenant tenant);
    Tenant* search(int tenantID);
    void remove(int tenantID);
    std::vector<Tenant> getTraversal();
};