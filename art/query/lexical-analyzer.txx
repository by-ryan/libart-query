namespace art::query
{

  template<typename I, typename E>
  basic_lexical_analyzer_t<I, E>::
  basic_lexical_analyzer_t(iterator begin, end_iterator end)
    : current_{std::move(begin)},
      end_{std::move(end)}
  {}

  template<typename I, typename E>
  basic_lexical_analyzer_t<I, E>::
  basic_lexical_analyzer_t(basic_lexical_analyzer_t const& other)
    : current_{other.current_},
      end_{other.end_}
  {}

  template<typename I, typename E>
  basic_lexical_analyzer_t<I, E>::
  basic_lexical_analyzer_t(basic_lexical_analyzer_t&& other)
    : current_{std::move(other.current_)},
      end_{std::move(other.end_)}
  {}

  template<typename I, typename E>
  basic_lexical_analyzer_t<I, E>::
  ~basic_lexical_analyzer_t() noexcept = default;

  template<typename I, typename E>
  basic_lexical_analyzer_t<I, E>::char_type
  basic_lexical_analyzer_t<I, E>::
  extract_char()
  {
    if (current_ == end_)
      return 0;

    return *current_++;
  }

} // namespace art::query
