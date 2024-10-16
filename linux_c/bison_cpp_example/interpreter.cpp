/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Krzysztof Narkiewicz <krzysztof.narkiewicz@RDL.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include "interpreter.h"
#include "command.h"

#include <sstream>

using namespace RDL;

Interpreter::Interpreter() :
    // m_commands(),
    m_scanner(*this),
    m_parser(m_scanner, *this),
    m_location(0)
{
    // m_parser.set_debug_level(1);
}

int Interpreter::parse() {
    m_location = 0;
    return m_parser.parse();
}

void Interpreter::clear() {
    m_location = 0;
    // m_commands.clear();
    m_trigger.clear();
    m_cond.clear();
    m_execs.clear();
}

std::string Interpreter::str() {
    string s;

    s = "Trigger: " + m_trigger.print() + "\n";
    s += "Condition: " + m_cond.print() + "\n";
    for(auto& e : m_execs) {
        s += "Exec: " + e->print() + "\n";
    }

    return s;
}

void Interpreter::switchInputStream(std::istream *is) {
    m_scanner.switch_streams(is, NULL);
    // m_commands.clear();
    m_trigger.clear();
    m_cond.clear();
    m_execs.clear();
}

// void Interpreter::addCommand(const Command &cmd)
// {
//     m_commands.push_back(cmd);
// }
void Interpreter::setTrigger(condition_expression& exp)
{
    m_trigger = exp;
}

void Interpreter::setCond(condition_expression& exp)
{
    m_cond = exp;
}

void Interpreter::addExec(std::shared_ptr<rdl_exec> exec)
{
    m_execs.push_back(exec);
}

nlohmann::json Interpreter::generateCondJson()
{
    nlohmann::json j_condition;

    j_condition["moment"] = nlohmann::json::array();
    j_condition["status"] = nlohmann::json::array();

    nlohmann::json t = m_trigger.genTriggerJson();
    for(auto& item : t) {
        j_condition["moment"].push_back(item);
    }

    nlohmann::json c = m_cond.genCondJson();
    for(auto& item : c) {
        j_condition["status"].push_back(item);
    }

    // @day @between may pushed to trigger by app. compatible with this case.
    nlohmann::json wrong_cond = m_trigger.genCondJson();
    for(auto& item : wrong_cond) {
        j_condition["status"].push_back(item);
    }

    std::string cond_logic = m_cond.get_exp_logic();
    if( cond_logic.empty() ) {
        j_condition["operation"] = "&";  // the default logic algo for conditions.
    } else {
        j_condition["operation"] = cond_logic;
    }

    j_condition["cooldown"] = 1000;

    return j_condition;
}

nlohmann::json Interpreter::generateExecJson()
{
    //TODO:
    nlohmann::json j_exec = nlohmann::json::array();

    for(auto& e : m_execs) {
        j_exec.push_back(e->genJson());
    }

    return j_exec;
}

nlohmann::json Interpreter::generateOtRuleJson()
{
    nlohmann::json rule;

    nlohmann::json cond = generateCondJson();
    rule["condition"] = cond;

    rule["local_action"] = generateExecJson();

    return rule;
}


void Interpreter::increaseLocation(unsigned int loc) {
    m_location += loc;
    cout << "increaseLocation(): " << loc << ", total = " << m_location << endl;
}

unsigned int Interpreter::location() const {
    return m_location;
}
