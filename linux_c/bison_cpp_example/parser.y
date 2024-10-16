/*
 * The MIT License (MIT)
 * ... (License text remains the same)
 */

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0"
%defines
%define api.parser.class { Parser }

%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace { RDL }
%code requires
{
    #include <iostream>
    #include <string>
    #include <vector>
    #include <memory>
    #include <stdint.h>
    #include "command.h"
    #include "rdl_condition.h"
    #include "rdl_act.h"

    using namespace std;

    namespace RDL {
        class Scanner;
        class Interpreter;
        // class Command; // Declare Command class
        class condition;
        class condition_expression;
        class rule;
        class rdl_exec;
    }
}

%code top
{
    #include <iostream>
    #include <memory>
    #include "scanner.h"  // Replace with your actual header
    #include "parser.hpp" // Replace with your actual header
    #include "interpreter.h" // Replace with your actual header
    #include "location.hh" // Replace with your actual header
    #include "rdl_condition.h"
    #include "rdl_act.h"
    #include "json.hpp"

    static RDL::Parser::symbol_type yylex(RDL::Scanner &scanner, RDL::Interpreter &driver) {
        return scanner.get_next_token();
    }

    using namespace RDL;

    std::string remove_quotos(std::string str)
    {
        if(str.length() >= 2) {
            str = str.substr(1, str.length()-2);  //remove "", only keep the content.
        }

        return str;
    }
}

%lex-param { RDL::Scanner &scanner }
%lex-param { RDL::Interpreter &driver }
%parse-param { RDL::Scanner &scanner }
%parse-param { RDL::Interpreter &driver }
%locations

// %define lr.type canonical-lr

%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%token END 0 "end of file"

%token <std::string> STRING  "STRING"
%token <int64_t>     NUMBER   "NUMBER"
%token <bool>        BOOL    "BOOL"
%token VALUE_ANY     "any"

%token <std::string> DID     "did"
%token <std::string> IF      "IF"
%token <std::string> THEN    "THEN"
%token <std::string> ENDIF   "ENDIF"
%token <std::string> AND     "AND"
%token <std::string> OR      "OR"
%token <std::string> COMPARATOR "comparator"
%token ASSIGN  "="

%token AT_CLOCK    "@clock"
%token AT_DAY      "@day"
%token AT_BETWEEN  "@between"
%token AT_SOMEDAY  "@someday"


%token COMMA ","

//
%token <std::string> ARG_INDEX "#arg"
%left ARG_INDEX

%token SET_TARGET "=>"

%token EXEC_SLEEP "SLEEP"
%token <std::string> EXEC_SCENE "SCENE"



%token LEFTPAR "("
%token RIGHTPAR ")"
%token LEFTBRACE "{"
%token RIGHTBRACE "}"

%token SEMICOLON ";"

%token COLON ":"

%left COMPARATOR
%left LOGIC_OPERATOR_AND
%left LOGIC_OPERATOR_OR // Define precedence for OR


%type< shared_ptr<cond_base> > prop_item_cmp trigger_event_item trigger_clock_item
%type< shared_ptr<cond_base> > cond_day_item cond_between_item

%type< RDL::condition_expression> one_trigger
%type< RDL::condition_expression> trigger_exp

%type< nlohmann::json > target_value

%type< nlohmann::json > arg_value_list
%type< nlohmann::json > action_arg_expression
%type< nlohmann::json > act_args

%type< nlohmann::json >  one_nest_param_arg
%type< nlohmann::json >  nest_assign_list
%type< nlohmann::json >  nest_assign_single



%left VALUE_DELIM
%left EXPRESSION_DELIM

%type< RDL::rdl_exec > action

%start program

%%

program :   {
                cout << "*** RUN ***" << endl;
                driver.clear();
            }
        | IF trigger_exp THEN action_expression ENDIF
            {
                $2.set_in_trigger(true);
                driver.setTrigger($2);

                cout << "*** STOP RUN ***" << endl;
                cout << driver.str() << endl;
            }

        | IF trigger_exp AND trigger_exp THEN action_expression ENDIF
            {
                $2.set_in_trigger(true);
                driver.setTrigger($2);

                $4.set_in_trigger(false);
                driver.setCond($4);

                cout << "*** STOP RUN ***" << endl;
                cout << driver.str() << endl;
            }
        ;

trigger_exp:  one_trigger { $$ = $1; }
            | trigger_exp LOGIC_OPERATOR_AND one_trigger
                {   RDL::condition_expression exp;
                    exp.append($1);
                    exp.append($3);

                    RDL::cond_exp_operator op("&&");
                    exp.add( std::make_shared<cond_exp_operator>(op));
                    $$ = exp;
                }
            | trigger_exp LOGIC_OPERATOR_OR one_trigger
                {   RDL::condition_expression exp;
                    exp.append($1);
                    exp.append($3);
                    RDL::cond_exp_operator op("||");
                    exp.add(std::make_shared<cond_exp_operator>(op));
                    $$ = exp;
                }
            | LEFTPAR trigger_exp RIGHTPAR { $$ = $2;}
            ;

/*
cond_exp:     one_cond { $$ = $1; }
            | cond_exp LOGIC_OPERATOR_AND one_cond
                {   RDL::condition_expression exp;
                            exp.append($1);
                            exp.append($3);

                            RDL::cond_exp_operator op("&&");
                            RDL::condition cond(op);
                            exp.add(cond);
                            $$ = exp;
                }
            | cond_exp LOGIC_OPERATOR_OR one_cond
                {   RDL::condition_expression exp;
                            exp.append($1);
                            exp.append($3);
                            RDL::cond_exp_operator op("||");
                            RDL::condition cond(op);
                            exp.add(cond);
                            $$ = exp;
                        }
            | LEFTPAR cond_exp RIGHTPAR
                { $$ = $2;}
            ;
*/


one_trigger: prop_item_cmp   { RDL::condition_expression exp; exp.add($1); $$ = exp;}
            | trigger_event_item { RDL::condition_expression exp; exp.add($1); $$ = exp;}
            | trigger_clock_item { RDL::condition_expression exp; exp.add($1); $$ = exp;}

              /* @day 和 @between 应该是不能作为触发条件的，app写错了，那就兼容这种错误了。 */
            | cond_day_item      { RDL::condition_expression exp; exp.add($1); $$ = exp;}
            | cond_between_item  { RDL::condition_expression exp; exp.add($1); $$ = exp;}
        ;



// shared by trigger and condition .
prop_item_cmp: DID COMPARATOR target_value
                {
                    cond_prop prop($1, $2, $3);
                    $$ = std::make_shared<cond_prop>(prop);
                }
    ;

// did.1.2 == {}
trigger_event_item : DID COMPARATOR LEFTBRACE RIGHTBRACE
            {
                RDL::cond_event evt($1);
                $$ = std::make_shared<cond_event>(evt);
            }
        | DID COMPARATOR LEFTBRACE action_arg_expression RIGHTBRACE
            {
                RDL::cond_event evt($1, $2, $4);
                $$ = std::make_shared<cond_event>(evt);
            }
    ;


trigger_clock_item : AT_CLOCK COMPARATOR STRING
                {
                    std::string s = remove_quotos($3);
                    trigger_clock clk(s);
                    $$ = std::make_shared<trigger_clock>(clk);
                }
    ;

cond_day_item : AT_DAY COMPARATOR STRING
                {
                    std::string s = remove_quotos($3);
                    cond_day day(s);
                    $$ = std::make_shared<cond_day>(day);
                }
    ;


cond_between_item: AT_BETWEEN COMPARATOR STRING
                {
                    std::string s = remove_quotos($3);
                    cond_between between(s);
                    $$ = std::make_shared<cond_between>(between);
                }
    ;


action_expression: action
    | action_expression action
    ;


action: DID SET_TARGET target_value SEMICOLON
                {
                    rdl_exec_write_property p($1, $3);
                    driver.addExec( std::make_shared<rdl_exec_write_property>(p) );
                    $$ = p;
                }
    | EXEC_SLEEP SET_TARGET NUMBER SEMICOLON
                {
                    rdl_exec_sleep s($3);
                    driver.addExec( std::make_shared<rdl_exec_sleep>(s) );
                    $$ = s;
                }
    | EXEC_SCENE SEMICOLON
                {
                    std::string txt = $1;
                    size_t startPos = txt.find('{');
                    size_t endPos = txt.find('}');
                    std::string v = txt.substr( startPos + 1, endPos - startPos - 1 );

                    rdl_exec_scene s( std::stoul(v) );
                    driver.addExec( std::make_shared<rdl_exec_scene>(s) );
                    $$ = s;
                }
    | DID SEMICOLON
                {
                    //action without args.
                    nlohmann::json empty;
                    rdl_exec_action_in a($1, empty);
                    driver.addExec( std::make_shared<rdl_exec_action_in>(a) );
                    $$ = a;
                }
    | DID SET_TARGET act_args SEMICOLON
                {
                    rdl_exec_action_in a($1, $3);
                    driver.addExec( std::make_shared<rdl_exec_action_in>(a) );
                    $$ = a;
                }
    ;



/*
    case 1: xxx
    case 2: xxx, yyy
*/
arg_value_list : target_value
        {
            $$ = nlohmann::json::array( {$1} );
        }
    | one_nest_param_arg
        {
            $$ = nlohmann::json::array( {$1} );
        }
            /*
            | arg_value_list COMMA target_value
            {
                $1.push_back($3);
                $$ = $1;
            }
            */
    ;


one_nest_param_arg : LEFTPAR nest_assign_list RIGHTPAR
        {
            $$ = $2;
        }
    ;

// nest_assign_list is json array.
nest_assign_list : nest_assign_single
        {
            nlohmann::json result = nlohmann::json::array( {$1} );
            $$ = result;
        }
    | nest_assign_list COMMA nest_assign_single
        {
            $1.push_back($3);
            $$ = $1;
        }
    ;


nest_assign_single: ARG_INDEX COLON target_value
    {
        nlohmann::json result;
        std::string piid = $1.substr(1); //remove the begining '#'
        result["piid"] = piid;
        result["value"] = $3;
        $$ = result;
    }
    ;



/*
    foramt: #1 = xxx
*/
action_arg_expression : ARG_INDEX ASSIGN arg_value_list
        {
            nlohmann::json result;
            std::string piid = $1.substr(1); //remove the begining '#'
            result["piid"] = piid;
            result["value"] = $3;
            $$ = result;
        }
    ;

/*
    case 1: #1 = xxx
    case 2: #1 = xxx, #2 = yyy
*/
act_args : action_arg_expression
        {
            $$ = nlohmann::json::array({$1});
        }
    | act_args COMMA action_arg_expression
        {
            $1.push_back($3);
            $$ = $1;
        }
    ;



target_value: NUMBER { nlohmann::json v = $1;  $$ = v; }
          | STRING {
                     std::string content($1);
                     cout << "!!! string length()=" << content.length() << std::endl;
                     if(content.length() >= 2) {
                        content = content.substr(1, content.length()-2);  //remove "", only keep the content.
                     }
                     nlohmann::json v = content;
                     $$ = v;
                    }
          | BOOL   { nlohmann::json v = $1;  $$ = v; }
          | VALUE_ANY { nlohmann::json v;  $$ = v; }
          ;

%%

// ... (error function remains the same) ...
// Bison expects us to provide implementation - otherwise linker complains
void RDL::Parser::error(const location &loc , const std::string &message) {

        // Location should be initialized inside scanner action, but is not in this example.
        // Let's grab location directly from driver class.
	// cout << "Error: " << message << endl << "Location: " << loc << endl;

        cout << "Error: " << message << endl << "Error location: " << driver.location() << endl;
}
