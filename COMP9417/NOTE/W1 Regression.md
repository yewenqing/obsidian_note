

## 一、 文档全景概览

- **文档总体主题、核心目的与面向对象：**
    
      
    - 本文档是新南威尔士大学（UNSW）2026年第3学期（T3）开设的《COMP9417: Machine Learning & Data Mining》课程的第一周讲义（Week 1: Regression）。
        
          
        
    - 核心目的在于向学生介绍机器学习的基础概念，并深度讲解用于数值预测的监督学习算法——线性回归，包括其底层数学推导、概率解释、正则化方法、模型评估指标以及偏差-方差权衡（Bias-Variance Tradeoff）。
        
          
        
    - 面向对象为选修该课程的UNSW在校学生，要求具备基础的概率论与统计学知识。
        
          
        
- **整体目录结构与行文逻辑脉络：**
    
      
    1. Administration（课程行政安排）
        
          
        
    2. A Brief Course Introduction（机器学习课程简介）
        
          
        
    3. Introduction to Regression（回归任务简介）
        
          
        
    4. Learning Linear Regression Models（线性回归模型学习与参数估计）
        
          
        
    5. Step back: Statistical Techniques for Data Analysis（补充：数据分析的统计学技术）
        
          
        
    6. Univariate Linear Regression（单变量线性回归）
        
          
        
    7. Multiple linear regression（多元线性回归）
        
          
        
    8. Linear Regression for curve shapes（用于曲线形状的线性回归/多项式回归）
        
          
        
    9. Regularisation（正则化）
        
          
        
    10. Train, Validation & Test Data（训练集、验证集与测试集）
        
          
        
    11. Model Evaluation（模型评估）
        
          
        
    12. Some further issues in learning linear regression models（线性回归模型学习的其他问题）
        
          
        
    13. Local (nearest-neighbor) regression（局部/最近邻回归）
        
          
        
    14. Bias-Variance Tradeoff（偏差-方差权衡）
        
          
        

## 二、 逐章节深度拆解

### 1. Administration（课程行政安排）

- **章节核心要点：** 详细列出了课程的授课教师团队、沟通渠道、教学安排与考核标准。
    
      
    
- **关键论据与逻辑：** 无特定学术论证，纯行政信息宣告。
    
      
    
- **核心数据、表格或专有名词：**
    
      
    - 授课负责人：A/Prof Gustavo Batista。
        
          
        
    - 考核比例：作业1（15%，第3周交）、作业2（15%，第6周交）、小组项目（20%，第9周交，每组4-5人）、期末考试（50%）。
        
          
        
    - 工具：所有作业均需使用Python编写。
        
          
        
    - 课程进度表：第1周（回归），第2/3周（分类），第4周（树学习），第5/7周（核方法），第7/8周（集成学习），第8周（神经学习），第9周（无监督学习），第10周（学习理论），第6周为灵活调整周/假期。
        
          
        

### 2. A Brief Course Introduction（机器学习课程简介）

- **章节核心要点：** 定义机器学习，阐述课程覆盖与不覆盖的领域，并通过案例介绍机器学习流水线及监督/无监督学习的区别。
    
      
    
- **关键论据与逻辑：** 通过引用领域学者的经典著作来界定机器学习与数据挖掘的边界，并解释监督学习在工业界占据主导地位的原因是因为其目标定义和误差评估（损失函数）更容易建立。
    
      
    
- **核心数据、表格或专有名词：**
    
      
    - 经典定义引用：T. Mitchell (1997) 提出“自动从经验中改进的程序”；S. Shwartz (2014) 提出“自动检测数据中的有意义模式”；I. Witten (2016) 定义数据挖掘为“提取隐含的、未知的、有用的信息”。
        
          
        
    - 不覆盖的内容：概率论与统计学基础、大量的深度学习、强化学习、大数据、AI伦理。
        
          
        
    - Machine learning pipeline（机器学习流水线）：Database -> Data Retrieval -> Data Preparation (Data Cleaning & Pre-processing, Feature Engineering & Extraction, Feature Scaling & Selection) -> Modeling -> Model Evaluation & Tuning -> Deployment & Monitoring。
        
          
        

### 3. Introduction to Regression（回归任务简介）

- **章节核心要点：** 引入回归概念，区分其与分类任务的不同。
    
      
    
- **关键论据与逻辑：** 分类预测离散值（如垃圾邮件识别），而回归预测连续数值。
    
      
    
- **核心数据、表格或专有名词：**
    
      
    - 房价预测线性回归方程案例：$\text{House Price} = 8775.58 + 147.12 \times \text{House Size} + 9660.37 \times \text{Bedrooms} + 25691.99 \times \text{Bathrooms} - 1285.01 \times \text{Age}$。
        
          
        

### 4. Learning Linear Regression Models（线性回归模型学习）

- **章节核心要点：** 讲解线性回归的数学建模、损失函数（均方误差）、优化算法（梯度下降与闭式解）及其概率解释与前提假设。
    
      
    
- **关键论据与逻辑：** 作者首先定义残差平方和，随后通过梯度下降推导迭代更新法则；接着通过矩阵求导给出解析解；最后，证明在残差服从正态分布的假设下，最小二乘法等价于最大似然估计（MLE）。
    
      
    
- **核心数据、表格或专有名词（硬核提取）：**
    
      
    - 假设函数：$\hat{y} = \theta_0 + \theta_1 x_1 + \dots + \theta_n x_n = h(x)$。
        
          
        
    - 向量化表达：$x = [x_0, x_1, \dots, x_n]^T$，设定 $x_0 = 1$；$\theta = [\theta_0, \theta_1, \dots, \theta_n]^T$。
        
          
        
    - 代价函数/损失函数（Cost/Loss Function $J(\theta)$）：$J(\theta) = \sum_{j=1}^m (y_j - x_j^T\theta)^2 = (y - X\theta)^T(y - X\theta)$。
        
          
        
    - MSE（均方误差）：$\frac{1}{m}\sum_{j=1}^m (y_j - x_j^T\theta)^2$。
        
          
        
    - 梯度下降更新法则：$\theta_i^{(t+1)} := \theta_i^{(t)} - \alpha \frac{\partial}{\partial \theta_i} J(\theta_i^{(t)})$，其中 $\alpha$ 为学习率。
        
          
        
    - LMS（最小均方）更新规则：$\theta_i^{(t+1)} := \theta_i^{(t)} + 2\alpha(y_j - h_\theta(x_j))x_{ji}$。
        
          
        
    - 正规方程（Normal Equations）/ 闭式解：$\theta = (X^T X)^{-1} X^T y$。
        
          
        
    - 概率解释：假设 $y_j = x_j^T\theta + \epsilon_j$，且 $\epsilon_j \sim N(0, \sigma^2)$，似然函数 $\mathcal{L}(\theta) = P(y\vert{}X; \theta)$。最大化对数似然 $l(\theta)$ 在数学上完全等同于最小化平方误差 $\sum_{j=1}^m (y_j - x_j^T\theta)^2$。
        
          
        
    - 线性回归的四大假设：Linearity（线性关系）、Homoscedasticity（同方差性）、Independence（独立性）、Normality of residuals（残差正态性）。
        
          
        

### 5. Step back: Statistical Techniques for Data Analysis（补充：统计学技术）

- **章节核心要点：** 回顾样本与总体的关系，以及常用的统计估计和相关性度量。
    
      
    
- **关键论据与逻辑：** 概率是从总体推导样本（演绎），而统计是从样本推断总体（归纳）。通过计算相关系数只能发现线性关联，不能证明因果关系。
    
      
    
- **核心数据、表格或专有名词（硬核提取）：**
    
      
    - 样本均值（无偏）：$\bar{x} = \frac{1}{N}\sum_{i=1}^N x_i$。
        
          
        
    - 样本方差（无偏）：$s^2 = \frac{1}{N-1}\sum_i (x_i - \bar{x})^2$。
        
          
        
    - 样本标准差（有偏）：$s = \sqrt{s^2}$。
        
          
        
    - 协方差（Covariance）：$cov(x,y) = \frac{\sum_i (x_i - \bar{x})(y_i - \bar{y})}{N-1} = \frac{(\sum_i x_i y_i) - N\bar{x}\bar{y}}{N-1}$。
        
          
        
    - 皮尔逊相关系数（Pearson correlation $r$）：$r = \frac{cov(x,y)}{\sqrt{var(x)}\sqrt{var(y)}}$。介于 -1 到 +1 之间，仅适用于捕获线性关系。
        
          
        

### 6. Univariate Linear Regression（单变量线性回归）

- **章节核心要点：** 探讨只有一个自变量时的线性回归具体解，并分析异常值（Outliers）的影响。
    
      
    
- **关键论据与逻辑：** 通过最小化误差偏导数为零，推导出斜率和截距的代数表达式。此外，强调由于最小二乘法的特性（残差和为0），模型极易受到异常值的拉扯。
    
      
    
- **核心数据、表格或专有名词：**
    
      
    - 斜率参数：$\theta_1 = \frac{Cov(x,y)}{var(x)} = \frac{\sum_{j=1}^m (x_j - \bar{x})(y_j - \bar{y})}{\sum_{j=1}^m (x_j - \bar{x})^2}$。
        
          
        
    - 截距参数：$\theta_0 = \bar{y} - \theta_1\bar{x}$。
        
          
        
    - 平移特性（Translation）：将所有 $x$ 减去其均值（Zero-center），截距将等于 $y$ 的均值，回归系数不受影响。
        
          
        

### 7. Multiple linear regression（多元线性回归）

- **章节核心要点：** 将单变量扩展至多变量情形。
    
      
    
- **关键论据与逻辑：** 增加变量可以使预测的置信区间更窄。其本质依然是矩阵运算下的最优化问题。
    
      
    
- **核心数据、表格或专有名词：**
    
      
    - 公式范例：$\hat{w} = \theta_0 + \theta_1 h + \theta_2 b$。
        
          
        
    - 最小化目标：$\sum_{j=1}^m (w_j - (\theta_0 + \theta_1 h_j + \theta_2 b_j))^2$。
        
          
        

### 8. Linear Regression for curve shapes（用于曲线形状的线性回归）

- **章节核心要点：** 论证线性回归可以通过变量转换（如多项式展开）来拟合非线性曲线。
    
      
    
- **关键论据与逻辑：** 只要模型关于“参数（$\theta$）”是线性的，它就属于线性回归，即使特征本身包含非线性项（如 $x^2, x^3$）。
    
      
    
- **核心数据、表格或专有名词：**
    
      
    - 多项式回归示例：$\hat{y} = \theta_0 + \theta_1 x_1 + \theta_2 x_1^2 + \theta_3 x_1^3$。
        
          
        
    - 令 $x_2 = x_1^2, x_3 = x_1^3$，原式转化为：$\hat{y} = \theta_0 + \theta_1 x_1 + \theta_2 x_2 + \theta_3 x_3$。
        
          
        
    - 非线性回归的反例：$\hat{y} = \frac{\theta_1 x}{\theta_2 + x}$（关于参数非线性）。
        
          
        

### 9. Regularisation（正则化）

- **章节核心要点：** 引入正则化技术以防止过拟合，通过对参数大小施加惩罚（收缩）来控制模型复杂度。
    
      
    
- **关键论据与逻辑：** 在损失函数中加入权重惩罚项，使得模型在拟合数据的同时尽可能保持极小的参数权重，从而避免对训练数据中的噪声过度敏感。
    
      
    
- **核心数据、表格或专有名词（硬核提取）：**
    
      
    - 正则化代价函数通用形式：$J(\theta) = \sum_{j=1}^m (y_j - h_\theta(x_j))^2 + \lambda \sum_{i=1}^n \theta_i^2$。
        
          
        
    - Ridge Regression（岭回归）：目标函数 $\theta^* = \arg\min (y-X\theta)^T(y-X\theta) + \lambda\vert{}\vert{}\theta\vert{}\vert{}^2$。
        
          
        
    - Ridge 闭式解：$\theta = (X^T X + \lambda I)^{-1} X^T y$（$\lambda I$ 加在对角线上提高了矩阵求逆的数值稳定性）。
        
          
        
    - LASSO 回归：将正则化项替换为权重的绝对值之和 $\sum_i \vert{}\theta_i\vert{}$，其特点是倾向于产生稀疏解（Sparse solutions，即将部分无关特征的权重直接压缩为0）。
        
          
        

### 10. Train, Validation & Test Data（训练集、验证集与测试集）

- **章节核心要点：** 明确数据集划分的定义及其泛化目标。
    
      
    
- **关键论据与逻辑：** 只有通过模型从未见过的数据进行测试，才能真实反映模型的泛化能力。
    
      
    
- **核心数据、表格或专有名词：**
    
      
    - Train Data：用于学习模型及其参数。
        
          
        
    - Validation Data：在调整超参数时提供无偏评估。
        
          
        
    - Test Data：用于最终测试，在实践中此数据的真实标签对模型不可见。
        
          
        
    - Generalization（泛化能力）：模型对从同一分布提取的未见新数据的适应能力。
        
          
        

### 11. Model Evaluation（模型评估）

- **章节核心要点：** 罗列并解释了用于回归模型的四大核心评估指标。
    
      
    
- **关键论据与逻辑：** 绝对误差指标（RMSE/MAE）适合衡量具体偏差但难以跨数据集对比；比例型指标（$R^2$及调整$R^2$）能够直观反映模型对方差的解释比例和质量。
    
      
    
- **核心数据、表格或专有名词（硬核提取）：**
    
      
    - RMSE（均方根误差）：$RMSE = \sqrt{\frac{1}{m}\sum_{j=1}^m (y_j - \hat{y}_j)^2}$。
        
          
        
    - MAE（平均绝对误差）：$MAE = \frac{1}{m}\sum_{j=1}^m \vert{}y_j - \hat{y}_j\vert{}$。
        
          
        
    - R-squared（决定系数）：$R^2 = 1 - \frac{\sum_{j=1}^m (y_j - \hat{y}_j)^2}{\sum_{j=1}^m (y_j - \bar{y})^2}$。
        
          
        
    - Adjusted R-squared（调整后的决定系数）：$R_{adjusted}^2 = 1 - \left[ \frac{(1-R^2)(m-1)}{m-n-1} \right]$，其中 $m$ 是样本总量，$n$ 是预测变量/特征的数量。
        
          
        

### 12. Some further issues in learning linear regression models（线性回归的进阶问题）

- **章节核心要点：** 讨论如何处理分类（离散）特征、特征交互以及模型选择/降维的方法。
    
      
    
- **关键论据与逻辑：** 使用指示变量解决分类映射问题，使用贪婪图搜索（Greedy search）解决特征子集筛选问题以降低模型复杂度。
    
      
    
- **核心数据、表格或专有名词：**
    
      
    - Indicator variables（指示变量/二元变量）：值为0或1，例如吃药 $D=1$，否则 $D=0$。模型为 $y = 70 + 5D + 0.44 \times Age$。
        
          
        
    - Interaction effect（交互效应）：引入新变量 $z = D \times Age$，模型变为 $y = 70 + 5D + 0.44 \times Age + 0.21z$。
        
          
        
    - 模型选择三大路径：1. Subset-selection（子集选择/逐步回归），2. Shrinkage（正则化收缩），3. Dimensionality-reduction（降维映射）。
        
          
        
    - 子集搜索算法：Forward-selection（前向选择，从无到有加）、Backward-elimination（后向剔除，从全到缺删）、Bidirectional（双向结合），评判标准通常基于计算 $R^2$ 的变化。
        
          
        

### 13. Local (nearest-neighbor) regression（局部/最近邻回归）

- **章节核心要点：** 介绍基于实例的惰性学习方法（Lazy learning），特别是 KNN 在数值预测中的应用。
    
      
    
- **关键论据与逻辑：** 不需要预先构建全局模型，而是通过“记住”所有训练数据，在预测时寻找最近的邻居并对周围实例执行局部线性（或多项式）拟合。
    
      
    
- **核心数据、表格或专有名词（硬核提取）：**
    
      
    - 欧几里得距离（Euclidean distance）：$d(x_i, x_j) = \sqrt{\sum_{k=1}^n (x_{ik} - x_{jk})^2}$。
        
          
        
    - K-nearest neighbour (KNN) 数值预测公式：$\hat{y}_q = \frac{\sum_{i=1}^k f(x_i)}{k}$。
        
          
        
    - 局部回归形式：$\hat{y} = \hat{f}(x) = \theta_0 + \theta_1 x_1 + \dots + \theta_n x_n$ 仅拟合查询点 $x_q$ 的 $k$ 个最近邻，产生“分段逼近”（Piecewise approximation）。
        
          
        

### 14. Bias-Variance Tradeoff（偏差-方差权衡）

- **章节核心要点：** 阐述机器学习中最核心的误差分解原理，解释欠拟合与过拟合的本质属性。
    
      
    
- **关键论据与逻辑：** 模型复杂度过低导致高偏差（模型没学到规律），复杂度过高导致高方差（模型连噪声也背下来了）。最终目标是通过调整复杂度来寻找使总体预测误差最小的最优平衡点。
    
      
    
- **核心数据、表格或专有名词：**
    
      
    - Bias（偏差）：模型平均预测值与尝试预测的正确值之间的差异。高偏差 = Underfitting（欠拟合）。
        
          
        
    - Variance（方差）：给定数据点的模型预测的可变性（数据散布程度）。高方差 = Overfitting（过拟合）。
        
          
        
    - Bias-Variance Decomposition（误差分解公式）：期望误差 = Bias² + Variance + $\epsilon$（不可约噪声）。
        
          
        

## 三、 核心结论、洞察与全篇总结

- **全篇最核心的结论与建议：**
    
      
    1. **最小二乘法与最大似然的等价性：** 在假设残差服从独立同分布（i.i.d.）的正态分布前提下，通过最小化均方误差（MSE）寻找到的线性回归参数 $\theta$，在数学上严格等同于最大似然估计（MLE）的最优解。
        
          
        
    2. **过拟合必须通过结构化约束来解决：** 单纯依靠增加特征（包括多项式特征展开）虽然能逼近任意非线性曲线，但必然面临高方差（过拟合）。必须引入正则化（Ridge或LASSO）或特征子集搜索来控制参数规模，实现最佳的偏差-方差权衡。
        
          
        
    3. **算法评估的多维性：** 单一指标不足以评估回归模型。RMSE和MAE侧重于数值绝对偏差度量，而 Adjusted R-squared 引入了对模型参数复杂度的惩罚项，是跨维度对比模型质量更全面客观的标准。
        
          
        
- **文档实际参考价值评估：** 该文档具有极高的学术严谨性与基石价值。它不仅浮于算法调用的表面，而是深度拆解了“从损失函数的推导 $\rightarrow$ 矩阵形式的闭式解/梯度下降迭代法则 $\rightarrow$ 背后的概率论底层假设 $\rightarrow$ 到模型评估与正则化约束”这一完整的算法黑盒。对于旨在建立坚实数学基础的机器学习入门者与从业者而言，这是一份兼具理论推导与工程实践（如评估指标选取、分类变量处理）的极高质量审计级教学参考。