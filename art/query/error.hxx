#ifndef art__query__error_hxx_
#define art__query__error_hxx_

#include <art/query/source-location.hxx>
#include <art/query/types.hxx>

namespace art::query
{

  class warning_t
  {
  public:
    warning_t(source_location_t, string);

    source_location_t const&
    origin() const;

    string const&
    description() const;

  private:
    source_location_t origin_;
    string description_;

  };

  class error_t
  {
  public:
    error_t(source_location_t source, string);

    source_location_t const&
    origin() const;

    string const&
    description() const;

  private:
    source_location_t origin_;
    string description_;

  };

} // namespace art::query

#endif
