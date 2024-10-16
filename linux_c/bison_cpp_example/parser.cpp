// A Bison parser, made by GNU Bison 3.8.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

// "%code top" blocks.
#line 40 "parser.y"

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

#line 66 "parser.cpp"




#include "parser.hpp"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "parser.y"
namespace  RDL  {
#line 166 "parser.cpp"

  /// Build a parser object.
   Parser :: Parser  (RDL::Scanner &scanner_yyarg, RDL::Interpreter &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

   Parser ::~ Parser  ()
  {}

   Parser ::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
   Parser ::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

   Parser ::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
   Parser ::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
   Parser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

   Parser ::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

   Parser ::symbol_kind_type
   Parser ::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

   Parser ::stack_symbol_type::stack_symbol_type ()
  {}

   Parser ::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_trigger_exp: // trigger_exp
      case symbol_kind::S_one_trigger: // one_trigger
        value.YY_MOVE_OR_COPY<  RDL::condition_expression > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_action: // action
        value.YY_MOVE_OR_COPY<  RDL::rdl_exec  > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arg_value_list: // arg_value_list
      case symbol_kind::S_one_nest_param_arg: // one_nest_param_arg
      case symbol_kind::S_nest_assign_list: // nest_assign_list
      case symbol_kind::S_nest_assign_single: // nest_assign_single
      case symbol_kind::S_action_arg_expression: // action_arg_expression
      case symbol_kind::S_act_args: // act_args
      case symbol_kind::S_target_value: // target_value
        value.YY_MOVE_OR_COPY<  nlohmann::json  > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_prop_item_cmp: // prop_item_cmp
      case symbol_kind::S_trigger_event_item: // trigger_event_item
      case symbol_kind::S_trigger_clock_item: // trigger_clock_item
      case symbol_kind::S_cond_day_item: // cond_day_item
      case symbol_kind::S_cond_between_item: // cond_between_item
        value.YY_MOVE_OR_COPY<  shared_ptr<cond_base>  > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOL: // "BOOL"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "NUMBER"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // "STRING"
      case symbol_kind::S_DID: // "did"
      case symbol_kind::S_IF: // "IF"
      case symbol_kind::S_THEN: // "THEN"
      case symbol_kind::S_ENDIF: // "ENDIF"
      case symbol_kind::S_AND: // "AND"
      case symbol_kind::S_OR: // "OR"
      case symbol_kind::S_COMPARATOR: // "comparator"
      case symbol_kind::S_ARG_INDEX: // "#arg"
      case symbol_kind::S_EXEC_SCENE: // "SCENE"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

   Parser ::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_trigger_exp: // trigger_exp
      case symbol_kind::S_one_trigger: // one_trigger
        value.move<  RDL::condition_expression > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_action: // action
        value.move<  RDL::rdl_exec  > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arg_value_list: // arg_value_list
      case symbol_kind::S_one_nest_param_arg: // one_nest_param_arg
      case symbol_kind::S_nest_assign_list: // nest_assign_list
      case symbol_kind::S_nest_assign_single: // nest_assign_single
      case symbol_kind::S_action_arg_expression: // action_arg_expression
      case symbol_kind::S_act_args: // act_args
      case symbol_kind::S_target_value: // target_value
        value.move<  nlohmann::json  > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_prop_item_cmp: // prop_item_cmp
      case symbol_kind::S_trigger_event_item: // trigger_event_item
      case symbol_kind::S_trigger_clock_item: // trigger_clock_item
      case symbol_kind::S_cond_day_item: // cond_day_item
      case symbol_kind::S_cond_between_item: // cond_between_item
        value.move<  shared_ptr<cond_base>  > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOL: // "BOOL"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "NUMBER"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // "STRING"
      case symbol_kind::S_DID: // "did"
      case symbol_kind::S_IF: // "IF"
      case symbol_kind::S_THEN: // "THEN"
      case symbol_kind::S_ENDIF: // "ENDIF"
      case symbol_kind::S_AND: // "AND"
      case symbol_kind::S_OR: // "OR"
      case symbol_kind::S_COMPARATOR: // "comparator"
      case symbol_kind::S_ARG_INDEX: // "#arg"
      case symbol_kind::S_EXEC_SCENE: // "SCENE"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
   Parser ::stack_symbol_type&
   Parser ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_trigger_exp: // trigger_exp
      case symbol_kind::S_one_trigger: // one_trigger
        value.copy<  RDL::condition_expression > (that.value);
        break;

      case symbol_kind::S_action: // action
        value.copy<  RDL::rdl_exec  > (that.value);
        break;

      case symbol_kind::S_arg_value_list: // arg_value_list
      case symbol_kind::S_one_nest_param_arg: // one_nest_param_arg
      case symbol_kind::S_nest_assign_list: // nest_assign_list
      case symbol_kind::S_nest_assign_single: // nest_assign_single
      case symbol_kind::S_action_arg_expression: // action_arg_expression
      case symbol_kind::S_act_args: // act_args
      case symbol_kind::S_target_value: // target_value
        value.copy<  nlohmann::json  > (that.value);
        break;

      case symbol_kind::S_prop_item_cmp: // prop_item_cmp
      case symbol_kind::S_trigger_event_item: // trigger_event_item
      case symbol_kind::S_trigger_clock_item: // trigger_clock_item
      case symbol_kind::S_cond_day_item: // cond_day_item
      case symbol_kind::S_cond_between_item: // cond_between_item
        value.copy<  shared_ptr<cond_base>  > (that.value);
        break;

      case symbol_kind::S_BOOL: // "BOOL"
        value.copy< bool > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "NUMBER"
        value.copy< int64_t > (that.value);
        break;

      case symbol_kind::S_STRING: // "STRING"
      case symbol_kind::S_DID: // "did"
      case symbol_kind::S_IF: // "IF"
      case symbol_kind::S_THEN: // "THEN"
      case symbol_kind::S_ENDIF: // "ENDIF"
      case symbol_kind::S_AND: // "AND"
      case symbol_kind::S_OR: // "OR"
      case symbol_kind::S_COMPARATOR: // "comparator"
      case symbol_kind::S_ARG_INDEX: // "#arg"
      case symbol_kind::S_EXEC_SCENE: // "SCENE"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

   Parser ::stack_symbol_type&
   Parser ::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_trigger_exp: // trigger_exp
      case symbol_kind::S_one_trigger: // one_trigger
        value.move<  RDL::condition_expression > (that.value);
        break;

      case symbol_kind::S_action: // action
        value.move<  RDL::rdl_exec  > (that.value);
        break;

      case symbol_kind::S_arg_value_list: // arg_value_list
      case symbol_kind::S_one_nest_param_arg: // one_nest_param_arg
      case symbol_kind::S_nest_assign_list: // nest_assign_list
      case symbol_kind::S_nest_assign_single: // nest_assign_single
      case symbol_kind::S_action_arg_expression: // action_arg_expression
      case symbol_kind::S_act_args: // act_args
      case symbol_kind::S_target_value: // target_value
        value.move<  nlohmann::json  > (that.value);
        break;

      case symbol_kind::S_prop_item_cmp: // prop_item_cmp
      case symbol_kind::S_trigger_event_item: // trigger_event_item
      case symbol_kind::S_trigger_clock_item: // trigger_clock_item
      case symbol_kind::S_cond_day_item: // cond_day_item
      case symbol_kind::S_cond_between_item: // cond_between_item
        value.move<  shared_ptr<cond_base>  > (that.value);
        break;

      case symbol_kind::S_BOOL: // "BOOL"
        value.move< bool > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "NUMBER"
        value.move< int64_t > (that.value);
        break;

      case symbol_kind::S_STRING: // "STRING"
      case symbol_kind::S_DID: // "did"
      case symbol_kind::S_IF: // "IF"
      case symbol_kind::S_THEN: // "THEN"
      case symbol_kind::S_ENDIF: // "ENDIF"
      case symbol_kind::S_AND: // "AND"
      case symbol_kind::S_OR: // "OR"
      case symbol_kind::S_COMPARATOR: // "comparator"
      case symbol_kind::S_ARG_INDEX: // "#arg"
      case symbol_kind::S_EXEC_SCENE: // "SCENE"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
   Parser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
   Parser ::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
   Parser ::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
   Parser ::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
   Parser ::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   Parser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   Parser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   Parser ::debug_level_type
   Parser ::debug_level () const
  {
    return yydebug_;
  }

  void
   Parser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

   Parser ::state_type
   Parser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
   Parser ::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
   Parser ::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
   Parser ::operator() ()
  {
    return parse ();
  }

  int
   Parser ::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (scanner, driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_trigger_exp: // trigger_exp
      case symbol_kind::S_one_trigger: // one_trigger
        yylhs.value.emplace<  RDL::condition_expression > ();
        break;

      case symbol_kind::S_action: // action
        yylhs.value.emplace<  RDL::rdl_exec  > ();
        break;

      case symbol_kind::S_arg_value_list: // arg_value_list
      case symbol_kind::S_one_nest_param_arg: // one_nest_param_arg
      case symbol_kind::S_nest_assign_list: // nest_assign_list
      case symbol_kind::S_nest_assign_single: // nest_assign_single
      case symbol_kind::S_action_arg_expression: // action_arg_expression
      case symbol_kind::S_act_args: // act_args
      case symbol_kind::S_target_value: // target_value
        yylhs.value.emplace<  nlohmann::json  > ();
        break;

      case symbol_kind::S_prop_item_cmp: // prop_item_cmp
      case symbol_kind::S_trigger_event_item: // trigger_event_item
      case symbol_kind::S_trigger_clock_item: // trigger_clock_item
      case symbol_kind::S_cond_day_item: // cond_day_item
      case symbol_kind::S_cond_between_item: // cond_between_item
        yylhs.value.emplace<  shared_ptr<cond_base>  > ();
        break;

      case symbol_kind::S_BOOL: // "BOOL"
        yylhs.value.emplace< bool > ();
        break;

      case symbol_kind::S_NUMBER: // "NUMBER"
        yylhs.value.emplace< int64_t > ();
        break;

      case symbol_kind::S_STRING: // "STRING"
      case symbol_kind::S_DID: // "did"
      case symbol_kind::S_IF: // "IF"
      case symbol_kind::S_THEN: // "THEN"
      case symbol_kind::S_ENDIF: // "ENDIF"
      case symbol_kind::S_AND: // "AND"
      case symbol_kind::S_OR: // "OR"
      case symbol_kind::S_COMPARATOR: // "comparator"
      case symbol_kind::S_ARG_INDEX: // "#arg"
      case symbol_kind::S_EXEC_SCENE: // "SCENE"
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: %empty
#line 156 "parser.y"
            {
                cout << "*** RUN ***" << endl;
                driver.clear();
            }
#line 804 "parser.cpp"
    break;

  case 3: // program: "IF" trigger_exp "THEN" action_expression "ENDIF"
#line 161 "parser.y"
            {
                yystack_[3].value.as <  RDL::condition_expression > ().set_in_trigger(true);
                driver.setTrigger(yystack_[3].value.as <  RDL::condition_expression > ());

                cout << "*** STOP RUN ***" << endl;
                cout << driver.str() << endl;
            }
#line 816 "parser.cpp"
    break;

  case 4: // program: "IF" trigger_exp "AND" trigger_exp "THEN" action_expression "ENDIF"
#line 170 "parser.y"
            {
                yystack_[5].value.as <  RDL::condition_expression > ().set_in_trigger(true);
                driver.setTrigger(yystack_[5].value.as <  RDL::condition_expression > ());

                yystack_[3].value.as <  RDL::condition_expression > ().set_in_trigger(false);
                driver.setCond(yystack_[3].value.as <  RDL::condition_expression > ());

                cout << "*** STOP RUN ***" << endl;
                cout << driver.str() << endl;
            }
#line 831 "parser.cpp"
    break;

  case 5: // trigger_exp: one_trigger
#line 182 "parser.y"
                          { yylhs.value.as <  RDL::condition_expression > () = yystack_[0].value.as <  RDL::condition_expression > (); }
#line 837 "parser.cpp"
    break;

  case 6: // trigger_exp: trigger_exp LOGIC_OPERATOR_AND one_trigger
#line 184 "parser.y"
                {   RDL::condition_expression exp;
                    exp.append(yystack_[2].value.as <  RDL::condition_expression > ());
                    exp.append(yystack_[0].value.as <  RDL::condition_expression > ());

                    RDL::cond_exp_operator op("&&");
                    exp.add( std::make_shared<cond_exp_operator>(op));
                    yylhs.value.as <  RDL::condition_expression > () = exp;
                }
#line 850 "parser.cpp"
    break;

  case 7: // trigger_exp: trigger_exp LOGIC_OPERATOR_OR one_trigger
#line 193 "parser.y"
                {   RDL::condition_expression exp;
                    exp.append(yystack_[2].value.as <  RDL::condition_expression > ());
                    exp.append(yystack_[0].value.as <  RDL::condition_expression > ());
                    RDL::cond_exp_operator op("||");
                    exp.add(std::make_shared<cond_exp_operator>(op));
                    yylhs.value.as <  RDL::condition_expression > () = exp;
                }
#line 862 "parser.cpp"
    break;

  case 8: // trigger_exp: "(" trigger_exp ")"
#line 200 "parser.y"
                                           { yylhs.value.as <  RDL::condition_expression > () = yystack_[1].value.as <  RDL::condition_expression > ();}
#line 868 "parser.cpp"
    break;

  case 9: // one_trigger: prop_item_cmp
#line 230 "parser.y"
                             { RDL::condition_expression exp; exp.add(yystack_[0].value.as <  shared_ptr<cond_base>  > ()); yylhs.value.as <  RDL::condition_expression > () = exp;}
#line 874 "parser.cpp"
    break;

  case 10: // one_trigger: trigger_event_item
#line 231 "parser.y"
                                 { RDL::condition_expression exp; exp.add(yystack_[0].value.as <  shared_ptr<cond_base>  > ()); yylhs.value.as <  RDL::condition_expression > () = exp;}
#line 880 "parser.cpp"
    break;

  case 11: // one_trigger: trigger_clock_item
#line 232 "parser.y"
                                 { RDL::condition_expression exp; exp.add(yystack_[0].value.as <  shared_ptr<cond_base>  > ()); yylhs.value.as <  RDL::condition_expression > () = exp;}
#line 886 "parser.cpp"
    break;

  case 12: // one_trigger: cond_day_item
#line 235 "parser.y"
                                 { RDL::condition_expression exp; exp.add(yystack_[0].value.as <  shared_ptr<cond_base>  > ()); yylhs.value.as <  RDL::condition_expression > () = exp;}
#line 892 "parser.cpp"
    break;

  case 13: // one_trigger: cond_between_item
#line 236 "parser.y"
                                 { RDL::condition_expression exp; exp.add(yystack_[0].value.as <  shared_ptr<cond_base>  > ()); yylhs.value.as <  RDL::condition_expression > () = exp;}
#line 898 "parser.cpp"
    break;

  case 14: // prop_item_cmp: "did" "comparator" target_value
#line 243 "parser.y"
                {
                    cond_prop prop(yystack_[2].value.as < std::string > (), yystack_[1].value.as < std::string > (), yystack_[0].value.as <  nlohmann::json  > ());
                    yylhs.value.as <  shared_ptr<cond_base>  > () = std::make_shared<cond_prop>(prop);
                }
#line 907 "parser.cpp"
    break;

  case 15: // trigger_event_item: "did" "comparator" "{" "}"
#line 251 "parser.y"
            {
                RDL::cond_event evt(yystack_[3].value.as < std::string > ());
                yylhs.value.as <  shared_ptr<cond_base>  > () = std::make_shared<cond_event>(evt);
            }
#line 916 "parser.cpp"
    break;

  case 16: // trigger_event_item: "did" "comparator" "{" action_arg_expression "}"
#line 256 "parser.y"
            {
                RDL::cond_event evt(yystack_[4].value.as < std::string > (), yystack_[3].value.as < std::string > (), yystack_[1].value.as <  nlohmann::json  > ());
                yylhs.value.as <  shared_ptr<cond_base>  > () = std::make_shared<cond_event>(evt);
            }
#line 925 "parser.cpp"
    break;

  case 17: // trigger_clock_item: "@clock" "comparator" "STRING"
#line 264 "parser.y"
                {
                    std::string s = remove_quotos(yystack_[0].value.as < std::string > ());
                    trigger_clock clk(s);
                    yylhs.value.as <  shared_ptr<cond_base>  > () = std::make_shared<trigger_clock>(clk);
                }
#line 935 "parser.cpp"
    break;

  case 18: // cond_day_item: "@day" "comparator" "STRING"
#line 272 "parser.y"
                {
                    std::string s = remove_quotos(yystack_[0].value.as < std::string > ());
                    cond_day day(s);
                    yylhs.value.as <  shared_ptr<cond_base>  > () = std::make_shared<cond_day>(day);
                }
#line 945 "parser.cpp"
    break;

  case 19: // cond_between_item: "@between" "comparator" "STRING"
#line 281 "parser.y"
                {
                    std::string s = remove_quotos(yystack_[0].value.as < std::string > ());
                    cond_between between(s);
                    yylhs.value.as <  shared_ptr<cond_base>  > () = std::make_shared<cond_between>(between);
                }
#line 955 "parser.cpp"
    break;

  case 22: // action: "did" "=>" target_value ";"
#line 295 "parser.y"
                {
                    rdl_exec_write_property p(yystack_[3].value.as < std::string > (), yystack_[1].value.as <  nlohmann::json  > ());
                    driver.addExec( std::make_shared<rdl_exec_write_property>(p) );
                    yylhs.value.as <  RDL::rdl_exec  > () = p;
                }
#line 965 "parser.cpp"
    break;

  case 23: // action: "SLEEP" "=>" "NUMBER" ";"
#line 301 "parser.y"
                {
                    rdl_exec_sleep s(yystack_[1].value.as < int64_t > ());
                    driver.addExec( std::make_shared<rdl_exec_sleep>(s) );
                    yylhs.value.as <  RDL::rdl_exec  > () = s;
                }
#line 975 "parser.cpp"
    break;

  case 24: // action: "SCENE" ";"
#line 307 "parser.y"
                {
                    std::string txt = yystack_[1].value.as < std::string > ();
                    size_t startPos = txt.find('{');
                    size_t endPos = txt.find('}');
                    std::string v = txt.substr( startPos + 1, endPos - startPos - 1 );

                    rdl_exec_scene s( std::stoul(v) );
                    driver.addExec( std::make_shared<rdl_exec_scene>(s) );
                    yylhs.value.as <  RDL::rdl_exec  > () = s;
                }
#line 990 "parser.cpp"
    break;

  case 25: // action: "did" ";"
#line 318 "parser.y"
                {
                    //action without args.
                    nlohmann::json empty;
                    rdl_exec_action_in a(yystack_[1].value.as < std::string > (), empty);
                    driver.addExec( std::make_shared<rdl_exec_action_in>(a) );
                    yylhs.value.as <  RDL::rdl_exec  > () = a;
                }
#line 1002 "parser.cpp"
    break;

  case 26: // action: "did" "=>" act_args ";"
#line 326 "parser.y"
                {
                    rdl_exec_action_in a(yystack_[3].value.as < std::string > (), yystack_[1].value.as <  nlohmann::json  > ());
                    driver.addExec( std::make_shared<rdl_exec_action_in>(a) );
                    yylhs.value.as <  RDL::rdl_exec  > () = a;
                }
#line 1012 "parser.cpp"
    break;

  case 27: // arg_value_list: target_value
#line 340 "parser.y"
        {
            yylhs.value.as <  nlohmann::json  > () = nlohmann::json::array( {yystack_[0].value.as <  nlohmann::json  > ()} );
        }
#line 1020 "parser.cpp"
    break;

  case 28: // arg_value_list: one_nest_param_arg
#line 344 "parser.y"
        {
            yylhs.value.as <  nlohmann::json  > () = nlohmann::json::array( {yystack_[0].value.as <  nlohmann::json  > ()} );
        }
#line 1028 "parser.cpp"
    break;

  case 29: // one_nest_param_arg: "(" nest_assign_list ")"
#line 358 "parser.y"
        {
            yylhs.value.as <  nlohmann::json  > () = yystack_[1].value.as <  nlohmann::json  > ();
        }
#line 1036 "parser.cpp"
    break;

  case 30: // nest_assign_list: nest_assign_single
#line 365 "parser.y"
        {
            nlohmann::json result = nlohmann::json::array( {yystack_[0].value.as <  nlohmann::json  > ()} );
            yylhs.value.as <  nlohmann::json  > () = result;
        }
#line 1045 "parser.cpp"
    break;

  case 31: // nest_assign_list: nest_assign_list "," nest_assign_single
#line 370 "parser.y"
        {
            yystack_[2].value.as <  nlohmann::json  > ().push_back(yystack_[0].value.as <  nlohmann::json  > ());
            yylhs.value.as <  nlohmann::json  > () = yystack_[2].value.as <  nlohmann::json  > ();
        }
#line 1054 "parser.cpp"
    break;

  case 32: // nest_assign_single: "#arg" ":" target_value
#line 378 "parser.y"
    {
        nlohmann::json result;
        std::string piid = yystack_[2].value.as < std::string > ().substr(1); //remove the begining '#'
        result["piid"] = piid;
        result["value"] = yystack_[0].value.as <  nlohmann::json  > ();
        yylhs.value.as <  nlohmann::json  > () = result;
    }
#line 1066 "parser.cpp"
    break;

  case 33: // action_arg_expression: "#arg" "=" arg_value_list
#line 393 "parser.y"
        {
            nlohmann::json result;
            std::string piid = yystack_[2].value.as < std::string > ().substr(1); //remove the begining '#'
            result["piid"] = piid;
            result["value"] = yystack_[0].value.as <  nlohmann::json  > ();
            yylhs.value.as <  nlohmann::json  > () = result;
        }
#line 1078 "parser.cpp"
    break;

  case 34: // act_args: action_arg_expression
#line 407 "parser.y"
        {
            yylhs.value.as <  nlohmann::json  > () = nlohmann::json::array({yystack_[0].value.as <  nlohmann::json  > ()});
        }
#line 1086 "parser.cpp"
    break;

  case 35: // act_args: act_args "," action_arg_expression
#line 411 "parser.y"
        {
            yystack_[2].value.as <  nlohmann::json  > ().push_back(yystack_[0].value.as <  nlohmann::json  > ());
            yylhs.value.as <  nlohmann::json  > () = yystack_[2].value.as <  nlohmann::json  > ();
        }
#line 1095 "parser.cpp"
    break;

  case 36: // target_value: "NUMBER"
#line 419 "parser.y"
                     { nlohmann::json v = yystack_[0].value.as < int64_t > ();  yylhs.value.as <  nlohmann::json  > () = v; }
#line 1101 "parser.cpp"
    break;

  case 37: // target_value: "STRING"
#line 420 "parser.y"
                   {
                     std::string content(yystack_[0].value.as < std::string > ());
                     cout << "!!! string length()=" << content.length() << std::endl;
                     if(content.length() >= 2) {
                        content = content.substr(1, content.length()-2);  //remove "", only keep the content.
                     }
                     nlohmann::json v = content;
                     yylhs.value.as <  nlohmann::json  > () = v;
                    }
#line 1115 "parser.cpp"
    break;

  case 38: // target_value: "BOOL"
#line 429 "parser.y"
                   { nlohmann::json v = yystack_[0].value.as < bool > ();  yylhs.value.as <  nlohmann::json  > () = v; }
#line 1121 "parser.cpp"
    break;

  case 39: // target_value: "any"
#line 430 "parser.y"
                      { nlohmann::json v;  yylhs.value.as <  nlohmann::json  > () = v; }
#line 1127 "parser.cpp"
    break;


#line 1131 "parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
   Parser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   Parser ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
   Parser ::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  //  Parser ::context.
   Parser ::context::context (const  Parser & yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
   Parser ::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
   Parser ::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
   Parser ::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char  Parser ::yypact_ninf_ = -47;

  const signed char  Parser ::yytable_ninf_ = -1;

  const signed char
   Parser ::yypact_[] =
  {
      15,    21,     6,    18,    30,    54,    55,    21,    -1,   -47,
     -47,   -47,   -47,   -47,   -47,   -47,    -2,    69,    73,    74,
      44,    41,    21,     5,     5,   -47,   -47,   -47,   -47,    31,
     -47,   -47,   -47,   -47,   -47,    45,    57,    29,    37,   -47,
       2,   -47,   -47,    65,   -47,    53,    36,   -47,    77,   -47,
     -47,   -47,    41,    10,   -47,   -47,   -10,    56,    58,    39,
      62,   -47,   -47,   -47,    63,   -47,   -47,   -47,   -47,    59,
       0,   -47,   -47,    49,    62,   -47,   -47,   -47
  };

  const signed char
   Parser ::yydefact_[] =
  {
       2,     0,     0,     0,     0,     0,     0,     0,     0,     5,
       9,    10,    11,    12,    13,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,    36,    38,    39,     0,
      14,    17,    18,    19,     8,     0,     0,     0,     0,    20,
       0,     6,     7,     0,    15,     0,     0,    25,     0,    24,
       3,    21,     0,     0,    16,    34,     0,     0,     0,     0,
       0,    33,    28,    27,     0,    26,    22,    23,     4,     0,
       0,    30,    35,     0,     0,    29,    32,    31
  };

  const signed char
   Parser ::yypgoto_[] =
  {
     -47,   -47,    43,    47,   -47,   -47,   -47,   -47,   -47,    33,
     -33,   -47,   -47,   -47,    13,   -29,   -47,   -46
  };

  const signed char
   Parser ::yydefgoto_[] =
  {
       0,     2,     8,     9,    10,    11,    12,    13,    14,    38,
      39,    61,    62,    70,    71,    45,    56,    30
  };

  const signed char
   Parser ::yytable_[] =
  {
      57,    25,    26,    27,    28,    51,    15,    63,    21,    64,
      22,    52,     3,    25,    26,    27,    28,    55,    65,    74,
       4,     5,     6,     1,    29,    75,    51,    76,     3,    23,
      24,    16,    23,    24,    60,    72,     4,     5,     6,    25,
      26,    27,    28,    17,    35,     7,    35,    50,    35,    68,
      20,    43,    25,    26,    27,    28,    43,    49,    44,    36,
      37,    36,    37,    36,    37,    40,    46,    18,    19,    34,
      41,    42,    31,    47,    23,    24,    32,    33,    48,    53,
      54,    58,    69,    43,    66,    59,    67,    77,    73
  };

  const signed char
   Parser ::yycheck_[] =
  {
      46,     3,     4,     5,     6,    38,     0,    53,     9,    19,
      11,     9,     7,     3,     4,     5,     6,    46,    28,    19,
      15,    16,    17,     8,    26,    25,    59,    73,     7,    30,
      31,    13,    30,    31,    24,    64,    15,    16,    17,     3,
       4,     5,     6,    13,     7,    24,     7,    10,     7,    10,
       7,    20,     3,     4,     5,     6,    20,    28,    27,    22,
      23,    22,    23,    22,    23,    22,    21,    13,    13,    25,
      23,    24,     3,    28,    30,    31,     3,     3,    21,    14,
      27,     4,    20,    20,    28,    52,    28,    74,    29
  };

  const signed char
   Parser ::yystos_[] =
  {
       0,     8,    35,     7,    15,    16,    17,    24,    36,    37,
      38,    39,    40,    41,    42,     0,    13,    13,    13,    13,
      36,     9,    11,    30,    31,     3,     4,     5,     6,    26,
      51,     3,     3,     3,    25,     7,    22,    23,    43,    44,
      36,    37,    37,    20,    27,    49,    21,    28,    21,    28,
      10,    44,     9,    14,    27,    49,    50,    51,     4,    43,
      24,    45,    46,    51,    19,    28,    28,    28,    10,    20,
      47,    48,    49,    29,    19,    25,    51,    48
  };

  const signed char
   Parser ::yyr1_[] =
  {
       0,    34,    35,    35,    35,    36,    36,    36,    36,    37,
      37,    37,    37,    37,    38,    39,    39,    40,    41,    42,
      43,    43,    44,    44,    44,    44,    44,    45,    45,    46,
      47,    47,    48,    49,    50,    50,    51,    51,    51,    51
  };

  const signed char
   Parser ::yyr2_[] =
  {
       0,     2,     0,     5,     7,     1,     3,     3,     3,     1,
       1,     1,     1,     1,     3,     4,     5,     3,     3,     3,
       1,     2,     4,     4,     2,     2,     4,     1,     1,     3,
       1,     3,     3,     3,     1,     3,     1,     1,     1,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const  Parser ::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"STRING\"",
  "\"NUMBER\"", "\"BOOL\"", "\"any\"", "\"did\"", "\"IF\"", "\"THEN\"",
  "\"ENDIF\"", "\"AND\"", "\"OR\"", "\"comparator\"", "\"=\"",
  "\"@clock\"", "\"@day\"", "\"@between\"", "\"@someday\"", "\",\"",
  "\"#arg\"", "\"=>\"", "\"SLEEP\"", "\"SCENE\"", "\"(\"", "\")\"",
  "\"{\"", "\"}\"", "\";\"", "\":\"", "LOGIC_OPERATOR_AND",
  "LOGIC_OPERATOR_OR", "VALUE_DELIM", "EXPRESSION_DELIM", "$accept",
  "program", "trigger_exp", "one_trigger", "prop_item_cmp",
  "trigger_event_item", "trigger_clock_item", "cond_day_item",
  "cond_between_item", "action_expression", "action", "arg_value_list",
  "one_nest_param_arg", "nest_assign_list", "nest_assign_single",
  "action_arg_expression", "act_args", "target_value", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
   Parser ::yyrline_[] =
  {
       0,   156,   156,   160,   169,   182,   183,   192,   200,   230,
     231,   232,   235,   236,   242,   250,   255,   263,   271,   280,
     289,   290,   294,   300,   306,   317,   325,   339,   343,   357,
     364,   369,   377,   392,   406,   410,   419,   420,   429,   430
  };

  void
   Parser ::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
   Parser ::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 14 "parser.y"
} //  RDL 
#line 1649 "parser.cpp"

#line 433 "parser.y"


// ... (error function remains the same) ...
// Bison expects us to provide implementation - otherwise linker complains
void RDL::Parser::error(const location &loc , const std::string &message) {

        // Location should be initialized inside scanner action, but is not in this example.
        // Let's grab location directly from driver class.
	// cout << "Error: " << message << endl << "Location: " << loc << endl;

        cout << "Error: " << message << endl << "Error location: " << driver.location() << endl;
}
