# Dynamic-Delta-Hedging
Implementing a dynamic delta hedging strategy for google stock
Delta-hedging is a hedging strategy that aims to replicate the value of a financial derivative, such as a
Call option, written on a traded asset through dynamically buying (or selling) a proper number of shares of
the underlying asset and borrowing from (or lending to) a bank.
Description of the delta-hedging process:
1. Let the hedging period be from a start-date t0 to an end-date tN . At start date t0, assuming there is
an initial cash position in the amount of $0.
2. At t0, we sell a European call option contract with expiration date T, strike price K. Assume the
option contract is written on one share of stock and t0 < tN ≤ T.
3. To hedge the short position in the European call, we decide to buy δ shares of the underlying stock
at t0, where δ =
∂V
∂S is the rate of change of option value V with respect to changes in the underlying
price S.
4. As δ changes during the hedging period, we need to re-balance our portfolio (buy/sell stocks) everyday
to maintain a long position of δi shares of stock for each date ti
, i = 1, 2, ..., N. δi shall be calculated
using implied volatility for each date.
5. For each date ti
, i = 1, 2, ..., N, calculate the cumulative hedging error till ti
:
HEi = δi−1Si + Bi−1e
ri−1∆t − Vi
where Bi = δi−1Si + Bi−1e
ri−1δt − δiSi (i ≥ 1) and B0 = V0 − δ0S0. Si
, Vi
, ri respectively denote the
stock price, option price, risk-free rate at time ti
, i = 0, 1, ..., N. ∆t represents 1 business day, which is
1
252 year.
6. For each date ti
, two types of profit-and-loss (PNL) of selling a Call option at time 0 are defined as
follows. Assume no transaction costs.
• PNL = Call option market quote at time 0 – Call option market quote at time ti
.
• PNL with hedge = Cumulative hedging error.
