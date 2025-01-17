#ifndef PROCEDURAL_ACTIONBUILDER_H
#define PROCEDURAL_ACTIONBUILDER_H

#include <vector>
#include <ontologenius/clients/ontologyClients/ObjectPropertyClient.h>
#include "procedural/reader/types/ParsedSimpleAction.h"
#include "procedural/reader/types/ParsedComposedAction.h"
#include "procedural/core/Types/ActionType.h"
#include "procedural/utils/ActionRecognition.h"
namespace procedural {

class ActionBuilder
{
public:
    ActionBuilder() = default;
    ActionBuilder(const std::vector<ParsedSimpleAction_t>& simple_actions,
                  std::vector<ParsedComposedAction_t>& composed_actions);

    void build(const std::vector<ParsedSimpleAction_t>& simple_actions,
               std::vector<ParsedComposedAction_t>& composed_actions,
               ObjectPropertyClient* client);
    void buildSimpleAction(const std::vector<ParsedSimpleAction_t>& simple_actions);
    void buildComposedAction(std::vector<ParsedComposedAction_t>& composed_actions);
    void display();
    std::vector<ActionType*> getActions() { return actions_; };
private:
    ObjectPropertyClient* property_client_;
    std::vector<ParsedComposedAction_t> incomplete_creation_state_machine_;
    std::vector<ActionType*> actions_;
    bool completeRemap(SubStateMachine_t& sub_state_machine);
    void combineActions(const std::vector<ParsedSimpleAction_t>& simple_actions,
                        std::vector<ParsedComposedAction_t>& composed_actions);
    void buildIncomplete();
};

} // procedural

#endif //PROCEDURAL_ACTIONBUILDER_H
