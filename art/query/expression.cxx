#include <art/query/expression.hxx>

namespace art::query
{

  source_location_t const&
  expression_t::
  origin() const
  {
    return container_->origin_();
  }

  void
  accept(expression_t const& e, visitor_t& v)
  {
    e.container_->accept_(v);
  }

  string
  to_string(expression_t const& e)
  {
    return e.container_->to_string_();
  }

} // namespace art::query
