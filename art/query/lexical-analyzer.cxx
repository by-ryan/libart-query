#include <art/query/lexical-analyzer.hxx>

#include <cctype>
#include <sstream>

namespace art::query
{

  lexical_analyzer_t::
  ~lexical_analyzer_t() noexcept = default;

  token_t
  lexical_analyzer_t::
  peek()
  {
    if (!current_)
      current_ = extract();

    return *current_;
  }

  void
  lexical_analyzer_t::
  consume()
  {
    current_ = extract();
  }

  lexical_analyzer_t::
  lexical_analyzer_t() = default;

  token_t
  lexical_analyzer_t::
  extract()
  {
    char_type c = peek_char();

    while (is_whitespace(c)) {
      consume_char();
      c = peek_char();
    }

    if (c == 0)
      return token_t{token_type_t::end};

    if (c == ':') {
      consume_char();
      return token_t{token_type_t::colon};
    }

    if (c == '(') {
      consume_char();
      return token_t{token_type_t::open_parens};
    }

    if (c == ')') {
      consume_char();
      return token_t{token_type_t::close_parens};
    }

    if (c == '"') {
      consume_char();

      c = peek_char();

      std::stringstream str;

      while (c != 0 && c != '"') {
        str << (char)c; // FIXME: UTF-8 encode.
        consume_char();
        c = peek_char();
      }

      consume_char();

      return token_t{token_type_t::quoted_term, str.str()};
    }

    std::stringstream str;

    while (c != 0 && !is_whitespace(c) && c != '(' && c != ')' && c != ':') {
      consume_char();
      str << (char)c; // FIXME: UFT-8 encode.
      c = peek_char();
    }

    auto term = str.str();

    auto lower = [](string str)
    {
      for (auto& j : str) {
        j = std::tolower(j);
      }

      return str;
    };

    if (lower(term) == "and")
      return token_t{token_type_t::logical_and};

    if (lower(term) == "or")
      return token_t{token_type_t::logical_or};

    if (lower(term) == "not")
      return token_t{token_type_t::logical_not};

    return token_t{token_type_t::simple_term, std::move(term)};
  }

  lexical_analyzer_t::char_type
  lexical_analyzer_t::
  peek_char()
  {
    if (!next_char_)
      next_char_ = extract_char();

    return *next_char_;
  }

  void
  lexical_analyzer_t::
  consume_char()
  {
    next_char_ = extract_char();
  }

  bool
  lexical_analyzer_t::
  is_whitespace(char_type c)
  {
    return c == ' ' || c == '\t' || c == '\v';
  }

} // namespace art::query
