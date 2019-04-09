#pragma once

#include <list>

template<typename T>
static typename std::list <T>::iterator CircularNext(std::list<T> &pList, typename std::list<T>::iterator &it)
{
  if (std::next(it) != pList.end())
  {
    return std::next(it);
  }
  return pList.begin();
}

template<typename T>
static typename std::list <T>::iterator CircularPrev(std::list<T> &pList, typename std::list<T>::iterator &it)
{
  if (it != pList.begin())
  {
    return std::prev(it);
  }
  return --pList.end();
}