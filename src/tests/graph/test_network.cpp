#include "procedural/core/Types/FactPattern.h"
#include "procedural/graph/Network.h"
#include <iostream>
#include <vector>
#include <set>

int main()
{
    std::vector<std::vector<procedural::FactPattern>> list_facts;
    procedural::FactPattern F = procedural::FactPattern(false, "A", "MoveThrought", "O", false);
    procedural::FactPattern F1 = procedural::FactPattern(false, "A", "hasInHand", "O", false);
    procedural::FactPattern F2 = procedural::FactPattern(true, "O", "overSupport", "S", true);
    procedural::FactPattern F3 = procedural::FactPattern(true, "O", "inContainer", "S", true);
/*    std::cout << "Before Network \n"<< std::endl;
   std::cout << F.toString() << std::endl;
   std::cout << F1.toString() << std::endl;
   std::cout << F2.toString() << std::endl;
   std::cout << F3.toString() << std::endl;
   std::cout << "END Before Network \n"<< std::endl; */

   /*  list_facts.resize(3);
    list_facts[0].push_back(F);
    list_facts[1].push_back(F1);
    list_facts[2].push_back(F2);
    list_facts[2].push_back(F3);
 */
    std::vector<procedural::PatternTransition_t> list_test;

    list_test.emplace_back(0,&F,1,true); 
    list_test.emplace_back(0,&F1,2,true); 
    list_test.emplace_back(1,&F1,2,false); 
    list_test.emplace_back(2,&F2,3,false); 
    list_test.emplace_back(1,&F2,3,false); 
    list_test.emplace_back(0,&F2,3,true); 

    procedural::Network N = procedural::Network("pick",0);

    for(const auto& pattern : list_test)
    {
        N.addState(pattern);
    }
    std::cout << N.map2String()<<"\n" << std::endl;
    std::cout << N.getCurrentState()->toString() << std::endl;





 



    // procedural::Network N = procedural::Network(list_facts, "pick",0);
    procedural::Network * N2 = N.clone();
//    N.displayNetwork();
//    N.displayVariables();

    std::vector<procedural::Fact> facts;
    facts.emplace_back(true, "Bastien", "MoveThrought", "Cube");
    // facts.emplace_back(true, "Bob", "hasInHand", "Cube");
    // facts.emplace_back(true, "Cube", "hasInHand", "Cube");
    facts.emplace_back(true, "Bastien", "hasInHand", "Cube");
    // facts.emplace_back(true, "Cube", "overSupport", "Table");
    facts.emplace_back(false, "Cube", "overSupport", "Table");
//
    for(auto& fact : facts)
    {
        std::cout << "--------------" << std::endl;
        std::cout << "fact : " << fact.toString() << std::endl;
        N.evolve(fact);
//        N.displayVariables();
//        N.displayNetwork();
        std::cout << N.getCurrentState()->toString() << std::endl;
    }
    
    std::cout << "------------------- N--------------------" << std::endl;
    
    std::cout << N.map2String()<<"\n" << std::endl;
 
    std::cout << "-------------------N2--------------------" << std::endl;
    
    std::cout << N2->map2String()<<"\n" << std::endl;
    std::cout << N2->getCurrentState()->toString()<<"\n" << std::endl;

 


    /*procedural::Fact Fp = procedural::Fact(true, "Bastien", "MoveThrought", "Cube");
    procedural::Fact Fp1 = procedural::Fact(true, "Bastien", "hasInHand", "Cube");
    procedural::Fact Fp2 = procedural::Fact(false, "Cube", "overSupport", "Table");
    std::cout << Fact::individuals_table.toString() << std::endl;
    std::cout << Fp.getProperty() << std::endl;
    N.evolve(Fp);
    N.displayVariables();
    N.displayNetwork();
    N.evolve(Fp1);
    N.displayVariables();
    N.displayNetwork();
    N.evolve(Fp2);
    N.displayVariables();
    N.displayNetwork();*/


    return 0;
}

