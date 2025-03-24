#include <art/query/match.hxx>

namespace art::query
{

  bool
  match(query_t const& q, predicate_t const& p)
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
      static
      bool
      match(optional<expression_t> const& e, predicate_t const& p)
      {
        matcher_t m{p};

        if (e) {
          accept(*e, m);
        }

        return m.result;
      }

    private:
      explicit
      matcher_t(predicate_t const& p)
        : predicate_{p}
      {}

      void
      visit_default() override
      {
        result = false;
      }

      void
      visit(term_t const& e) override
      {
        result = predicate_(e);
      }

      void
      visit(tag_t const& e) override
      {
        result = predicate_(e);
      }

      void
      visit(logical_and_t const& e) override
      {
        result = match(e.left(), predicate_) && match(e.right(), predicate_);
      }

      void
      visit(logical_or_t const& e) override
      {
        result = match(e.left(), predicate_) || match(e.right(), predicate_);
      }

      void
      visit(logical_not_t const& e) override
      {
        result = !match(e.right(), predicate_);
      }

      void
      visit(parenthesized_t const& e) override
      {
        result = match(e.expr(), predicate_);
      }

      predicate_t const& predicate_;
      bool result{};

    };

    return matcher_t::match(q.expr(), p);
  }

} // namespace art::query
