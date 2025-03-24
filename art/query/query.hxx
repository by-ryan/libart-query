#ifndef art__query__query_hxx_
#define art__query__query_hxx_

#include <art/query/error.hxx>
#include <art/query/expression.hxx>
#include <art/query/types.hxx>
#include <art/query/visitor.hxx>

namespace art::query
{

  class query_t
  {
  public:
    query_t(optional<expression_t> e,
            vector<warning_t> warnings,
            vector<error_t> errors);

    optional<expression_t> const&
    expr() const;

    vector<warning_t> const&
    warnings() const;

    vector<error_t> const&
    errors() const;

  private:
    optional<expression_t> expr_;
    vector<warning_t> warnings_;
    vector<error_t> errors_;

  };

  void
  accept(query_t const& q, visitor_t& v);

  string
  to_string(query_t const& q);

} // namespace art::query

#endif
