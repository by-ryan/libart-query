#ifndef art__query__syntactical_analyzer_hxx_
#define art__query__syntactical_analyzer_hxx_

#include <art/query/expression.hxx>
#include <art/query/lexical-analyzer.hxx>
#include <art/query/parse-context.hxx>
#include <art/query/query.hxx>
#include <art/query/types.hxx>

namespace art::query
{

  class syntactical_analyzer_t
  {
  public:
    syntactical_analyzer_t(lexical_analyzer_t&, parse_context_t&);

    lexical_analyzer_t&
    lexer();

    parse_context_t&
    context();

    query_t
    try_parse();

  private:
    optional<expression_t>
    try_parse_primary_expression();

    optional<expression_t>
    try_parse_logical_and();

    optional<expression_t>
    try_parse_logical_or();

    optional<expression_t>
    try_parse_expression();

  private:
    lexical_analyzer_t& lexer_;
    parse_context_t& context_;

  };

} // namespace art::query

#endif
