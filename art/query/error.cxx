#include <art/query/error.hxx>

namespace art::query
{

  warning_t::
  warning_t(source_location_t origin, string description)
    : origin_{std::move(origin)},
      description_{std::move(description)}
  {}

  source_location_t const&
  warning_t::
  origin() const
  {
    return origin_;
  }

  string const&
  warning_t::
  description() const
  {
    return description_;
  }

  error_t::
  error_t(source_location_t origin, string description)
    : origin_{std::move(origin)},
      description_{std::move(description)}
  {}

  source_location_t const&
  error_t::
  origin() const
  {
    return origin_;
  }

  string const&
  error_t::
  description() const
  {
    return description_;
  }

} // namespace art::query
