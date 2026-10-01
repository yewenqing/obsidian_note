
  

### COMP9417 - 机器学习

#### 辅导课：回归 I - 答案

在本辅导课中，我们探讨了线性回归的理论基础。我们首先研究了 1 维线性回归（单变量线性回归），然后将分析扩展到多元线性回归。如果您对本辅导课中涉及的数学知识感到不确定，我们强烈建议阅读教材中对应的章节（该书在网上可免费获取）： _数学与机器学习（Mathematics for Machine Learning）_，作者：Marc Peter Deisenroth、A. Aldo Faisal 和 Cheng Soon Ong。 在整个课程中，我们将其简称为 MML 书籍。

  

#### 问题 1.（单变量最小二乘法）

单变量线性回归模型是一个线性方程 $y = w_0 + w_1 x$。学习该模型需要将其拟合到训练数据样本 $(x_1, y_1), \dots, (x_n, y_n)$ 中，以最小化损失（通常为均方误差 MSE），即 $\mathcal{L} = \frac{1}{n}\sum_{i=1}^{n}(y_{i}-(w_{0}+w_{1}x_{i}))^{2}$。为了找到使该误差函数最小化的最佳参数 $w_0$ 和 $w_1$，我们需要求出误差梯度 $\frac{\partial\mathcal{L}}{\partial w_{0}}$ 和 $\frac{\partial\mathcal{L}}{\partial w_{1}}$。因此，我们需要通过求偏导数来推导这些表达式，将它们设为零，并求解 $w_0$ 和 $w_1$。

  

##### (a) 推导单变量线性回归模型的最小二乘估计量（MSE 损失函数的极小值点）。

**解答：**

首先，将单变量线性回归 $y = w_0 + w_1 x$ 的损失函数写为：

  

$$\mathcal{L} = \mathcal{L}(w_0, w_1) = \frac{1}{n}\sum_{i=1}^{n}(y_{i}-(w_{0}+w_{1}x_{i}))^{2} = \frac{1}{n}\sum_{i=1}^{n}(y_{i}-w_{0}-w_{1}x_{i})^{2}$$

在损失函数 $\mathcal{L}$ 的极小值点处，关于 $w_0$ 和 $w_1$ 的偏导数应当为零。我们首先对 $w_0$ 求偏导：

  

$$\frac{\partial\mathcal{L}}{\partial w_{0}} = \frac{\partial}{\partial w_{0}}\frac{1}{n}\sum_{i=1}^{n}(y_{i}-w_{0}-w_{1}x_{i})^{2}$$

$$= \frac{1}{n}\sum_{i=1}^{n}\frac{\partial}{\partial w_{0}}(y_{i}-w_{0}-w_{1}x_{i})^{2}$$

$$= \frac{1}{n}\sum_{i=1}^{n}-2(y_{i}-w_{0}-w_{1}x_{i})$$

$$= -2 \left[\frac{1}{n}\sum_{i=1}^{n}y_{i}-w_{0}\frac{1}{n}\sum_{i=1}^{n}1-w_{1}\frac{1}{n}\sum_{i=1}^{n}x_{i}\right]$$

$$= -2[\overline{y}-w_{0}-w_{1}\overline{x}]$$

其中，我们引入了记号 $\overline{f}$ 来表示 $f$ 的样本平均值，即 $\overline{f} = \frac{1}{m}\sum_{j=1}^{m}f_j$（此处样本量为 $n$）。现在，将其设为零并求解 $w_0$：

  

$$-2[\overline{y}-w_{0}-w_{1}\overline{x}] = 0 \implies w_{0}=\overline{y}-w_{1}\overline{x}$$

注意，我们尚未真正解出 $w_0$，因为该表达式依赖于 $w_1$，而我们同样需要对 $w_1$ 进行优化。接下来，对 $w_1$ 求偏导：

  

$$\frac{\partial\mathcal{L}}{\partial w_{1}} = \frac{\partial}{\partial w_{1}}\frac{1}{n}\sum_{i=1}^{n}(y_{i}-w_{0}-w_{1}x_{i})^{2}$$

$$= \frac{1}{n}\sum_{i=1}^{n}-2x_{i}(y_{i}-w_{0}-w_{1}x_{i})$$

$$= -2 \left[\frac{1}{n}\sum_{i=1}^{n}x_{i}y_{i}-w_{0}\frac{1}{n}\sum_{i=1}^{n}x_{i}-w_{1}\frac{1}{n}\sum_{i=1}^{n}x_{i}^{2}\right]$$

$$= -2[\overline{xy}-w_{0}\overline{x}-w_{1}\overline{x^{2}}]$$

现在，将其设为零并求解 $w_1$：

  

$$-2[\overline{xy}-w_{0}\overline{x}-w_{1}\overline{x^{2}}] = 0 \implies w_{1} = \frac{\overline{xy}-w_{0}\overline{x}}{\overline{x^{2}}}$$

我们现在得到了一个用 $w_1$ 表示 $w_0$ 的表达式，以及一个用 $w_0$ 表示 $w_1$ 的表达式。这些被称为**正规方程（Normal Equations）**。为了得到 $w_0$ 和 $w_1$ 的显式解，我们可以将 $w_0$ 代入 $w_1$ 的方程中并求解：

  

$$w_{1} = \frac{\overline{xy}-w_{0}\overline{x}}{\overline{x^{2}}}$$

$$= \frac{\overline{xy}-(\overline{y}-w_{1}\overline{x})\overline{x}}{\overline{x^{2}}}$$

$$= \frac{\overline{xy}-\overline{x}\overline{y}+w_{1}\overline{x}^{2}}{\overline{x^{2}}}$$

重新排列并求解 $w_1$ 可得：

  

$$w_{1} = \frac{\overline{xy}-\overline{x}\overline{y}}{\overline{x^{2}}-\overline{x}^{2}}$$

至此，我们得到了回归参数 $w_0$ 和 $w_1$ 的显式解，推导完成。

  

##### (b) 证明数据的中心点（即点 $(\overline{x}, \overline{y})$）始终在最小二乘回归线上。

**解答：**

最小二乘回归线为：

  

$$\hat{y}(x) = w_{0}+w_{1}x$$

$$= (\overline{y}-\frac{\overline{xy}-\overline{x}\overline{y}}{\overline{x^{2}}-\overline{x}^{2}}\overline{x})+(\frac{\overline{xy}-\overline{x}\overline{y}}{\overline{x^{2}}-\overline{x}^{2}})x$$

其中“hat（帽子）”符号通常表示估计值或预测值，在此情况下，$\hat{y}(x)$ 是我们在评估点 $x$ 处对 $y$ 的估计。代入 $x = \overline{x}$ 可得：

  

$$\hat{y}(\overline{x}) = \overline{y}$$

因此，最小二乘回归线必然穿过数据中心点：$(\overline{x}, \overline{y})$。

  

##### (c) 为了确保您理解这一过程，请尝试求解带有“L2”正则化版本的线性回归损失函数，其中我们添加了一个惩罚 $w_1$ 大小的惩罚项。设 $\lambda > 0$，并考虑正则化损失：

$$\mathcal{L}(w_{0},w_{1})=\frac{1}{n}\sum_{i=1}^{n}(y_{i}-(w_{0}+w_{1}x_{i}))^{2}+\lambda w_{1}^{2}$$

**解答：**

对新问题重复上述步骤可得：

  

$$w_{0}=\overline{y}-w_{1}\overline{x}$$

$$w_{1}=\frac{\overline{xy}-\overline{x}\overline{y}}{\overline{x^{2}}-\overline{x}^{2}+\lambda}$$

#### 问题 2.（多元最小二乘法）

在上一个问题中，我们找到了单变量（单特征）问题的最小二乘解。现在我们将此推广到具有 $p$ 个特征的情况。设 $x_1, x_2, \dots, x_n$ 是 $\mathbb{R}^p$ 中的 $n$ 个特征向量（例如对应于 $n$ 个样本）：

我们将这些特征向量堆叠成一个单一矩阵 $X \in \mathbb{R}^{n \times p}$，称为**设计矩阵（design matrix）**。惯例是将特征向量堆叠，使得 $X$ 的每一行对应一个特定的样本：

  

$$x_{i}=[\begin{matrix}x_{i0}\\ x_{i1}\\ \vdots\\ x_{ip-1}\end{matrix}], \quad X=[\begin{matrix}x_{1}^{T}\\ x_{2}^{T}\\ \vdots\\ x_{n}^{T}\end{matrix}]=[\begin{matrix}x_{10}&x_{11}&\cdot\cdot\cdot&x_{1,p-1}\\ x_{20}&x_{21}&\cdot\cdot\cdot&x_{2p-1}\\ \vdots&\vdots&\vdots&\vdots\\ x_{n0}&x_{n1}&\cdot\cdot\cdot&x_{n,p-1}\end{matrix}]$$

其中上标 $T$ 表示转置操作。注意，标准做法是将特征向量的第一个元素设为 1 以处理偏置项，因此我们假设对于所有 $i = 1, \dots, n$，都有 $x_{i0} = 1$。与前一个问题类似，目标是学习一个权重向量 $w \in \mathbb{R}^p$ 并进行预测：

  

$$\hat{y}_{i}=w^{T}x_{i}=w_{0}+w_{1}x_{i1}+w_{2}x_{i2}+\cdot\cdot\cdot+w_{p-1}x_{i,p-1}$$

其中 $\hat{y}_i$ 表示第 $i$ 个预测值。为了求解 $w$ 中的最优权重，我们可以使用与之前相同的程序并采用 MSE：

  

$$\mathcal{L}(w_{0},w_{1},...,w_{p-1})=\frac{1}{n}\sum_{i=1}^{n}(y_{i}-\hat{y}_{i})^{2}=\frac{1}{n}\sum_{i=1}^{n}(y_{i}-(w_{0}+w_{1}x_{i1}+w_{2}x_{i2}+\cdot\cdot\cdot+w_{p-1}x_{i,p-1}))^{2}$$

解决该问题的一种方法是对 $p$ 个权重中的每一个分别求导并求解得到的方程，但这将极其繁琐。更高效的方法是借助矩阵符号。我们可以将上述损失写为：

  

$$\mathcal{L}(w)=\frac{1}{n}\vert{}\vert{}y-Xw\vert{}\vert{}_{2}^{2}$$

其中 $\vert{}\vert{}\cdot\vert{}\vert{}_2$ 是欧几里得范数。在本问题的其余部分，我们假设 $X$ 是一个满秩矩阵，这意味着我们能够计算 $X^T X$ 的逆矩阵。

  

##### (a) 证明 $\mathcal{L}(w)$ 具有一个临界点：

$$\hat{w}=(X^{T}X)^{-1}X^{T}y$$

注意：此处的临界点意味着 $\left(\frac{d\mathcal{L}(w)}{dw}\right)(\hat{w})=0$（即在临界点处求值的梯度为零）。

_提示 1_：如果 $u$ 是 $\mathbb{R}^n$ 中的向量， $v$ 是 $\mathbb{R}^n$ 中的固定向量，则 $\frac{\partial v^{T}u}{\partial u}=v$。

_提示 2_：如果 $A$ 是固定的 $n \times n$ 矩阵，且 $f = z^T A z$，则 $\frac{\partial u^{T}Au}{\partial u}=Au+A^{T}u$。

  

**解答：**

我们有：

  

$$\vert{}\vert{}y-Xw\vert{}\vert{}_{2}^{2}=(y-Xw)^{T}(y-Xw) = y^{T}y-2y^{T}Xw+w^{T}X^{T}Xw$$

为了最小化上述表达式，我们对 $w$ 求导并令其等于零：

  

$$\frac{d}{dw}(y^{T}y-2y^{T}Xw+w^{T}X^{T}Xw) = -2X^{T}y+2X^{T}Xw \overset{\text{set}}{=} 0$$

求解上式中的 $w$ 可得：

  

$$2X^{T}Xw = 2X^{T}y \implies \hat{w}=(X^{T}X)^{-1}X^{T}y$$

##### (b) 条件 $\left(\frac{d\mathcal{L}(w)}{dw}\right)(\hat{w})=0$ 是证明 $w$ 是 $\mathcal{L}$ 的（全局）极小值点的必要条件，但不是充分条件，因为该点可能是一个局部极小值点或鞍点。证明 (a) 部分中的临界点确实是 $\mathcal{L}$ 的全局极小值点。

_提示 1_：$\mathcal{L}(w)$ 是 $w \in \mathbb{R}^p$ 的函数，因此其海森矩阵 $H$ 是二阶偏导数的 $p \times p$ 矩阵，即 $H$ 的 $(k,l)$ 个元素为 $H_{kl}=\frac{\partial^{2}\mathcal{L}(w)}{\partial w_{k}\partial w_{l}}$。我们通常写作 $H=\nabla_{w}^{2}\mathcal{L}(w)$。注意海森矩阵在多元函数中扮演二阶导数角色。

_提示 2_：如果函数的海森矩阵是半正定的，则该函数是凸函数，这意味着对于任何向量 $u$，都有 $u^T Hu \ge 0$。

_提示 3_：凸函数的任何临界点都是全局最小值。

  

**解答：**

利用第一个提示，我们首先计算 $\mathcal{L}$ 的海森矩阵：

  

$$\nabla_{w}^{2}\mathcal{L}(w)=\nabla_{w}(\nabla_{w}\mathcal{L}(w)) = \nabla_{w}(-2X^{T}y+2X^{T}Xw) = 2X^{T}X$$

然后，对于任意向量 $u \in \mathbb{R}^p$，我们有：

  

$$u^{T}(2X^{T}X)u=2(Xu)^{T}(Xu)=2\vert{}\vert{}Xu\vert{}\vert{}_{2}^{2}\ge 0$$

因为范数总是非负的。因此，$\mathcal{L}$ 确实是凸函数，故前面求出的临界点确实是 $\mathcal{L}$ 的全局极小值点。

  

##### (c) 在接下来的部分中，我们将使用上面推导的公式来验证我们在单变量情况下的解。假设 $p=2$，写出以下各项的值：$x_i, y, w, X, X^T X, (X^T X)^{-1}, X^T y$。

**解答：**

我们有以下结果：

  

$$x_{i}=[\begin{matrix}1\\ x_{i1}\end{matrix}]\in\mathbb{R}^{2}, \quad y=[\begin{matrix}y_{1}\\ y_{2}\\ \vdots\\ y_{n}\end{matrix}]\in\mathbb{R}^{n}, \quad w=[\begin{matrix}w_{0}\\ w_{1}\end{matrix}]\in\mathbb{R}^{2}$$

$$X=[\begin{matrix}1&x_{11}\\ 1&x_{21}\\ \vdots&\vdots\\ 1&x_{n1}\end{matrix}]\in\mathbb{R}^{n\times 2}$$

$$X^{T}X=[\begin{matrix}n&n\overline{x}\\ n\overline{x}&n\overline{x^{2}}\end{matrix}]\in\mathbb{R}^{2\times 2}$$

$$(X^{T}X)^{-1}=\frac{1}{n(\overline{x^{2}}-\overline{x}^{2})}[\begin{matrix}\overline{x^{2}}&-\overline{x}\ -\overline{x}&1\end{matrix}], \quad X^{T}y=[\begin{matrix}n\overline{y}\ n\overline{xy}\end{matrix]$

  

##### (d) 使用上一部分的结果计算 $p=2$ 情况下的最小二乘估计。

**解答：**

将 (a) 和 (b) 部分的结果组合起来：

  

$$\hat{w}=(X^{T}X)^{-1}X^{T}y=[\begin{matrix}\overline{y}-w_{1}\overline{x}\\ \frac{\overline{xy}-\overline{x}\overline{y}}{\overline{x^{2}}-\overline{x}^{2}}\end{matrix}]$$

这与前一个问题中使用蛮力方法得到的结果完全相同。

  

##### (e) 考虑以下问题：输入 $x_1, \dots, x_5 = 3, 6, 7, 8, 11$，输出 $y_1, \dots, y_5 = 13, 8, 11, 2, 6$。通过手算和 Python 计算最小二乘解并绘图，最后用 sklearn 验证。

**解答：**

对应的 Python 代码如下：

  

Python

```
import matplotlib.pyplot as plt
import numpy as np
from sklearn import linear_model

y = np.array([13, 8, 11, 2, 6])
x = np.array([3, 6, 7, 8, 11])
n = x.shape[0]

# 构造设计矩阵 X
X = np.concatenate([np.ones((n, 1)), x.reshape(-1, 1)], axis=1)

# 计算最小二乘解
XTX = X.T @ X
XTXinv = np.linalg.inv(XTX)
XTy = X.T @ y
least_squares_estimate = XTXinv @ XTy

# sklearn 比较
model = linear_model.LinearRegression()
model.fit(x.reshape(-1, 1), y)

# 绘图
xx = np.linspace(0, 13, 1000)
plt.scatter(x, y, color="red")
# 假设拟合直线方程
plt.plot(xx, model.intercept_ + model.coef_[0] * xx, color="blue", label='fit')
plt.legend()
plt.xlabel('X')
plt.ylabel('y')
plt.savefig("LSLine.png")
plt.show()
```

##### (f) 进阶：如果 $X$ 不是满秩矩阵会发生什么？最小二乘法会失效吗？

**解答：**

答案是不会。我们可以使用一种称为伪逆（pseudo-inverse）**或**摩尔-彭罗斯伪逆（Moore-Penrose Inverse）的方法。在 NumPy 中，可以通过命令 `np.linalg.pinv` 轻松计算伪逆。

  

##### (g) 讨论特征映射（feature map）的概念。如何在最小二乘回归中使用特征映射？

**解答：**

如果我们处理的数据包含 $(x_i, y_i)$，其中 $x_i \in \mathbb{R}^p$，特征映射就是任何将数据从原始 $p$ 维空间映射到某个新 $K$ 维空间的函数 $\phi: \mathbb{R}^p \rightarrow \mathbb{R}^K$。例如当 $p=1$ 时：

  

$$\phi(x) = [x, x^2, x^3, \log x]^T$$

我们的模型变为：

  

$$\hat{y}_{i}=w^{T}\phi(x_{i})$$

我们构建新的设计矩阵 $\Phi \in \mathbb{R}^{n \times K}$：

  

$$\Phi=[\begin{matrix}\phi(x_{1})^{T}\\ \phi(x_{2})^{T}\\ \vdots\\ \phi(x_{n})^{T}\end{matrix}]$$

并求解相同的最小化问题：

  

$$\hat{w} = \arg\min_{w\in\mathbb{R}^{K}}\frac{1}{n}\vert{}\vert{}y-\Phi w\vert{}\vert{}_{2}^{2} \implies \hat{w}=(\Phi^{T}\Phi)^{-1}\Phi^{T}y$$

##### (h) 均方误差（MSE）为 $\text{MSE}(w)=\frac{1}{n}\vert{}\vert{}y-Xw\vert{}\vert{}_{2}^{2}$，而误差平方和（SSE）为 $\text{SSE}(w)=\vert{}\vert{}y-Xw\vert{}\vert{}_{2}^{2}$。判断以下陈述真伪并解释：

(i) $\arg\min_{w\in\mathbb{R}^{p}}\text{MSE}(w)=\arg\min_{w\in\mathbb{R}^{p}}\text{SSE}(w)$

(ii) $\min_{w\in\mathbb{R}^{p}}\text{MSE}(w)=\min_{w\in\mathbb{R}^{p}}\text{SSE}(w)$

  

**解答：**

  

- 第 (i) 个陈述是**正确的**，但第 (ii) 个陈述是**不正确的**。
    
      
    
- 通过将函数乘以一个正常数，其极小值点（arg min）保持不变。然而，最小值（min）本身会受到常数因子的影响。
    
      
    
- 在寻找最小二乘问题的最优权重 $w$ 时，使用 MSE 还是 SSE 得到的解是完全相同的。但 MSE 能够反映模型产生的平均平方误差，而 SSE 表示总平方误差，MSE 在样本量不同时更具可比性和意义。
    
      
    

#### 问题 3.（总体与样本参数）

##### (a) 总体和样本有什么区别？

**解答：**

  

- 总体（Population）**是我们希望了解其性质的全体对象，而**样本（Sample）是我们能够获取到的总体子集。例如在新冠疫苗试验中，总体是全人类，而样本是参与临床试验的一小部分具有代表性的人群。
    
      
    

##### (b) 什么是总体参数？我们如何对其进行估计？

**解答：**

  

- 总体参数是未知的、希望通过数据进行估计的量（例如总体均值 $\mu$）。
    
      
    
- 我们通常使用样本统计量（如样本均值 $\overline{X} = \frac{1}{n}\sum X_i$）作为总体参数的估计量。总体参数通常用希腊字母（如 $\mu, p$）表示。