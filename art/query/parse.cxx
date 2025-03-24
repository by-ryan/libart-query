#include <art/query/parse.hxx>

#include <art/query/lexical-analyzer.hxx>
#include <art/query/syntactical-analyzer.hxx>

namespace art::query
{

  query_t
  try_parse(string const& q, parse_context_t& context)
  {
    string_lexical_analyzer_t lexer{q.begin(), q.end()};
    return syntactical_analyzer_t{lexer, context}.try_parse();
  }

} // namespace art::query
