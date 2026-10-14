# COMP9417 机器学习 — 作业 2 中文翻译

以下是你上传的 《COMP9417 - Machine Learning Assignment 2》 的中文翻译，共 8 页。

我会按照原文的顺序翻译，保留所有数学公式、题目编号、分值、代码、参数设置和提交要求，方便你对照英文原文完成作业。

## 一、作业概述（第 1 页）

### 引言（Introduction）

在本次作业中，我们将重新研究梯度下降（Gradient Descent），并展示这一简单原理如何产生丰富的学习动态以及强大的算法。

第一题分析一维线性模型中的在线随机梯度下降（Online Stochastic Gradient Descent，SGD），通过推导精确的数学表达式，揭示估计量如何随时间变化。

第二题研究正则化逻辑回归（Regularized Logistic Regression），将其数学表达与数值稳定的实现方法、特征选择，以及利用交叉验证选择正则化强度联系起来。

### 分数分配

本次作业总分为 28 分。

|题目|小题|分值|
|---|---|---|
|第一题|(a)、(b)、(c)、(d)|各 1 分|
|第一题|(e)|2 分|
|第一题|(f)、(g)|各 3 分|
|第一题|(h)|2 分|
|第二题|(a)|2 分|
|第二题|(b)、(c)、(d)|各 1 分|
|第二题|(e)|2 分|
|第二题|(f)|3 分|
|第二题|(g)、(h)|各 2 分|

## 二、提交要求（第 2–3 页）

### 需要提交的内容（What to Submit）

- 一份 PDF 文件，包含所有题目的解答。每道题应提供文字说明以及要求的图表。部分题目会要求提供生成答案所使用代码的截图，只有在题目明确要求时才需要加入截图。
    
- 一个单独的 ZIP 压缩文件，包含本次作业使用的全部 `.py` Python 代码文件。代码必须与报告中展示的代码一致。
    
- 不遵守上述要求可能被扣分。
    
- 排版不佳、格式混乱也可能被扣分。请保持整洁，确保答案清晰；必要时每道大题从新的一页开始。
    
- 不能提交 Jupyter Notebook，否则该项作业成绩为零。 但你可以在 Notebook 中开发代码，再复制到 `.py` 文件，或者使用 `nbconvert` 等工具进行转换。
    

### 论坛与学术诚信

学校将在 Moodle 上开设本次作业的讨论论坛。

发帖前，请先阅读已有问题并进行基本的网上调查。只允许提出澄清题意的问题。任何被认为是在索要答案的问题，都可能被忽略或删除。

请定期查看 Moodle 公告，了解作业说明是否有更新。你有责任自行检查。

必须独立完成作业，不得与课程中的其他人讨论具体解答。可以对题目进行一般性讨论，但必须独立写出答案。如果与其他同学讨论过题目，必须在提交材料中注明对方姓名和 zID。

学校会监控 Chegg、StackExchange 等在线论坛。将作业题目发布到这些网站等同于抄袭，并可能导致学术不端处分。

### 生成式 AI 的使用规定

必须独立完成作业。

将 ChatGPT、Claude、Copilot、Gemini 等生成式 AI 工具产生的数学推导、代码、图表或文字评论作为自己的作品提交，属于学术不端。

数学推导题的评分依据包括推导过程的正确性和清晰程度。无法解释自己答案的学生可能被要求参加学术诚信面试。

### 允许使用的 Python 库

第二题允许使用：

- `NumPy`
    
- `pandas`
    
- `matplotlib`
    

以下工具仅能在题目明确允许的情况下使用：

- `sklearn.model_selection.train_test_split`
    
- `sklearn.preprocessing.StandardScaler`
    
- `sklearn.metrics.log_loss`
    
- `scipy.optimize.minimize`
    
- `sklearn.linear_model.LogisticRegression`
    

必须自行实现正则化损失函数和留一交叉验证（LOOCV）过程。

禁止使用：

- `LogisticRegressionCV`
    
- `GridSearchCV`
    
- `cross_val_score`
    
- 任何其他现成的交叉验证或超参数搜索实现
    

违反规定的相关题目将获得零分。

### 文字分析如何评分

当题目要求你进行评论或解释时，必须提出关于模型的观点，并用自己运行得到的结果作为依据。

仅仅重复图表展示的现象，而不解释原因，不能得分。

### 最终提交检查清单

需要提交两个文件：

|文件名|内容|
|---|---|
|`zID_report.pdf`|所有题目的解答、图表及要求的代码截图|
|`zID_code.zip`|所有 `.py` 代码文件|

注意：PDF 不要放进 ZIP 文件；所有图表必须嵌入 PDF，不能单独提交图片文件。

如果与其他同学讨论过题目，须在 PDF 中注明其姓名和 zID。

禁止使用 SymPy 或其他符号计算工具完成推导题，必须手动推导，否则相关题目自动记零分。

### 截止时间与迟交处罚

作业截止时间

2026 年 11 月 1 日（星期日）18:00

论坛答疑结束

2026 年 10 月 30 日（星期五）17:00

Moodle 论坛在周末不会受到积极监控。因此，在截止日期前的星期六或星期日提出的问题，很可能无法在提交截止前得到回复。请尽量在星期五下午前提出问题。

迟交每天扣除总分的 5%，即：

$$ 0.05\times28=1.4\text{ 分/天} $$

例如，原本得分为 20/28，但迟交 3 天：

$$ 20-3\times1.4=15.8 $$

迟交超过 5 天将获得零分。

必须通过 Moodle 提交，没有例外。

## 三、第一题：在线随机梯度下降（第 4–5 页）

Question 1. Online Stochastic Gradient Descent（共 14 分）

假设在每个时间点 $t=1,2,\ldots$，我们观察到由以下一维线性模型生成的数据：

$$ y_t=w^\star x_t+\eta_t $$

其中：

$$ x_t\sim N(0,1),\qquad \eta_t\sim N(0,\sigma^2) $$

$x_t$ 和 $\eta_t$ 相互独立，并且不同时间点之间也相互独立。

我们的目标是通过最小化总体均方损失（Population Mean Squared Loss）来估计 $w^\star$：

$$ L(w)=\frac12\mathbb E[(wx-y)^2] $$

这里，$x$ 和 $y$ 表示从模型中随机抽取的一组一般样本，因此 $L(w)$ 是关于 $w$ 的确定性函数。

下标 $t$ 同时表示样本编号和迭代次数。下面研究的是在线算法：在第 $t$ 次迭代时，算法只观察一个样本 $(x_t,y_t)$，之后不会再次使用该样本。

注意，$w_t$ 是随机变量。它由之前观察到的随机样本

$$ (x_1,\eta_1),\ldots,(x_{t-1},\eta_{t-1}) $$

决定。因此，$w_t$ 与当前尚未被抽取的 $(x_t,\eta_t)$ 相互独立。

下面各小题中的期望是对这些随机样本的所有可能实现取平均，而不是只针对算法的一次运行。

提交要求： 本题所有小题都必须提供推导过程，可以打字或手写。

### (a) 计算总体梯度（1 分）

明确计算总体梯度：

$$ \nabla L(w) $$

并证明它与

$$ (w-w^\star) $$

成正比。

### (b) 完整梯度下降更新（1 分）

假设我们能够直接计算完整的期望。

写出使用步长 $\alpha>0$ 最小化 $L(w)$ 的梯度下降更新公式。

注意：由于该更新需要计算完整的期望，因此实际上无法直接运行。第 (c) 小题将解决这个问题。

### (c) 在线 SGD 更新公式（1 分）

在实际情况中，我们只能观察到样本 $(x_t,y_t)$。

解释如何构造总体梯度的一个无偏随机估计（Unbiased Stochastic Estimate），并利用它推导在线随机梯度下降更新公式：

$$ \boxed{w_{t+1}=w_t-\alpha(w_tx_t-y_t)x_t} $$

### (d) 误差递推公式（1 分）

定义估计误差：

$$ \delta_t=w_t-w^\star $$

证明在给定模型下，误差满足以下递推关系：

$$ \boxed{\delta_{t+1}=(1-\alpha x_t^2)\delta_t+\alpha\eta_tx_t} $$

从**偏差（Bias）和方差（Variance）**的角度解释递推式中的两项。

### (e) 估计量的期望（2 分）

计算：

$$ \mathbb E[\delta_{t+1}] $$

并解释为什么可以将乘积的期望分解为两个期望的乘积。

当初始化为 $w_0=0$ 时，证明：

$$ \boxed{\mathbb E[w_t]=\left(1-(1-\alpha)^t\right)w^\star} $$

回答：

1. 对于哪些 $\alpha>0$，当 $t\to\infty$ 时，$\mathbb E[w_t]$ 收敛？
    
2. 收敛的极限是什么？
    

### (f) 均方误差递推（3 分）

证明均方误差

$$ \mathrm{MSE}_t=\mathbb E[\delta_t^2] $$

满足：

$$ \boxed{\mathbb E[\delta_{t+1}^2]=c_\alpha\mathbb E[\delta_t^2]+\alpha^2\sigma^2} $$

其中：

$$ c_\alpha=1-2\alpha+3\alpha^2 $$

### (g) 求解均方误差递推式（3 分）

假设 $w_0=0$，求解上述递推关系，证明：

$$ \boxed{ \mathrm{MSE}_t =c_\alpha^t(w^\star)^2+ \frac{\alpha^2\sigma^2}{1-c_\alpha}(1-c_\alpha^t) } $$

### (h) 极限均方误差（2 分）

推导：

$$ \lim_{t\to\infty}\mathrm{MSE}_t $$

并确定使其收敛的 $\alpha$ 取值范围。

将这一范围与第 (e) 小题中 $\mathbb E[w_t]$ 收敛所要求的 $\alpha$ 范围进行比较，并解释为什么两个范围不同。

最后，对结果进行评论。

## 四、第二题：正则化逻辑回归（第 5–8 页）

Question 2. Regularized Logistic Regression（共 14 分）

重要说明：除非题目明确要求，否则不得使用任何现成的算法实现。违反规定可能导致整道第二题得零分。

本题将研究用于二分类问题的正则化逻辑回归模型，即预测一个二元类别标签。

对于线性回归等连续目标变量的回归问题，我们通常使用均方误差损失；而对于逻辑回归，我们最小化的是对数损失（Log-loss），也称为交叉熵损失（Cross-Entropy Loss）。

回顾以下定义：

参数向量：

$$ \beta=(\beta_1,\ldots,\beta_p)\in\mathbb R^p $$

截距：

$$ \beta_0\in\mathbb R $$

类别标签和特征：

$$ y_i\in\{0,1\},\qquad x_i\in\mathbb R^p $$

其中 $i=1,\ldots,n$。

对数损失为：

$$ L(\beta_0,\beta)= \sum_{i=1}^{n} \left[ y_i\ln\frac{1}{\sigma(\beta_0+\beta^Tx_i)} + (1-y_i)\ln\frac{1}{1-\sigma(\beta_0+\beta^Tx_i)} \right] $$

其中 sigmoid 函数为：

$$ \sigma(z)=\frac{1}{1+e^{-z}} $$

实际应用中，我们通常添加一个惩罚项，求解：

$$ \boxed{ (\hat\beta_0,\hat\beta) = \arg\min_{\beta_0,\beta} \left\{ CL(\beta_0,\beta)+\operatorname{penalty}(\beta) \right\} } \tag{1} $$

其中：

- 惩罚项通常不作用于截距 $\beta_0$。
    
- $C>0$ 是一个超参数。
    

例如，在 $\ell_2$ 正则化中：

$$ \operatorname{penalty}(\beta)=\frac12\|\beta\|_2^2 $$

这相当于逻辑回归的 Ridge 正则化版本。

软件版本说明：

本题使用以下版本进行测试：

- scikit-learn 1.9
    
- pandas 3.0
    
- scipy 1.18
    

从 scikit-learn 1.8 开始，`LogisticRegression` 的正则化类型通过 `l1_ratio` 参数设置：

- `l1_ratio=0`：$\ell_2$ 正则化
    
- `l1_ratio=1`：$\ell_1$ 正则化
    

旧版的 `penalty` 参数已被弃用，不要使用。

### (a) 不同逻辑回归目标函数的等价性（2 分）

考虑以下另一种 $\ell_2$ 正则化目标函数写法。

这里类别标签使用：

$$ \tilde y_i\in\{-1,1\} $$

而不是：

$$ y_i\in\{0,1\} $$

目标函数为：

$$ \boxed{ (\hat w,\hat c)= \arg\min_{w,c} \left\{ \frac12w^Tw+ C\sum_{i=1}^n \ln(1+\exp(-\tilde y_i(w^Tx_i+c))) \right\} } \tag{2} $$

严格论证：当

$$ \tilde y_i=2y_i-1 $$

时，公式 (1)（采用 $\ell_2$ 正则化）与公式 (2) 的目标函数完全相同，因此得到相同的最优解：

$$ \hat\beta_0=\hat c,\qquad \hat\beta=\hat w $$

scikit-learn 官方文档第 1.1.11 节还使用第三种形式表示相同的模型。

当所有样本权重均为 1，且

$$ \hat p(x_i)=\sigma(w^Tx_i+w_0) $$

时，最小化的目标函数为：

$$ \frac1n\sum_{i=1}^n \left[ -y_i\ln\hat p(x_i) -(1-y_i)\ln(1-\hat p(x_i)) \right] + \frac{1}{nC}\frac12\|w\|_2^2 $$

解释为什么这个目标函数也具有相同的最优解。

最后，描述参数 $C$ 在这些目标函数中的作用，以及它与标准 Ridge 正则化参数 $\lambda$ 的关系。

提交内容： 文字解释及数学推导过程。

### (b) LogSumExp 的数值稳定性（1 分）

在逻辑回归损失以及许多机器学习问题中，我们经常遇到：

$$ \operatorname{LogSumExp}(x_1,\ldots,x_n) = \log(e^{x_1}+\cdots+e^{x_n}) $$

这种表达式在计算时可能出现数值溢出（Numerical Overflow）。

例如，数学上：

$$ \log(\exp(x))=x $$

但当 $x$ 很大时，直接计算可能失败。可以尝试：

```
np.log(np.exp(1200))
```

本题将研究一种避免此类问题的技巧。

(I) 令：

$$ x^*=\max(x_1,\ldots,x_n) $$

证明：

$$ \boxed{ \operatorname{LogSumExp}(x_1,\ldots,x_n) = x^*+\log\left( e^{x_1-x^*}+\cdots+e^{x_n-x^*} \right) } $$

(II) 证明对数内部的每一个指数项都大于 0 且小于或等于 1。

(III) 据此解释为什么这种改写可以避免数值溢出。

提交内容： 文字解释及推导过程。

### (c) 数据预处理（1 分）

从本小题开始，使用 Moodle 提供的 `songs.csv` 数据集。

该数据集包含不同歌曲的信息，以及代表歌曲流派的类别变量。

原文还提供了一个了解数据集的链接，但深入理解每个特征并不是本次作业的重点。

读取数据并完成以下预处理步骤。

(I) 删除以下特征列：

```
"Artist Name""Track Name""key""mode""time signature""instrumentalness"
```

(II) 筛选二分类数据

原始数据集包含 11 个类别，但本题使用的逻辑回归模型只处理二分类。

只保留：

- 类别 1：alternative（另类音乐）
    
- 类别 8：metal（金属音乐）
    

重新编码目标变量：

$$ y= \begin{cases} 1 & \text{metal}\\ -1 & \text{alternative} \end{cases} $$

继续之前，使用 `np.unique` 检查类别标签是否正确。

(III) 修正歌曲时长

原始数据集中的 `duration in min/ms` 列存在数据录入问题：

大部分时长以毫秒记录，但有些以分钟记录。

将所有时长统一转换为分钟。

如果数值大于或等于 100，则认为其单位为毫秒，需要除以 60000。

最后将列名改为：

```
"duration min"
```

(IV) 处理缺失值

删除任何特征仍存在缺失值的行。

处理完成后，数据集应包含：

3166 行。

(V) 划分训练集和测试集

使用：

```
sklearn.model_selection.train_test_split
```

将数据分为：

```
X_trainX_testy_trainy_test
```

设置：

```
test_size=0.3random_state=17
```

以确保结果可复现。

(VI) 特征标准化

使用：

```
sklearn.preprocessing.StandardScaler
```

仅在训练集上拟合标准化器（Scaler）。

然后使用这个已经拟合的标准化器分别转换训练集和测试集。

(VII) 输出数据检查结果

打印以下四个变量的第一行和最后一行：

```
X_trainX_testy_trainy_test
```

对于 `X_train` 和 `X_test`，只需要打印前三列。

提交内容： 第 (VII) 步要求的打印结果，并将代码放入 ZIP 文件。

原文脚注：从 pandas 3.0 开始，像 `df.Class.replace(..., inplace=True)` 这样的链式原地操作不再修改原 DataFrame，而且可能不会产生明显错误。应改为显式赋值，例如 `df["Class"] = ...`。

### (d) 为什么只在训练集上拟合 StandardScaler？（1 分）

在 (c) 中，我们仅使用训练数据拟合 `StandardScaler`，然后用它转换训练集和测试集。

结合真实世界的预测问题，解释：

1. 为什么这是正确的处理方式？
    
2. 如果使用整个数据集来拟合标准化器，可能会出现什么问题？
    

提交内容： 文字解释。

### (e) 实现正则化逻辑回归损失函数（2 分） 

编写 Python 函数：

```
reg_log_loss(W, C, X, y)
```

该函数用于计算模型 $W=(c,w)$ 在数据 $X,y$ 上、正则化参数为 $C$ 时的损失。

数据包含 $n$ 个观测值，并且：

$$ y\in\{-1,1\} $$

损失函数定义为：

$$ \boxed{ \frac12\|w\|_2^2+ C\sum_{i=1}^n \ln(1+e^{-y_i(w^Tx_i+c)}) } $$

其中：

- $W$ 数组的第一个元素是截距 $c$。
    
- $W$ 的剩余元素是权重向量 $w$。
    

注意：编写函数时，必须避免 (b) 中讨论的数值溢出问题。

为此，应使用：

```
np.logaddexp
```

提示：

$$ 1=e^0 $$

为了检查实现是否正确，下面的代码应得到指定结果：

```
c = -1.4w = 0.1 * np.ones(X_train.shape[1])W = np.insert(w, 0, c)reg_log_loss(W=W, C=0.001, X=X_train, y=y_train)# returns 2.310784588863121
```

接下来，将参数修改为：

```
w = 0.25 * np.ones(X_train.shape[1])c = 0.6
```

运行函数并打印损失值。

注意：将截距和权重合并到一个数组 $W$ 中，对于下一小题的代码实现非常重要。

提交内容： 新参数下计算出的损失值、代码截图，以及 ZIP 中的 Python 代码。

### (f) 拟合正则化逻辑回归模型（3 分）

现在我们已经能够稳定地计算任意模型 $W=(c,w)$ 的损失，因此可以开始拟合逻辑回归模型。

编写 Python 函数：

```
reg_log_fit(X, y, C)
```

该函数应返回拟合后的参数：

$$ \hat W=(\hat c,\hat w) $$

函数只能使用：

```
scipy.optimize.minimize
```

进行数值优化。

可以直接使用 (e) 中编写的 `reg_log_loss` 函数作为优化目标。

优化设置为：

```
C = 0.5method = "L-BFGS-B"
```

使用默认优化选项，不需要自行提供梯度。

初始参数与 (e) 中的代码相同：

```
w = 0.1 * np.ones(X_train.shape[1])W0 = np.insert(w, 0, -1.4)
```

完成拟合后，执行以下任务。

(I) 评估自己实现的模型

使用：

```
sklearn.metrics.log_loss
```

计算模型在训练集和测试集上的损失。

回顾模型预测 $y_i=1$ 的概率：

$$ P(y_i=1\mid x_i)=\sigma(\hat w^Tx_i+\hat c) $$

其中 $x_i$ 是单个样本的特征向量。

同时报告拟合得到的截距：

$$ \hat c $$

(II) 与 sklearn 的逻辑回归比较

使用：

```
sklearn.linear_model.LogisticRegression
```

设置：

```
C=0.5l1_ratio=0solver="lbfgs"tol=1e-6
```

计算该模型的训练集损失和测试集损失，并报告截距 `intercept_`。

(III) 使用 liblinear 求解器

保持其他参数不变，将求解器改为：

```
solver="liblinear"
```

重新拟合 sklearn 模型，并报告截距。

你会发现它的截距与 (I)、(II) 中的截距略有不同。

阅读 `LogisticRegression` 官方文档中关于 `intercept_scaling` 参数的说明，并解释产生差异的原因。

可选提示：

使用 `scipy.optimize.minimize` 时，可以通过 `lambda` 函数调用之前的损失函数：

```
g = lambda W: reg_log_loss(W, *args)
```

提交内容： 自己实现的模型及两个 sklearn 模型的训练集损失、测试集损失和截距；对 (III) 的解释；代码截图；ZIP 中的代码。

### (g) $\ell_1$ 正则化与特征选择（2 分）

到目前为止，我们一直任意选择超参数 $C$。

本小题将研究 $C$ 对拟合模型的影响。

重点考虑使用 $\ell_1$ 正则化的目标函数：

$$ \boxed{ \|w\|_1+ C\sum_{i=1}^n \ln(1+e^{-y_i(w^Tx_i+c)}) } $$

使用 sklearn 实现：

```
LogisticRegression(    l1_ratio=1,    solver="liblinear",    C=c)
```

使用以下代码生成 100 个 $C$ 值：

```
Cs = np.logspace(-3, 0, num=100)
```

对于每一个 $C$：

1. 使用训练数据拟合模型。
    
2. 保存每个特征对应的回归系数。
    

绘制一张图：

- 横轴：$\log(C)$
    
- 纵轴：回归系数的数值
    
- 每个特征对应一条曲线
    

换句话说，这张图应该展示当 $C$ 取不同值时，模型中每个特征的系数如何变化。

根据图表回答：

1. 为什么 $\ell_1$ 正则化可以被认为是一种特征选择方法？
    
2. 根据图表，你认为哪些特征最重要？
    
3. 为什么认为这些特征重要？
    

提交内容： 一张图、文字分析、代码截图，以及 ZIP 中的代码。

图表必须有清晰的图例，并且按照以下颜色顺序区分不同特征：

```
[    'red',    'brown',    'green',    'blue',    'orange',    'pink',    'purple',    'grey',    'black',    'y']
```

### (h) 使用留一交叉验证选择 C（2 分）

现在我们将使用交叉验证从数据中选择超参数 $C$。

具体方法是：

留一交叉验证（Leave-One-Out Cross Validation，LOOCV）。

首先使用以下代码生成候选 $C$ 值：

```
Cs = np.logspace(-2, 1, num=25)
```

由于 LOOCV 的计算成本较高，本题只使用训练数据的前 20%。

具体来说，使用：

$$ n=443 $$

即 `X_train` 和 `y_train` 的前 443 个观测值。

对于每个 $C$，执行以下步骤。

(I) 逐一留出样本并训练模型

对于：

$$ i=1,\ldots,n $$

从数据集中删除第 $i$ 个观测值，并使用剩余数据拟合带有 $\ell_1$ 正则化的逻辑回归模型。

模型与 (g) 中使用的相同。

因此，对于每一个 $C$，总共需要训练 $n$ 个模型。

(II) 计算被留出样本的损失

对于第 $i$ 个模型（即训练时排除了第 $i$ 个样本的模型），计算其对被留出的样本 $y_i$ 进行预测时的对数损失。

(III) 计算平均交叉验证损失

对所有 $n$ 个被留出样本的损失取平均，得到该 $C$ 对应的 LOOCV 分数。

然后：

1. 绘制 LOOCV 分数与 $C$ 的关系图，横轴必须使用对数刻度。
    
2. 报告最优的 $C$ 值。
    
3. 简要解释当 $C$ 很小和很大时，曲线的形状及其原因。
    

重要限制：

本小题不允许使用任何现成的交叉验证实现。

但允许使用：

```
sklearn.linear_model.LogisticRegression
```

来拟合模型，以及：

```
sklearn.metrics.log_loss
```

来计算损失。

必须从零开始自行编写 LOOCV 过程，并使用基本的 `matplotlib` 功能自行绘图。

提交内容： 一张图、文字分析、本小题所用代码的截图，以及 ZIP 中的代码。

原文脚注：`sklearn.metrics.log_loss` 无法仅根据单个标签推断完整的类别集合，因此必须显式指定类别，例如：

```
log_loss([y_i], probs, labels=[-1, 1])
```

## 五、整份作业的任务汇总

|小题|主要任务|必须提交的内容|
|---|---|---|
|Q1 (a)–(h)|在线 SGD 的数学推导、期望、MSE 和收敛性分析|完整手写或打字推导|
|Q2 (a)|证明三种目标函数等价|推导与解释|
|Q2 (b)|LogSumExp 数值稳定性|推导与解释|
|Q2 (c)|清洗歌曲数据、划分数据集、标准化|指定打印结果、代码|
|Q2 (d)|解释数据泄漏问题|文字解释|
|Q2 (e)|实现正则化损失函数|损失值、代码截图、代码|
|Q2 (f)|拟合模型并与 sklearn 比较|损失、截距、解释、代码截图、代码|
|Q2 (g)|分析 L1 正则化与特征选择|系数变化图、分析、代码截图、代码|
|Q2 (h)|手动实现 LOOCV，寻找最佳 C|交叉验证曲线、最佳 C、分析、代码截图、代码|

特别注意： 第一题重点是数学推导，第二题重点是 Python 实现、模型比较和实验分析。整份作业必须遵守独立完成的要求，尤其不能直接提交生成式 AI 产生的推导、代码或文字作为自己的成果。

以上是这份 8 页作业的完整中文翻译，未包含题目的解答。