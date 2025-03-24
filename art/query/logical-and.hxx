#ifndef art__query__logical_and_hxx_
#define art__query__logical_and_hxx_

#include <art/query/expression.hxx>
#include <art/query/source-location.hxx>
#include <art/query/types.hxx>

namespace art::query
{

  class logical_and_t
  {
  public:
    logical_and_t(expression_t, expression_t);

    logical_and_t(source_location_t, expression_t, expression_t);

    source_location_t const&
    origin() const;

    expression_t const&
    left() const;

    expression_t const&
    right() const;

  private:
    source_location_t origin_;
    expression_t left_;
    expression_t right_;

  };

  string
  to_string(logical_and_t const&);

} // namespace art::query

#endif
