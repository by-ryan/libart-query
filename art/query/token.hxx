#ifndef art__query__token_hxx_
#define art__query__token_hxx_

#include <art/query/types.hxx>

#include <iostream>

namespace art::query
{

  enum class token_type_t
  {
    end,

    simple_term,
    quoted_term,

    colon,

    logical_and,
    logical_not,
    logical_or,

    open_parens,
    close_parens

  };

  class token_t
  {
  public:
    explicit
    token_t(token_type_t, optional<string> = nullopt);

    token_type_t
    type() const;

    optional<string> const&
    value() const;

  private:
    token_type_t type_;
    optional<string> value_;

  };

  std::ostream&
  operator<<(std::ostream&, token_t const&);

} // namespace art::query

#endif
