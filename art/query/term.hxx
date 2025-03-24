#ifndef art__query__term_hxx_
#define art__query__term_hxx_

#include <art/query/expression.hxx>
#include <art/query/source-location.hxx>
#include <art/query/types.hxx>

namespace art::query
{

  class term_t
  {
  public:
    enum term_type_t
    {
      simple,
      quoted
    };

    term_t(term_type_t, string);

    term_t(source_location_t, term_type_t, string);

    source_location_t const&
    origin() const;

    term_type_t
    type() const;

    string const&
    value() const;

  private:
    source_location_t origin_;

    term_type_t type_;
    string value_;
  };

  string
  to_string(term_t const&);

} // namespace art::query

#endif
