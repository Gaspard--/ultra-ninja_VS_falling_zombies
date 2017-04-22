#ifndef BIND_HPP
# define BIND_HPP

# include <algorithm>

template<class T>
class Bind
{
private:
  T t;
  unsigned int *count;
public:
  Bind(T t)
    : t(t), count(new unsigned int(1))
  {
    t.bind();
  }

  Bind(Bind<T> const &b)
    : t(b.t), count(b.count)
  {
    ++*count;
  }

  ~Bind()
  {
    if (!--*count)
      {
	t.unbind();
	delete count;
      }
  }

  Bind<T> &operator=(Bind<T> b)
  {
    std::swap(t, b.t);
    std::swap(count, b.count);
    return *this;
  }

};

#endif
