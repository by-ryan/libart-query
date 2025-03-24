#include <art/query/logical-not.hxx>

#include <sstream>

namespace art::query
{

  logical_not_t::
  logical_not_t(expression_t right)
    : right_{std::move(right)}
  {}

  logical_not_t::
  logical_not_t(source_location_t origin, expression_t right)
    : origin_{std::move(origin)},
      right_{std::move(right)}
  {}

  source_location_t const&
  logical_not_t::
  origin() const
  {
    return origin_;
  }

  expression_t const&
  logical_not_t::
  right() const
  {
    return right_;
  }

  string
  to_string(logical_not_t const& e)
  {
    std::stringstream str;

    str << "NOT " << to_string(e.right());

    return str.str();
  }

} // namespace art::query
