#ifndef art__query__source_location_hxx_
#define art__query__source_location_hxx_

#include <art/query/types.hxx>

namespace art::query
{

  struct source_location_t
  {
    string name;
    uint32_t row{};
    uint32_t column{};

  };

} // namespace art::query

#endif
