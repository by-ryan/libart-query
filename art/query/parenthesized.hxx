#ifndef art__query__parenthesized_hxx_
#define art__query__parenthesized_hxx_

#include <art/query/expression.hxx>
#include <art/query/types.hxx>

namespace art::query
{

  class parenthesized_t
  {
  public:
    explicit
    parenthesized_t(expression_t);

    parenthesized_t(source_location_t, expression_t);

    source_location_t const&
    origin() const;

    expression_t const&
    expr() const;

  private:
    source_location_t origin_;
    expression_t expr_;

  };

  string
  to_string(parenthesized_t const& e);

} // namespace art::query

#endif
