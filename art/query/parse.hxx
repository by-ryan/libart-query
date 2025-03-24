#ifndef art__query__parse_hxx_
#define art__query__parse_hxx_

#include <art/query/parse-context.hxx>
#include <art/query/query.hxx>
#include <art/query/types.hxx>

namespace art::query
{

  query_t
  try_parse(string const&, parse_context_t&);

} // namespace art::query

#endif
