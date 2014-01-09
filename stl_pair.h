/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef __SGI_STL_INTERNAL_PAIR_H
#define __SGI_STL_INTERNAL_PAIR_H

__STL_BEGIN_NAMESPACE

/*
 * pair 并不是一个Container，并不支持Container的元素标准访问法。
 * 凡是需要返回两个值的函数，通常可以利用pair
 * pair 隶属于哪个concept取决于其实例化的参数隶属的concept
 * 标准库并没有针对实例化pair的类型concept的划分来取舍相关的函数，
 * 在使用过程中，客户端需要根据实例化类型的concept选取合适的函数。
 * */
template <class _T1, class _T2>
struct pair {
  typedef _T1 first_type;
  typedef _T2 second_type;

  _T1 first;
  _T2 second;
  pair() : first(_T1()), second(_T2()) {}
  pair(const _T1& __a, const _T2& __b) : first(__a), second(__b) {}

/* 需要编译器支持成员模板函数
 * 相关类型需要可转化
 * */
#ifdef __STL_MEMBER_TEMPLATES
  template <class _U1, class _U2>
  pair(const pair<_U1, _U2>& __p) : first(__p.first), second(__p.second) {}
#endif
};

template <class _T1, class _T2>
inline bool operator==(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{ 
  return __x.first == __y.first && __x.second == __y.second; 
}

template <class _T1, class _T2>
inline bool operator<(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y)
{ 
  return __x.first < __y.first || 
         (!(__y.first < __x.first) && __x.second < __y.second); 
}

/* C++ use a method I'll dub "best conversion". The idea is to select the function which has the simplest conversions for the arguments to the parameters.
 * It starts by first producing a list of candidate functions that can be called by the arguments.
 * Next, the arguments are compared, one by one, with the corresponding parameters and a note is made about how close a match it is. 
 *
 * Java and D use a method called "partial ordering" to find the best match. The idea of partial ordering is to select the most specialized function, not the function with the simplest argument conversions.
 * Just like for best conversion, first a list of candidate functions is produced. The "most specialized" function in that list is selected based on the following process. Suppose there are two functions in the candidate list, f1() and f2(). If the parameters to f1() can successfully be used as arguments to f2(), but not vice-versa, then f1() is considered to be "more specialized" than f2(). This process is repeated for each possible pairing of functions in the candidate list. If one emerges as more specialized than any of the others, it is selected, otherwise there is an ambiguity error.
 *
 * Interestingly, D and C++ use partial ordering to resolve template overloading. C# and Java do not have specialization for templates.
 */
#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

template <class _T1, class _T2>
inline bool operator!=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return !(__x == __y);
}

template <class _T1, class _T2>
inline bool operator>(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return __y < __x;
}

template <class _T1, class _T2>
inline bool operator<=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return !(__y < __x);
}

template <class _T1, class _T2>
inline bool operator>=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
  return !(__x < __y);
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */

template <class _T1, class _T2>
inline pair<_T1, _T2> make_pair(const _T1& __x, const _T2& __y)
{
  return pair<_T1, _T2>(__x, __y);
}

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_PAIR_H */

// Local Variables:
// mode:C++
// End:
