#include <art/query/term.hxx>

namespace art::query
{

  term_t::
  term_t(term_type_t type, string value)
    : type_{type},
      value_{std::move(value)}
  {}

  term_t::
  term_t(source_location_t origin,
       term_type_t type,
       string value)
    : origin_{std::move(origin)},
      type_{type},
      value_{std::move(value)}
  {}

  source_location_t const&
  term_t::
  origin() const
  {
    return origin_;
  }

  term_t::term_type_t
  term_t::
  type() const
  {
    return type_;
  }

  string const&
  term_t::
  value() const
  {
    return value_;
  }

  string
  to_string(term_t const& term)
  {
    if (term.type() == term_t::simple)
      return term.value();

    // fixme: escape term.value()?
    //
    return "\"" + term.value() + "\"";
  }

} // namespace art::query
