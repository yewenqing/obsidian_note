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