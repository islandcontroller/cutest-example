/*!****************************************************************************
 * @file
 * lambda.h
 *
 * @brief
 * Lambda-like expressions in C using GCC statement exprs
 *
 * @note
 * In order to mitigate warnings associated with dynamic code generation, use
 * the "BEGIN/END_LAMBDA_SECTION" macros. Usage of lambdas also requires the
 * use of an executable stack, by specifying "-z execstack" in linker options.
 *
 * @date  04.06.2023
 ******************************************************************************/

#ifndef UTIL_LAMBDA_H_
#define UTIL_LAMBDA_H_

/*- Macros -------------------------------------------------------------------*/
/*! Temporary warning suppression for generated trampoline                    */
#define BEGIN_LAMBDA_SECTION()    \
  _Pragma("GCC diagnostic push"); \
  _Pragma("GCC diagnostic ignored \"-Wtrampolines\"")
#define END_LAMBDA_SECTION()      \
  _Pragma("GCC diagnostic pop")

/*! Lambda function macro:
 * args: argument list surrounded by parentheses, e.g. "(int x, char y)"
 * ret: return type, e.g. "void"
 * body: function body, surrounded by braces, e.g. { return true; }           */
#define LAMBDA(args, ret, body)   ({ ret _fn args body; _fn; })

/*! Unused argument placeholders                                              */
#define _1                        _unused1 __attribute__((unused))
#define _2                        _unused2 __attribute__((unused))
#define _3                        _unused3 __attribute__((unused))
#define _4                        _unused4 __attribute__((unused))
#define _5                        _unused5 __attribute__((unused))
#define _6                        _unused6 __attribute__((unused))

#endif /* UTIL_LAMBDA_H_ */
