#ifndef RDL_ACT_H
#define RDL_ACT_H

#include <string>
#include "json.hpp"

namespace RDL
{

enum rdl_exec_type
{
    EXEC_TYPE_WRITE_PROPERTY,
    EXEC_TYPE_ACTION_IN,
    EXEC_TYPE_SLEEP,
    EXEC_TYPE_SCENE,
};

class rdl_exec {
protected:
    rdl_exec_type exec_type;

public:
    virtual std::string print() {
        return "NEED_OVERRIDE";
    };

    virtual nlohmann::json genJson() {
        return nlohmann::json();
    };

    virtual ~rdl_exec() {}
};

class rdl_exec_write_property : public rdl_exec
{
    std::string id;
    nlohmann::json value;

public:
    rdl_exec_write_property(std::string id, nlohmann::json value) : id(id), value(value) {
        exec_type = EXEC_TYPE_WRITE_PROPERTY;
    }

    nlohmann::json genJson() override {
        std::vector<std::string> split_did =  string_split(id, '.');
        nlohmann::json j;
        j["did"]  = split_did[0];
        j["siid"] = split_did[1];

        if( !value.empty()) {
            j["exec"] = "ctrl";
            if( value.is_boolean() ) {
                j["piids"] = { {split_did[2], (value == true ? 1 : 0) } };
            } else {
                j["piids"] = { {split_did[2], value} };
            }
        } else {
            j["exec"] = "flow";
            j["factor"] = 1; // value = kx+b
            j["base"] = 0;
        }

        return j;
    }

    virtual std::string print() override {
        return "WRITE_PROP " + id + " TO: " + value.dump();
    }
};

class rdl_exec_action_in :  public rdl_exec
{
    std::string id;
    nlohmann::json value;

public:
    rdl_exec_action_in(std::string id, nlohmann::json& value) : id(id), value(value) {
        exec_type = EXEC_TYPE_ACTION_IN;
    }

    nlohmann::json genJson() override {
        std::vector<std::string> split_did =  string_split(id, '.');
        nlohmann::json j;
        j["did"]  = split_did[0];
        j["siid"] = split_did[1];
        j["piid"] = split_did[2];
        j["args"] =  value;
        j["exec"] = "action_TODO";

        return j;
    }

    virtual std::string print() override {
        return  "ACTION_IN " + id + " args: " + value.dump();
    }
};

class rdl_exec_sleep :  public rdl_exec
{
    uint32_t value;
public:
    rdl_exec_sleep(uint32_t value) : value(value) {
        exec_type = EXEC_TYPE_SLEEP;
    }

    nlohmann::json genJson() override {
        nlohmann::json j = { {"exec", "timeout"}, {"time", value}};
        return j;
    }

    std::string print() override {
        return "SLEEP " +  std::to_string(value);
    }
};

class rdl_exec_scene :  public rdl_exec
{
    uint32_t value;

public:
    rdl_exec_scene(uint32_t value) : value(value) {
        exec_type = EXEC_TYPE_SCENE;
    }

     nlohmann::json genJson() override {
        nlohmann::json j = { {"exec", "scene"}, {"sceneId", std::to_string(value)} };
        return j;
    }

    std::string print() override {
        return "SCENE " + std::to_string(value);
    }
};







}

#endif