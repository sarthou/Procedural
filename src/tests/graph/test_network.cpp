#include "procedural/core/Types/FactPattern.h"
#include "procedural/core/Types/ActionDescription.h"
#include "procedural/core/Graph/Network.h"
#include <iostream>
#include <exception>
#include <vector>
#include <set>

int main()
{
    procedural::FactPattern F = procedural::FactPattern(false, "A", "MoveThrought", "O", false);
    procedural::FactPattern F1 = procedural::FactPattern(false, "A", "hasInHand", "O", false);
    procedural::FactPattern F2 = procedural::FactPattern(true, "O", "overSupport", "S", true);
    procedural::FactPattern F3 = procedural::FactPattern(true, "O", "inContainer", "S", true);

    std::cout << "============= TEST BAD NETWORK no init =============" << std::endl;
    std::vector<procedural::PatternTransition_t> list_test_bad_network;
    list_test_bad_network.emplace_back(1, &F1, 2); 
    list_test_bad_network.emplace_back(2, &F2, 3); 
    list_test_bad_network.emplace_back(3, &F2, 1); 
    
    procedural::Network N_1 = procedural::Network("noInit",0);

    for(const auto& pattern : list_test_bad_network)
        N_1.addTransition(pattern);
    try 
    {
        N_1.closeNetwork();
    } catch(std::exception& e)
    {
        std::cerr<< e.what() << std::endl;
    }


    std::cout << N_1.getName() << " is " << (N_1.isClosed() ? "" : "NOT ") << "close" << std::endl;
    std::cout << N_1.getName() << " is " << (N_1.isValid() ? "" : "NOT ") << "valid" << std::endl;
    std::cout << std::endl;
    
    std::cout << "============= TEST BAD NETWORK multiple init =============" << std::endl;
    std::vector<procedural::PatternTransition_t> list_test_bad_network_multi;
    list_test_bad_network_multi.emplace_back(1, &F1, 2); 
    list_test_bad_network_multi.emplace_back(3, &F2, 2); 
    
    procedural::Network N_2 = procedural::Network("multi",0);

    for(const auto& pattern : list_test_bad_network_multi)
        N_2.addTransition(pattern);
    try
    {
        N_2.closeNetwork();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    std::cout << N_2.getName() << " is " << (N_2.isClosed() ? "" : "NOT ") << "close" << std::endl;
    std::cout << N_2.getName() << " is " << (N_2.isValid() ? "" : "NOT ") << "valid" << std::endl;
    std::cout << std::endl;

    std::cout << "============= TEST CREATION NETWORK =============" << std::endl;

    std::vector<procedural::PatternTransition_t> list_test;
    list_test.emplace_back(0, &F, 1); 
    list_test.emplace_back(0, &F1, 2); 
    list_test.emplace_back(1, &F1, 2); 
    list_test.emplace_back(2, &F2, 3); 
    list_test.emplace_back(1, &F2, 3); 
    list_test.emplace_back(0, &F2, 3); 

    std::cout << "======== TEST ADD NETWORK =======" << std::endl;
    std::vector<procedural::ActionDescription_t> file_descriptions;
    file_descriptions.emplace_back("??","isA","PlaceAction");
    file_descriptions.emplace_back("??","isPerformedBy","?A");
    file_descriptions.emplace_back("??","isPerformedOn","?O");
    file_descriptions.emplace_back("??","isPerformedFrom","?S");
    
    procedural::Network N = procedural::Network("pick",0);

    for(const auto& pattern : list_test)
        N.addTransition(pattern);
    for(const auto& des : file_descriptions)
        N.addDescription(des);
    N.closeNetwork();

    std::cout << N.getName() << " is " << (N.isClosed() ? "" : "NOT ") << "close" << std::endl;
    std::cout << N.getName() << " is " << (N.isValid() ? "" : "NOT ") << "valid" << std::endl;
    std::cout << std::endl;

    std::cout << "============= TEST CLOSE NETWORK =============" << std::endl;

    N.addTransition(list_test.front());

    std::cout << "============= ORIGINAL NETWORK =============" << std::endl;
    std::cout << N.toString() << "\n" << std::endl;
    std::cout << "Current state is: " <<  N.getCurrentState()->toString() << std::endl << std::endl;
    N.displayVariables();

    std::cout << "============= CLONED NETWORK =============" << std::endl;
    procedural::Network* N2 = N.clone(10);

    std::cout << N2->getName() << " is " << (N2->isClosed() ? "" : "NOT ") << "close" << std::endl;
    std::cout << N2->getName() << " is " << (N2->isValid() ? "" : "NOT ") << "valid" << std::endl;
    
    std::cout << N2->toString() << "\n" << std::endl;
    std::cout << "Current state is: " << N2->getCurrentState()->toString() << std::endl << std::endl;
    N2->displayVariables();

    std::cout << "======== CLONED NETWORK EVOLUTION ========" << std::endl;
    std::vector<procedural::Fact> facts;
    facts.emplace_back(true, "Bastien", "MoveThrought", "Cube",1);
    facts.emplace_back(true, "Bob", "hasInHand", "Cube",2);
    // facts.emplace_back(true, "Cube", "hasInHand", "Cube",3);
    facts.emplace_back(true, "Bastien", "hasInHand", "Cube",4);
    // facts.emplace_back(true, "Cube", "overSupport", "Table",5);
    facts.emplace_back(false, "Cube", "overSupport", "Table",6);

    for(auto& fact : facts)
    {
        std::cout << "fact : " << fact.toString() << std::endl;
        N2->evolve(&fact);
        std::cout << N2->getCurrentState()->toString() << std::endl;
        N2->displayVariables();
        std::cout << "--------------" << std::endl;
    }
    
    std::cout << "============= ORIGINAL NETWORK =============" << std::endl;
    std::cout << "Current state is: " <<  N.getCurrentState()->toString() << std::endl << std::endl;
    N.displayVariables();
    
    std::cout << "============= CLONED NETWORK =============" << std::endl;
    std::cout << "Current state is: " <<  N2->getCurrentState()->toString() << std::endl << std::endl;
    N2->displayVariables();
    std::cout<< N2->describe() << std::endl;
    std::cout<< N2->describe(true) << std::endl;

    return 0;
}

