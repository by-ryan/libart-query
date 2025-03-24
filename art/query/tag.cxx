#include <art/query/tag.hxx>

namespace art::query
{

  tag_t::
  tag_t(string identifier, term_t value)
    : identifier_{std::move(identifier)},
      value_{std::move(value)}
  {}

  tag_t::
  tag_t(source_location_t origin,
      string identifier,
      term_t value)
    : origin_{std::move(origin)},
      identifier_{std::move(identifier)},
      value_{std::move(value)}
  {}

  source_location_t const&
  tag_t::
  origin() const
  {
    return origin_;
  }

  string const&
  tag_t::
  identifier() const
  {
    return identifier_;
  }

  term_t const&
  tag_t::
  value() const
  {
    return value_;
  }

  string
  to_string(tag_t const& e)
  {
    return e.identifier() + ":" + to_string(e.value());
  }

} // namespace art::query
