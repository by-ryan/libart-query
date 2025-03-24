#ifndef art__query__tag_hxx_
#define art__query__tag_hxx_

#include <art/query/expression.hxx>
#include <art/query/source-location.hxx>
#include <art/query/term.hxx>
#include <art/query/types.hxx>

namespace art::query
{

  class tag_t
  {
  public:
    tag_t(string, term_t);

    tag_t(source_location_t, string, term_t);

    source_location_t const&
    origin() const;

    string const&
    identifier() const;

    term_t const&
    value() const;

  private:
    source_location_t origin_;

    string identifier_;
    term_t value_;
  };

  string
  to_string(tag_t const& e);

} // namespace imperium::contract::query

#endif
