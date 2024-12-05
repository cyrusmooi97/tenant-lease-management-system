#include <string>  
#include <iostream> 

void displayMenu() {
    std::cout << "\n### Tenant and Lease Management System BST ###\n";
    std::cout << "1. Insert Tenant\n";
    std::cout << "2. Search Tenant by ID\n";
    std::cout << "3. Delete Tenant by ID\n";
    std::cout << "4. Display All Tenants\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your choice: ";
}

template <typename Func, typename... Args>
void addTimer(Func&& func, Args&&... args) {
    auto start = std::chrono::steady_clock::now();
    
    // Forward the arguments to the provided function
    std::forward<Func>(func)(std::forward<Args>(args)...);

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Elapsed time: " << duration.count() << " ms\n";
}