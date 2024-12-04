#include "tenant_bst_utils.h"
#include <fstream>
#include <sstream>
#include <iostream>

void loadTenantData(const std::string& fileName, TenantBST& tenantBST) {
    std::ifstream file(fileName);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string tenantIDStr, name, leaseIDStr, leaseStart, leaseEnd;

        std::getline(ss, tenantIDStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, leaseIDStr, ',');
        std::getline(ss, leaseStart, ',');
        std::getline(ss, leaseEnd, ',');

        int tenantID = std::stoi(tenantIDStr);
        int leaseID = std::stoi(leaseIDStr);

        Tenant tenant(tenantID, name, leaseID, leaseStart, leaseEnd);
        tenantBST.insert(tenant);
    }

    file.close();
}