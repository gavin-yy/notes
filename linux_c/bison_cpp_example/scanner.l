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

%{
	#include <iostream>
	#include <cstdlib>
	#include "scanner.h"
	#include "interpreter.h"
	#include "parser.hpp"
	#include "location.hh"

	using namespace std;

	// Original yyterminate() macro returns int. Since we're using Bison 3 variants
	// as tokens, we must redefine it to change type from `int` to `Parser::semantic_type`
	#define yyterminate() RDL::Parser::make_END(RDL::location());

	// This will track current scanner location.
	// Action is called when length of the token is known.
	#define YY_USER_ACTION m_driver.increaseLocation(yyleng);

	// !!!WARNING!!!
	// Location API is used, but the location is not initialized, 'cause I'm lazy. When making
	// a token with make_{something} method you can pass detailed token location. Current location
	// is accessible with m_driver.location() method. All puzzle elements are there - just
	// pass location value in every action code block below. I'm going to waste more time writing
	// this excuse than putting this boilerplate below...
	//
	// Location class can be found in location.hh and posistion.hh files. It's just a bit too much
	// boilerplate for this small example. Bummer.
%}

%option nodefault
%option noyywrap
%option c++
%option yyclass="Scanner"
%option prefix="RDL_"

DID  [a-zA-Z0-9][a-zA-Z0-9_@\-]*

%%

{DID}\.[0-9]+\.[0-9]+    {
                          cout << "Scanner: DID [" << yytext << "]" << endl;
                          return RDL::Parser::make_DID(yytext, RDL::location( /* put location data here if you want */ ));
                        }


IF  {
        cout << "Scanner: IF [" << yytext << "]" << endl;
        return RDL::Parser::make_IF(yytext, RDL::location());
    }

THEN    {
            cout << "Scanner: THEN [" << yytext << "]" << endl;
            return RDL::Parser::make_THEN(yytext, RDL::location());
        }

ENDIF   {
            cout << "Scanner: ENDIF [" << yytext << "]" << endl;
            return RDL::Parser::make_ENDIF(yytext, RDL::location());
        }


AND     {
            cout << "Scanner: AND [" << yytext << "]" << endl;
            return RDL::Parser::make_AND(yytext, RDL::location());
        }


true|false {
                cout << "Scanner: BOOL [" << yytext << "]" << endl;
                return RDL::Parser::make_BOOL(yytext, RDL::location( /* put location data here if you want */ ));
            }


ANY|any  {
            cout << "Scanner: ANY [" << yytext << "]" << endl;
            return RDL::Parser::make_VALUE_ANY(RDL::location());
        }

"=>"    {
            cout << "Scanner: SET [" << yytext << "]" << endl;
            return RDL::Parser::make_SET_TARGET(RDL::location());
        }

"=="|"!="|"<"|">"|"<="|">=" {
            cout << "Scanner: EQ [" << yytext << "]" << endl;
            return RDL::Parser::make_COMPARATOR(yytext, RDL::location());
            }



"&&"    {
            cout << "Scanner: LOGIC_&& [" << yytext << "]" << endl;
            return RDL::Parser::make_LOGIC_OPERATOR_AND(RDL::location());
        }

"||"    {
            cout << "Scanner: LOGIC_|| [" << yytext << "]" << endl;
            return RDL::Parser::make_LOGIC_OPERATOR_OR(RDL::location());
        }


SLEEP   {
            cout << "Scanner: SLEEP [" << yytext << "]" << endl;
            return RDL::Parser::make_EXEC_SLEEP(RDL::location());
        }

\@clock {
            cout << "Scanner: @clock [" << yytext << "]" << endl;
            return RDL::Parser::make_AT_CLOCK( RDL::location());
        }

\@day   {
            cout << "Scanner: @clock [" << yytext << "]" << endl;
            return RDL::Parser::make_AT_DAY( RDL::location());
        }

\@between  {
            cout << "Scanner: @clock [" << yytext << "]" << endl;
            return RDL::Parser::make_AT_BETWEEN( RDL::location());
            }






\@\{[0-9]+\}  {
                std::string text(yytext);
                std::cout << "Scanner: [" << text << "]" << std::endl;
                return RDL::Parser::make_EXEC_SCENE(text, RDL::location());
              }

\#[0-9]+    {
                cout << "Scanner: # [" << yytext << "]" << endl;
                return RDL::Parser::make_ARG_INDEX(yytext, RDL::location());
            }

\=          {
                cout << "Scanner: '=' [" << yytext << "]" << endl;
                return RDL::Parser::make_ASSIGN(RDL::location());
            }

\:          {
                cout << "Scanner: ':' [" << yytext << "]" << endl;
                return RDL::Parser::make_COLON(RDL::location());
            }


\"([^\\\"]|\\.)*\"  {
                std::string text(yytext);
                cout << "Scanner: STRING [" << text << "]" << endl;
                return RDL::Parser::make_STRING(text, RDL::location());
                }

\(          {
                cout << "Scanner: '('" << endl;
                return RDL::Parser::make_LEFTPAR(RDL::location());
            }

\)          {
                cout << "Scanner: ')'" << endl;
                return RDL::Parser::make_RIGHTPAR(RDL::location());
            }

\{          {
                cout << "Scanner: '{'" << endl;
                return RDL::Parser::make_LEFTBRACE(RDL::location());
            }

\}          {
                cout << "Scanner: '}'" << endl;
                return RDL::Parser::make_RIGHTBRACE(RDL::location());
}

;           {
                cout << "Scanner: ';'" << endl;
                return RDL::Parser::make_SEMICOLON(RDL::location());
            }

,           {
                cout << "Scanner: ','" << endl;
                return RDL::Parser::make_COMMA(RDL::location());
            }

[\n\t ]     {
                //cout << "Scanner: whitechar (ignored)" << endl;
            }

[1-9][0-9]* {
                cout << "Scanner: decimal number: " << yytext << endl;
                uint64_t number = strtoull(yytext, 0, 10);
                return RDL::Parser::make_NUMBER(number, RDL::location());
            }

.           {
                cout << "Scanner: unknown character [" << yytext << "]" << endl;
            }

<<EOF>>     { return yyterminate(); }


%%
