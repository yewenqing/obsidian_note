
### COMP9417 - 机器学习

#### 辅导课：回归 II

##### 问题 1. 最大似然估计 (MLE)

在本题中，我们将首先复习，然后通过几个例子来练习使用 MLE 技术进行参数估计。如果您已经熟悉 MLE 的概念，可以跳过以下引言。

  

设定如下：我们抽取 $n$ 个观测值（数据），记为 $X_1, X_2, \dots, X_n$，并假设这些数据是从某个概率分布 $P$ 中独立抽取的。简写形式为：

  

$$X_1, \dots, X_n \stackrel{\text{i.i.d.}}{\sim} P$$

其中 i.i.d. 代表独立同分布（independent and identically distributed）。在实践中，我们永远无法直接接触到 $P$，我们只能观察到来自 $P$ 的样本（即 $X_1, \dots, X_n$），并利用它们来了解 $P$ 的某些性质。在最简单的情况下，我们假设 $P$ 属于一个参数化族。例如，如果我们假设 $P$ 属于正态分布族，那么我们就是在假设 $P$ 具有以下形式的概率密度函数（pdf）：

  

$$p_{\theta}(x) = \frac{1}{\sqrt{2\pi\sigma^2}} \exp\left(-\frac{(x-\mu)^2}{2\sigma^2}\right)$$

其中 $\theta = (\mu, \sigma^2)$，$\mu \in \mathbb{R}$，$\sigma > 0$。我们通常称 $\mu$ 为均值，$\sigma^2$ 为方差，并将所有未知参数组合成一个位于某个参数空间 $\Theta$ 中的单一参数向量 $\theta$。在这个特定例子中，$\Theta = \mathbb{R} \times [0, \infty)$。在此假设下，如果我们知道 $\theta$，我们就知道了 $P$，因此学习问题就简化为学习尽可能最佳的参数 $\theta^*$，这也是“参数化”这一名称的由来。

  

继续这个例子，我们需要一种量化特定 $\theta$ 选择好坏的方法。为此，我们首先回忆这样一个事实：对于独立的集合 $A, B, C$，有 $P(A \text{ 且 } B \text{ 且 } C) = P(A)P(B)P(C)$。因此，我们有：

  

- 观测到 $X_1, \dots, X_n$ 的概率
    
      
    
- $=$ 观测到 $X_1$ 的概率 $\times \dots \times$ 观测到 $X_n$ 的概率
    
      
    
- $= p_{\theta}(X_1) \times \dots \times p_{\theta}(X_n)$
    
      
    
- $= \prod_{i=1}^{n} p_{\theta}(X_i)$
    
      
    
- $=: L(\theta)$
    
      
    

我们将 $L(\theta)$ 称为似然函数（Likelihood），它是参数向量 $\theta$ 的函数。我们将这个量解释为：在使用特定参数选择时观测到当前数据的概率。显然，我们希望选择能给我们带来最高可能似然的参数，即我们希望找到最大似然估计量：

  

$$\hat{\theta}_{\text{MLE}} := \arg\max_{\theta \in \Theta} L(\theta)$$

由于这只是一个优化问题，我们可以利用微积分的知识来求解 MLE 估计量。

  

**(a)** 假设 $X_1, \dots, X_n \stackrel{\text{i.i.d.}}{\sim} N(\mu, 1)$，也就是我们已经知道潜在分布是总体方差为 1 的正态分布，但总体均值是未知的。计算 $\hat{\mu}_{\text{MLE}}$。

_提示_：使用对数似然（log-likelihood）通常要容易得多，即求解以下优化问题：

  

$$\theta_{\text{MLE}} := \arg\max_{\theta \in \Theta} \log L(\theta)$$

这给出的答案与求解原问题完全相同（为什么？）。

  

**(b)** 假设 $X_1, \dots, X_n \stackrel{\text{i.i.d.}}{\sim} \text{Bernoulli}(p)$，计算 $\hat{p}_{\text{MLE}}$。回想一下，伯努利分布是离散的，其概率质量函数为：

  

$$\mathbb{P}(X=k) = p^k (1-p)^{1-k}, \quad k = 0, 1, \quad p \in [0, 1]$$

**(c)** 选做题：假设 $X_1, \dots, X_n \stackrel{\text{i.i.d.}}{\sim} N(\mu, \sigma^2)$。计算 $\langle \hat{\mu}_{\text{MLE}}, \hat{\sigma}_{\text{MLE}}^2 \rangle$。

  

##### 问题 2. 估计量的偏差与方差 (Bias and Variance)

在上一题中，我们讨论了作为参数估计方法的 MLE。但估计参数的方法有无数种。例如，人们可以选择使用样本中位数（sample median）而不是 MLE。拥有一个能够以系统方式比较估计量的框架是非常有用的，这就引出了机器学习中的两个核心概念：**偏差（bias）**和**方差（variance）**。

  

假设真实参数为 $\theta$，我们有一个估计量 $\tilde{\theta}$（注：原文此处符号或有混用，通常记作 $\hat{\theta}$）。注意，估计量只是观测到的（随机）数据的一个函数（即我们可以始终写出 $\hat{\theta} = \hat{\theta}(X)$），因此它本身也是一个随机变量！

因此我们可以定义：

  

$$\text{bias}(\hat{\theta}) = \mathbb{E}(\hat{\theta}) - \theta$$

$$\text{var}(\hat{\theta}) = \mathbb{E}(\hat{\theta} - \mathbb{E}(\hat{\theta}))^2$$

本周的实验也会探讨这些概念，鼓励你在完成这道题时同步去做实验练习，以获得全面的理解。用文字简短总结实验内容：

  

- **偏差（bias）**：告诉我们估计量的期望值距离真实值有多远。回想一下，估计量是我们观测到的数据样本的函数。估计量的期望可以这样想象：假设我们拥有的不是单个数据样本，而是无数个数据样本。我们在每个样本上计算相同的估计量，然后取平均值。这就是估计量的期望值。
    
      
    
- **方差（variance）**：告诉我们的估计量有多大变异性。同样，如果我们有无数个数据样本，我们就能够计算无数次估计量，并检查估计量在所有样本中的变异情况。
    
      
    

一个好的估计量应该具有低偏差和低方差。

  

**(a)** 求 $\hat{\mu}_{\text{MLE}}$ 的偏差和方差，其中 $X_1, X_2, \dots, X_n \stackrel{\text{i.i.d.}}{\sim} N(\mu, 1)$。

  

**(b)** 求 $\hat{p}_{\text{MLE}}$ 的偏差和方差，其中 $X_1, X_2, \dots, X_n \stackrel{\text{i.i.d.}}{\sim} \text{Bernoulli}(p)$。

  

**(c)** 均方误差（MSE）是统计学和机器学习中广泛使用的指标。对于真实参数 $\theta$ 的估计量 $\hat{\theta}$，我们通过以下公式定义其 MSE：

  

$$\text{MSE}(\hat{\theta}) := \mathbb{E}(\hat{\theta} - \theta)^2$$

证明 MSE 遵循偏差-方差分解，即我们可以将其写为：

  

$$\text{MSE}(\hat{\theta}) = \text{bias}(\hat{\theta})^2 + \text{var}(\hat{\theta})$$

##### 问题 3. 最小二乘回归的概率视角

在上周的辅导课中，我们纯粹从优化的角度来看待最小二乘问题。我们指定了想要拟合的模型：

  

$$\hat{y} = w^T x$$

以及损失函数（MSE），然后直接找到了使损失最小化的权重向量 $w$。我们证明了当使用 MSE 时，最佳的权重向量由下式给出：

  

$$\hat{w} = (X^T X)^{-1} X^T y$$

在本题中，我们将探讨另一种观点，我们可以称之为统计学视角。统计学视角的中心是**数据生成过程（Data Generating Process, DGP）**，它假设存在某个生成数据的真实底层函数（我们称之为 $f$），但我们只能获取关于 $f$ 的带噪声观测值。也就是说，我们观测到的是：

  

$$y = f(x) + \epsilon$$

其中 $\epsilon$ 是某些随机噪声。

  

例如，假设你的 $y$ 代表肯辛顿（Kensington）的每日气温。任何温度计——甚至是昂贵的温度计——都容易产生测量误差，因此我们实际观测到的是真实温度（$f(x)$）加上一些随机噪声 $\epsilon$。通常，我们假设噪声服从均值为零、方差为 $\sigma^2$ 的正态分布。

现在，考虑一个（很强的）假设：$f(x)$ 是线性的，这意味着存在某个真实值 $\beta^*$ 使得 $f(x) = x^T \beta^*$。因此，我们有：

  

$$y = x^T \beta^* + \epsilon, \quad \epsilon \sim N(0, \sigma^2)$$

从而：

  

$$y \vert{} x \sim N(x^T \beta^*, \sigma^2)$$

这意味着我们的响应（在已知特征值 $x$ 的条件下）遵循均值为 $x^T \beta^*$、方差为 $\sigma^2$ 的正态分布。因此，我们可以将数据视为来自该分布的随机观测样本，这反过来又允许我们像在前面问题中那样，通过最大似然法来估计未知参数。

  

**(a)** 给定数据集 $D = \{(x_1, y_1), \dots, (x_n, y_n)\}$，并做出如下假设：对于某些未知的 $\beta^*$ 以及相互独立的 $\epsilon_i \sim N(0, \sigma^2)$，有 $y_i \vert{} x_i = x_i^T \beta^* + \epsilon_i$。

写出该问题的对数似然函数以及最大似然估计的目标，并求解 MLE 估计量 $\hat{\beta}_{\text{MLE}}$。

  

##### 问题 4. 几何解释

在本题中，我们将探讨最小二乘（LS）、Ridge（岭回归）和 LASSO 回归模型的某些几何直观。

  

**(a)** 考虑下图，它展示了在各种 $p$-范数下单位球的等高线图（如果不熟悉等高线图，请参阅 lab0）。解释图中的含义，并对图中表示的四个向量 $((1, 1), (1/2, -1/2), (-1/2, 1/2), (0, -1))$ 进行评述。此外，第一个图（$p=0.5$）与其他图有什么区别？

_(注：原文档附带了多张不同 $p$ 值下的等高线图，展示了 $p=0.5, 1, 2, \infty$ 时的几何形状)_

  

**(b)** 我们先前看到岭回归的目标定义为：

  

$$\hat{\beta}_{\text{ridge}} = \arg\min_{\beta} \{\vert{}\vert{}y - X\beta\vert{}\vert{}_2^2 + \lambda \vert{}\vert{}\beta\vert{}\vert{}_2^2\}$$

定义岭回归目标的另一种（等价）方式是通过约束优化：

  

$$\hat{\beta}_{\text{ridge}} = \arg\min_{\beta} \vert{}\vert{}y - X\beta\vert{}\vert{}_2^2 \quad \text{subject to } \vert{}\vert{}\beta\vert{}\vert{}_2 \le k$$

这说明我们想要找到使平方损失最小化的 $\beta$，但该解必须同时属于半径为 $k$ 的 2-范数球内。注意，通常情况下，$k$ 和 $\lambda$ 并不是同一个东西。约束优化的表述为我们提供了岭回归解的一个优美的几何解释，接下来我们将进行探讨。

在此之前，我们还注意到 LASSO 也有一个无约束版本：

  

$$\hat{\beta}_{\text{LASSO}} = \arg\min_{\beta} \{\vert{}\vert{}y - X\beta\vert{}\vert{}_2^2 + \lambda \vert{}\vert{}\beta\vert{}\vert{}_1\}$$

以及一个约束版本：

  

$$\hat{\beta}_{\text{LASSO}} = \arg\min_{\beta} \vert{}\vert{}y - X\beta\vert{}\vert{}_2^2 \quad \text{subject to } \vert{}\vert{}\beta\vert{}\vert{}_1 \le k$$

其中 Ridge 和 LASSO 中的 $\lambda$、$k$ 在一般情况下是不同的。这些目标函数几乎完全相同，它们仅在惩罚/约束项所使用的范数选择上有所不同。这实际上在实践中导致了巨大且非常重要的差异。

现在，考虑到这一点，解释以下图表：

_(注：原文档附带了最小二乘、Ridge 和 LASSO 的几何对比图，展示了等高线与不同约束边界的交点)_

显式讨论 Ridge 和 LASSO 解之间的差异。

  

**(c)** 据说 LASSO 具有诱导稀疏性（induce sparsity）的作用。这是什么意思？拥有稀疏解为什么可能是令人向往的？