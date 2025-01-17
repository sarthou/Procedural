#ifndef PROCEDURAL_PARSEDCOMPOSEDACTION_H
#define PROCEDURAL_PARSEDCOMPOSEDACTION_H
#include "procedural/reader/types/ParsedPattern.h"
#include "procedural/reader/types/ParsedDescription.h"
#include "procedural/reader/types/ParsedParameters.h"
#include "procedural/reader/types/ParsedRemap.h"
#include <iostream>

namespace procedural {
struct ParsedComposedAction_t
{
    ParsedComposedAction_t() : regex_type(R"(\s*([^_\s]*)_?([^\s]*)?\s*)")
    {};

    std::regex regex_type;
    std::string type;
    std::string subtype;
    procedural::ParsedParameters_t parameters;
    procedural::ParsedPattern_t pattern;
    procedural::ParsedDescriptions_t descriptions;
    procedural::ParsedRemaps_t remaps;

    void linkRemapPattern()
    {
        for (auto& remap_element: remaps.remaps)
        {
            auto literal = remap_element.first;
            auto find = [literal](const SubStateMachine_t& subnet) { return subnet.literal == literal; };
            auto result = std::find_if(pattern.sub_state_machines.begin(), pattern.sub_state_machines.end(), find);
            if (result != pattern.sub_state_machines.end())
                result->remap = remap_element.second.remap;
            else
                std::cout << "Warning : not state machine find for this remap literal : " << literal << std::endl;
        }


    }
    std::string getName()
    {
        std::string res = type;
        return subtype.empty() ? res : res + "_" + subtype;
    }

    void addPattern(const ParsedPattern_t& new_pattern)
    {
        pattern = new_pattern;
        max_level = new_pattern.max_level;
        if (remaps.empty() == false)
            linkRemapPattern();
    }
    void addRemap(const ParsedRemaps_t& new_remap)
    {
        remaps = new_remap;
        if (pattern.empty() == false)
            linkRemapPattern();
    }

    friend std::ostream& operator<<(std::ostream& os, const ParsedComposedAction_t& lhs)
    {
        os << "Composed Action : " << lhs.type;
        os << (lhs.subtype.empty() ? "\n" : "_" + lhs.subtype + "\n");
        os << lhs.pattern;
        os << "Description : \n" << lhs.descriptions;
        os << ((lhs.parameters.empty()) ? "" : "Parameters : \n") << lhs.parameters;

        return os;
    }

    void setType(const std::string& str_type)
    {
        std::smatch results;
        std::regex_search(str_type, results, regex_type);
        type = results[1];
        subtype = results[2];
    }
    int max_level;
};
}


#endif //PROCEDURAL_PARSEDCOMPOSEDACTION_H
