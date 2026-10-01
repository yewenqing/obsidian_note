
## 一、 文档全景概览

- **文档总体主题、核心目的与面向对象：** 该文档是新南威尔士大学（UNSW Australia）COMP9417“机器学习与数据挖掘”课程的授课课件（分类问题第一部分）。其核心目的在于向学生系统性地介绍解决分类问题的机器学习方法，使读者能够复现理论结果、概述算法技术，并描述相关主题的实际应用。面向对象主要为选修该课程的计算机科学及相关专业的学生或机器学习初学者。
    
      
    
- **整体目录结构与行文逻辑脉络：**
    
    该文档未提供显式的目录页，但根据全量扫描，其行文逻辑脉络严格按以下顺序展开：
    
      
    1. 课程目标与分类问题简介（Aims & Introduction）
        
          
        
    2. 生成式与判别式学习算法对比（Generative vs. Discriminative algorithm）
        
          
        
    3. 二维空间中的线性分类（Linear classification in two dimensions）
        
          
        
    4. 逻辑回归算法深度解析（Logistic Regression）
        
          
        
    5. 机器学习的任务框架与泛化理论（How solve a task / Generalisation）
        
          
        
    6. 训练与测试及交叉验证方法（Train-and-test / Cross-validation）
        
          
        
    7. 数据类型分类体系（Data Types）
        
          
        
    8. 二元分类任务及误差评估指标（Binary Classification task & Evaluation metrics）
        
          
        
    9. 缺失值的处理策略（Missing Values）
        
          
        
    10. 距离度量标准（Minkowski distance 等）
        
          
        
    11. 最近质心分类器（Nearest Centroid Classifier）
        
          
        
    12. K-最近邻算法原理与优缺点（K-Nearest Neighbour Algorithm）
        
          
        
    13. 维度灾难及噪音处理（Curse of Dimensionality & Dealing with noise）
        
          
        

## 二、 逐章节深度拆解

### 1. 课程目标、简介与分类器类型（第 1-10 页）

- **章节核心要点：** 介绍了分类（有时称为概念学习）是机器学习的主流方法，旨在学习一个将输入数据点映射到离散输出（类别）的函数。通过在鱼类加工厂利用宽度（Width）和亮度（Lightness）特征对海鲈鱼（Sea bass）与鲑鱼（Salmon）进行分类的案例，直观展示了分类过程。详细区分了生成式算法与判别式算法。
    
      
    
- **关键论据与逻辑：** 生成式算法分别对每个类建立模型，学习机制 $p(x\vert{}y)$ 和类先验 $p(y)$，从而得到 $p(x,y)=p(x\vert{}y)p(y)$。在预测时，通过计算 $p(y=0\vert{}x)=\frac{p(x\vert{}y=0)p(y=0)}{p(x)}$ 并比较大小来决定归属。判别式算法不建立多类模型，而是专注于寻找分离类别的决策边界，直接学习 $p(y\vert{}x)$。
    
      
    
- **核心数据、表格或专有名词：** Concept learning（概念学习）、Generative learning algorithm（生成式学习算法）、Discriminative learning algorithm（判别式学习算法）、Class prior（类先验）。
    
      
    

### 2. 线性分类与逻辑回归（第 11-22 页）

- **章节核心要点：** 探讨了线性分类器如何在二维空间中寻找分离正负类的直线。指出基础线性分类器通过正负类质心连线的中点来构建决策边界。随后深入讲解了逻辑回归（一种概率线性分类器），强调由于二元数据的非正态分布及输出需限制在 [0,1] 范围内，常规线性回归失效，因此引入 Sigmoid 曲线建模。
    
      
    
- **关键论据与逻辑：** 线性决策边界定义为 $x^Tw=-c=t$，其中权重向量 $w=p-n$ 垂直于决策边界，阈值 $t=\frac{\vert{}\vert{}p\vert{}\vert{}^2-\vert{}\vert{}n\vert{}\vert{}^2}{2}$。逻辑回归将概率建模为 $P(y=1\vert{}x)=\frac{1}{1+e^{-x^T\beta}}$。在参数估计上，利用最大似然原则（Maximum likelihood principle）推导出凸代价函数（Convex cost function），并使用梯度下降法（Gradient Descent）求解全局最小值。逻辑回归的优点是易于实现、解释和扩展到多类，缺点是在高维数据中易过拟合、需要特征转换处理非线性边界、对异常值敏感且要求变量间共线性低。
    
      
    
- **核心数据、表格或专有名词：** Weight vector（权重向量）、Decision threshold（决策阈值）、Sigmoid curve（S型曲线）、Maximum likelihood principle（最大似然原则）、对数似然函数 $l(\beta)=\sum_{i=1}^{m}[y^{(i)}\log(h_\beta(x^{(i)})) + (1-y^{(i)})\log(1-h_\beta(x^{(i)}))]$、代价函数 $J(\beta)$、Convex（凸函数）、Regularization（正则化）、Collinearity（共线性）。
    
      
    

### 3. 泛化能力与交叉验证（第 23-30 页）

- **章节核心要点：** 阐述了机器学习解决任务的整体流程图，并引出“泛化（Generalisation）”这一核心目标，即训练好的模型对未见数据的分类或预测能力。详细介绍了为了评估泛化能力而使用的多种训练与测试方法。
    
      
    
- **关键论据与逻辑：** 泛化基于三大假设：样本是独立同分布随机抽取的（i.i.d）、分布是平稳的、训练/验证/测试集均来自同一分布。为了防止模型评估与测试集耦合，介绍了三种交叉验证方法：Holdout method（留出法，划分为训练集和测试集）、Leave-One-Out Cross validation (LOOCV，留一法交叉验证) 以及 K-fold Cross Validation（K折交叉验证）。强调必须使用独立的验证集（Validation set）进行超参数调整和模型选择，以确保测试集的独立性。
    
      
    
- **核心数据、表格或专有名词：** Generalisation（泛化）、i.i.d（独立同分布）、Stationary（平稳的）、Holdout method、LOOCV、K-fold Cross Validation、Validation set（验证集）、Hyperparameter tuning（超参数调优）。
    
      
    

### 4. 数据类型体系（第 31-33 页）

- **章节核心要点：** 总结了机器学习中必须将数据转换为数值形式的基本要求，并对数据类型进行了详尽的分类。
    
      
    
- **关键论据与逻辑：** 顶层分为数值型（Numerical，如整数、浮点数）和类别型（Categorical，非数值的离散标签）。进一步细化为7个子类：无关数据（Irrelevant，如姓名）、名词性数据（Nominal，无数值关系的离散值）、二元数据（Binary，仅两种可能）、序数数据（Ordinal，可排序但间距无意义）、计数数据（Count，非负整数）、时间数据（Time，循环连续形式）和区间数据（Interval，有刻度且可测距）。
    
      
    
- **核心数据、表格或专有名词：** Numerical、Categorical、Irrelevant、Nominal、Binary、Ordinal、Count、Time、Interval。
    
      
    

### 5. 二元分类任务与评估指标（第 34-40 页）

- **章节核心要点：** 定义了二元分类任务中的正类（$y=1$）和负类（$y=0$），并指出在实际中（如癌症预测）两类误判的成本往往不相等。全面推导了分类模型性能的各项数学评估指标。
    
      
    
- **关键论据与逻辑：** 通过列举混淆矩阵（Confusion matrix）中的真正例（TP）、真负例（TN）、假正例（FP）和假负例（FN）来定义各类指标。分类准确率（Accuracy）等于正确预测数除以总测试集大小；错误率等于 $1 - Accuracy$。精确率（Precision）=$TP / (TP+FP)$；召回率（Recall/Sensitivity/TPR）=$TP / (TP+FN)$。F1 分数是精确率和召回率的调和平均数：$F_1 = 2 \times \frac{precision \times recall}{precision + recall}$。ROC 曲线下的面积（AUC）评估模型在不同阈值下的区分能力，AUC 接近 1 为佳，0.5 代表无分离能力。
    
      
    
- **核心数据、表格或专有名词：** Binomial classification（二项分类）、Contingency table（列联表）、Confusion matrix（混淆矩阵）、TP/TN/FP/FN、Indicator function $I[]$、Precision/correctness、Recall/sensitivity/completeness/true positive rate (TPR)、F1 score、Harmonic mean（调和平均数）、AUC-ROC curve。
    
      
    

### 6. 缺失值处理策略（第 41-48 页）

- **章节核心要点：** 列举了现实数据存在缺失的原因（人为错误、传感器错误、软件缺陷、预处理故障），并逐一评估了五种处理缺失值的常用方法及其优劣。
    
      
    
- **关键论据与逻辑：**
    
      
    1. 删除含缺失值的样本：缺失为随机时鲁棒，但导致数据丢失，缺失比例高时表现极差。
        
          
        
    2. 用均值/中位数/众数替换：适合小数据集，但会降低变量的方差，给模型增加偏差，整体表现较差。
        
          
        
    3. 分配唯一类别或最频繁类别：无数据丢失且易实现，但专用于类别特征，可能会增加模型的方差或偏差。
        
          
        
    4. 预测缺失值：如果偏差小于遗漏变量偏差则能改进模型，但常仅被视为真实值的替代品。
        
          
        
    5. 使用支持缺失值的算法：无需构建预测模型，但此类算法在大型数据库中极耗时。
        
          
        
- **核心数据、表格或专有名词：** Imputing（插补）、Omitted variable bias（遗漏变量偏差）。
    
      
    

### 7. 距离度量与样本代表（第 49-60 页）

- **章节核心要点：** 详细定义了最近邻算法所需的各类距离计算公式及其数学属性，并介绍了数据群组的“代表点（Exemplar）”概念。
    
      
    
- **关键论据与逻辑：** 核心公式为闵可夫斯基距离（Minkowski distance）：$Dis_p(x,y) = (\sum_{j=1}^d \vert{}x_j - y_j\vert{}^p)^{1/p}$。当 $p=2$ 时为欧几里得距离（Euclidean distance）；$p=1$ 时为曼哈顿距离（Manhattan distance）；$p=\infty$ 时为切比雪夫距离（Chebyshev distance）；$L_0$ 范数计算不同元素的数量。对于非实数数据，可使用汉明距离（Hamming distance）或莱文斯坦距离（Levenshtein distance）。所有距离度量必须满足自身距离为0、非负性、对称性和三角不等式（$p<1$ 时三角不等式不成立）。在代表点选择上，算术平均值（Centroid）使欧几里得距离平方和最小化，而中心点（Medoid）则限制代表点必须是实际存在的数据点，其计算复杂度为 $O(n^2)$。
    
      
    
- **核心数据、表格或专有名词：** Minkowski distance、Euclidean distance（2-norm）、Manhattan/cityblock distance（1-norm）、Chebyshev distance、Hamming distance、Levenshtein/edit distance、Rotation invariant（旋转不变性）、Triangle inequality（三角不等式）、Pseudo-metric（伪度量）、Exemplar（代表点）、Medoid（中心点）、Centroid（质心）、Geometric median（几何中位数）。
    
      
    

### 8. 最近质心分类器（第 61-66 页）

- **章节核心要点：** 介绍了一种基于最小距离原则的简单分类器，即每个类的代表点就是该类的质心。
    
      
    
- **关键论据与逻辑：** 在训练阶段计算每类的均值向量 $\mu_k = \frac{1}{\vert{}C_k\vert{}} \sum_{j \in C_k} x_j$；在测试阶段将未知对象归入距离最近的质心所属类。当使用欧几里得距离时，它与基础线性分类器的决策边界完全一致。优点是简单、快速、适用于类紧凑且相互远离的情况；缺点是面对多峰（Multimodal）、非球形数据、异常值、噪音和缺失数据时表现极差。
    
      
    
- **核心数据、表格或专有名词：** Nearest Centroid Classifier、Minimum distance principle（最小距离原则）、Mean vector（均值向量）。
    
      
    

### 9. K-最近邻算法（KNN）（第 67-84 页）

- **章节核心要点：** 全面剖析了 KNN 作为一种基于实例（Instance-based）、死记硬背（Rote learning）和惰性学习（Lazy learning）的分类方法。
    
      
    
- **关键论据与逻辑：** KNN 在分类时通过计算查询点与训练实例的距离，并在 $k$ 个最近邻居中进行投票 $\hat{f}(x_q) \leftarrow \arg \max_{v \in V} \sum_{j=1}^k \delta(v, f(x_j))$，若为实值目标则取均值。为防止不同尺度属性的干扰，必须进行数据归一化（如 Min-max 归一化 $x_{jr}' = \frac{x_{jr} - \min(x_{jr})}{\max(x_{jr}) - \min(x_{jr})}$ 或 Z-score 归一化）。1-NN 具有低偏差但高方差，增加 $k$ 会增加偏差降低方差。为了改进，引入了距离加权 KNN，权重 $w_i = \frac{1}{Dis(x_q, x_i)^2}$；当 $k=m$（全体样本）时称为 Shepard 方法。KNN 算法优点是准确、训练极快；缺点是查询极慢（简单搜索 $O(n)$，超过 10 维树结构优化失效）、假定所有属性同等重要而易受无关属性干扰。其评估通常采用留一法交叉验证（LOOCV）。
    
      
    
- **核心数据、表格或专有名词：** Rote learning（机械学习）、Lazy learning（惰性学习）、Min-max normalisation、Z-score、Distance-Weighted KNN、Shepard's method、$O(n)$、$O(\log n)$。
    
      
    

### 10. 维度灾难与噪音处理（第 85-96 页）

- **章节核心要点：** 深入探讨了高维空间对距离分类器的致命影响（即维度灾难），并给出了应对策略及实际应用案例。
    
      
    
- **关键论据与逻辑：** 随着维度增加，所有数据点在距离上趋于等距，使得距离度量失去定性意义。同时，实例空间中的“单元”呈指数级增长，需要指数级的庞大数据量来支撑，且协方差等参数极难估计。应对维度灾难的策略包括对属性进行权重拉伸（最小化交叉验证误差）甚至将其设为0剔除。针对噪音问题，除增加 $k$ 值外，可使用 IB3（Instance-Based Learning 3）算法：记录实例的预测表现并根据阈值丢弃表现差的实例。最后展示了 KNN 在自动化多发性硬化病变（MS-lesion）图像分割上的成功应用。
    
      
    
- **核心数据、表格或专有名词：** Curse of Dimensionality（维度灾难）、IB3（Instance-Based Learning 3）、Automated MS-lesion segmentation。
    
      
    

## 三、 核心结论、洞察与全篇总结

- **全篇核心结论与行动建议：**
    
      
    1. **算法选择不存在银弹：** 判别式算法（如逻辑回归）在处理高维数据特征或需直接寻找线性决策边界时效率优异；而生成式算法和基于实例的惰性学习（如 KNN）则在捕获局部复杂模式时表现更好。实践中应根据数据分布（是否多峰、非线性）及任务核心痛点（需训练快还是预测快）严格遴选算法。
        
          
        
    2. **数据预处理决定了模型的生死：** KNN 等距离敏感型算法必须在训练前完成严格的尺度归一化（Min-max 或 Z-score），并且需针对性解决缺失值问题。绝不能直接使用未经尺度缩放的原始数据进行距离度量计算。
        
          
        
    3. **防范“维度灾难”陷阱：** 当特征维度超过 10-20 维时，基于距离度量的算法（如 KNN 及其高效搜索树变体）的性能与算力消耗将呈指数级恶化。必须前置采用特征选择、属性加权（如利用交叉验证动态调整属性权重）等降维手段进行干预。
        
          
        
    4. **泛化评估体系不可妥协：** 严禁使用训练集评估模型能力。为了获得真实的泛化表现且不污染测试集，必须剥离出独立的验证集用于超参数调优，或采用 $K$ 折交叉验证 / 留一法交叉验证（LOOCV）来建立起可靠的评估基准。
        
          
        
- **文档实际参考价值评估：**
    
    该文档作为一份高密度的大学教材级课件，为机器学习从业者及数据审计员提供了一个极端严谨、数学推导详尽的分类问题知识底座。其价值不仅在于提供了一系列“开箱即用”的算法公式和距离矩阵百科，更在于它指出了每个算法在面对高维、噪音、缺失值等真实工程环境下的“阿喀琉斯之踵”，是一份指导如何进行稳健模型选型与系统级纠偏的高价值参考指南。