#include <art/query/logical-or.hxx>

#include <sstream>

namespace art::query
{

  logical_or_t::
  logical_or_t(expression_t left, expression_t right)
    : left_{std::move(left)},
      right_{std::move(right)}
  {}

  logical_or_t::
  logical_or_t(source_location_t origin,
               expression_t left,
               expression_t right)
    : origin_{std::move(origin)},
      left_{std::move(left)},
      right_{std::move(right)}
  {}

  source_location_t const&
  logical_or_t::
  origin() const
  {
    return origin_;
  }

  expression_t const&
  logical_or_t::
  left() const
  {
    return left_;
  }

  expression_t const&
  logical_or_t::
  right() const
  {
    return right_;
  }

  string
  to_string(logical_or_t const& e)
  {
    std::stringstream str;

    str << to_string(e.left());
    str << " or ";
    str << to_string(e.right());

    return str.str();
  }

} // namespace art::query
