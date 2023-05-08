#ifndef PROCEDURAL_ACTION_H
#define PROCEDURAL_ACTION_H

#include <string>
#include <vector>
#include <map>

#include "procedural/core/Types/Fact.h"
#include "procedural/core/Types/SpecializedAction.h"

namespace procedural {

class Action
{
public:
    explicit Action(const std::string& name);

    bool addPatterns(const SpecializedAction& pattern);

    bool feed(Fact* fact, TimeStamp_t currentTimestamp);

    std::set<uint32_t> checkCompleteNetworks(TimeStamp_t currentTimestamp);

    void displayCurrentState();

    void cleanPatterns(std::set<uint32_t> set_id);
    void clean();

    std::string toString();

    std::string currentState(bool shortVersion = true);

    bool checkSubAction(Action* action);

    std::unordered_set<Network*> getCompleteNetworks() { return complete_networks_;};
    std::string getName() const { return name_;};
    bool checkNewExplanation();
    std::vector<Network*> getNewExplanation();

    double maxTtl();

    std::vector<SpecializedAction> getSpecializedActions() {return patterns_;};
private:
    std::string name_;
    std::unordered_set<Network*> complete_networks_;
    std::unordered_set<Network*> updated_sub_networks_;
    bool flag_;

    std::vector<SpecializedAction> patterns_;

};

} // namespace procedural

#endif // PROCEDURAL_ACTION_H
