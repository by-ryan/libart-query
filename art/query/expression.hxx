#ifndef art__query__expression_hxx_
#define art__query__expression_hxx_

#include <art/query/error.hxx>
#include <art/query/source-location.hxx>
#include <art/query/types.hxx>
#include <art/query/visitor.hxx>

namespace art::query
{

class expression_t
{
public:
  template<typename E>
  expression_t(E e)
    : container_{make_shared<container_t<E>>(std::move(e))}
  {}

  source_location_t const&
  origin() const;

  friend
  void
  accept(expression_t const&, visitor_t&);

  friend
  string
  to_string(expression_t const&);

private:
  struct abstract_t
  {
    virtual
    ~abstract_t() noexcept = default;

    virtual
    source_location_t const&
    origin_() const = 0;

    virtual
    void
    accept_(visitor_t& v) const = 0;

    virtual
    string
    to_string_() const = 0;

  };

  template<typename E>
  struct container_t
    : abstract_t
  {
    explicit
    container_t(E e)
      : e{std::move(e)}
    {}

    ~container_t() noexcept override
    {}

    source_location_t const&
    origin_() const override
    {
      return e.origin();
    }

    void
    accept_(visitor_t& v) const override
    {
      if (auto c = dynamic_cast<basic_visitor_t<E>*>(&v); c) {
        c->visit(e);
        return;
      }

      v.visit_default();
    }

    string
    to_string_() const override
    {
      return to_string(e);
    }

    E e;
  };

  shared_ptr<abstract_t const> container_;
};

} // namespace art::query

#endif
