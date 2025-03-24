#ifndef art__query__match_hxx_
#define art__query__match_hxx_

#include <art/query/types.hxx>

#include <art/query/logical-and.hxx>
#include <art/query/logical-not.hxx>
#include <art/query/logical-or.hxx>
#include <art/query/parenthesized.hxx>
#include <art/query/query.hxx>
#include <art/query/tag.hxx>
#include <art/query/term.hxx>

namespace art::query
{

  using predicate_t = function<
    bool(variant<term_t, tag_t> const&)
  >;

  bool
  match(query_t const&, predicate_t const&);

  template<typename Q, typename P>
  Q
  transform(optional<query_t> const& q, P const& predicate)
  {
    class matcher_t
      : public visitor_t,
        public basic_visitor_t<term_t>,
        public basic_visitor_t<tag_t>,
        public basic_visitor_t<logical_and_t>,
        public basic_visitor_t<logical_not_t>,
        public basic_visitor_t<logical_or_t>,
        public basic_visitor_t<parenthesized_t>
    {
    public:
      P const& predicate;

      static
      Q
      transform(optional<expression_t> const& e, P const& predicate)
      {
        matcher_t m{predicate};

        if (e) {
          accept(*e, m);
        }

        return m.result;
      }

    private:
      explicit
      matcher_t(P const& predicate)
        : predicate{predicate}
      {}

      void
      visit_default() override
      {}

      void
      visit(term_t const& term) override
      {
        result = predicate(term);
      }

      void
      visit(tag_t const& tag) override
      {
        result = predicate(tag);
      }

      void
      visit(logical_and_t const& logical_and) override
      {
        result = transform(logical_and.left(), predicate) && transform(logical_and.right(), predicate);
      }

      void
      visit(logical_or_t const& logical_or) override
      {
        result = transform(logical_or.left(), predicate) || transform(logical_or.right(), predicate);
      }

      void
      visit(logical_not_t const& logical_not) override
      {
        result = !transform(logical_not.right(), predicate);
      }

      void
      visit(parenthesized_t const& parenthesized) override
      {
        result = transform(parenthesized.expr(), predicate);
      }

      Q result{};

    };

    if (q) {
      return matcher_t::transform(q->expr(), predicate);
    }

    return Q{};
  }

} // namespace art::query

#endif
