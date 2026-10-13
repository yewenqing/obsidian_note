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

Here  $\mathbb E[(1-\alpha x_t^2)\delta_t]$ can be splits into $\mathbb E[(1-\alpha x_t^2)] \mathbb E[\delta_t]$ is because $x_t$ and $\delta_t$ are independent to each others

To Prove:
	when $w_0 = 0:$
$$\mathbb E[w_t]=\left(1-(1-\alpha)^t\right)w^\star$$

Since:
	$$
	 \mathbb E[\delta_{t+1}] = (1-\alpha)\mathbb E[\delta_t]
	$$
Therefore:
$$\mathbb E[\delta_{t}] = (1-\alpha)^t\mathbb E[\delta_0]$$


$$
\begin{aligned}
\mathbb E[w_t] &= \mathbb[\delta_t] + \mathbb[w^*]\\
&= (1-\alpha)^t\mathbb E[\delta_0] + w^*\\
&= (1-\alpha)^t\mathbb E[w_0 - w^*] + w^*\\
\text{If $w_0=0$}:\\
&= 1-(1-\alpha)^tw^* \\
\end{aligned}
$$

Thus, when $w_0=0$:
$$\mathbb E[w_t] =  1-(1-\alpha)^tw^*$$

If $t$ approaches infinity, $\mathbb{E}[w_t]$ converges to $w^*$ when $\alpha$ is in the interval $(0, 2)$.
### (f)
$$
\begin{aligned}
 \mathbb E[\delta_{t+1}^2] &= \mathbb E[((1-\alpha x_t^2)\delta + \alpha \eta_t x_t)^2]\\
 &= \mathbb E[(1-\alpha x_t^2)^2\delta^2 + 2 \alpha (1-\alpha x_t^2)\delta_t\eta_t x_t + (\alpha \eta_t x_t)^2)]\\
 
 &= \mathbb E[(1-\alpha x_t^2)^2\delta^2] + 2 \alpha \mathbb E[(1-\alpha x_t^2)\delta_t x_t \eta_t] +\mathbb E [(\alpha \eta_t x_t)^2)]\\
 
 &= \mathbb E [1-2\alpha x_t^2+\alpha^2 x_t^4]\mathbb E[\delta^2] + 2 \alpha \mathbb E[(1-\alpha x_t^2)\delta_t x_t ]\mathbb E [\eta_t] +\alpha^2 \mathbb E [\eta_t^2] \mathbb E[ x_t^2]\\ 
 \text{Since: } & \mathbb E[x^2] = 1 \ \mathbb E[x^4] = 3\ \mathbb E[\eta] = 0 \   \mathbb E[\eta^2] = \sigma^2\\
 &= (1-2\alpha+3\alpha^2) \mathbb E[\delta_t^2]+\alpha^2\sigma^2 \\
 & =c_\alpha\mathbb E[\delta_t^2]+\alpha^2\sigma^2
\end{aligned}
$$

Thus:
$$\mathbb E[\delta_{t+1}^2]=c_\alpha\mathbb E[\delta_t^2]+\alpha^2\sigma^2$$


### (g)
Let $$\begin{aligned}
MSE_t &= M_t\\
c_\alpha &= c\\
\alpha^2\sigma^2 &= b
\end{aligned}$$

$$
\begin{aligned}
MSE_t&=c_\alpha MSE_{t-1}+\alpha^2\sigma^2\\
M_t &= cM_{t-1} + b\\
&=c^2M_{t-2}+cb+b\\
&=c^3M_{t-3} + c^2b + cb+b\\
&......\\
&=c^tM_0+b\sum^{t-1}_{k=0}c^k\\
\text{If $w_0=0$,$\delta_0 = -w^*$ $M_0 = w^{*2}$}\\
\text{for $c \neq 0:$}\\
&=c^tw^{*2}+b\frac{1-c^t}{1-c}\\
&= c_\alpha^t(w^\star)^2+ \frac{\alpha^2\sigma^2}{1-c_\alpha}(1-c_\alpha^t)
\end{aligned}
$$

Thus: $$\mathrm{MSE}_t =c_\alpha^t(w^\star)^2+ \frac{\alpha^2\sigma^2}{1-c_\alpha}(1-c_\alpha^t)$$

### (h)
$$
\begin{aligned}
 \lim_{t\to\infty}\mathrm{MSE}_t &= \lim_{t\to\infty} c^tw^{*2}+b\frac{1-c^t}{1-c}\\
 \text{If $|c| < 1$:}  \lim_{t\to\infty} c^t = 0\\
 &=\frac{b}{1-c}\\
 &=\frac{\alpha^2\sigma^2}{2\alpha-3\alpha^2}\\
 &=\frac{\alpha\sigma^2}{2-3\alpha}\\
\end{aligned}
$$


$$
\begin{aligned}
|1-2\alpha+3\alpha^2| < 1\\
-1<1-2\alpha+3\alpha^2 < 1\\
-2<-2\alpha+3\alpha^2<0\\
0<\alpha <\frac{2}{3}

\end{aligned}
$$Therefore when $0< \alpha < \frac{2}{3}$,  $\lim_{t\to\infty}\mathrm{MSE}_t$ will converges into $\frac{\alpha\sigma^2}{2-3\alpha}$