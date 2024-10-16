#include "rdl_condition.h"

using namespace RDL;

std::string condition_expression::print()
{
    std::string result = "";
    for (auto &c : conditions) {
        result += c->print();
        result += " ";
    }
    return result;
}

nlohmann::json condition_expression::genTriggerJson()
{
    nlohmann::json result = nlohmann::json::array();

    for(auto &c : conditions) {
        if( (c->get_type() == condition_type::PROP) && !in_trigger) {
            continue;   // porp can be trigger or condition. is exp is conditon, bypass it.
        }

        nlohmann::json j = c->genTriggerJson();
        if( j.empty() ) {
            continue;  //compatible , not a trigger expression.
                       // @day , @between , OPERATOR goes here.
        }

        result.push_back(j);
    }

    return result;
}

nlohmann::json condition_expression::genCondJson()
{
    nlohmann::json result = nlohmann::json::array();

    for(auto &c : conditions) {
        if( (c->get_type() == condition_type::PROP) && in_trigger) {
            continue;   // porp can be trigger or condition. is exp is conditon, bypass it.
        }

        nlohmann::json j = c->genCondJson();
        if( j.empty() ) {
            continue;
        }

        if( c->get_type() == condition_type::OPERATOR ) {
            exp_logic = j.get<std::string>();
            continue;
        }

        result.push_back(j);
    }

    return result;
}