#ifndef art__query__types_hxx_
#define art__query__types_hxx_

#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace art::query
{

  using std::int8_t;
  using std::int16_t;
  using std::int32_t;
  using std::int64_t;
  using std::uint8_t;
  using std::uint16_t;
  using std::uint32_t;
  using std::uint64_t;

  using std::make_shared;
  using std::shared_ptr;
  using std::weak_ptr;

  using std::optional;
  using std::nullopt;

  using std::vector;
  using std::variant;

  using std::string;
  using strings = vector<string>;

  using std::function;

} // namespace art::query

#endif
