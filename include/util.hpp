#ifndef UTIL_HPP_
# define UTIL_HPP_

template<class R, class Op>
class Supplier
{
private:
  Op op;

public:
  constexpr Supplier(Op op)
    : op(op)
  {}

  constexpr R get() const {
    return op();
  }
};

template<class Y, class X, class Op>
class Function
{
private:
  Op op;

public:
  constexpr Function(Op op)
    : op(op)
  {}
  
  constexpr Y apply(X const &x) const {
    return op(x);
  }
};

#endif // !UTIL_HPP_
