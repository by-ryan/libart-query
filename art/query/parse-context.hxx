#ifndef art__query__parse_context_hxx_
#define art__query__parse_context_hxx_

#include <art/query/error.hxx>
#include <art/query/source-location.hxx>
#include <art/query/types.hxx>

namespace art::query
{

  class parse_context_t
  {
  public:
    parse_context_t();

    vector<warning_t> const&
    warnings() const;

    vector<error_t> const&
    errors() const;

    void
    report_warning(warning_t);

    void
    report_error(error_t);

  private:
    vector<warning_t> warnings_;
    vector<error_t> errors_;

  };

} // namespace art::query

#endif
