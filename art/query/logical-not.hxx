#ifndef art__query__logical_not_t_hxx_
#define art__query__logical_not_t_hxx_

#include <art/query/expression.hxx>
#include <art/query/types.hxx>

namespace art::query
{

  class logical_not_t
  {
  public:
    explicit
    logical_not_t(expression_t);

    logical_not_t(source_location_t, expression_t);

    source_location_t const&
    origin() const;

    expression_t const&
    right() const;

  private:
    source_location_t origin_;
    expression_t right_;
  };

  string
  to_string(logical_not_t const& e);

} // namespace art::query

#endif
