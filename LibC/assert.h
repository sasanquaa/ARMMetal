#ifndef _ASSERT_H
#    define _ASSERT_H
#    define static_assert _Static_assert
#endif

#undef assert

#ifndef NDEBUG
#    define assert(expression) ((void)0)
#else
#    define assert(ignore) ((void)0)
#endif
