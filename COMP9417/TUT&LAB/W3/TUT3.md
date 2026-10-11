# COMP9417 — Machine Learning

## Tutorial：分类（Classification）

---

# Question 1：贝叶斯法则（Bayes Rule）

假设某种疾病在人群中出现的概率为：

$$  
P(D)=0.01  
$$

如果一个人患有该疾病，那么检测结果呈阳性的概率为：

$$  
P(T^+|D)=0.95  
$$

如果一个人**没有**患该疾病，那么检测结果呈阳性的概率为：

$$  
P(T^+|\neg D)=0.05  
$$

### (a)

计算检测结果呈阳性的概率：

$$  
P(T^+)  
$$

### (b)

已知检测结果为阳性，计算该个体实际患有这种疾病的概率：

$$  
P(D|T^+)  
$$

### (c)

现在假设对该个体进行**第二次检测**，并且检测结果再次呈阳性。

也就是说：

> 两次检测，两次均为阳性。

假设在“患有该疾病”这一条件下，两次检测的结果相互独立。求此时该个体患有该疾病的概率。

注意，这里的**条件独立（conditional independence）**指的是：
$$
P(T^+|D)P(T^+|D)  
$$

而**不是**：
$$
P(T^+)P(T^+)  
$$

你也可以假设，在“没有患该疾病”这一条件下，两次检测结果同样条件独立。

---

# Question 2：Lecture 复习（Lecture Review）

本题将复习 Lecture 中的一些重要概念。

### (a)

什么是**概率分类（probabilistic classification）**？

它与**非概率分类方法（non-probabilistic classification methods）**有什么区别？

### (b)

什么是**朴素贝叶斯假设（Naive Bayes assumption）**？

为什么我们需要这个假设？

### (c)

考虑 Lecture 中将电子邮件分类为：

- Spam：垃圾邮件
    
- Ham：正常邮件
    

的问题。

训练数据总结如下。

每一行代表一封电子邮件，每封邮件都是由集合

$$  
{a,b,c,d,e}  
$$

中的单词组合而成：

```
e1  b d e b b d e
e2  b c e b b d d e c c
e3  a d a d e a e e
e4  b a d b e d a b
e5  a b a b a b a e d
e6  a c a c a c a e d
e7  e a e d a e a
e8  d e d e d
```

我们将单词 (d,e) 视为**停用词（stop words）**。

停用词指的是对于分类没有帮助的词。例如，英文单词 `"the"` 出现得过于频繁，因此通常无法有效帮助我们判断一篇文档属于 spam 还是 ham。

因此，我们定义词汇表：

$$  
V={a,b,c}  
$$

这里共有两个类别，因此：

$$  
k=2  
$$

并假设类别的**先验概率（prior）**是均匀的：

$$  
p(c_+)=p(c_-)=\frac12  
$$

其中：

$$  
c_+=spam  
$$

$$  
c_-=ham  
$$

复习 **多元伯努利朴素贝叶斯（Multivariate Bernoulli Naive Bayes）** 模型，并对下面的测试样本进行分类。

假设我们收到一封新的电子邮件：

$$  
e_?=abbdebb  
$$

判断它应该被分类为 spam 还是 ham。

### (d)

接下来，复习多元伯努利模型中的**平滑（Smoothing）**。

为什么我们需要进行平滑？

在使用经过平滑的 **Multivariate Bernoulli Naive Bayes** 模型后，上一问的分类结果会发生什么变化？

### (e)

使用**多项式朴素贝叶斯（Multinomial Naive Bayes）**模型重新进行上一部分的分析。

这一问**不使用平滑（without smoothing）**。

使用下面的测试邮件：

$$  
e_?=abbdebbcc  
$$

进行分类。

### (f)

再次进行上一问的分析，但这次使用：

**经过平滑的 Multinomial Naive Bayes 模型（smoothed Multinomial Naive Bayes model）。**

---

# Question 3：二元逻辑回归的两种视角

## Binary Logistic Regression, Two Perspectives

回顾之前几周的内容，我们可以从两种不同的角度理解**最小二乘回归（least squares regression）**。

第一种是纯粹的**优化问题（optimisation problem）**：

> 最小化均方误差 MSE。

第二种是**统计问题（statistical problem）**：

> 使用最大似然估计 MLE。

现在我们从类似的两个角度讨论**二元逻辑回归（Binary Logistic Regression）**。

假设给定数据集：

$$  
D={(x_i,y_i)}_{i=1}^{n}  
$$

其中 (x_i) 表示**特征向量（feature vector）**，与线性回归中的情况相同。

但是现在：

$$  
y_i  
$$

是**二元变量（binary）**。

我们的目标是将输出建模为：

> 某一个数据点属于两个类别之一的概率。

我们将预测概率记作：

$$  
P(y=1|x)=p(x)  
$$

并使用下面的模型：

$$  
\hat p(x)=\sigma(\hat w^Tx)  
$$

其中 sigmoid 函数为：

$$  
\sigma(z)=\frac{1}{1+e^{-z}}  
$$

而：

$$  
\hat w  
$$

是我们估计得到的**权重向量（weight vector）**。

然后，可以通过选择概率最大的类别来构造分类器：
$$
\arg\max_{k=0,1}  
P(\hat y=k|x)  
$$

也就是说：

$$  
\hat y=  
\begin{cases}  
1,&\sigma(\hat w^Tx)\geq0.5\  
0,&\text{otherwise}  
\end{cases}  
$$

注意：

不要将函数

$$  
\sigma(z)  
$$

与通常用于表示**标准差（standard deviation）**的参数 (\sigma) 混淆。

---

## (a)

在 Logistic Regression 的数学表达中，**Logistic Sigmoid 函数**

$$  
\sigma()  
$$

起什么作用？

为什么在这里不能简单地使用**线性回归（Linear Regression）**？

画出：

$$  
\sigma(z)  
$$

的图像可能有助于回答这个问题。

---

## (b)

首先，从**统计学视角（statistical view）**考虑 Logistic Regression。

回顾线性回归的统计学解释。

在线性回归中，我们假设：

$$  
y|x  
\sim  
N(x^T\beta^*,\sigma^2)  
$$

而现在我们处理的是**二元随机变量（binary-valued random variables）**，因此假设：

$$  
y|x  
\sim  
Bernoulli(p^*)  
$$

其中：

$$ 
p^* =\sigma(x^Tw^*)  
$$

这里：

$$  
p^*=\sigma(x^Tw^*)  
$$

表示一个样本真实属于类别 1 的未知概率。

我们假设这个概率由某个真实但未知的权重向量：

$$  
w^*  
$$

控制。

请写出数据集：

$$  
D  
$$

的 **log-likelihood（对数似然）**，将其表示为 (w) 的函数。

进一步写出相应的：

**MLE（Maximum Likelihood Estimation，最大似然估计）优化目标。**

但是：

> **不需要尝试求解这个优化问题。**

---

## (c)

另一种理解 Logistic Regression 的方式，是完全从**优化（optimisation）**的角度考虑这个问题。

这种方法要求我们首先选择一个**损失函数（loss function）**，然后求出对应的最小化解。

写出 Logistic Regression 使用 **MSE（Mean Squared Error，均方误差）**时的优化目标。

然后讨论：

> 你认为 MSE 是 Logistic Regression 中合适的损失函数吗？为什么？

---

## (d) Optional

考虑下面的问题。

给定两个**离散概率分布（discrete probability distributions）**：

$$  
P  
$$

和：

$$  
Q  
$$

我们希望量化：

> (Q) 与 (P) 相差多远。

这是统计学和信息论中非常常见的问题。

最常见的一种衡量两个概率分布差异的方法是计算：

**Kullback–Leibler Divergence（KL Divergence，KL 散度）**

也称为：

**Relative Entropy（相对熵）**。

定义为：
$$
\sum_{x\in X}  
P(x)  
\ln  
\frac{P(x)}{Q(x)}  
$$

这里对底层随机变量所有可能的取值进行求和。

一种比较直观的理解方式是：

假设：

- (P) 是**真实概率分布（true distribution）**
    
- (Q) 是我们得到的**估计概率分布（estimate）**
    

那么我们希望知道：

> 我们的估计 (Q) 到底有多差？

现在考虑两个 Bernoulli 分布：

$$  
P=Bernoulli(p)  
$$

以及：

$$  
Q=Bernoulli(q)  
$$

写出这两个 Bernoulli 分布之间的：

$$  
D_{KL}(P|Q)  
$$

---

## (e) Optional

继续从**优化视角**考虑 Logistic Regression。

在我们的设定中，可以通过比较：

$$  
\hat p_i  
$$

和真实标签：

$$  
y_i  
$$

来衡量预测结果与真实结果之间的差异。

具体来说，考虑下面两个 Bernoulli 分布：

$$  
P_i=Bernoulli(y_i)  
$$

和：

$$  
Q_i=Bernoulli(\hat p_i)  
$$

使用这两个分布之间的 **KL Divergence**，写出一个适用于 Logistic Regression 的**最小化问题（minimization problem）**。

---

## (f) Optional

在 Logistic Regression 以及其他**二元分类问题（binary classification problems）**中，我们通常使用：

**Cross-Entropy Loss（交叉熵损失，XE Loss）**

定义为：
$$
-a\ln b  
-(1-a)\ln(1-b)  
$$

利用上一问得到的结果，讨论：

> 为什么 Cross-Entropy Loss 是一个合适的损失函数？

同时说明 Logistic Regression 的：

- **统计学视角（statistical view）**
    
- **优化视角（optimisation view）**
    

之间存在什么联系。