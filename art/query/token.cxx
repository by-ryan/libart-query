#include <art/query/token.hxx>

namespace art::query
{

  token_t::
  token_t(token_type_t type, optional<string> value)
    : type_{type},
      value_{std::move(value)}
  {}

  token_type_t
  token_t::
  type() const
  {
    return type_;
  }

  optional<string> const&
  token_t::
  value() const
  {
    return value_;
  }

  std::ostream&
  operator<<(std::ostream& o, token_t const& token)
  {
    switch (token.type()) {
      case token_type_t::end:
        o << "end";
        break;

      case token_type_t::simple_term:
        o << "simple-term";
        break;

      case token_type_t::quoted_term:
        o << "quoted-term";
        break;

      case token_type_t::colon:
        o << "colon";
        break;

      case token_type_t::logical_and:
        o << "logical-and";
        break;

      case token_type_t::logical_not:
        o << "logical-not";
        break;

      case token_type_t::logical_or:
        o << "logical-or";
        break;

      case token_type_t::open_parens:
        o << "open-parens";
        break;

      case token_type_t::close_parens:
        o << "close-parens";
        break;


    }

    if (auto v = token.value(); v) {
      o << ": " << *v;
    }

    o << '\n';

    return o;
  }

} // namespace art::query
