## 1
### (a)
$$
\begin{aligned}
L(w) &= \frac{1}{2}\mathbb{E}[(wx-y)^2]\\
\nabla L(w) &= \frac{1}{2}\mathbb{E}[(2(wx^2-yx)]\\
&= \mathbb{E}[(wx^2-yx]\\
&= \mathbb{E} [wx^2-w^*x^2 + \eta  x]\\
&= (w-w^*)\mathbb E[x^2] +\mathbb E[ \eta  x]\\
&=(w-w^*)1 +0\\
&= w-w^*
\end{aligned}
$$

### (b)
$$
\begin{aligned}
w_{t+1} &= w_t - \alpha \nabla L(w_t)\\
&=w_t-\alpha (w_t-w^*)\\
&=(1-\alpha)w_t + \alpha w^*
\end{aligned}
$$
### (c)
SGD:
	$$w_{t+1}=w_t-\alpha g_t$$

$$
\begin{aligned}
 \nabla L(w_t) &= \mathbb E[(w_tx-y)x]\\
 g_t &= (w_tx_t-y_t)x_t\\
 w_{t+1} &= w_t - \alpha(w_tx_t-y_t)x_t
\end{aligned}
$$

### (d)
To Prove:
$$ \delta_{t+1}=(1-\alpha x_t^2)\delta_t+\alpha\eta_tx_t $$
$$
\begin{aligned}
\delta_{t} &= w_{t}-w^*\\
\delta_{t+1} &= w_{t+1}-w^*\\
&= w_t- \alpha (w_tx_t-y_t)x_t-w^*\\
&=\delta_t-\alpha(w_tx_t-(w^*x_t+\eta_t))x_t\\
&=\delta_t-\alpha((w_t-w^*)x_t-\eta_t))x_t\\
&=\delta_t-\alpha(\delta_tx_t-\eta_t))x_t\\
&=(1-\alpha x_t^2)\delta_t+\alpha\eta_tx_t 
\end{aligned}
$$

The first part of the formula, $(1-\alpha x_t^2)\delta_t$, represents the accumulated bias carried over to the next epoch, while the second part, $\alpha\eta_tx_t$, represents the error generated in the current epoch.


### (e)

$$
\begin{aligned}
 \mathbb E[\delta_{t+1}] &= \mathbb E[(1-\alpha x_t^2)\delta_t] + \alpha \mathbb E[\eta_tx_t]\\
 &=  \mathbb E[(1-\alpha x_t^2)] \mathbb E[\delta_t] + 0\\
 &= (1-\alpha)\mathbb E[\delta_t]\\
\end{aligned}

$$

To Prove:
	when $w_0 = 0:$
$$\mathbb E[w_t]=\left(1-(1-\alpha)^t\right)w^\star$$

Assume