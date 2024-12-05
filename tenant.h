
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct Tenant {
    int tenantID;       
    std::string name;
    int leaseID;
    std::string leaseStart;
    std::string leaseEnd;

    Tenant() 
        : tenantID(0), name(""), leaseID(0), leaseStart(""), leaseEnd("") {}

    Tenant(int id, const std::string& n, int lid, const std::string& start, const std::string& end)
        : tenantID(id), name(n), leaseID(lid), leaseStart(start), leaseEnd(end) {}

    template <typename Func>
    static void loadTenantData(const std::string& fileName, Func&& func) {
        std::ifstream file(fileName);
        std::string line;

        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << fileName << std::endl;
            return;
        }
        // Skip the header line
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
            std::forward<Func>(func)(tenant);
        }

        file.close();
    }
};