#ifndef PROCEDURAL_PATTERNRECOGNITION_H
#define PROCEDURAL_PATTERNRECOGNITION_H

#include <vector>
#include "procedural/core/Types/PatternTransition.h"
#include "procedural/core/Graph/Network.h"
#include "procedural/core/Types/Fact.h"

namespace procedural {

class PatternRecognition
{
public:
    PatternRecognition(const std::string& name,
                       std::vector<PatternTransition_t>& patterns,
                       std::vector<ActionDescription_t>& descriptions);

    bool isValid() const { return is_valid_; }
    int getNextId();
    std::set<uint32_t> checkNetwork();

    void checkNetworkComplete(Network* net);
    void cleanInvolve(const std::set<uint32_t>& list_valid_facts);

    void feed(Fact* fact);

    std::string toString();

    std::string currentState(bool shortVersion = true);

private:
    static int id_;

    std::string name_;
    Network* root_network_; //issue when i try without *
    std::unordered_set<Network*> networks_;
    std::unordered_set<Network*> complete_networks_;
    bool is_valid_;
};

} // namespace procedural

#endif //PROCEDURAL_PATTERNRECOGNITION_H
