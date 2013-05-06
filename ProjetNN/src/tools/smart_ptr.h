#pragma once

#ifdef _WIN32
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif
#endif

#ifdef _WIN32
#define isnan(_X) _isnan(_X)
#endif



#include <stdio.h>
#include <string>
#include <vector>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>


#define SPTR boost::shared_ptr

template<class Source, class Target>
inline SPTR<Target> sptr_dynamic_cast(const SPTR<Source>& s) {return boost::dynamic_pointer_cast<Target>(s);}


