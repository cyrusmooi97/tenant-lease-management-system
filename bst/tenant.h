#include <string>

struct Tenant {
    int tenantID;       
    std::string name;
    int leaseID;
    std::string leaseStart;
    std::string leaseEnd;

    Tenant() 
        : tenantID(0), name(""), leaseID(0), leaseStart(""), leaseEnd("") {}

    Tenant(int id, std::string n, int lid, std::string start, std::string end)
        : tenantID(id), name(n), leaseID(lid), leaseStart(start), leaseEnd(end) {}
};

struct TenantNode {
    Tenant data;
    TenantNode* left; 
    TenantNode* right;

    TenantNode(Tenant tenant) : data(tenant), left(nullptr), right(nullptr) {}
};