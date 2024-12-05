#include <iostream> 
#include <string>   
#include <vector>   
#include <fstream>  
#include <sstream>  
#include <chrono>
#include <thread>
#include "main_utils.cpp"
#include "avlTree.h"

void searchTestCase(const std::string& fileName, int count) {
    AVLTree tenantAVLtree;
    
    auto startInsert = std::chrono::steady_clock::now();
    auto endInsert = std::chrono::steady_clock::now();

    Tenant::loadTenantData(fileName, [&tenantAVLtree, &startInsert, &endInsert](const Tenant& tenant) {
        startInsert = std::chrono::steady_clock::now(); 
        tenantAVLtree.insert(tenant);
        endInsert = std::chrono::steady_clock::now();  
    });

    std::chrono::duration<double, std::milli> durationInsert = endInsert - startInsert;
    double totalElapsedInsert = durationInsert.count();
    std::cout << count << " Average time per insert: " << totalElapsedInsert / count << " ms" << std::endl;


    auto start = std::chrono::steady_clock::now();
    
    int i = 0;
    while (i < count) {
        Tenant* tenant = tenantAVLtree.search(i);
        i++;
    }
    
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    double totalElapsed = duration.count();
    std::cout << count  << "Average time per search: " << totalElapsed / count << " ms" << std::endl;
}

int main() {
    const std::string file100kName = "dataset/tenant_data_100k.dat";
    const std::string file50kName = "dataset/tenant_data_50k.dat";
    const std::string file10kName = "dataset/tenant_data_10k.dat";

    int hundredK = 100000;
    int fiftyK = 50000;
    int tenK = 10000;

    std::vector<std::pair<std::string, int>> testCases = {
        {file100kName, 100000},
        {file50kName, 50000},
        {file10kName, 10000}
    };

    for (const auto& testCase : testCases) {
        searchTestCase(testCase.first, testCase.second);
    }

    return 0;
}