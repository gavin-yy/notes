// A Bison parser, made by GNU Bison 3.8.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file parser.hpp
 ** Define the  RDL ::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
// "%code requires" blocks.
#line 16 "parser.y"

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

#line 72 "parser.hpp"

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"
#include <typeinfo>
#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 14 "parser.y"
namespace  RDL  {
#line 213 "parser.hpp"




  /// A Bison parser.
  class  Parser 
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {
      YY_ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // trigger_exp
      // one_trigger
      char dummy1[sizeof ( RDL::condition_expression)];

      // action
      char dummy2[sizeof ( RDL::rdl_exec )];

      // arg_value_list
      // one_nest_param_arg
      // nest_assign_list
      // nest_assign_single
      // action_arg_expression
      // act_args
      // target_value
      char dummy3[sizeof ( nlohmann::json )];

      // prop_item_cmp
      // trigger_event_item
      // trigger_clock_item
      // cond_day_item
      // cond_between_item
      char dummy4[sizeof ( shared_ptr<cond_base> )];

      // "BOOL"
      char dummy5[sizeof (bool)];

      // "NUMBER"
      char dummy6[sizeof (int64_t)];

      // "STRING"
      // "did"
      // "IF"
      // "THEN"
      // "ENDIF"
      // "AND"
      // "OR"
      // "comparator"
      // "#arg"
      // "SCENE"
      char dummy7[sizeof (std::string)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        TOKEN_YYEMPTY = -2,
    TOKEN_END = 0,                 // "end of file"
    TOKEN_YYerror = 256,           // error
    TOKEN_YYUNDEF = 257,           // "invalid token"
    TOKEN_STRING = 258,            // "STRING"
    TOKEN_NUMBER = 259,            // "NUMBER"
    TOKEN_BOOL = 260,              // "BOOL"
    TOKEN_VALUE_ANY = 261,         // "any"
    TOKEN_DID = 262,               // "did"
    TOKEN_IF = 263,                // "IF"
    TOKEN_THEN = 264,              // "THEN"
    TOKEN_ENDIF = 265,             // "ENDIF"
    TOKEN_AND = 266,               // "AND"
    TOKEN_OR = 267,                // "OR"
    TOKEN_COMPARATOR = 268,        // "comparator"
    TOKEN_ASSIGN = 269,            // "="
    TOKEN_AT_CLOCK = 270,          // "@clock"
    TOKEN_AT_DAY = 271,            // "@day"
    TOKEN_AT_BETWEEN = 272,        // "@between"
    TOKEN_AT_SOMEDAY = 273,        // "@someday"
    TOKEN_COMMA = 274,             // ","
    TOKEN_ARG_INDEX = 275,         // "#arg"
    TOKEN_SET_TARGET = 276,        // "=>"
    TOKEN_EXEC_SLEEP = 277,        // "SLEEP"
    TOKEN_EXEC_SCENE = 278,        // "SCENE"
    TOKEN_LEFTPAR = 279,           // "("
    TOKEN_RIGHTPAR = 280,          // ")"
    TOKEN_LEFTBRACE = 281,         // "{"
    TOKEN_RIGHTBRACE = 282,        // "}"
    TOKEN_SEMICOLON = 283,         // ";"
    TOKEN_COLON = 284,             // ":"
    TOKEN_LOGIC_OPERATOR_AND = 285, // LOGIC_OPERATOR_AND
    TOKEN_LOGIC_OPERATOR_OR = 286, // LOGIC_OPERATOR_OR
    TOKEN_VALUE_DELIM = 287,       // VALUE_DELIM
    TOKEN_EXPRESSION_DELIM = 288   // EXPRESSION_DELIM
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::yytokentype token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 34, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_STRING = 3,                            // "STRING"
        S_NUMBER = 4,                            // "NUMBER"
        S_BOOL = 5,                              // "BOOL"
        S_VALUE_ANY = 6,                         // "any"
        S_DID = 7,                               // "did"
        S_IF = 8,                                // "IF"
        S_THEN = 9,                              // "THEN"
        S_ENDIF = 10,                            // "ENDIF"
        S_AND = 11,                              // "AND"
        S_OR = 12,                               // "OR"
        S_COMPARATOR = 13,                       // "comparator"
        S_ASSIGN = 14,                           // "="
        S_AT_CLOCK = 15,                         // "@clock"
        S_AT_DAY = 16,                           // "@day"
        S_AT_BETWEEN = 17,                       // "@between"
        S_AT_SOMEDAY = 18,                       // "@someday"
        S_COMMA = 19,                            // ","
        S_ARG_INDEX = 20,                        // "#arg"
        S_SET_TARGET = 21,                       // "=>"
        S_EXEC_SLEEP = 22,                       // "SLEEP"
        S_EXEC_SCENE = 23,                       // "SCENE"
        S_LEFTPAR = 24,                          // "("
        S_RIGHTPAR = 25,                         // ")"
        S_LEFTBRACE = 26,                        // "{"
        S_RIGHTBRACE = 27,                       // "}"
        S_SEMICOLON = 28,                        // ";"
        S_COLON = 29,                            // ":"
        S_LOGIC_OPERATOR_AND = 30,               // LOGIC_OPERATOR_AND
        S_LOGIC_OPERATOR_OR = 31,                // LOGIC_OPERATOR_OR
        S_VALUE_DELIM = 32,                      // VALUE_DELIM
        S_EXPRESSION_DELIM = 33,                 // EXPRESSION_DELIM
        S_YYACCEPT = 34,                         // $accept
        S_program = 35,                          // program
        S_trigger_exp = 36,                      // trigger_exp
        S_one_trigger = 37,                      // one_trigger
        S_prop_item_cmp = 38,                    // prop_item_cmp
        S_trigger_event_item = 39,               // trigger_event_item
        S_trigger_clock_item = 40,               // trigger_clock_item
        S_cond_day_item = 41,                    // cond_day_item
        S_cond_between_item = 42,                // cond_between_item
        S_action_expression = 43,                // action_expression
        S_action = 44,                           // action
        S_arg_value_list = 45,                   // arg_value_list
        S_one_nest_param_arg = 46,               // one_nest_param_arg
        S_nest_assign_list = 47,                 // nest_assign_list
        S_nest_assign_single = 48,               // nest_assign_single
        S_action_arg_expression = 49,            // action_arg_expression
        S_act_args = 50,                         // act_args
        S_target_value = 51                      // target_value
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_trigger_exp: // trigger_exp
      case symbol_kind::S_one_trigger: // one_trigger
        value.move<  RDL::condition_expression > (std::move (that.value));
        break;

      case symbol_kind::S_action: // action
        value.move<  RDL::rdl_exec  > (std::move (that.value));
        break;

      case symbol_kind::S_arg_value_list: // arg_value_list
      case symbol_kind::S_one_nest_param_arg: // one_nest_param_arg
      case symbol_kind::S_nest_assign_list: // nest_assign_list
      case symbol_kind::S_nest_assign_single: // nest_assign_single
      case symbol_kind::S_action_arg_expression: // action_arg_expression
      case symbol_kind::S_act_args: // act_args
      case symbol_kind::S_target_value: // target_value
        value.move<  nlohmann::json  > (std::move (that.value));
        break;

      case symbol_kind::S_prop_item_cmp: // prop_item_cmp
      case symbol_kind::S_trigger_event_item: // trigger_event_item
      case symbol_kind::S_trigger_clock_item: // trigger_clock_item
      case symbol_kind::S_cond_day_item: // cond_day_item
      case symbol_kind::S_cond_between_item: // cond_between_item
        value.move<  shared_ptr<cond_base>  > (std::move (that.value));
        break;

      case symbol_kind::S_BOOL: // "BOOL"
        value.move< bool > (std::move (that.value));
        break;

      case symbol_kind::S_NUMBER: // "NUMBER"
        value.move< int64_t > (std::move (that.value));
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
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t,  RDL::condition_expression&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const  RDL::condition_expression& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t,  RDL::rdl_exec && v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const  RDL::rdl_exec & v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t,  nlohmann::json && v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const  nlohmann::json & v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t,  shared_ptr<cond_base> && v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const  shared_ptr<cond_base> & v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, bool&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const bool& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, int64_t&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const int64_t& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_trigger_exp: // trigger_exp
      case symbol_kind::S_one_trigger: // one_trigger
        value.template destroy<  RDL::condition_expression > ();
        break;

      case symbol_kind::S_action: // action
        value.template destroy<  RDL::rdl_exec  > ();
        break;

      case symbol_kind::S_arg_value_list: // arg_value_list
      case symbol_kind::S_one_nest_param_arg: // one_nest_param_arg
      case symbol_kind::S_nest_assign_list: // nest_assign_list
      case symbol_kind::S_nest_assign_single: // nest_assign_single
      case symbol_kind::S_action_arg_expression: // action_arg_expression
      case symbol_kind::S_act_args: // act_args
      case symbol_kind::S_target_value: // target_value
        value.template destroy<  nlohmann::json  > ();
        break;

      case symbol_kind::S_prop_item_cmp: // prop_item_cmp
      case symbol_kind::S_trigger_event_item: // trigger_event_item
      case symbol_kind::S_trigger_clock_item: // trigger_clock_item
      case symbol_kind::S_cond_day_item: // cond_day_item
      case symbol_kind::S_cond_between_item: // cond_between_item
        value.template destroy<  shared_ptr<cond_base>  > ();
        break;

      case symbol_kind::S_BOOL: // "BOOL"
        value.template destroy< bool > ();
        break;

      case symbol_kind::S_NUMBER: // "NUMBER"
        value.template destroy< int64_t > ();
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
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return  Parser ::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// Default constructor.
      by_kind ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that);
#endif

      /// Copy constructor.
      by_kind (const by_kind& that);

      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t);

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type (token_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type (token_type (tok), l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::TOKEN_END
                   || (token::TOKEN_YYerror <= tok && tok <= token::TOKEN_YYUNDEF)
                   || tok == token::TOKEN_VALUE_ANY
                   || (token::TOKEN_ASSIGN <= tok && tok <= token::TOKEN_COMMA)
                   || (token::TOKEN_SET_TARGET <= tok && tok <= token::TOKEN_EXEC_SLEEP)
                   || (token::TOKEN_LEFTPAR <= tok && tok <= token::TOKEN_EXPRESSION_DELIM));
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, bool v, location_type l)
        : super_type (token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const bool& v, const location_type& l)
        : super_type (token_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::TOKEN_BOOL);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, int64_t v, location_type l)
        : super_type (token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const int64_t& v, const location_type& l)
        : super_type (token_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::TOKEN_NUMBER);
#endif
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type (token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type (token_type (tok), v, l)
#endif
      {
#if !defined _MSC_VER || defined __clang__
        YY_ASSERT (tok == token::TOKEN_STRING
                   || (token::TOKEN_DID <= tok && tok <= token::TOKEN_COMPARATOR)
                   || tok == token::TOKEN_ARG_INDEX
                   || tok == token::TOKEN_EXEC_SCENE);
#endif
      }
    };

    /// Build a parser object.
     Parser  (RDL::Scanner &scanner_yyarg, RDL::Interpreter &driver_yyarg);
    virtual ~ Parser  ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
     Parser  (const  Parser &) = delete;
    /// Non copyable.
     Parser & operator= (const  Parser &) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END (location_type l)
      {
        return symbol_type (token::TOKEN_END, std::move (l));
      }
#else
      static
      symbol_type
      make_END (const location_type& l)
      {
        return symbol_type (token::TOKEN_END, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::TOKEN_YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::TOKEN_YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::TOKEN_YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::TOKEN_YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_STRING, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_STRING (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_STRING, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NUMBER (int64_t v, location_type l)
      {
        return symbol_type (token::TOKEN_NUMBER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_NUMBER (const int64_t& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_NUMBER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BOOL (bool v, location_type l)
      {
        return symbol_type (token::TOKEN_BOOL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BOOL (const bool& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_BOOL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VALUE_ANY (location_type l)
      {
        return symbol_type (token::TOKEN_VALUE_ANY, std::move (l));
      }
#else
      static
      symbol_type
      make_VALUE_ANY (const location_type& l)
      {
        return symbol_type (token::TOKEN_VALUE_ANY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DID (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_DID, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DID (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_DID, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_IF, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IF (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_IF, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_THEN (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_THEN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_THEN (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_THEN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENDIF (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_ENDIF, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ENDIF (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_ENDIF, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_AND, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_AND (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_AND, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_OR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_OR (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_OR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMPARATOR (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_COMPARATOR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_COMPARATOR (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_COMPARATOR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN (location_type l)
      {
        return symbol_type (token::TOKEN_ASSIGN, std::move (l));
      }
#else
      static
      symbol_type
      make_ASSIGN (const location_type& l)
      {
        return symbol_type (token::TOKEN_ASSIGN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AT_CLOCK (location_type l)
      {
        return symbol_type (token::TOKEN_AT_CLOCK, std::move (l));
      }
#else
      static
      symbol_type
      make_AT_CLOCK (const location_type& l)
      {
        return symbol_type (token::TOKEN_AT_CLOCK, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AT_DAY (location_type l)
      {
        return symbol_type (token::TOKEN_AT_DAY, std::move (l));
      }
#else
      static
      symbol_type
      make_AT_DAY (const location_type& l)
      {
        return symbol_type (token::TOKEN_AT_DAY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AT_BETWEEN (location_type l)
      {
        return symbol_type (token::TOKEN_AT_BETWEEN, std::move (l));
      }
#else
      static
      symbol_type
      make_AT_BETWEEN (const location_type& l)
      {
        return symbol_type (token::TOKEN_AT_BETWEEN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AT_SOMEDAY (location_type l)
      {
        return symbol_type (token::TOKEN_AT_SOMEDAY, std::move (l));
      }
#else
      static
      symbol_type
      make_AT_SOMEDAY (const location_type& l)
      {
        return symbol_type (token::TOKEN_AT_SOMEDAY, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (location_type l)
      {
        return symbol_type (token::TOKEN_COMMA, std::move (l));
      }
#else
      static
      symbol_type
      make_COMMA (const location_type& l)
      {
        return symbol_type (token::TOKEN_COMMA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ARG_INDEX (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_ARG_INDEX, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ARG_INDEX (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_ARG_INDEX, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SET_TARGET (location_type l)
      {
        return symbol_type (token::TOKEN_SET_TARGET, std::move (l));
      }
#else
      static
      symbol_type
      make_SET_TARGET (const location_type& l)
      {
        return symbol_type (token::TOKEN_SET_TARGET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXEC_SLEEP (location_type l)
      {
        return symbol_type (token::TOKEN_EXEC_SLEEP, std::move (l));
      }
#else
      static
      symbol_type
      make_EXEC_SLEEP (const location_type& l)
      {
        return symbol_type (token::TOKEN_EXEC_SLEEP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXEC_SCENE (std::string v, location_type l)
      {
        return symbol_type (token::TOKEN_EXEC_SCENE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_EXEC_SCENE (const std::string& v, const location_type& l)
      {
        return symbol_type (token::TOKEN_EXEC_SCENE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LEFTPAR (location_type l)
      {
        return symbol_type (token::TOKEN_LEFTPAR, std::move (l));
      }
#else
      static
      symbol_type
      make_LEFTPAR (const location_type& l)
      {
        return symbol_type (token::TOKEN_LEFTPAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RIGHTPAR (location_type l)
      {
        return symbol_type (token::TOKEN_RIGHTPAR, std::move (l));
      }
#else
      static
      symbol_type
      make_RIGHTPAR (const location_type& l)
      {
        return symbol_type (token::TOKEN_RIGHTPAR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LEFTBRACE (location_type l)
      {
        return symbol_type (token::TOKEN_LEFTBRACE, std::move (l));
      }
#else
      static
      symbol_type
      make_LEFTBRACE (const location_type& l)
      {
        return symbol_type (token::TOKEN_LEFTBRACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RIGHTBRACE (location_type l)
      {
        return symbol_type (token::TOKEN_RIGHTBRACE, std::move (l));
      }
#else
      static
      symbol_type
      make_RIGHTBRACE (const location_type& l)
      {
        return symbol_type (token::TOKEN_RIGHTBRACE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEMICOLON (location_type l)
      {
        return symbol_type (token::TOKEN_SEMICOLON, std::move (l));
      }
#else
      static
      symbol_type
      make_SEMICOLON (const location_type& l)
      {
        return symbol_type (token::TOKEN_SEMICOLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COLON (location_type l)
      {
        return symbol_type (token::TOKEN_COLON, std::move (l));
      }
#else
      static
      symbol_type
      make_COLON (const location_type& l)
      {
        return symbol_type (token::TOKEN_COLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOGIC_OPERATOR_AND (location_type l)
      {
        return symbol_type (token::TOKEN_LOGIC_OPERATOR_AND, std::move (l));
      }
#else
      static
      symbol_type
      make_LOGIC_OPERATOR_AND (const location_type& l)
      {
        return symbol_type (token::TOKEN_LOGIC_OPERATOR_AND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOGIC_OPERATOR_OR (location_type l)
      {
        return symbol_type (token::TOKEN_LOGIC_OPERATOR_OR, std::move (l));
      }
#else
      static
      symbol_type
      make_LOGIC_OPERATOR_OR (const location_type& l)
      {
        return symbol_type (token::TOKEN_LOGIC_OPERATOR_OR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VALUE_DELIM (location_type l)
      {
        return symbol_type (token::TOKEN_VALUE_DELIM, std::move (l));
      }
#else
      static
      symbol_type
      make_VALUE_DELIM (const location_type& l)
      {
        return symbol_type (token::TOKEN_VALUE_DELIM, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXPRESSION_DELIM (location_type l)
      {
        return symbol_type (token::TOKEN_EXPRESSION_DELIM, std::move (l));
      }
#else
      static
      symbol_type
      make_EXPRESSION_DELIM (const location_type& l)
      {
        return symbol_type (token::TOKEN_EXPRESSION_DELIM, l);
      }
#endif


    class context
    {
    public:
      context (const  Parser & yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const  Parser & yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
     Parser  (const  Parser &);
    /// Non copyable.
     Parser & operator= (const  Parser &);
#endif


    /// Stored state numbers (used for stacks).
    typedef signed char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static symbol_kind_type yytranslate_ (int t);

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const signed char yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const signed char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const signed char yytable_[];

    static const signed char yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yylast_ = 88,     ///< Last index in yytable_.
      yynnts_ = 18,  ///< Number of nonterminal symbols.
      yyfinal_ = 15 ///< Termination state number.
    };


    // User arguments.
    RDL::Scanner &scanner;
    RDL::Interpreter &driver;

  };

  inline
   Parser ::symbol_kind_type
   Parser ::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33
    };
    // Last valid token kind.
    const int code_max = 288;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
   Parser ::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_trigger_exp: // trigger_exp
      case symbol_kind::S_one_trigger: // one_trigger
        value.copy<  RDL::condition_expression > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_action: // action
        value.copy<  RDL::rdl_exec  > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_arg_value_list: // arg_value_list
      case symbol_kind::S_one_nest_param_arg: // one_nest_param_arg
      case symbol_kind::S_nest_assign_list: // nest_assign_list
      case symbol_kind::S_nest_assign_single: // nest_assign_single
      case symbol_kind::S_action_arg_expression: // action_arg_expression
      case symbol_kind::S_act_args: // act_args
      case symbol_kind::S_target_value: // target_value
        value.copy<  nlohmann::json  > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_prop_item_cmp: // prop_item_cmp
      case symbol_kind::S_trigger_event_item: // trigger_event_item
      case symbol_kind::S_trigger_clock_item: // trigger_clock_item
      case symbol_kind::S_cond_day_item: // cond_day_item
      case symbol_kind::S_cond_between_item: // cond_between_item
        value.copy<  shared_ptr<cond_base>  > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOL: // "BOOL"
        value.copy< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "NUMBER"
        value.copy< int64_t > (YY_MOVE (that.value));
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
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
   Parser ::symbol_kind_type
   Parser ::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
   Parser ::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
   Parser ::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_trigger_exp: // trigger_exp
      case symbol_kind::S_one_trigger: // one_trigger
        value.move<  RDL::condition_expression > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_action: // action
        value.move<  RDL::rdl_exec  > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_arg_value_list: // arg_value_list
      case symbol_kind::S_one_nest_param_arg: // one_nest_param_arg
      case symbol_kind::S_nest_assign_list: // nest_assign_list
      case symbol_kind::S_nest_assign_single: // nest_assign_single
      case symbol_kind::S_action_arg_expression: // action_arg_expression
      case symbol_kind::S_act_args: // act_args
      case symbol_kind::S_target_value: // target_value
        value.move<  nlohmann::json  > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_prop_item_cmp: // prop_item_cmp
      case symbol_kind::S_trigger_event_item: // trigger_event_item
      case symbol_kind::S_trigger_clock_item: // trigger_clock_item
      case symbol_kind::S_cond_day_item: // cond_day_item
      case symbol_kind::S_cond_between_item: // cond_between_item
        value.move<  shared_ptr<cond_base>  > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_BOOL: // "BOOL"
        value.move< bool > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_NUMBER: // "NUMBER"
        value.move< int64_t > (YY_MOVE (s.value));
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
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
   Parser ::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
   Parser ::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
   Parser ::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  inline
   Parser ::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  inline
  void
   Parser ::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
   Parser ::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
   Parser ::symbol_kind_type
   Parser ::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  inline
   Parser ::symbol_kind_type
   Parser ::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

#line 14 "parser.y"
} //  RDL 
#line 2189 "parser.hpp"




#endif // !YY_YY_PARSER_HPP_INCLUDED
