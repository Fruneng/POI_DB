
//******************************************************************************
// RCF - Remote Call Framework
//
// Copyright (c) 2005 - 2012, Delta V Software. All rights reserved.
// http://www.deltavsoft.com
//
// RCF is distributed under dual licenses - closed source or GPL.
// Consult your particular license for conditions of use.
//
// If you have not purchased a commercial license, you are using RCF 
// under GPL terms.
//
// Version: 2.0
// Contact: support <at> deltavsoft.com 
//
//******************************************************************************

//
// detail/impl/posix_mutex.ipp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef RCF_DETAIL_IMPL_POSIX_MUTEX_IPP
#define RCF_DETAIL_IMPL_POSIX_MUTEX_IPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#if defined(BOOST_HAS_PTHREADS)

#include <RCF/thread/posix_mutex.hpp>
#include <RCF/thread/push_options.hpp>

namespace RCF {
namespace detail {

posix_mutex::posix_mutex()
{
  int error = ::pthread_mutex_init(&mutex_, 0);
  RCF_VERIFY(error == 0, Exception(_RcfError_ThreadingError("pthread_mutex_init()"), error));
}

} // namespace detail
} // namespace RCF

#include <RCF/thread/pop_options.hpp>

#endif // defined(BOOST_HAS_PTHREADS)

#endif // RCF_DETAIL_IMPL_POSIX_MUTEX_IPP
