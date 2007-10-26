/*  ===== actuar: an R package for Actuarial Science =====
 *
 *  Functions to generate variates of phase-type distributions. This
 *  file is based on dpq.c with the following modifications:
 *
 *     1. support for a matrix argument;
 *     2. no iteration over the parameters;
 *     3. support for two parameter distributions only.
 *
 *  For details, see random.c.
 *
 *  AUTHOR: Vincent Goulet <vincent.goulet@act.ulaval.ca>
 */

#include <R.h>
#include <Rinternals.h>
#include "actuar.h"
#include "locale.h"

/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * THESE FUNCTIONS ARE NOT YET ADAPTED FOR PHASE-TYPE DISTRIBUTIONS
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 */

static Rboolean randomphtype2(double (*f)(), double *a, int na,
			      double *b, int nb, double *x, int n)
{
    double ai, bi;
    int i;
    Rboolean naflag = FALSE;
    for (i = 0; i < n; i++)
    {
	ai = a[i % na];
	bi = b[i % nb];
	x[i] = f(ai, bi);
	if (!R_FINITE(x[i])) naflag = TRUE;
    }
    return(naflag);
}

#define RANDPHTYPE2(num, fun) \
	case num: \
	    random2(fun, REAL(a), na, REAL(b), nb, REAL(x), n); \
	    break

SEXP do_randomphtype2(int code, SEXP args)
{
    SEXP x, a, b;
    int i, n, na, nb;
    Rboolean naflag = FALSE;

    /* Check validity of arguments */
    if (!isVector(CAR(args)) ||
	!isNumeric(CADR(args)) ||
	!isNumeric(CADDR(args)))
	error(_("invalid arguments"));

    /* Number of variates to generate */
    if (LENGTH(CAR(args)) == 1)
    {
	n = asInteger(CAR(args));
	if (n == NA_INTEGER || n < 0)
	    error(_("invalid arguments"));
    }
    else
	n = LENGTH(CAR(args));

    /* If n == 0, return numeric(0) */
    PROTECT(x = allocVector(REALSXP, n));
    if (n == 0)
    {
	UNPROTECT(1);
	return(x);
    }

    /* If length of parameters < 1, return NaN */
    na = LENGTH(CADR(args));
    nb = LENGTH(CADDR(args));
    if (na < 1 || nb < 1)
    {
	for (i = 0; i < n; i++)
	    REAL(x)[i] = NA_REAL;
    }
    /* Otherwise, dispatch to appropriate r* function */
    else
    {
	PROTECT(a = coerceVector(CADR(args), REALSXP));
	PROTECT(b = coerceVector(CADDR(args), REALSXP));
	naflag = FALSE;
	GetRNGstate();
	switch (code)
	{
	    RAND2(1, rphtype);
	default:
	    error(_("internal error in do_randomphtype2"));
	}
	if (naflag)
	    warning(R_MSG_NA);
	PutRNGstate();
	UNPROTECT(2);
    }
    UNPROTECT(1);
    return x;
}


/* Main function, the only one used by .External(). */
SEXP do_randomphtype(SEXP args)
{
    int i;
    const char *name;

    /* Extract distribution name */
    args = CDR(args);
    name = CHAR(STRING_ELT(CAR(args), 0));

    /* Dispatch to do_random{1,2,3,4} */
    for (i = 0; fun_tab[i].name; i++)
    {
	if (!strcmp(fun_tab[i].name, name))
	    return fun_tab[i].cfun(fun_tab[i].code, CDR(args));
    }

    /* No dispatch is an error */
    error(_("internal error in do_randomphtype"));

    return args;		/* never used; to keep -Wall happy */
}