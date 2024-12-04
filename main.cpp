#include <iostream> 
#include <string>   
#include <vector>   
#include <fstream>  
#include <sstream>  
#include <chrono>
#include <thread>
#include "bst/bst.h"  
#include "bst/tenant_bst_utils.h"

void displayMenu() {
    std::cout << "\nTenant and Lease Management System\n";
    std::cout << "1. Insert Tenant\n";
    std::cout << "2. Search Tenant by ID\n";
    std::cout << "3. Delete Tenant by ID\n";
    std::cout << "4. Display All Tenants (In-Order)\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    TenantBST tenantBST;
    int choice;
    
    loadTenantData("dataset/tenant_data_100k.dat", tenantBST);
    do {
        displayMenu();
        std::cin >> choice;
        auto start = std::chrono::steady_clock::now();

        switch (choice) {
            case 1: {
                Tenant tenant;
                std::cout << "Enter Tenant ID: ";
                std::cin >> tenant.tenantID;
                std::cout << "Enter Tenant Name: ";
                std::cin.ignore();
                std::getline(std::cin, tenant.name);
                std::cout << "Enter Lease Start Date: ";
                std::getline(std::cin, tenant.leaseStart);
                std::cout << "Enter Lease End Date: ";
                std::getline(std::cin, tenant.leaseEnd);
                std::cout << "Enter Monthly Rent: ";
             
                tenantBST.insert(tenant); 
                std::cout << "Tenant inserted successfully.\n";
                break;
            }

            case 2: {
                int tenantID;
                std::cout << "Enter Tenant ID to search: ";
                std::cin >> tenantID;

                Tenant* tenant = tenantBST.search(tenantID);
                if (tenant) {
                    std::cout << "Tenant Found: \n";
                    std::cout << "ID: " << tenant->tenantID << ", Name: " << tenant->name
                              << ", Lease Start: " << tenant->leaseStart
                              << ", Lease End: " << tenant->leaseEnd;
                              
                } else {
                    std::cout << "Tenant not found.\n";
                }
                break;
            }

            case 3: {
                int tenantID;
                std::cout << "Enter Tenant ID to delete: ";
                std::cin >> tenantID;

                tenantBST.remove(tenantID);
                std::cout << "Tenant deleted (if existed).\n";
                break;
            }

            case 4: {
                std::vector<Tenant> tenants = tenantBST.getTraversal();
                std::cout << "List of Tenants:\n";
                for (const Tenant& tenant : tenants) {
                    std::cout << "ID: " << tenant.tenantID 
                            << ", Name: " << tenant.name
                            << ", Lease Start: " << tenant.leaseStart
                            << ", Lease End: " << tenant.leaseEnd;
                }
                break;
            }

            case 5: {
                std::cout << "Exiting the system.\n";
                break;
            }

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "Elapsed time: " << duration.count() << " ms\n";

    } while (choice != 5);

    return 0;
}