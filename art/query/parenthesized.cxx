#include <art/query/parenthesized.hxx>

#include <sstream>

namespace art::query
{

  parenthesized_t::
  parenthesized_t(expression_t expr)
    : expr_{std::move(expr)}
  {}

  parenthesized_t::
  parenthesized_t(source_location_t origin, expression_t expr)
    : origin_{std::move(origin)},
      expr_{std::move(expr)}
  {}

  source_location_t const&
  parenthesized_t::
  origin() const
  {
    return origin_;
  }

  expression_t const&
  parenthesized_t::
  expr() const
  {
    return expr_;
  }

  string
  to_string(parenthesized_t const& e)
  {
    std::stringstream str;

    str << '(' << to_string(e.expr()) << ')';

    return str.str();
  }

} // namespace art::query
