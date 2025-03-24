#include <art/query/parse-context.hxx>

namespace art::query
{

  parse_context_t::
  parse_context_t()
  {}

  vector<warning_t> const&
  parse_context_t::
  warnings() const
  {
    return warnings_;
  }

  vector<error_t> const&
  parse_context_t::
  errors() const
  {
    return errors_;
  }

  void
  parse_context_t::
  report_warning(warning_t w)
  {
    warnings_.emplace_back(std::move(w));
  }

  void
  parse_context_t::
  report_error(error_t e)
  {
    errors_.emplace_back(std::move(e));
  }

} // namespace art::query
