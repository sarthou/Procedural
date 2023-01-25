#include <iostream>
#include "procedural/graph/Network.h"

namespace procedural {

Network::Network(const std::vector<std::vector<FactPattern>>& patterns, const std::string& name) : name_(name),
                                                                                                   current_state_(
                                                                                                           nullptr),literal_variables_({}),variables_({})
{
    for (auto index = 0; index < patterns.size() + 1; index++)
        graph_.emplace_back(name_, index);

    buildNetwork(patterns);
    linkNetwork();


//    for (auto& var: literal_variables_)
//        std::cout << var << std::endl;
//    for (auto& var: variables_)
//        std::cout << var.toString() << std::endl;
//    std::cout << "try print" << std::endl;

    graph_.front().setInitialNode();
    current_state_ = &graph_.front();

}

void Network::buildNetwork(const std::vector<std::vector<FactPattern>>& patterns)
{
    for (auto index_pattern = 0; index_pattern < patterns.size(); index_pattern++)
    {

        if (patterns[index_pattern].size() == 1)
            addTransitionIndex(patterns[index_pattern].front(), index_pattern);
        else
        {
            for (auto& or_pattern: patterns[index_pattern])
            {
                addTransitionIndex(or_pattern, index_pattern);
            }
        }
    }
}


void Network::linkNetwork()
{
    for(auto& state : graph_)
    {
        state.link_transitions(variables_);
//        state.expand_transitions();
    }

}
void Network::checkVar(const FactPattern& pattern)
{
    if (literal_variables_.find(pattern.getVarSubject()) == literal_variables_.end())
    {
        literal_variables_.insert(pattern.getVarSubject());
        variables_.emplace_back(pattern.getVarSubject());
//        std::cout << "add var : " << pattern.getVarSubject() << std::endl;
    }
    if (literal_variables_.find(pattern.getVarObject()) == literal_variables_.end())
    {
        literal_variables_.insert(pattern.getVarObject());
        variables_.emplace_back(pattern.getVarObject());
//        std::cout << "add var : " << pattern.getVarObject() << std::endl;

    }

}


void Network::addTransitionIndex(const FactPattern& pattern, int32_t index)
{
//    std::cout << pattern.toString() << std::endl;
//    std::cout<<"Add in map var subject : "<<pattern.getVarSubject()<<std::endl;
//    std::cout<<"Add in map var object : "<<pattern.getVarObject()<<std::endl;
    checkVar(pattern);
    Transition t = Transition(pattern);

    graph_[index].addTransition(t, &(graph_[index + 1]));
    if (pattern.isRequired())
    {
        for (auto i = 0; i < index; i++)
        {
            graph_[i].addTransition(t, &(graph_[index + 1]));
        }
    }
}

void Network::displayNetwork()
{
    for (auto& state: graph_)
    {
        std::cout << state.toString() << "\n\n" << std::endl;

    }
}

void Network::displayCurrentState()
{

    std::cout << current_state_->toString() << "\n\n" << std::endl;

}

void Network::displayVariables()
{
    for (auto& var: variables_)
    {
        std::cout << "key : " << var.literal << " => " << std::to_string(var.value) << std::endl;
    }
}

bool Network::evolve(const Fact& fact)
{
    auto evolution = current_state_->evolve(fact);
    if (evolution == nullptr)
        return false;
    current_state_ = evolution;
    return true;
}

void Network::updateVariables(const Fact& fact, const Transition& update_transition)
{
//    variables_map_.at(update_transition.getVarObject()) = fact.getObject();
//    variables_map_.at(update_transition.getVarSubject()) = fact.getSubject();
    for (auto& state: graph_)
    {
//        for (auto& transition: state.getTransitions())
//        {
//            transition.checkUpdate(this);
//        }
    }
}




}

