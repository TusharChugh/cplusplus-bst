#pragma once

#ifndef LIBCPP_HIDDEN_
#define LIBCPP_HIDDEN_ __attribute__( ( __visibility__( "hidden" ) ) )
#endif

#ifndef LIBCPP_VISIBLE_
#define LIBCPP_VISIBLE_ __attribute__( ( __visibility__( "default" ) ) )
#endif

#ifndef LIBCPP_INLINE_VISIBILITY_
#define LIBCPP_INLINE_VISIBILITY_ __attribute__( ( __visibility__( "hidden" ), __always_inline__ ) )
#endif