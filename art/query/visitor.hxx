#ifndef art__query__visitor_hxx_
#define art__query__visitor_hxx_

namespace art::query
{

  class visitor_t
  {
  public:
    virtual
    ~visitor_t() noexcept = default;

    virtual
    void
    visit_default() = 0;

  protected:
    visitor_t() = default;

  };

  template<typename V>
  class basic_visitor_t
  {
  public:
    virtual
    void
    visit(V const&) = 0;

  protected:
    basic_visitor_t() = default;

    ~basic_visitor_t() noexcept = default;

  };

} // namespace art::query

#endif
