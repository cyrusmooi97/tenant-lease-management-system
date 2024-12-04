#include <iostream> 
#include <string>   
#include <vector>   
#include <fstream>  
#include <sstream>  
#include <chrono>
#include <thread>
#include "bst/bst.h"  
#include "bst/tenant_bst_utils.h"
#include "main_utils.cpp"

template <typename Func, typename... Args>
void addTimer(Func&& func, Args&&... args) {
    auto start = std::chrono::steady_clock::now();
    
    // Forward the arguments to the provided function
    std::forward<Func>(func)(std::forward<Args>(args)...);

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Elapsed time: " << duration.count() << " ms\n";
}

int main() {
    TenantBST tenantBST;
    int choice;
    
    loadTenantData("dataset/tenant_data_100k.dat", tenantBST);
    do {
        displayMenu();
        std::cin >> choice;
        
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
                
                bool success = false;
                addTimer([&tenantBST, &success](Tenant t) { 
                    success = tenantBST.insert(t);  // This will update the success variable
                }, tenant);

                if (success) {
                    std::cout << "Tenant inserted successfully.\n";
                } else {
                    std::cout << "Insertion failed for tenant with ID: " << tenant.tenantID << ". Duplicate found.\n";
                }
                break;
            }

            case 2: {
                int tenantID;
                std::cout << "Enter Tenant ID to search: ";
                std::cin >> tenantID;

                addTimer([&tenantBST](int tenantID) { 
                    Tenant* tenant = tenantBST.search(tenantID); 
                    if (tenant) {
                    std::cout << "Tenant Found: \n";
                    std::cout << "ID: " << tenant->tenantID << ", Name: " << tenant->name
                              << ", Lease Start: " << tenant->leaseStart
                              << ", Lease End: " << tenant->leaseEnd;
                              
                    } else {
                        std::cout << "Tenant not found.\n";
                    }
                }, tenantID);
                
                break;
            }

            case 3: {
                int tenantID;
                std::cout << "Enter Tenant ID to delete: ";
                std::cin >> tenantID;

                addTimer([&tenantBST](int tenantID) { tenantBST.remove(tenantID); }, tenantID);
                std::cout << "Tenant deleted (if existed).\n";
                break;
            }

            case 4: {
                std::vector<Tenant> tenants;
                addTimer([&tenantBST, &tenants]() { tenants = tenantBST.getTraversal(); });

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
       
    } while (choice != 5);
    
    // //manual test case
    // auto start = std::chrono::steady_clock::now();

    // Tenant* tenant = tenantBST.search(4864);
    // if (tenant) {
    //     std::cout << "Tenant Found: \n";
    //     std::cout << "ID: " << tenant->tenantID << ", Name: " << tenant->name
    //                 << ", Lease Start: " << tenant->leaseStart
    //                 << ", Lease End: " << tenant->leaseEnd;
                    
    // } else {
    //     std::cout << "Tenant not found.\n";
    // }
    // auto end = std::chrono::steady_clock::now();
    // std::chrono::duration<double, std::milli> duration = end - start;
    // std::cout << "Elapsed time: " << duration.count() << " ms\n";
    
    return 0;
}

