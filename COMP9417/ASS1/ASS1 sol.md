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


![[Pasted image 20261001181444.png]]![[Pasted image 20261001181512.png]]

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
$$\nabla L_j(\beta) = [0,0,...,-(y_j-\beta_j),...]^T +  2\lambda W^T W\hat{\beta}$$


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

$$\frac{\partial \lambda \vert{}\vert{}W\beta\vert{}\vert{}_2^2}{\partial \beta} =   2\lambda W^T W\hat{\beta}$$
Therefore:
$$\nabla L_j(\beta) = [0,0,...,-(y_j-\beta_j),...]^T +  2\lambda W^T W\hat{\beta}$$