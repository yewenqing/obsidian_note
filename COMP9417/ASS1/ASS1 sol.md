## a
$$
\begin{aligned}
f(x) &= \frac{1}{2} \vert{}\vert{}Ax - b\vert{}\vert{}_2^2 + \frac{\gamma}{2} \vert{}\vert{}x\vert{}\vert{}_2^2 \\
&= \frac{1}{2} (Ax-b)^T(Ax-b)+ \frac{\gamma}{2} x^Tx \\
&= \frac{1}{2} (x^TA^T-b^T)(Ax-b)+ \frac{\gamma}{2} x^Tx \\
&= \frac{1}{2} (x^TA^TAx-x^TA^Tb-b^TAx-b^Tb)+\frac{\gamma}{2} x^Tx\\
&= \frac{1}{2} (x^TA^TAx-2x^TA^Tb--b^Tb)+\frac{\gamma}{2} x^Tx\\
\nabla f(x) &=  \frac{1}{2} [2A^TAx - 2A^Tb +0] + \gamma x\\
&=A^TAx-A^Tb+\gamma x\\
&= A^T(Ax-b) + \gamma x
\end{aligned}
$$
![[Pasted image 20261001011148.png]]
![[Pasted image 20261001011136.png]]

![[Pasted image 20261001011048.png]]
Since $f(x)$ is a Convex function, it's local minimum is the global minimum, therefore the algorithm converge to the true minimizer.

---
## b
Prove: 
$$\hat{\beta} = \arg \min_{\beta} L(\beta) = (I + 2\lambda p W^T W)^{-1} y$$
Given:
$$L(\beta) = \frac{1}{2p} \vert{}\vert{}y - \beta\vert{}\vert{}_2^2 + \lambda \vert{}\vert{}W\beta\vert{}\vert{}_2^2$$

$$
\begin{aligned}
L(\beta) &= \frac{1}{2p} \vert{}\vert{}y - \beta\vert{}\vert{}_2^2 + \lambda \vert{}\vert{}W\beta\vert{}\vert{}_2^2\\
&=\frac{1}{2p} (y-\beta)^T(y-\beta)+ \lambda(W\beta)^T(W\beta)\\
&=\frac{1}{2p} (y^Ty-\beta ^Ty-y^T\beta +\beta^T\beta)+ \lambda(\beta ^T W^T W\beta)\\
&=\frac{1}{2p} (y^Ty-2\beta ^Ty+\beta^T\beta)+ \lambda(\beta ^T W^T W\beta)\\
\nabla L(\beta)&=\frac{1}{2p} (0-2y+2\beta)+ 2\lambda W^T W\beta \\
&=\frac{1}{p} (\beta - y)+ 2\lambda W^T W\beta\\
\nabla L(\hat{\beta})=0 &=\frac{1}{p} (\hat{\beta} - y)+ 2\lambda W^T W\hat{\beta} \\
0 &=\hat{\beta} - y+ 2p\lambda W^T W\hat{\beta}\\
y &= \hat{\beta}+ 2p\lambda W^T W\hat{\beta}\\
y &=(I + 2p\lambda W^T W)\hat{\beta}\\
\hat{\beta} &= (I + 2p\lambda W^T W)^{-1} y
\end{aligned}
$$


![[Pasted image 20261002215742.png]]![[Pasted image 20261002215728.png]]

---
## c
![[20261001_183958.jpg]]

Therefore
$$\frac{1}{2p} \vert{}\vert{}y - \beta\vert{}\vert{}_2^2 = \frac{1}{2p} \sum^p_{i=1}{(y_i-\beta_i)^2} $$
The purpose of this term is to make $\beta$ to fit $y$ as closely as possible in order to minimize the value of this term.
$$\lambda \vert{}\vert{}W\beta\vert{}\vert{}_2^2 = \lambda \sum^{p-2}_{i=1}(\beta_i-2\beta_{i+1}+\beta_{i+2})^2 =  \lambda \sum^{p-2}_{i=1}((\beta_i-\beta_{i+1})-(\beta_{i+1} -\beta_{i+2}))^2 $$The purpose of this term is to make $\beta$ smooth, thereby preventing overfitting.

---
## d
$$
\begin{aligned}
L(\beta) &= \frac{1}{2p} \vert{}\vert{}y - \beta\vert{}\vert{}_2^2 + \lambda \vert{}\vert{}W\beta\vert{}\vert{}_2^2\\
&=\frac{1}{2p}\sum^p_{j=1}(y_i-\beta _i)^2 +\frac{\lambda}{p} \sum^p_{j=1}\vert{}\vert{}W\beta\vert{}\vert{}_2^2\\
&=\frac{1}{p}\sum^p_{j=1}\frac{1}{2}(y_i-\beta _i)^2 +\frac{1}{p} \sum^p_{j=1}\lambda \vert{}\vert{}W\beta\vert{}\vert{}_2^2\\
&=\frac{1}{p}\sum^p_{j=1}(\frac{1}{2}(y_i-\beta _i)^2 +\lambda \vert{}\vert{}W\beta\vert{}\vert{}_2^2)\\
L_j(\beta) &= \frac{1}{2}(y_i-\beta _i)^2 +\lambda \vert{}\vert{}W\beta\vert{}\vert{}_2^2
\end{aligned}
$$To Prove:
$$\nabla L_j(\beta) = [0,0,...,-(y_j-\beta_j),...]^T +  2\lambda W^T W\beta$$


Since
$$
\nabla L_j(\beta) = \frac{1}{2}\frac{\partial (y_j-\beta_j)^2}{\partial \beta} +\frac{\partial \lambda \vert{}\vert{}W\beta\vert{}\vert{}_2^2}{\partial \beta}
$$

$$
\begin{aligned}
\frac{\partial (y_j-\beta_j)^2}{\partial \beta} &= [\frac{\partial (y_j-\beta_j)^2}{\partial \beta_1} ,\frac{\partial (y_j-\beta_j)^2}{\partial \beta_2} ,...,\frac{\partial (y_j-\beta_j)^2}{\partial \beta_j} ,...]^T\\
&=[0,0,...,-2(y_j-\beta_j),...]^T

\end{aligned}
$$

$$\frac{\partial \lambda \vert{}\vert{}W\beta\vert{}\vert{}_2^2}{\partial \beta} =   2\lambda W^T W\beta$$
Therefore:
$$\nabla L_j(\beta) = [0,0,...,-(y_j-\beta_j),...]^T +  2\lambda W^T W\beta$$


---
## e
![[Pasted image 20261002232817.png]]
![[Pasted image 20261002224612.png]]

---
## f

![[Pasted image 20261002230711.png]]
![[Pasted image 20261002230543.png]]


---
## g
### (i)

Given:
$$L^{(-j)}(\beta) = \frac{1}{2p} \sum_{i \neq j} (y_i - \beta_i)^2 + \lambda \vert{}\vert{}W\beta\vert{}\vert{}_2^2$$


$$\tilde{L}(\beta) = \frac{1}{2p} \vert{}\vert{}\tilde{y} - \beta\vert{}\vert{}_2^2 + \lambda \vert{}\vert{}W\beta\vert{}\vert{}_2^2$$

To Prove:
    $$\tilde{L}(\beta) = L^{(-j)}(\beta) + \frac{1}{2p} (u_j - \beta_j)^2$$



$$
\begin{aligned}
\tilde{L}(\beta) &= \frac{1}{2p} \vert{}\vert{}\tilde{y} - \beta\vert{}\vert{}_2^2 + \lambda \vert{}\vert{}W\beta\vert{}\vert{}_2^2\\
&= \frac{1}{2p} \sum^p_{i=1}(y_i-\beta_i)^2- \frac{1}{2p}(y_j-\beta_j)+ \frac{1}{2p}(u_j - \beta_j)^2++ \lambda \vert{}\vert{}W\beta\vert{}\vert{}_2^2\\
&= L^{-j}(\beta) + \frac{1}{2p}(u_j-\beta_j)^2
\end{aligned}
$$

Since
 $$ u =\hat{\beta}^{(-j)} = argmin(L^{(-j)}(\beta)) $$
 Therefore For all $\beta$ :
 $$L^{(-j)}(\beta) \geq L^{(-j)}(u)$$
And For all $\beta$ :
$$(u_j - \beta_j)^2 \geq 0 = (u_j - u_j)^2$$

Thus $u$ is $\tilde{L}(\beta)$ 's minimum value point
### (ii)

$$
\begin{aligned}
\tilde{L}(\beta) &=  L^{-j}(\beta) + \frac{1}{2p}(u_j-\beta_j)^2\\
\nabla \tilde{L}(\beta) &=  \nabla  L^{-j}(\beta) +  \frac{1}{2p}\nabla(u_j-\beta_j)^2 \\
&=\frac{1}{p}((\beta - y) - (\beta_j-y_j)e_j) + 2\lambda W^TW\beta + \frac{1}{p}(\beta_j- u_j)e_j\\
&= \frac{1}{p}((\beta - y) - ( \beta _j -y_j)e_j + (\beta_j- u_j)e_j) + 2\lambda W^TW\beta \\
&= \frac{1}{p}((\beta -\beta_je_j + \beta_je_j) - (y - y_je_j+u_je_j)) + 2\lambda W^TW\beta \\
&= \frac{1}{p}(\beta- \tilde{y}) + 2\lambda W^TW\beta \\
0 &=  \frac{1}{p}(u- \tilde{y}) + 2\lambda W^TWu\\
0 &= u- \tilde{y} + 2p\lambda W^TWu\\
\tilde{y} &=  u+ 2p\lambda W^TWu\\
\tilde{y} &=  (I + 2p\lambda W^TW)u\\
u &= (I + 2p\lambda W^TW)^{-1} \tilde{y}\\
u &= S \tilde{y}
\end{aligned}
$$


### (iii)

To Prove:
$$ y_j-u_j = \frac{y_j  - \beta_j}{1-S_{jj}} $$
Since

$$
\begin{aligned}
u &= S\tilde{y}\\
u_j & =e_j^TS\tilde{y}\\
\\
\hat{\beta} &= Sy\\
\beta_j & =e_j^TS{y}\\
\end{aligned}
$$

$$
\begin{aligned}

u_j - \beta_j & =e_j^TS\tilde{y} - e_j^TS{y}\\
&= e_j^TS(\tilde{y} - y)\\
&= e_j^TSe_j(u_j - y_j)\\
u_j - \beta_j &= S_{jj}(u_j - y_j)\\
y_j + u_j - \beta_j &= y_j + S_{jj}u_j - S_{jj}y_j\\
y_j  - \beta_j &= y_j- u_j + S_{jj}u_j - S_{jj}y_j\\
&= (1-S_{jj})(y_j-u_j)\\
\frac{y_j  - \beta_j}{1-S_{jj}} &= y_j-u_j
\end{aligned}
$$


$$
CV(\lambda) = \frac{1}{p} \sum_{j=1}^{p} (y_j - \hat{\beta}_j^{(-j)})^2 = \frac{1}{p} \sum_{j=1}^{p} (y_j - u_j)^2 = \frac{1}{p} \sum_{j=1}^{p} \left( \frac{y_j - \hat{\beta}_j}{1 - S_{jj}} \right)^2
$$

### (iv)
For each $\lambda$, the matrix $S=(I+2\lambda pW^TW)^{-1}$ and the $\hat\beta=Sy$ only need to be computed once. Hence, we not need to compute $\hat{\beta}^{-j}$ for $j$ in $1$ to $p$.



---
## h
![[Pasted image 20261003083736.png]]



| index | direct              | shortcut            | abs difference         |
| ----- | ------------------- | ------------------- | ---------------------- |
| 0     | 6.766953130133532   | 6.766953130133521   | 1.1546319456101628e-14 |
| 75    | -0.5147178641526244 | -0.5147178641526224 | 1.9984014443252818e-15 |
| 149   | -6.280030686138764  | -6.28003068613876   | 3.552713678800501e-15  |


Largest difference: 1.1546319456101628e-14
Selected lambda: 0.001
Selected CV: 2.624132717945774
CV at lambda=0.9: 5.967694398878391

![[Pasted image 20261003085706.png]]![[Pasted image 20261003085734.png]]


---
## i
$$
\begin{aligned}
y_i &= \beta^*_j+\epsilon_j\\
(y_i -\hat{\beta}^{(-j)}_j)^2 &= (\beta^*_j -\hat{\beta}^{(-j)}_j +\epsilon_j)^2\\
&= (\beta^*_j -\hat{\beta}^{(-j)}_j)^2 + 2(\beta^*_j -\hat{\beta}^{(-j)}_j)\epsilon_j + \epsilon_j^2 \\
\mathbb{E}[(y_i -\hat{\beta}^{(-j)}_j)^2]&= \mathbb{E}[(\beta^*_j -\hat{\beta}^{(-j)}_j)^2] + 2\mathbb{E}[(\beta^*_j -\hat{\beta}^{(-j)}_j)\epsilon_j] + \mathbb{E}[\epsilon_j^2]\\
&= \mathbb{E}[(\beta^*_j -\hat{\beta}^{(-j)}_j)^2] + \sigma^ 2\\
\\
\mathbb{E}[CV(\lambda)] &= \frac{1}{p} \sum_{j=1}^{p}\mathbb{E}[(y_j - \hat{\beta}_j^{(-j)})^2]\\
&=  \frac{1}{p} \sum_{j=1}^{p} \mathbb{E}[(\beta^*_j -\hat{\beta}^{(-j)}_j)^2] + \sigma^ 2\\
&= \sigma^2 + \frac{1}{p} \sum_{j=1}^{p} \mathbb{E}[(\hat{\beta}_j^{(-j)} - \beta_j^*)^2]
\end{aligned}
$$
![[Pasted image 20261003095657.png]]

![[Pasted image 20261003095723.png]]

| Rule               | Average reconstruction error |
| ------------------ | ---------------------------: |
| CV-selected        |                     0.005070 |
| Fixed lambda=0.001 |                     0.032614 |
| Oracle             |                     0.004511 |
Conclusion:
The Oracle achieves the lowest average reconstruction error; the results from the CV-selected method are very close to those of the Oracle and significantly lower than those obtained with a fixed $\lambda=0.001$; using the CV-selected method is the optimal solution when $\beta^*$is unknown.