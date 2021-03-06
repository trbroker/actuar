\name{Burr}
\alias{Burr}
\alias{dburr}
\alias{pburr}
\alias{qburr}
\alias{rburr}
\alias{mburr}
\alias{levburr}
\title{The Burr Distribution}
\description{
  Density function, distribution function, quantile function, random generation,
  raw moments and limited moments for the Burr distribution with
  parameters \code{shape1}, \code{shape2} and \code{scale}.
}
\usage{
dburr(x, shape1, shape2, rate = 1, scale = 1/rate,
      log = FALSE)
pburr(q, shape1, shape2, rate = 1, scale = 1/rate,
      lower.tail = TRUE, log.p = FALSE)
qburr(p, shape1, shape2, rate = 1, scale = 1/rate,
      lower.tail = TRUE, log.p = FALSE)
rburr(n, shape1, shape2, rate = 1, scale = 1/rate)
mburr(order, shape1, shape2, rate = 1, scale = 1/rate)
levburr(limit, shape1, shape2, rate = 1, scale = 1/rate,
        order = 1)
}
\arguments{
  \item{x, q}{vector of quantiles.}
  \item{p}{vector of probabilities.}
  \item{n}{number of observations. If \code{length(n) > 1}, the length is
    taken to be the number required.}
  \item{shape1, shape2, scale}{parameters. Must be strictly positive.}
  \item{rate}{an alternative way to specify the scale.}
  \item{log, log.p}{logical; if \code{TRUE}, probabilities/densities
    \eqn{p} are returned as \eqn{\log(p)}{log(p)}.}
  \item{lower.tail}{logical; if \code{TRUE} (default), probabilities are
    \eqn{P[X \le x]}{P[X <= x]}, otherwise, \eqn{P[X > x]}.}
  \item{order}{order of the moment.}
  \item{limit}{limit of the loss variable.}
}
\details{
  The Burr distribution with parameters \code{shape1} \eqn{=
    \alpha}{= a}, \code{shape2} \eqn{= \gamma}{= b} and \code{scale}
  \eqn{= \theta}{= s} has density:
  \deqn{f(x) = \frac{\alpha \gamma (x/\theta)^\gamma}{%
      x[1 + (x/\theta)^\gamma]^{\alpha + 1}}}{%
    f(x) = (a b (x/s)^b)/(x [1 + (x/s)^b]^(a + 1))}
  for \eqn{x > 0}, \eqn{\alpha > 0}{a > 0}, \eqn{\gamma > 0}{b > 0}
  and \eqn{\theta > 0}{s > 0}.

  The Burr is the distribution of the random variable
  \deqn{\theta \left(\frac{X}{1 - X}\right)^{1/\gamma},}{%
    s (X/(1 - X))^(1/b),}
  where \eqn{X} has a beta distribution with parameters \eqn{1}
  and \eqn{\alpha}{a}.

  The Burr distribution has the following special cases:
  \itemize{
    \item A \link[=dllogis]{Loglogistic} distribution when \code{shape1
      == 1};
    \item A \link[=dparalogis]{Paralogistic} distribution when
    \code{shape2 == shape1};
    \item A \link[=dpareto]{Pareto} distribution when \code{shape2 ==
      1}.
  }

  The \eqn{k}th raw moment of the random variable \eqn{X} is
  \eqn{E[X^k]}{E[X^k]}, \eqn{-\gamma < k < \alpha\gamma}{-shape2 < k <
  shape1 * shape2}.

  The \eqn{k}th limited moment at some limit \eqn{d} is \eqn{E[\min(X,
  d)^k]}{E[min(X, d)^k]}, \eqn{k > -\gamma}{k > -shape2}
  and \eqn{\alpha - k/\gamma}{shape1 - k/shape2} not a negative integer.
}
\value{
  \code{dburr} gives the density,
  \code{pburr} gives the distribution function,
  \code{qburr} gives the quantile function,
  \code{rburr} generates random deviates,
  \code{mburr} gives the \eqn{k}th raw moment, and
  \code{levburr} gives the \eqn{k}th moment of the limited loss
  variable.

  Invalid arguments will result in return value \code{NaN}, with a warning.
}
\note{
  \code{levburr} computes the limited expected value using
  \code{\link{betaint}}.

  Distribution also known as the Burr Type XII or Singh-Maddala
  distribution. See also Kleiber and Kotz (2003) for alternative names
  and parametrizations.
}
\references{
  Kleiber, C. and Kotz, S. (2003), \emph{Statistical Size Distributions
  in Economics and Actuarial Sciences}, Wiley.

  Klugman, S. A., Panjer, H. H. and Willmot, G. E. (2012),
  \emph{Loss Models, From Data to Decisions, Fourth Edition}, Wiley.
}
\author{
  Vincent Goulet \email{vincent.goulet@act.ulaval.ca} and
  Mathieu Pigeon
}
\examples{
exp(dburr(1, 2, 3, log = TRUE))
p <- (1:10)/10
pburr(qburr(p, 2, 3, 2), 2, 3, 2)

## variance
mburr(2, 2, 3, 1) - mburr(1, 2, 3, 1) ^ 2

## case with shape1 - order/shape2 > 0
levburr(10, 2, 3, 1, order = 2)

## case with shape1 - order/shape2 < 0
levburr(10, 1.5, 0.5, 1, order = 2)
}
\keyword{distribution}
