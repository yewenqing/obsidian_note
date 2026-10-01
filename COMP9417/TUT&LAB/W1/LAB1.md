
### 线性回归、LASSO 与 Ridge 岭回归

  

  

_最后修订时间：2024 年 5 月 28 日 星期二，16:20:00 AEST_

  

  

本实验在以下包的版本环境中进行了测试：

  

|**包名**|**版本号**|
|---|---|
|`sklearn`|`1.4.2`|
|`pandas`|`2.2.1`|
|`numpy`|`1.26.4`|
|`matplotlib-learn`|`3.8.4`|
|`seaborn`|`0.13.0`|

  

  

### 引言

  

  

在本实验中，我们将更深入地探讨线性模型，具体包括：

  

1. 线性回归以及如何在 Python 库 `scikit-learn`（通常简称为 `sklearn`）中运行线性回归模型。这里的重点是建模的实践方面，您应该查看本周的辅导课（tutorial）来理解底层的运行机制。对于您而言，理解本课程所涵盖概念的理论和实践两方面是非常重要的。
    
      
    
2. 正则化线性模型，即 LASSO 和 Ridge（岭回归）模型。
    
      
    

**注意：本 notebook 仅在 Python 3 环境下进行过测试。**

  

  

  

  

#### 什么是 `sklearn`？

  

  

在本课程中，我们将严重依赖 `sklearn` 模块，其中包含了本课程将要涵盖的许多算法的实现。以下链接汇总了可用的不同类型算法，您很可能在课程的某个阶段用到所有这些算法：

  

[https://scikit-learn.org/stable/](https://scikit-learn.org/stable/?utm_source=gemini)

  

  

以下是不同部分含义的简要总结：

  

1. **分类（Classification）**：包含分类模型的实现，如支持向量机（SVM）和朴素贝叶斯（Naive Bayes）。分类指的是我们拥有形如 $(x_i, c_i)$ 的数据的情况，其中 $x_i$ 是特征集合，而 $c_i$ 是类别标签。例如，在图像分类任务中，我们可能有猫和狗的图像，并希望构建一个分类器，它以 $x_i$（像素集合）作为输入并预测正确的类别标签（0 表示猫，1 表示狗）。重要的是，类别标签始终是离散的几种可能选择之一。
    
      
    
2. **回归（Regression）**：类似于分类，但此时我们拥有的是数据 $(x_i, y_i)$，且 $y_i$ 是连续值。例如，$x_i$ 可以表示关于患者的信息（如年龄、体重、身高、血压），而 $y_i$ 可以表示患者从某项手术中恢复的几率。
    
      
    
3. **聚类（Clustering）**：第 1 部分和第 2 部分都是监督学习的例子，因为我们能够获取标签（$c_i$）或目标值（$y_i$）。但在许多感兴趣的情况下，我们无法获取标签，只能获取 $x_i$。例如，您拥有 100,000 篇机器可读的文本，您想要了解哪些文本是“相似的”。在这种情况下，您可能会使用聚类算法将相似的文本分到同一簇中。如果您的聚类算法成功了，您的簇可能会对应由同一作者撰写的文本、同一种体裁的文本等。
    
      
    
4. **降维（Dimensionality reduction）**：通常第 1、2、3 类中的 $x_i$ 可能是海量的。例如，一张 310 万像素的图像宽度为 2048 像素，高度为 1536 像素，可以表示为一个像素值的矩阵：
    
      
    

$$x_i = \begin{bmatrix} p_{1,1}&p_{1,2} &p_{1,3} & \cdots p_{1,2048}\\ p_{2,1}&p_{2,2} &p_{2,3} & \cdots p_{2,2048}\\ \vdots&\vdots &\vdots & \cdots \vdots\\ p_{1536,1}&p_{1536,2} &p_{1536,3} & \cdots p_{1536,2048}\\ \end{bmatrix}$$

其中每个元素表示图像该特定部分的亮度。因此我们总共有约 310 万个像素。在许多情况下，我们并不认为需要这么多的像素来理解图像中包含的内容，更重要的是，通常很难在合理的时间内在如此高维度的问题上运行机器学习算法。例如，可以通过注意到图像包含尖耳朵、尾巴和黑鼻子来识别一只狗的图像，而这些信息可能包含在 10,000 个像素的集合中。因此，理解如何将输入 $x_i \in \mathbb{R}^p$ 降维到某个低维空间 $z_i \in \mathbb{R}^k$（其中 $k \ll p$），且 $z_i$ 保留了 $x_i$ 中包含的大部分信息，是非常重要的。这就是该子模块中的算法所做的事情。

  

5. **模型选择（Model Selection）**：不仅要知道如何构建模型，还要能够从一系列模型中挑选出最好的模型，这一点至关重要。该子模块包含实现这一目标的算法。它还包含允许我们执行交叉验证以选择超参数的重要函数，这在接下来的几周（以及最终项目中）对我们非常重要。
    
      
    
6. **预处理（Preprocessing）**：在运行机器学习算法之前，我们通常需要对原始数据进行相当多的预处理。例如，我们可能希望将特征向量缩放到 $[0, 1]$ 范围内，或者处理缺失数据，亦或是生成新特征。
    
      
    

建议您定期参考此链接。在本实验中，我们将重点关注线性回归，它包含在回归部分中：

  

[https://scikit-learn.org/stable/supervised_learning.html#supervised-learning](https://www.google.com/search?q=https://scikit-learn.org/stable/supervised_learning.html%2523supervised-learning&utm_source=gemini)

  

  

  

  

#### `sklearn` 中的线性模型

  

  

接下来，我们将：

  

1. 使用 `sklearn` 创建一个具有指定样本数 ($n$) 和特征数 ($p$) 的虚拟数据集（toy dataset）
    
      
    
2. 将数据拆分为训练集和测试集
    
      
    
3. 将线性回归模型、LASSO 模型和 Ridge 模型拟合到训练数据。作为参考，回想一下这三个模型解决的是以下不同的优化目标：
    
      
    - 线性模型：$\hat{\beta} = \arg \min_{\beta} \frac{1}{n}\Vert{}y-X \beta\Vert{}^2_2$
        
          
        
          
        
    - LASSO 模型：$\hat{\beta}_{\text{LASSO}} = \arg \min_{\beta} \frac{1}{n}\Vert{}y-X \beta\Vert{}^2_2 + \lambda \Vert{} \beta \Vert{}_1$
        
          
        
          
        
    - Ridge 模型：$\hat{\beta}_{\text{Ridge}} = \arg \min_{\beta} \frac{1}{n}\Vert{}y-X \beta\Vert{}^2_2 + \alpha \Vert{} \beta \Vert{}_2^2$
        
          
        
          
        
4. 在测试数据上评估每个模型，并使用各种指标进行比较
    
      
    

MSE 项是一个“数据拟合（data-fit）”项，它通过观察真实 $y$ 值到预测值 $\hat{y} = X\beta$ 的距离来衡量模型对数据的拟合程度；而第二项（在 LASSO 和 Ridge 中）是一个惩罚项，随着解的长度增加而增加。长度是模型复杂度的代理，因此我们可以将该项视为偏好更简单的模型而非更复杂的模型。因此，LASSO 和 Ridge 代表了一种权衡：一方面，它们希望获得完美的拟合并将第一项降至零，但这实际上只能通过会导致惩罚项变得非常大的非常复杂的模型来实现。还要注意，$\alpha$ 和 $\lambda$ 被称为超参数，而我们通常将 $\beta$ 称为未知参数或模型的权重。

  

在整个过程中，请密切注意正在使用的子模块，并查阅通常是极佳参考资料的 `sklearn` 文档。另外，请注意我们拟合的是每个模型最基础的形式，您应该深入挖掘以了解可用的不同参数。

  

Python

```
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from sklearn.linear_model import LinearRegression, Lasso, Ridge
from sklearn.datasets import make_regression
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, mean_absolute_error
```

Python

```
# 设置随机种子以确保结果可复现
rs = np.random.RandomState(123)

# 创建 X, y 对的数据集
n = 1000                   # 样本数
p = 10                     # 特征数
noise = 0.4                # 为数据添加噪声
nmb_informative = p//2     # p 个特征中有多少个对预测真正有用
X, y = make_regression(n, p,
                       noise=noise,
                       n_informative=nmb_informative,
                       random_state=rs)

# 拆分为训练数据和测试数据
train_prop = 0.7           # 训练集数据比例
X_train, X_test, y_train, y_test = train_test_split(X, y, random_state=rs)

# 将模型拟合到训练数据
m_linearReg = LinearRegression().fit(X_train, y_train)
m_lasso = Lasso().fit(X_train, y_train)
m_ridge = Ridge().linearReg = LinearRegression().fit(X_train, y_train) if False else Ridge().fit(X_train, y_train) # 对应原代码 m_ridge = Ridge().fit(X_train, y_train)

# 计算各模型在训练数据上的预测值
ypred_train_linearReg = m_linearReg.predict(X_train)
ypred_train_lasso = m_lasso.predict(X_train)
ypred_train_ridge = m_ridge.predict(X_train)

# 计算各模型在测试数据上的预测值
ypred_test_linearReg = m_linearReg.predict(X_test)
ypred_test_lasso = m_lasso.predict(X_test)
ypred_test_ridge = m_ridge.predict(X_test)
```

请注意，`sklearn` 的实现都具有相同的方法，因此理解 `LinearRegression` 的实现原理意味着你基本上也理解了 `sklearn` 中任何其他回归算法的工作原理。

  

现在，我们已经拟合了各种模型，并希望对它们进行评估。我们可以使用 pandas 数据框让结果看起来更美观：

  

Python

```
# 首先计算指标并将其存入数组
loss_data = [
    ['linear regression',
     mean_squared_error(y_train, ypred_train_linearReg),
     mean_squared_error(y_test, ypred_test_linearReg),
     mean_absolute_error(y_train, ypred_train_linearReg),
     mean_absolute_error(y_test, ypred_test_linearReg)
    ],
    ['lasso',
     mean_squared_error(y_train, ypred_train_lasso),
     mean_squared_error(y_test, ypred_test_lasso),
     mean_absolute_error(y_train, ypred_train_lasso),
     mean_absolute_error(y_test, ypred_test_lasso)
    ],
    ['ridge',
     mean_squared_error(y_train, ypred_train_ridge),
     mean_squared_error(y_test, ypred_test_ridge),
     mean_absolute_error(y_train, ypred_train_ridge),
     mean_absolute_error(y_test, ypred_test_ridge)
    ]
]

# 创建一个 pandas 数据框，传入数组并命名列
cols = ['Model', 'train MSE', 'test MSE', 'train MAE', 'test MAE']
loss_df = pd.DataFrame(loss_data, columns=cols)
loss_df
```

#### 练习：

你能想出一个好理由来解释为什么 lasso 在这种情况下表现得如此糟糕吗？提示：超参数

  

（（算法上）选择更好 $\lambda$ 的方法之一是执行交叉验证，我们稍后将在实验中更深入地探讨。现在，我们注意到 sklearn 有一个内置对象，可以执行自动执行交叉验证以选择 $\lambda$ 的 LASSO 回归，称为 `LassoCV`——请注意，也有一个可用的 `LassoCV` 对象，同样也有 `RidgeCV` 对象）。正确选择 $\lambda$ 应该会使我们的结果发生巨大变化。我们按如下方式使用它：

  

Python

```
from sklearn.linear_model import LassoCV

m_lassoCV = LassoCV().fit(X_train, y_train)                 # 自动执行交叉验证以选择 lambda
ypred_train_lassoCV = m_lassoCV.predict(X_train)
ypred_test_lassoCV = m_lassoCV.predict(X_test)

# 将行添加到 loss_df
lassoCV_row = {'Model': 'lasso CV',
               'train MSE': mean_squared_error(y_train, ypred_train_lassoCV),
               'test MSE': mean_squared_error(y_test, ypred_test_lassoCV),
               'train MAE': mean_absolute_error(y_train, ypred_train_lassoCV),
               'test MAE' :mean_absolute_error(y_test, ypred_test_lassoCV)}

loss_df = pd.concat([loss_df, pd.DataFrame([lassoCV_row])],
                    ignore_index=True)
loss_df
```

让我们花一分钟时间检查我们拟合的线性模型对象。回想一下，线性模型只是最小化一个优化目标：

  

$$\hat{\beta} = \arg \min_{\beta} = \frac{1}{n} \Vert{} y-X\beta\Vert{}^2_2$$

如果我们想要访问计算出的估计值，即 $\hat{\beta}$ 的值，我们可以通过运行以下代码来实现：

  

- $\hat{\beta}_0 \leftrightarrow$ `m_linearReg.intercept_`
    
      
    
      
    
- $[\hat{\beta}_1, \hat{\beta}_2, \dots, \hat{\beta}_p ] \leftrightarrow$ `m_linearReg.coef_`
    
      
    
      
    

  

  

### 特征里有什么？

  

  

在本节中，让我们研究选择错误特征将如何影响模型的性能。在这种情况下，我们将使用单个特征。我们将指定一个“真实”函数 $f(x)=x^2$，然后创建一个“数据生成过程（data generating process）”，它允许我们从 $f$ 中对带噪声的观测值进行采样。我们通过以下方式采样：

  

$$y = f(x) + \epsilon, \qquad \epsilon \sim N(0, \sigma^2).$$

换句话说，我们数据集中的每个观测值 $y$ 都是在点 $x$ 处求值的 $f$ 加上一些随机的高斯噪声。我们将首先以这种方式生成 $n$ 个数据点，然后尝试将模型拟合到所得的数据集。我们将拟合两个模型：

  

1. 坏模型：$\hat{y} = b_0 + b_1 x$
    
      
    
      
    
2. 好模型：$\tilde{y} = w_0 + w_1 x^2$
    
      
    
      
    

我们称第一个模型为坏模型，因为我们知道真正的底层函数是平方函数，但我们的模型中只包含了 $x$。第二个模型是好模型，因为它使用了正确的特征。我们将使用单一特征，以便我们可以轻松可视化不同的模型拟合效果。

  

Python

```
n = 40
X = np.random.uniform(-1, 1, size=(n,1))          # 在 [-1, 1] 上均匀生成 40 个点并变形为列向量
noise = np.random.normal(0, 0.2, size=(n,1))      # 生成 40 个 sigma=0.2 的噪声变量
f = lambda x: x**2                                # 真实函数 f(x) = x^2
y = f(X) + noise                                  # 带噪声的观测值

bad_mod = LinearRegression()
bad_mod.fit(X, y)
```

Python

```
good_mod = LinearRegression()
good_mod.fit(np.concatenate((X,X**2), axis=1), y)
```

Python

```
# 可视化代码 - 有关绘图的更多详细信息，请参见入门实验

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14,5))
xrange = np.linspace(-1,1,1000)

# 第一个坐标轴
ax1.plot(xrange, f(xrange), color='blue', label='truth')
ax1.scatter(X, y, color='orange', label='noisy samples')

# 为 bad_mod 创建函数
bad_lr = lambda x: bad_mod.intercept_[0] + bad_mod.coef_[0][0]*x

ax1.plot(xrange, bad_lr(xrange), color='green', label='bad_mod')
ax1.legend()
ax1.set_title("bad model, $\hat{y} = b_0 + b_1 x$")

# 第二个坐标轴
ax2.plot(xrange, f(xrange), color='blue', label='truth')
ax2.scatter(X, y, color='orange', label='noisy samples')
# 为 good_mod 创建函数
good_lr = (lambda x: good_mod.intercept_[0]
           + good_mod.coef_[0][0]*x
           + good_mod.coef_[0][1]*x**2)
ax2.plot(xrange, good_lr(xrange), color='green', label='good_mod')
ax2.legend()
ax2.set_title("good model, $\tilde{y} = w_0 + w_1 x^2$")

plt.show()
```

从上面的练习中，我们可以看到思考在模型中包含哪些特征绝对是至关重要的。

  

#### 练习：

使用不同的真实函数重复上述实验，绘制结果并计算坏模型与好模型之间的 MSE

  

  

  

### 探索真实数据集

  

  

我们现在来看一个包含在 `life_expectancy.csv` 中的真实世界数据集，并介绍一些数据探索的技术。数据探索对于识别模型以及可能包含在模型中的特征非常重要。在前面的例子中，我们确切地知道“真实”模型是什么，但在现实中我们只能访问数据，并且必须某种程度上利用这些数据来学习对真理的良好估计。以下是对真实数据应该做的事情的粗略指南，您应该在整个课程中扩展这些技术（特别是在您的团队项目中）。

  

数据摘要：数据集中的 9 个特征代表婴儿死亡人数（Infant deaths）、酒精（Alcohol）、支出百分比（Percentage expenditure）、乙肝（Hepatitis B）、麻疹（Measles）、体质指数（BMI）、总支出（Total expenditure）、人口（Population）和学校教育（Schooling）。感兴趣的目标是预期寿命（Life expectancy）。总共有 500 条记录。

  

让我们读入数据并生成几个探索性图表。通常我们希望了解：

  

1. 目标变量和解释变量（特征）的分布
    
      
    
2. 是否有任何明显的异常值？
    
      
    
3. 目标变量与特征之间的关系是什么？例如，如果是线性的，那么线性模型是一个不错的选择。
    
      
    

此过程通常称为“探索性数据分析（EDA）”阶段。我们将使用 `seaborn` 模块进行绘图，当处理 pandas 数据框时，它很容易生成一些漂亮的图表，当然所有这些图表也可以使用 `matplotlib` 创建。

  

Python

```
import seaborn as sns
le_df = pd.read_csv("life_expectancy.csv")         # 使用 pandas 加载数据
```

Python

```
sns.boxplot(x=le_df['Life expectancy'])            # 使用箱线图检查目标变量的分布
plt.show()
```

接下来，我们观察目标变量（Life expectancy）与其他变量之间的相关性。如果特征高度相关（无论是正相关还是负相关），那么它们应该是模型的良好补充。但请注意，这些相关性仅捕获线性相关性，即使它们的关联性为零，两个变量也可能相关。有关一些很好的例子，请参见此处：

  

[https://blog.revolutionanalytics.com/2017/05/the-datasaurus-dozen.html](https://www.google.com/search?q=https://blog.revolutionanalytics.com/2017/05/the-datasaurus-dozen.html&utm_source=gemini)

  

  

请注意，相关矩阵是对称的，因此对角线上方的元素与对角线下方的元素相同。出于这个原因，我们只需要查看矩阵的下三角部分。

  

Python

```
corr_mat = le_df.corr()                               # 计算相关矩阵

mask = np.zeros_like(corr_mat, dtype=bool)            # 屏蔽上三角（相关矩阵是对称的）
mask[np.triu_indices_from(mask)] = True


f, ax = plt.subplots(figsize=(11, 9))
cmap = sns.diverging_palette(220, 10, as_cmap=True)   # 生成自定义色图
sns.heatmap(corr_mat, mask=mask, cmap=cmap, vmax=.3, center=0,
            square=True, linewidths=.5, cbar_kws={"shrink": .5})

plt.show()
```

另一种重要类型的图是对偶图（pair plot），它绘制了每个变量与其他所有变量的散点图。请注意，对角线包含每个变量的直方图。根据散点图，我们通常希望寻找似乎相关的变量。

  

Python

```
sns.pairplot(le_df)
plt.show()
```

#### 扩展练习：LASSO 与 Ridge 岭回归

在本练习中，我们将探讨 LASSO 和 Ridge 回归模型之间的区别，并将深入研究交叉验证及其如何为这些模型选择超参数。你需要完成以下任务：

  

Q1. 考虑数据集：`data.csv`，具有响应变量 $Y$ 和特征 $X_1, \dots, X_8$。创建一个成对图（pairs plot）来研究特征之间的相关性。描述你所看到的内容以及这可能如何影响线性回归模型。

  

Q2. 为了正确运行 LASSO 和 Ridge，我们通常会对数据集中的特征进行重新缩放。请解释原因。然后，使用 `sklearn.preprocessing.StandardScaler` 函数缩放你的特征。打印出 8 个特征中每一个特征的均值和方差（在它们被缩放之后）。

  

Q3. 现在我们将岭回归应用于该数据集，回想一下岭回归被定义为以下优化问题的解：

  

$$\hat{\beta} = \arg\min \left \{ \frac{1}{2}\Vert{}Y-X\beta \Vert{}^2_2 + \lambda \Vert{} \beta\Vert{}_2^2\right \}.$$

运行 $\lambda = \{0.01, 0.1, 0.5, 1, 1.5, 2, 5, 10, 20, 30, 50, 100, 200, 300\}$ 的岭回归。创建一个图，其中 $x$ 轴表示 $\log(\lambda)$，$y$ 轴表示每个拟合的岭模型中每个特征的系数。换句话说，该图应描述对于不同的 $\lambda$ 选择，模型中的每个系数会发生什么变化。对于此问题，允许您使用 Ridge 回归的 sklearn 实现来运行模型并提取系数，并使用基础的 matplotlib/numpy 来创建图表，但不得使用任何其他包来生成此图。用几行字评论你所看到的现象，特别是对于特征 3、4、5 你观察到了什么？

  

Q4. 现在，使用留一法交叉验证（LOOCV）为岭回归问题寻找一个好的 $\lambda$ 值。创建一个从 $0$ 到 $50$、步长为 $0.1$ 的 $\lambda$ 值网格，即网格为：$0, 0.1, 0.2, \dots, 50$。对于每个数据点 $i=1, \dots, n$，在移除了点 $i$ 的数据集上用每个 $\lambda$ 值运行岭回归，找到 $\hat{\beta}$，然后得到预测 $Y_i$ 的留一法误差。对所有 $n$ 个 $i$ 的选择求平方误差的平均值。绘制留一法误差随 $\lambda$ 变化的图并找到最佳 $\lambda$ 值。将你的结果与标准普通最小二乘法（OLS）进行比较，根据你的分析，岭回归似乎能提供更好的预测误差吗？请注意，对于此问题，你 **不得** 使用任何实现交叉验证的现有包，你必须从头开始自己编写代码。你必须使用基础的 matplotlib 功能从头开始创建图表。

  

Q5. 重复 Q3，但针对 LASSO

  

Q6. 重复 Q4，但针对 LASSO

  

Q7. 评论你观察到的内容，以及在预测问题中你会更喜欢哪个模型。如果是推断问题（inference problem）呢？