#ifndef VECT_HPP_
# define VECT_HPP_

# include <type_traits>
# include <math.h>
# include "util.hpp"

template <unsigned int dim, class T>
class Vect
{
private:
  T data[dim];

public:
  template<class Op, class P, class... U, typename std::enable_if<sizeof...(U) < dim>::type * = nullptr>
  constexpr Vect(Function<T, P, Op> function, U... indices)
    : Vect(function, dim - sizeof...(indices) - 1, indices...)
  {}

  template<class Op, class P, class... U, typename std::enable_if<sizeof...(U) == dim>::type * = nullptr>
  constexpr Vect(Function<T, P, Op> function, U... indices)
    : Vect(function.apply(indices)...)
  {}

  template<class V>
  constexpr Vect(V const (&other)[dim])
    : Vect(other, dim - 1u)
  {}

  template<class V, class... U, typename std::enable_if<sizeof...(U) < dim - 1>::type * = nullptr>
  constexpr Vect(V const (&other)[dim], unsigned int i, U... indices)
    : Vect(other, dim - sizeof...(indices) - 2u, i, indices...)
  {}

  template<class V, class... U, typename std::enable_if<sizeof...(U) == dim>::type * = nullptr>
  constexpr Vect(V const (&other)[dim], U... indices)
    : Vect(static_cast<T>(other[indices])...)
  {}

  template<class V>
  constexpr Vect(Vect<dim, V> const &other)
    : Vect(other, dim - 1u)
  {}

  template<class V, class... U, typename std::enable_if<sizeof...(U) < dim - 1>::type * = nullptr>
  constexpr Vect(Vect<dim, V> const &other, unsigned int i, U... indices)
    : Vect(other, dim - sizeof...(indices) - 2u, i, indices...)
  {}

  template<class V, class... U, typename std::enable_if<sizeof...(U) == dim>::type * = nullptr>
  constexpr Vect(Vect<dim, V> const &other, U... indices)
    : Vect(static_cast<T>(other[indices])...)
  {}

  template<class... U, typename std::enable_if<sizeof...(U) < dim - 1>::type * = nullptr>
  constexpr Vect(Vect<dim - 1, T> const &other, T added, U... indices)
    : Vect(other, added, indices..., dim - sizeof...(indices) - 2)
  {}

  template<class... U, typename std::enable_if<sizeof...(U) == dim - 1>::type * = nullptr>
  constexpr Vect(Vect<dim - 1, T> const &other, T added, U... indices)
    : Vect(other.data[indices]..., added)
  {}

  template<class... U, typename std::enable_if<sizeof...(U) == dim>::type * = nullptr>
  constexpr Vect(U... ts) : data{static_cast<T>(ts)...}
  {}

  template<class Operation>
  void applyOnSelf(Operation op)
  {
    unsigned int i(0);

    while (i < dim)
      {
	data[i] = op(i);
	i = i + 1;
      }
  }

  T &operator[](unsigned int index)
  {
    return (data[index]);
  }

  constexpr T const &operator[](unsigned int index) const
  {
    return (data[index]);
  }

  Vect<dim, T>& operator+=(Vect<dim, T> const &other)
  {
    this->applyOnSelf([this, other](unsigned int i){return this->data[i] + other[i];});
    return (*this);
  }

  Vect<dim, T>& operator-=(Vect<dim, T> const &other)
  {
    this->applyOnSelf([this, other](unsigned int i){return this->data[i] - other[i];});
    return (*this);
  }

  Vect<dim, T>& operator*=(Vect<dim, T> const &other)
  {
    this->applyOnSelf([this, other](unsigned int i){return this->data[i] * other[i];});
    return (*this);
  }

  Vect<dim, T>& operator/=(T const &other)
  {
    this->applyOnSelf([this, other](unsigned int i){return this->data[i] / other;});
    return (*this);
  }

  Vect<dim, T>& operator*=(T const &other)
  {
    this->applyOnSelf([this, other](unsigned int i){return this->data[i] * other;});
    return (*this);
  }


  Vect<dim, T>& operator^=(Vect<dim, T> const &other)
  {
    this->applyOnSelf([this, other](unsigned int i) {return this->data[i] ^ other[i];});
    return (*this);
  }

  // TODO optimize ?
  bool operator==(Vect<dim, T> const& other) const
  {
    for (unsigned int i = 0; i < dim; i++)
      {
	if (data[i] != other.data[i])
	  return false;
      }
    return true;
  }

  bool operator!=(Vect<dim, T> const& other) const
  {
    return !operator==(other);
  }

  // constexpr Vect<dim, bool> operator==(Vect<dim, T> const &other) const
  // {
  //   return Supplier<T, Vect<dim, bool>([this, other](unsigned int i){
  // 	return other[i] == (*this)[i];
  //     })>();
  // }

  // constexpr Vect<dim, bool> operator!=(Vect<dim, T> const &other) const
  // {
  //   return Vect<dim, bool>([this, other](unsigned int i){
  // 	return other[i] != (*this)[i];
  //     });
  // }

  template<class Op>
  constexpr static Vect<dim, T> applyOp(Op const op)
  {
    return Vect<dim, T>(Function<T, unsigned int, Op>(op));
  }

  template<class Op>
  constexpr Vect<dim, T> map(Op const op) const
  {
    return applyOp([op, this](unsigned int i) {
	return (op(data[i]));
      });
  }

  template<class Op, class U>
  constexpr Vect<dim, T> applyOpPerComponent(Op op, const Vect<dim, U>& other) const
  {
    return applyOp([this, other, op](unsigned int i) {
	return op((*this)[i], other[i]);
      });
  }

  template<class U>
  constexpr Vect<dim, T> operator+(Vect<dim, U> const &other) const
  {
    return Vect<dim, T>::applyOpPerComponent([](T a, U b) {
	return (a + b);
      }, other);
  }

  constexpr Vect<dim, T> operator*(Vect<dim, T> const &other) const
  {
    return Vect<dim, T>::applyOp([this, other](unsigned int i){
	return (*this)[i] * other[i];
      });
  }

  constexpr Vect<dim, T> operator*(T const &other) const
  {
    return Vect<dim, T>::applyOp([this, other](unsigned int i){
	return (*this)[i] * other;
      });
  }

  constexpr Vect<dim, T> operator/(Vect<dim, T> const &other) const
  {
    return Vect<dim, T>::applyOp([this, other](unsigned int i){
	return (*this)[i] / other[i];
      });
  }

  constexpr Vect<dim, T> operator/(T const &other) const
  {
    return Vect<dim, T>::applyOp([this, other](unsigned int i){
	return (*this)[i] / other;
      });
  }

  constexpr Vect<dim, T> operator%(Vect<dim, T> const &other) const
  {
    return Vect<dim, T>::applyOp([this, other](unsigned int i){
	return (*this)[i] % other[i];
      });
  }

  constexpr Vect<dim, T> operator-(Vect<dim, T> const &other) const
  {
    return Vect<dim, T>::applyOp([this, other](unsigned int i){
	return (*this)[i] - other[i];
      });
  }

  constexpr Vect<dim, T> operator-(void) const
  {
    return map([](T t){return (-t);});
  }

private:


public:
  T sum(void) const
  {
    unsigned int	i;
    T			result;

    result = 0u;
    i = 0u;
    while (i < dim)
      {
	result = result + data[i];
	i = i + 1u;
      }
    return (result);
  }

  T scalar(Vect<dim, T> const &other) const
  {
    return ((*this * other).sum());
  }

  T length2() const
  {
    return ((*this * *this).sum());
  }

  Vect<dim, T> normalized() const
  {
    return length2() > 0 ? ((*this) / sqrt(length2())) : *this;
  }

  template<unsigned int _dim = dim, typename std::enable_if<(_dim > 0)>::type* = nullptr>
  T x() const
  {
    return (data[0]);
  }

  template<unsigned int _dim = dim, typename std::enable_if<(_dim > 1)>::type* = nullptr>
  T y() const
  {
    return (data[1]);
  }

  template<unsigned int _dim = dim, typename std::enable_if<(_dim > 2)>::type* = nullptr>
  T z() const
  {
    return (data[2]);
  }

  template<unsigned int _dim = dim, typename std::enable_if<(_dim > 3)>::type* = nullptr>
  T w() const
  {
    return (data[3]);
  }

  template<unsigned int _dim = dim, typename std::enable_if<(_dim > 0)>::type* = nullptr>
  T &x()
  {
    return (data[0]);
  }

  template<unsigned int _dim = dim, typename std::enable_if<(_dim > 1)>::type* = nullptr>
  T &y()
  {
    return (data[1]);
  }

  template<unsigned int _dim = dim, typename std::enable_if<(_dim > 2)>::type* = nullptr>
  T &z()
  {
    return (data[2]);
  }

  template<unsigned int _dim = dim, typename std::enable_if<(_dim > 3)>::type* = nullptr>
  T &w()
  {
    return (data[3]);
  }

  T reduce()
  {

  }

  bool all()
  {
    unsigned int i(0);

    while (i < dim && data[i])
      i = i + 1;
    return (i == dim);
  }

  typedef T (&tab)[dim];

  operator tab()
  {
    return (data);
  }

  template<class L>
  static void forEach(Vect<dim, T> begin, Vect<dim, T> end, L l)
  {
    Vect<dim, T> index(begin);

    for (index[0] = begin[0]; index[0] < end[0]; ++index[0])
      for (index[1] = begin[1]; index[1] < end[1]; ++index[1])
	l(index);
  }
};

#endif // VECT_HPP_
