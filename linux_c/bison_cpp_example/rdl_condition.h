#ifndef RDL_CONDITION_H
#define RDL_CONDITION_H

#include <string>
#include <vector>
#include <memory>
#include <sstream>

#include "json.hpp"
#include "Tool.h"

//extern std::vector<std::string> string_split(const std::string &s, char delim);



namespace RDL
{
    enum class condition_type {
        OPERATOR,
        PROP, // moment: dataChange / moment: flowChange / status: prop

        EVENT, // moment: eventTrigger
        TIME,  // moment: timer

        DAY,     // status: day
        BETWEEN, // status: between
        SOMEDAY, // status: someday -- not support yet.

        INVALID,
    };

    class cond_base {
    public:
            cond_base() = default;
            virtual ~cond_base() = default;

            virtual condition_type get_type() = 0;
            virtual std::string print() = 0;
            virtual nlohmann::json genTriggerJson() = 0;
            virtual nlohmann::json genCondJson() = 0;
    };

    class trigger_clock : public cond_base
    {
    public:
        std::string value;

        trigger_clock() = default;

        trigger_clock(std::string value) {
            this->value = value;
        }

        condition_type get_type() override {
            return condition_type::TIME;
        }

        std::string print() override {
            return "@clock: " + value;
        }

        nlohmann::json genTriggerJson() override{
            nlohmann::json j = {
                {"momentType", "timer"},
                {"clock", value}
            };
            return j;
        }

        nlohmann::json genCondJson() override {
            return {}; //should not set as condition. return empty json
        }
    };

    class cond_day : public cond_base
    {
    public:
        std::string value;

        cond_day() = default;

        cond_day(std::string value) {
            this->value = value;
        }

        condition_type get_type() override {
            return condition_type::DAY;
        }

        std::string print() override {
            return "@day: " + value;
        }

        nlohmann::json genTriggerJson() override{
            return {}; //should not set as trigger. return empty json
        }

        nlohmann::json genCondJson() override{
            nlohmann::json j = {
                {"time", "day"},
                {"value", value}
            };
            return j;
        }
    };

    class cond_between : public cond_base
    {
    public:
        std::string value;

        cond_between() = default;

        cond_between(std::string value) {
            this->value = value;
        }

        condition_type get_type() override {
            return condition_type::BETWEEN;
        }

        std::string print() override{
            return "@between: " + value;
        }

        nlohmann::json genTriggerJson() override {
            return {}; //should not set as trigger. return empty json
        }

        nlohmann::json genCondJson() override {
            //TODO: split string by -
            nlohmann::json j = {
                {"time", "between"},
                {"begin", value},
                {"end", value}
            };
            return j;
        }
    };

    class cond_someday : public cond_base
    {
    public:
        std::string value;

        std::string print() override {
            return "@someday: " + value;
        }

        condition_type get_type() override {
            return condition_type::SOMEDAY;
        }

        nlohmann::json genTriggerJson() override {
            return {}; //should not set as trigger. return empty json
        }

        nlohmann::json genCondJson() override {
            return {};
        }
    };

    class cond_prop : public cond_base
    {
    public:
        std::string property_id;
        std::string comparator;
        nlohmann::json value;

        cond_prop() = default;

        cond_prop(std::string property_id, std::string comparator, nlohmann::json value) {
            this->property_id = property_id;
            this->comparator = comparator;
            this->value = value;
        }

        condition_type get_type() override {
            return condition_type::PROP;
        }

        int comparator_id(std::string comparator)   {
            if(comparator == "==") return 0;
            if(comparator == "!=") return 1;
            if(comparator == ">=") return 2;
            if(comparator == ">") return  3;
            if(comparator == "<=") return 4;
            if(comparator == "<") return 5;
            return -1;
        }

        std::string print() override {
            return "PROP:" + property_id + " COMPARE:" + comparator + " " + value.dump();
        }

        nlohmann::json genTriggerJson() override {
            nlohmann::json j;
            std::vector<std::string> split_did =  string_split(property_id, '.');
            j["did"]  = split_did[0];
            j["siid"] = static_cast<uint32_t>(std::stoul(split_did[1]));
            j["piid"] = static_cast<uint32_t>(std::stoul(split_did[2]));
            j["cmp"] = comparator_id(comparator);

            if( value.empty()) {
                j["momentType"] = "flowChange";
            } else {
                j["momentType"] = "dataChange";

                if( value.is_boolean()) {
                    j["value"] = (value ? 1 : 0);
                } else {
                    j["value"] = value;
                }
            }
            return j;
        }

        nlohmann::json genCondJson() override {
            nlohmann::json j;
            std::vector<std::string> split_did =  string_split(property_id, '.');
            j["did"]  = split_did[0];
            j["siid"] = static_cast<uint32_t>(std::stoul(split_did[1]));
            j["piid"] = static_cast<uint32_t>(std::stoul(split_did[2]));
            j["cmp"] = comparator_id(comparator);
            if( value.is_boolean()) {
                j["value"] = (value ? 1 : 0);
            } else {
                j["value"] = value;
            }
            return j;
        }
    };

    class cond_event : public cond_base
    {
    public:
        std::string event_id;

        std::string comparator;
        nlohmann::json value;

        cond_event() = default;

        // need compare event's value.
        cond_event(std::string event_id, std::string comparator, nlohmann::json value) {
            this->event_id = event_id;
            this->comparator = comparator;
            this->value = value;
        }

        condition_type get_type() override {
            return condition_type::EVENT;
        }

        // event w/o value.
        cond_event(std::string event_id) {
            this->event_id = event_id;
        }

        std::string print() override {
            return "EVENT: " + event_id;
        }

        nlohmann::json genTriggerJson() override {
            nlohmann::json j;
            std::vector<std::string> split_did =  string_split(event_id, '.');
            j["did"]  = split_did[0];
            j["siid"] = static_cast<uint32_t>(std::stoul(split_did[1]));
            j["eiid"] = static_cast<uint32_t>(std::stoul(split_did[2]));
            j["momentType"] = "eventTrigger";
            return j;
        }

        nlohmann::json genCondJson() override {
            return {};
        }
    };

    class cond_exp_operator : public cond_base
    {
    public:
        std::string value;

        cond_exp_operator() = default;

        cond_exp_operator(std::string value) {
            this->value = value;
        }

        condition_type get_type() override {
            return condition_type::OPERATOR;
        }

        std::string print() override {
            return "OPERATOR: " + value;
        }

        nlohmann::json genTriggerJson() override {
            return {};
        }

        nlohmann::json genCondJson() override {
            if( value == "&&") {
                return "&";
            } else {
                return "|";
            }
        }

    };

    class condition_expression
    {
    private:
        std::vector< std::shared_ptr<cond_base> > conditions;
        bool in_trigger; // condtion expression is for trigger. otherwise it is for condition.
        std::string exp_logic;
    public:
        condition_expression() {}

        void set_in_trigger(bool b) { in_trigger = b; }

        void add( std::shared_ptr<cond_base> cond)
        {
            conditions.push_back( cond );
        }

        void append(condition_expression &exp)
        {
            for (auto &c : exp.conditions) {
                conditions.push_back(c);
            }
        }

        std::string get_exp_logic() {
            return exp_logic;
        }

        void clear()
        {
            conditions.clear();
        }

        std::string print();

        //json array.
        nlohmann::json genTriggerJson();
        nlohmann::json genCondJson();

        ~condition_expression() {}
    };

} // end of namespace

#endif