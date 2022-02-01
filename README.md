# Dynamic-Delta-Hedging
Implemented a dynamic delta hedging strategy for google stock.
Delta-hedging is a hedging strategy that aims to replicate the value of a financial derivative, such as a
Call option, written on a traded asset through dynamically managing a proper number of shares of
the underlying asset and risk free security. The complete project is written in C++ with keeping appropriate object oriented design considerations in mind. 
The delta hedging process:
1. Assuming a hedging window from t0 to tN . 
2. At t0, we sell a European call option contract with expiration date T, strike price K. Assuming the option is written on one share of stock and t0 < tN ≤ T.
3. To hedge the short position in the European call and replicate a portfolio which will pay us the same payoff, we decide to buy δ shares of the underlying stock
at t0, where δ =
∂V
∂S is the rate of change of option value V with respect to changes in the underlying
price S.
4. As δ changes during the hedging period, we need to re-balance our portfolio everyday. Denoting δi as value of δ on ith day of the trading,
Every δi has to be calculated using implied volatility for each date.
5. Cumulative hedging error/ p/l out o strategy:
HEi = δi−1Si + Bi−1 *exp(ri−1∆t) − Vi
where Bi = δi−1Si + Bi−1*exp(ri−1δt) − δiSi (i ≥ 1) and B0 = V0 − δ0S0. 
Si, Vi, ri denoting the stock price, option price, risk-free rate at time ti
, i. ∆t represents 1 business day, which is 1/252 year.

The model used for pricing option is the Black)Scholes model, where the underlying stock moves in the following fashion:
Use the following model to simulate the price series {S0, S∆t, S2∆t, · · · , ST } at N equally-spaced
time points over time horizon [0, T] where ∆t = T/N:
St+∆t = St + µSt∆t + σSt*(√∆t)*Zt,

Complete following two tasks:
1) Assuming some initial conditions, generate 100 sample paths (simulations), price delta, hedging error for each of them for every day, and calculate a final P/L for each path. (Result generated in the output csv files)
2) Use the real market data from given files in the data folder,  calculate Implied volatility, delta, hedging error everyday for the real time market data everyday for a given observation window.
3) Calculate implied volatility smile for options with different Strike price
