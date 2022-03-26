/* Copied from the build dir cmake produces
 * 
 * 
 */

#ifndef GENERICMC_ICONFIX_EXPORT_H
#define GENERICMC_ICONFIX_EXPORT_H

#ifdef GENERICMC_ICONFIX_STATIC_DEFINE
#  define GENERICMC_ICONFIX_EXPORT
#  define GENERICMC_ICONFIX_NO_EXPORT
#else
#  ifndef GENERICMC_ICONFIX_EXPORT
#    ifdef GENERICMC_iconfix_EXPORTS
        /* We are building this library */
#      define GENERICMC_ICONFIX_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define GENERICMC_ICONFIX_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef GENERICMC_ICONFIX_NO_EXPORT
#    define GENERICMC_ICONFIX_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef GENERICMC_ICONFIX_DEPRECATED
#  define GENERICMC_ICONFIX_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef GENERICMC_ICONFIX_DEPRECATED_EXPORT
#  define GENERICMC_ICONFIX_DEPRECATED_EXPORT GENERICMC_ICONFIX_EXPORT GENERICMC_ICONFIX_DEPRECATED
#endif

#ifndef GENERICMC_ICONFIX_DEPRECATED_NO_EXPORT
#  define GENERICMC_ICONFIX_DEPRECATED_NO_EXPORT GENERICMC_ICONFIX_NO_EXPORT GENERICMC_ICONFIX_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef GENERICMC_ICONFIX_NO_DEPRECATED
#    define GENERICMC_ICONFIX_NO_DEPRECATED
#  endif
#endif

#endif /* GENERICMC_ICONFIX_EXPORT_H */
