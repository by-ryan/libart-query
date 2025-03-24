#include <art/query/query.hxx>

namespace art::query
{

  query_t::
  query_t(optional<expression_t> e,
          vector<warning_t> warnings,
          vector<error_t> errors)
    : expr_{std::move(e)},
      warnings_{std::move(warnings)},
      errors_{std::move(errors)}
  {}

  optional<expression_t> const&
  query_t::
  expr() const
  {
    return expr_;
  }

  vector<warning_t> const&
  query_t::
  warnings() const
  {
    return warnings_;
  }

  vector<error_t> const&
  query_t::
  errors() const
  {
    return errors_;
  }

  void
  accept(query_t const& q, visitor_t& v)
  {
    if (q.expr()) {
      accept(*q.expr(), v);
    }
  }

  string
  to_string(query_t const& q)
  {
    if (q.expr()) {
      return to_string(*q.expr());
    }

    return string{};
  }

} // namespace art::query
