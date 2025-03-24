#include <art/query/logical-and.hxx>
#include <art/query/logical-not.hxx>
#include <art/query/logical-or.hxx>
#include <art/query/parenthesized.hxx>
#include <art/query/syntactical-analyzer.hxx>
#include <art/query/tag.hxx>
#include <art/query/term.hxx>

namespace art::query
{

  syntactical_analyzer_t::
  syntactical_analyzer_t(lexical_analyzer_t& lexer,
                         parse_context_t& context)
    : lexer_{lexer},
      context_{context}
  {}

  lexical_analyzer_t&
  syntactical_analyzer_t::
  lexer()
  {
    return lexer_;
  }

  parse_context_t&
  syntactical_analyzer_t::
  context()
  {
    return context_;
  }

  query_t
  syntactical_analyzer_t::
  try_parse()
  {
    auto expr = try_parse_expression();

    if (expr) {
      auto last = lexer().peek();

      if (last.type() != token_type_t::end) {
        context().report_warning({{}, "trailing token at end of query"});
      }
    }

    return query_t{
      std::move(expr),
      context().warnings(),
      context().errors()
    };
  }

  optional<expression_t>
  syntactical_analyzer_t::
  try_parse_primary_expression()
  {
    optional<expression_t> expr;

    for (;;) {
      auto t = lexer().peek();

      if (t.type() == token_type_t::end) {
        break;
      }

      else if (t.type() == token_type_t::logical_not) {
        lexer().consume();

        auto rhs = try_parse_primary_expression();

        if (!rhs) {
          context().report_warning({{}, "expected expression after NOT"});
          break;
        }

        if (expr) {
          expr = logical_and_t{
            {}, *expr, logical_not_t{{}, *rhs}
          };
        }
        else {
          expr = logical_not_t{{}, *rhs};
        }
      }

      else if (t.type() == token_type_t::simple_term) {
        lexer().consume();

        // If the next token is a ':' then this is a tag.
        //
        if (lexer().peek().type() == token_type_t::colon) {
          lexer().consume();

          // consume trailing colons as well.
          //
          while (lexer().peek().type() == token_type_t::colon) {
            lexer().consume();
          }

          auto identifier = *t.value();

          // Next expect a term or quoted term.
          //
          t = lexer().peek();

          if (t.type() != token_type_t::simple_term &&
              t.type() != token_type_t::quoted_term) {
            context().report_warning({{}, "expected simple-term or quoted-term after tag" });
            lexer().consume();
            continue;
          }

          lexer().consume();

          // Construct the term
          //
          term_t term{
            {},
            t.type() == token_type_t::simple_term ? term_t::simple : term_t::quoted,
            *t.value()
          };

          if (expr) {
            expr = logical_or_t{
              {}, *expr, tag_t{{}, std::move(identifier), std::move(term)}
            };
          }
          else {
            expr = tag_t{{}, std::move(identifier), std::move(term)};
          }
        }
        else if (expr) {
          expr = logical_or_t{
            {}, *expr, term_t{{}, term_t::simple, *t.value()}
          };
        }
        else {
          expr = term_t{{}, term_t::simple, *t.value()};
        }
      }

      else if (t.type() == token_type_t::quoted_term) {
        if (expr) {
          expr = logical_or_t{
            {}, *expr, term_t{{}, term_t::quoted, *t.value()}
          };
        }
        else {
          expr = term_t{{}, term_t::quoted, *t.value()};
        }

        lexer().consume();
      }

      else if (t.type() == token_type_t::open_parens) {
        lexer().consume();

        t = lexer().peek();

        if (t.type() == token_type_t::close_parens) {
          lexer().consume();
          continue;
        }

        auto next_expr = try_parse_expression();

        if (!next_expr) {
          context().report_warning({{}, "expected expression inside parenthesis"});
          lexer().consume();
          continue;
        }

        next_expr = parenthesized_t{{}, *next_expr};

        if (expr) {
          expr = logical_or_t{{}, *expr, *next_expr};
        }
        else {
          expr = next_expr;
        }

        t = lexer().peek();
        if (t.type() != token_type_t::close_parens) {
          context().report_warning({{}, "expected end parenthesis"});
          lexer().consume();
          continue;
        }

        lexer().consume();
      }

      else {
        break;
      }
    }

    return expr;
  }

  optional<expression_t>
  syntactical_analyzer_t::
  try_parse_logical_and()
  {
    auto lhs = try_parse_primary_expression();

    if (!lhs) {
      return nullopt;
    }

    while (lexer().peek().type() == token_type_t::logical_and) {
      lexer().consume();
      auto rhs = try_parse_primary_expression();

      if (!rhs) {
        context().report_warning({{}, "expected expression after AND"});
        return lhs;
      }

      lhs = logical_and_t{{}, *lhs, *rhs};
    }

    return lhs;
  }

  optional<expression_t>
  syntactical_analyzer_t::
  try_parse_logical_or()
  {
    auto lhs = try_parse_logical_and();

    if (!lhs)
      return nullopt;

    while (lexer().peek().type() == token_type_t::logical_or) {
      lexer().consume();
      auto rhs = try_parse_logical_and();

      if (!rhs)
        return nullopt;

      lhs = logical_or_t{{}, *lhs, *rhs};
    }

    return lhs;
  }

  optional<expression_t>
  syntactical_analyzer_t::
  try_parse_expression()
  {
    auto invalid =  [](token_t const& token)
    {
      if (token.type() == token_type_t::end) {
        return false;
      }

      if (token.type() == token_type_t::simple_term) {
        return false;
      }

      if (token.type() == token_type_t::quoted_term) {
        return false;
      }

      if (token.type() == token_type_t::open_parens) {
        return false;
      }

      return true;
    };

    // filter leading invalid tokens.
    //
    while (invalid(lexer().peek())) {
      context().report_warning({{}, "invalid leading token"});
      lexer().consume();
    }

    return try_parse_logical_or();
  }

} // namespace art::query
