/*  ===== actuar: an R package for Actuarial Science =====
 *
 *  Table of functions internal to the package. First element is an
 *  argument to one of do_math or do_random, functions callable from
 *  .External(); second element is the C function actually called;
 *  third element is a code used in the latter.
 *
 *  Idea taken from R sources (see .../src/main/names.c).
 *
 *  AUTHOR: Vincent Goulet <vincent.goulet@act.ulaval.ca>
 */

#include <Rinternals.h>
#include "actuar.h"

FUNTAB fun_tab[] = { 
    /* DENSITY, CUMULATIVE PROBABILITY AND QUANTILE FUNCTIONS */
    /* One parameter distributions */
    {"dinvexp",		do_dpq1,	1},
    {"pinvexp",		do_dpq1,	2},
    {"qinvexp",		do_dpq1,	3},
    /* Two parameter distributions */
    {"dinvparalogis",	do_dpq2,	1},
    {"dpareto",		do_dpq2,	1},
    {"ppareto",		do_dpq2,	2},
    {"qpareto",		do_dpq2,	3},
    {"dinvpareto",	do_dpq2,	4},
    {"dpareto1",	do_dpq2,	7},
    {"ppareto1",	do_dpq2,	8},
    {"qpareto1",	do_dpq2,	9},
    {"dinvweibull",	do_dpq2,	9},
    /* Three parameter distributions */
    {"dburr",	        do_dpq3,	0},
    {"pburr",	        do_dpq3,	1},
    {"qburr",	        do_dpq3,	2},
    {"dgenpareto",	do_dpq3,	3},
    {"pgenpareto",	do_dpq3,	4},
    {"qgenpareto",	do_dpq3,	5},
    /* Four parameter distributions */
    {"dtrbeta",		do_dpq4,	1},
    {"ptrbeta",		do_dpq4,	2},
    {"qtrbeta",		do_dpq4,	3},
	
    /* RANDOM NUMBERS FUNCTIONS */
    /* Two parameter distributions */
    {"rllogis", 	do_random2,	0},
    {"rparalogis", 	do_random2,	1},
    {"rinvparalogis", 	do_random2,	1},
    {"rpareto", 	do_random2,	2},
    {"rinvpareto", 	do_random2,	2},
    {"rpareto1", 	do_random2,	6},
    {"rinvweibull",	do_random2,	5},               
    /* Three parameter distributions */
    {"rgenpareto", 	do_random3,	0},
    {"rburr", 		do_random3,	1},
    {"rinvburr", 	do_random3,	2},
    /* Four parameter distributions */
    {"rtrbeta", 	do_random4,	0},
    {0, 0, 0}
};
