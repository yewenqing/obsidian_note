
  

**COMP9417 - 机器学习**

**实验课（Tutorial）：回归 I**

  

在本节实验中，我们将探讨线性回归的理论基础。我们首先研究一维线性回归（单变量线性回归），然后将分析扩展到多元线性回归。如果您对本实验中涉及的任何数学知识感到不确定，我们强烈建议阅读教材中对应的章节（该书在网上可免费获取）：

《机器学习数学》（Mathematics for Machine Learning），作者：Marc Peter Deisenroth、A. Aldo Faisal 和 Cheng Soon Ong。

在整个课程中，我们将其简称为 **MML 书籍**。

  

### **问题 1.（单变量最小二乘法）**

单变量线性回归模型是一个线性方程 $y = w_0 + w_1 x$。学习这样一个模型需要将其拟合到训练数据样本 $(x_1, y_1), \dots, (x_n, y_n)$ 中，以最小化损失（通常为均方误差（MSE）），即 $\mathcal{L} = \frac{1}{n}\sum_{i=1}^{n}(y_{i}-(w_{0}+w_{1}x_{i}))^{2}$。为了找到使该误差函数最小化的最佳参数 $w_0$ 和 $w_1$，我们需要求出误差梯度 $\frac{\partial\mathcal{L}}{\partial w_{0}}$ 和 $\frac{\partial\mathcal{L}}{\partial w_{1}}$。因此，我们需要通过求偏导数来推导这些表达式，将它们设为零，并求解 $w_0$ 和 $w_1$。

  

- (a) 推导单变量线性回归模型的最小二乘估计量（MSE 损失函数的极小值点）。
    
      
    
- (b) 证明数据的中心点（即点 $\bar{x}, \bar{y}$）始终在最小二乘回归线上。
    
         
    
- (c) 为了确保您理解这一过程，请尝试求解带有某种“L2”正则化版本的线性回归损失函数，其中我们添加了一个惩罚 $w_1$ 大小的项。
    
    设 $\lambda > 0$，并考虑正则化损失：
    
      
    
    $$\mathcal{L}(w_0, w_1) = \frac{1}{n}\sum_{i=1}^{n}(y_i - (w_0 + w_1 x_i))^2 + \lambda w_1^2$$
    

### **问题 2.（多元最小二乘法）**

在上一个问题中，我们找到了单变量（单特征）问题的最小二乘解。现在我们将此推广到具有 $p$ 个特征的情况。设 $x_1, x_2, \dots, x_n$ 是 $\mathbb{R}^p$ 中的 $n$ 个特征向量（例如，对应于 $n$ 个样本），即：

  

$$x_i = \begin{bmatrix} x_{i0} \\ x_{i1} \\ \vdots \\ x_{ip-1} \end{bmatrix}$$

我们将这些特征向量堆叠成一个单一的矩阵 $X \in \mathbb{R}^{n \times p}$，称为**设计矩阵（design matrix）**。惯例是将特征向量堆叠，使得 $X$ 的每一行对应一个特定的样本，即：

  

$$X = \begin{bmatrix} x_1^T \\ x_2^T \\ \vdots \\ x_n^T \end{bmatrix} = \begin{bmatrix} x_{10} & x_{11} & \dots & x_{1,p-1} \\ x_{20} & x_{21} & \dots & x_{2,p-1} \\ \vdots & \vdots & \dots & \vdots \\ x_{n0} & x_{n1} & \dots & x_{np-1} \end{bmatrix}$$

其中上标 $T$ 表示转置操作。注意，为了处理偏置项（bias term），通常将特征向量的第一个元素取为 $1$，因此我们假定对于所有 $i = 1, \dots, n$，都有 $x_{i0} = 1$。

与前一个问题类似，目标是学习一个权重向量 $w \in \mathbb{R}^p$，并进行预测：

  

$$\hat{y}_i = w^T x_i = w_0 + w_1 x_{i1} + w_2 x_{i2} + \dots + w_{p-1} x_{i,p-1}$$

其中 $\hat{y}_i$ 表示第 $i$ 个预测值（注：原文此处 $y_i$ 笔误写作预测值，结合上下文指代预测输出）。为了求解 $w$ 中的最优权重，我们可以使用与之前相同的程序并使用 MSE：

  

$$\mathcal{L}(w_0, w_1, \dots, w_{p-1}) = \frac{1}{n}\sum_{i=1}^{n}(y_i - \hat{y}_i)^2 = \frac{1}{n}\sum_{i=1}^{n}(y_i - (w_0 + w_1 x_{i1} + w_2 x_{i2} + \dots + w_{p-1} x_{i,p-1}))^2$$

解决这个问题的一种方法是对 $p$ 个权重中的每一个分别求导并求解由此产生的方程，但这将极其繁琐。解决该问题更高效的方法是借助矩阵符号。我们可以将上述损失写为：

  

$$\mathcal{L}(w) = \frac{1}{n} \vert{}\vert{}y - Xw\vert{}\vert{}_2^2$$

其中 $\vert{}\vert{}\cdot\vert{}\vert{}_2$ 是欧几里得范数。在本问题的其余部分，我们假设 $X$ 是一个满秩矩阵（full-rank matrix），这意味着我们能够计算 $X^T X$ 的逆矩阵。

  

- (a) 证明 $\mathcal{L}(w)$ 具有一个临界点（critical point）：
    
      
    
    $$\hat{w} = (X^T X)^{-1} X^T y$$
    
    注意：此处的临界点意味着 $(\frac{d\mathcal{L}(w)}{dw})(\hat{w}) = 0$（即在临界点 $w$ 处求值的梯度为零）。
    
      
    - **提示 1**：如果 $u$ 是 $\mathbb{R}^n$ 中的向量，$v$ 是 $\mathbb{R}^n$ 中的固定向量，则 $\frac{\partial v^T u}{\partial u} = v$。
        
          
        
    - **提示 2**：如果 $A$ 是固定的 $n \times n$ 矩阵，且 $f = z^T A z$，则 $\frac{\partial u^T A u}{\partial u} = A u + A^T u$。
        
          
        
- (b) 条件 $(\frac{d\mathcal{L}(w)}{dw})(\hat{w}) = 0$ 是证明 $w$ 是 $\mathcal{L}$ 的（全局）极小值点的必要条件，但不是充分条件，因为该点可能是一个局部极小值点或鞍点。证明 (a) 部分中的临界点确实是 $\mathcal{L}$ 的全局极小值点。
    
      
    - **提示 1**：$\mathcal{L}(w)$ 是 $w \in \mathbb{R}^p$ 的函数，因此它的海森矩阵（Hessian）$H$ 是二阶偏导数的 $p \times p$ 矩阵，即 $H$ 的 $(k, l)$ 个元素为：
        
          
        
        $$H_{kl} = \frac{\partial^2 \mathcal{L}(w)}{\partial w_k \partial w_l}$$
        
        我们通常写作 $H = \nabla_w^2 \mathcal{L}(w)$，其中 $\nabla$ 是梯度算子，$\nabla^2$ 意味着求两次梯度。注意，海森矩阵在多元函数中扮演着二阶导数的角色。
        
          
        
    - **提示 2**：如果一个函数的海森矩阵是半正定的（positive semi-definite），则该函数是凸函数，这意味着对于任何向量 $u$，都有 $u^T H u \ge 0$。还要注意，这个条件意味着对于 $u$ 的任何选择，乘积项将始终是非负的。
        
          
        
    - **提示 3**：凸函数的任何临界点都是全局最小值。
        
          
        
- (c) 在接下来的部分中，我们将使用上面推导的公式来验证我们在单变量情况下的解。我们假设 $p = 2$，这样我们就有一个二维特征向量（一项用于截距，另一项用于我们的特征）。写出以下各项的值：
    
    $X$、$X^T X$、$(X^T X)^{-1}$、$X^T y$。
    
      
    
- (d) 使用上一部分的结果计算 $p = 2$ 情况下的最小二乘估计。
    
      
    
- (e) 考虑以下问题：我们有输入 $x_1, \dots, x_5 = 3, 6, 7, 8, 11$ 以及输出 $y_1, \dots, y_5 = 13, 8, 11, 2, 6$。通过手工计算和使用 Python 两种方式计算最小二乘解并绘制结果。最后，使用 `sklearn` 的实现来检查您的结果。
    
      
    
- (f) **进阶**：你们中的一些人可能会对我们假设 $X$ 是满秩矩阵感到担忧，这是一个为了确保 $X^T X$ 是可逆矩阵而做出的假设。如果 $X^T X$ 不可逆，那么我们将无法计算最小二乘解。那么如果 $X$ 不是满秩的会发生什么？最小二乘法会失效吗？答案是不会，我们可以使用一种叫做伪逆（pseudo-inverse）的东西，也称为 **摩尔-彭罗斯伪逆（Moore-Penrose Inverse）**。这超出了本课程的范围，感兴趣的读者可以参考以下笔记或 MML 的第二章。从非常高的层面来看，伪逆是一个在不可逆矩阵上表现得像逆矩阵的矩阵。在 NumPy 中，我们可以使用命令 `np.linalg.pinv` 轻松计算伪逆。
    
      
    
- (g) 讨论特征映射（feature map）的概念。在最小二乘回归的背景下，您将如何使用特征映射？
    
      
    
- (h) 均方误差（MSE）为：
    
      
    
    $$\text{MSE}(w) = \frac{1}{n} \vert{}\vert{}y - Xw\vert{}\vert{}_2^2$$
    
    而误差平方和（SSE）（也称为残差平方和（RSS））为：
    
      
    
    $$\text{SSE}(w) = \vert{}\vert{}y - Xw\vert{}\vert{}_2^2$$
    
    以下陈述是**正确**还是**错误**？请解释原因。
    
      
    
    - (i) $\arg\min_{w \in \mathbb{R}^p} \text{MSE}(w) = \arg\min_{w \in \mathbb{R}^p} \text{SSE}(w)$
        
          
        
    - (ii) $\min_{w \in \mathbb{R}^p} \text{MSE}(w) = \min_{w \in \mathbb{R}^p} \text{SSE}(w)$
        
          
        
    
    _符号说明_：回想一下，$\min_x g(x)$ 是 $g(x)$ 的最小值，而 $\arg\min_x g(x)$ 是使 $g(x)$ 最小化的 $x$ 的值。因此 $\min_x (x-2)^2 = 0$，但 $\arg\min_x (x-2)^2 = 2$。
    
      
    

### **问题 3.（总体与样本参数）**

- (a) 总体（population）和样本（sample）有什么区别？
    
      
    
- (b) 什么是总体参数（population parameter）？我们如何对其进行估计？