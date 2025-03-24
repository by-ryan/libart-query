#ifndef art__query__lexical_analyzer_hxx_
#define art__query__lexical_analyzer_hxx_

#include <art/query/token.hxx>
#include <art/query/types.hxx>

namespace art::query
{

  class lexical_analyzer_t
  {
  public:
    using char_type = uint32_t;

    virtual
    ~lexical_analyzer_t() noexcept;

    token_t
    peek();

    void
    consume();

  protected:
    lexical_analyzer_t();

    lexical_analyzer_t(lexical_analyzer_t const&) = delete;
    lexical_analyzer_t(lexical_analyzer_t&&) = delete;

    token_t
    extract();

    char_type
    peek_char();

    void
    consume_char();

    virtual
    char_type
    extract_char() = 0;

    lexical_analyzer_t& operator=(lexical_analyzer_t const&) = delete;
    lexical_analyzer_t& operator=(lexical_analyzer_t&&) = delete;

    static
    bool
    is_whitespace(char_type);

  private:
    optional<char_type> next_char_;
    optional<token_t> current_;

  };

  template<typename Iterator, typename EndIterator = Iterator>
  class basic_lexical_analyzer_t
    : public lexical_analyzer_t
  {
  public:
    using iterator = Iterator;
    using end_iterator = EndIterator;

    basic_lexical_analyzer_t(iterator, end_iterator);

    basic_lexical_analyzer_t(basic_lexical_analyzer_t const&);

    basic_lexical_analyzer_t(basic_lexical_analyzer_t&&);

    ~basic_lexical_analyzer_t() noexcept override;

    basic_lexical_analyzer_t&
    operator=(basic_lexical_analyzer_t const&) = delete;

    basic_lexical_analyzer_t&
    operator=(basic_lexical_analyzer_t&&) = delete;

  protected:
    char_type
    extract_char() override;

  private:
    iterator current_;
    end_iterator end_;

  };

  using string_lexical_analyzer_t = basic_lexical_analyzer_t<string::const_iterator>;

} // namespace art::query

#include <art/query/lexical-analyzer.txx>

#endif
