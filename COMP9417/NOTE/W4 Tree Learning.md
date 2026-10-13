# Week 4：Tree Learning（树学习）讲义知识点详解

这份讲义来自 UNSW 的 COMP9417 Machine Learning & Data Mining，主题是 Tree Learning（树学习），共 94 页。

我会按照讲义的知识结构，用中文解释核心概念，保留重要英文术语和数学公式，并结合讲义中的例子说明算法是怎么工作的。

## 一、整份讲义的知识框架

这节课的核心问题是：

如何让计算机通过训练数据，自动学会一套用于分类或预测的判断规则？

讲义主要涉及以下内容：

|模块|主要知识点|重要程度|
|---|---|---|
|1. 决策树基础|Decision Tree、分类、树的结构|基础|
|2. 决策树构建|TDIDT、ID3、CART|核心|
|3. 划分标准|Entropy、Information Gain|核心计算|
|4. 信息增益改进|Gain Ratio|重要|
|5. 过拟合与剪枝|Overfitting、Pre-pruning、Post-pruning|核心|
|6. 决策树扩展|连续特征、缺失值、代价敏感学习|重要|
|7. 学习算法原理|Hypothesis Space、Inductive Bias|理论|
|8. 回归树|Regression Tree、MSE、Variance|核心|
|9. 模型树|Model Tree、线性回归叶节点|进阶|

## 二、Decision Tree：什么是决策树？

讲义 PDF 第 3–17 页

### 1. 基本概念

决策树（Decision Tree）是一种监督学习（Supervised Learning）算法，可以用于：

- Classification（分类）：预测离散类别，例如是否打网球、鱼的种类。
    
- Regression（回归）：预测连续数值，例如药物效果、房价。
    

它的工作方式非常接近人类做判断的过程：不断提出问题，根据答案选择下一条路径，直到得到最终结果。

### 2. 决策树的三个组成部分

讲义中的 PlayTennis 决策树示意

|组成|英文|作用|
|---|---|---|
|根节点|Root Node|整棵树的起点|
|内部节点|Internal Node|检查某个特征|
|分支|Branch|特征测试的不同结果|
|叶节点|Leaf Node|输出最终预测|

### 3. 如何使用决策树进行预测？

讲义给出的例子是：

- Outlook = Rain
    
- Humidity = High
    
- Wind = Weak
    

预测是否打网球。

判断过程：

1. 根节点检查 Outlook，发现是 Rain，走右边。
    
2. 下一节点检查 Wind，发现是 Weak。
    
3. 到达叶节点 Yes。
    

因此：

\[ \boxed{\text{PlayTennis}=\text{Yes}} \]

注意：只需要检查从根节点到叶节点路径上的特征，并不需要检查所有特征。

## 三、TDIDT：决策树是如何训练出来的？

讲义 PDF 第 18–22 页

TDIDT 全称：

Top-Down Induction of Decision Trees

中文叫自顶向下决策树归纳算法。

它的核心思想是 Divide and Conquer（分而治之）。

### 1. 训练过程

输入训练数据集 S

选择最好的划分特征 A

根据 A 将数据分成多个子集

子集是否已经足够纯净？

Yes

创建叶节点

No

递归继续划分

这里有一个非常重要的问题：

什么叫最好的特征（Best Attribute）？

例如预测是否打网球时，我们可以先按照 Outlook 划分，也可以先按照 Wind 划分。

哪个更好？

我们希望划分后的每个子集尽可能只包含一种类别，这叫做 Purity（纯度）。

为了定量衡量纯度，就引出了下一部分最重要的概念：Entropy（熵）。

### 2. ID3、C4.5 和 CART 的区别

|算法|主要特点|
|---|---|
|ID3|经典分类树，使用 Information Gain 选择特征|
|C4.5|ID3 的扩展，支持连续特征，并使用 Gain Ratio 等改进|
|CART|分类与回归树，通常进行二叉划分，可用于分类和回归|

这份讲义在分类树构建部分主要使用 ID3 来解释原理。

## 四、Entropy：熵

讲义 PDF 第 23–29 页

这是整节课最重要的数学概念之一。

### 1. 什么是熵？

Entropy 衡量一个数据集的不确定性（Uncertainty）或不纯度（Impurity）。

假设有 10 个样本，要预测 Yes 或 No。

情况 A：10 Yes，0 No

Entropy = 0

完全确定，纯度最高。

情况 B：8 Yes，2 No

Entropy ≈ 0.722

存在不确定性，但大多数样本属于 Yes。

情况 C：5 Yes，5 No

Entropy = 1

两类各占一半，不确定性最大。

Yes

No

### 2. 熵的公式

对于二分类问题：

\[ \boxed{H(S)=-p_+\log_2p_+-p_-\log_2p_-} \]

其中：

- \(S\)：当前数据集
    
- \(p_+\)：正样本比例
    
- \(p_-\)：负样本比例
    
- \(\log_2\)：以 2 为底的对数
    

对于 \(k\) 个类别：

\[ \boxed{H(S)=-\sum_{i=1}^{k}p_i\log_2p_i} \]

约定 \(0\log_2 0=0\)。

### 3. 例题：6 个 Yes、4 个 No

总共有 10 个样本。

\[ p_+=0.6,\quad p_-=0.4 \]

代入：

\[ H(S)=-0.6\log_2(0.6)-0.4\log_2(0.4) \]

计算：

\[ H(S)\approx0.971 \]

这意味着该数据集仍有比较高的不确定性。

### 4. 熵的图像

二分类熵在 p = 0.5 时最大，在 p = 0 或 1 时为零。

需要记住三个结论：

- 熵越大，类别越混乱。
    
- 熵越小，类别越纯净。
    
- 决策树希望通过划分降低熵。
    

## 五、Information Gain：信息增益

讲义 PDF 第 30–36 页

理解了 Entropy，Information Gain 就很容易理解。

### 1. 信息增益的直觉

假设原始数据很混乱。

按照某个特征划分后，数据被分成几个更加纯净的子集。

我们希望衡量：

划分前的不确定性，比划分后减少了多少？

这就是 Information Gain（信息增益）。

### 2. 公式

\[ \boxed{ Gain(S,A)=H(S)-\sum_{v\in Values(A)} \frac{|S_v|}{|S|}H(S_v) } \]

其中：

- \(S\)：原始数据集
    
- \(A\)：准备测试的特征
    
- \(S_v\)：特征 \(A\) 取值为 \(v\) 的子集
    
- \(|S_v|/|S|\)：子集所占比例
    

公式可以记成：

\[ \text{Gain}=\text{划分前熵}-\text{划分后加权平均熵} \]

为什么要加权？

因为不同分支的样本数量可能不同。包含 100 个样本的分支，显然比包含 1 个样本的分支更能代表整体的不确定性。

### 3. 讲义中的 PlayTennis 例题

原始数据：

- 9 个 Yes
    
- 5 个 No
    
- 总计 14 个样本
    

原始熵：

\[ H(S)=-\frac9{14}\log_2\frac9{14} -\frac5{14}\log_2\frac5{14} \approx0.940 \]

现在比较按照 Outlook 和 Wind 划分。

方案 A：Outlook

|分支|Yes|No|熵|
|---|---|---|---|
|Sunny|2|3|0.971|
|Overcast|4|0|0|
|Rain|3|2|0.971|

因此：

\[ \begin{aligned} Gain(S,Outlook) &=0.940-\left(\frac5{14}(0.971)+\frac4{14}(0)+\frac5{14}(0.971)\right)\\ &\approx\boxed{0.246} \end{aligned} \]

方案 B：Wind

|分支|Yes|No|熵|
|---|---|---|---|
|Weak|6|2|0.811|
|Strong|3|3|1.000|

\[ \begin{aligned} Gain(S,Wind) &=0.940-\left(\frac8{14}(0.811)+\frac6{14}(1)\right)\\ &\approx\boxed{0.048} \end{aligned} \]

### 4. 比较结果

Outlook

0.246

Wind

0.048

因为：

\[ Gain(S,Outlook)>Gain(S,Wind) \]

所以 Outlook 比 Wind 更适合放在根节点。

ID3 的核心规则就是：每次选择 Information Gain 最大的特征进行划分。

### 5. 交互练习：计算信息增益

调整样本数量，观察信息增益如何变化

总 Yes：6

总 No：4

左分支 Yes：4

左分支 No：1

左分支

## 4 Yes / 1 No

熵 = 0.722

右分支

## 2 Yes / 3 No

熵 = 0.971

划分前熵

## 0.971

划分后熵

## 0.846

Information Gain

## 0.125

重置示例

试着让左右分支分别只包含 Yes 和 No，你会发现划分后熵变成 0，信息增益达到最大。

## 六、Gain Ratio：信息增益率

讲义 PDF 第 37–38 页

### 1. Information Gain 有什么问题？

信息增益有一个缺陷：

它倾向于选择具有大量不同取值的特征。

例如我们要预测是否打网球，候选特征有：

- Outlook：Sunny、Rain、Overcast
    
- Student ID：每个学生都有不同的编号
    

如果使用 Student ID，每个样本都可以单独成为一个叶节点。

这样训练集中的每个叶节点都是纯净的，信息增益可能非常高。

但 Student ID 对预测新学生是否打网球几乎没有意义。

这就是信息增益偏向高基数特征（High-cardinality Features）的问题。

### 2. Gain Ratio 的公式

首先计算 Split Entropy：

\[ SplitEntropy(S,A)= -\sum_v\frac{|S_v|}{|S|} \log_2\frac{|S_v|}{|S|} \]

然后：

\[ \boxed{ GainRatio(S,A)= \frac{Gain(S,A)}{SplitEntropy(S,A)} } \]

注意两个 Entropy 的区别：

|指标|衡量什么|
|---|---|
|Entropy|子集内部类别的不确定性|
|Split Entropy|数据被分配到不同分支的不确定性|
|Gain Ratio|对信息增益进行归一化|

Gain Ratio 通过考虑分支的数量和大小，减少对取值很多的特征的偏好。

补充一个细节：当 Split Entropy 为 0 时不能直接相除；而且 Gain Ratio 也不是在所有情况下都优于 Information Gain。

## 七、Overfitting：决策树为什么会过拟合？

讲义 PDF 第 39–40 页

### 1. 什么是 Overfitting？

Overfitting（过拟合）指模型过度适应训练数据，导致对新数据的预测效果变差。

假设训练集中有 100 个样本。

如果决策树不断分裂，直到每个叶节点只有一个样本，通常就可以记住这些训练样本的标签。

但是：

记住训练数据，不代表学会了真正的规律。

讲义第 40 页的曲线展示了典型现象：

根据讲义第 40 页的趋势绘制的示意数据，并非原图精确读数。

随着节点数量增加：

- Training Accuracy 通常继续上升。
    
- Test Accuracy 可能先上升，随后下降。
    

这意味着树太复杂，开始学习训练集中的噪声。

### 2. 为什么决策树容易过拟合？

主要原因有三个：

1. 决策树可以不断进行更细的划分。
    
2. 深层叶节点往往只有很少的样本，预测不稳定。
    
3. 贪心划分可能把训练集中的偶然现象当作规律。
    

因此，决策树训练并不是越深越好。

## 八、Pruning：如何防止过拟合？

讲义 PDF 第 41–50 页

Pruning（剪枝）是通过限制或删除部分树结构，降低模型复杂度。

讲义重点介绍两种方式。

### 1. Pre-pruning（预剪枝）

在训练过程中，提前停止继续划分。

例如：

- 树已经达到最大深度。
    
- 当前节点样本太少。
    
- 信息增益太小。
    
- 叶节点数量达到上限。
    

在 Python 的 `sklearn` 中，常见参数如下：

|参数|作用|
|---|---|
|`max_depth`|限制树的最大深度|
|`min_samples_split`|节点继续分裂需要的最少样本数|
|`min_samples_leaf`|每个叶节点至少需要多少样本|
|`max_leaf_nodes`|限制叶节点数量|
|`min_impurity_decrease`|要求分裂带来足够的不纯度下降|

优点：速度快，计算成本低。

缺点：可能停止得太早，导致 Underfitting（欠拟合）。

### 2. 为什么预剪枝可能出错？XOR 问题

讲义第 44 页专门使用 XOR 解释 Early Stopping。

XOR 的规则是：两个输入不同则输出 1，相同则输出 0。

|X|Y|XOR|
|---|---|---|
|0|0|0|
|0|1|1|
|1|0|1|
|1|1|0|

这个数据集有一个特殊性质：

- 单独检查 X，不能降低类别熵。
    
- 单独检查 Y，也不能降低类别熵。
    
- 但连续检查 X 和 Y，可以完美分类。
    

因为：

\[ Gain(S,X)=Gain(S,Y)=0 \]

如果预剪枝要求每次划分都必须产生正的信息增益，就可能在根节点停止。

然而真正的分类规则需要两层判断才能发现。

这说明：当前划分没有改善，不代表继续划分也没有改善。

### 3. Post-pruning（后剪枝）

后剪枝先生成比较完整的决策树，然后删除对泛化性能没有帮助的子树。

讲义中的 Reduced-Error Pruning（降低错误率剪枝）步骤：

1. 把数据划分为 Training Set 和 Validation Set。
    
2. 使用训练集生成决策树。
    
3. 尝试将某棵子树替换为一个叶节点。
    
4. 比较剪枝前后在验证集上的准确率。
    
5. 优先删除能改善验证准确率的子树。
    
6. 重复直到进一步剪枝不再有益。
    

后剪枝的好处是能够先观察到更复杂的特征交互，再决定哪些结构应该保留。

### 4. Minimum Error 和 Smallest Tree

讲义还介绍两种基于交叉验证的策略。

Minimum Error： 选择交叉验证误差最小的树。

\[ T^*=\arg\min_T CVError(T) \]

Smallest Tree： 使用 One Standard Error Rule（一个标准误差规则），在误差不超过最小误差加一个标准误差的候选树中，选择最简单的树。

讲义中的例子：

- Minimum Error 保留约 36 个节点。
    
- Smallest Tree 保留约 26 个节点。
    

它体现了机器学习中的重要原则：

当两个模型的预测效果足够接近时，通常优先选择更简单的模型。

## 九、决策树的其他重要扩展

讲义 PDF 第 51–64 页

### 1. Converting a Tree to Rules（把树转换为规则）

决策树从根节点到叶节点的每一条路径，都可以转换成一条 IF-THEN 规则。

例如：

\[ \begin{aligned} &IF\ Outlook=Sunny\\ &AND\ Humidity=High\\ &THEN\ PlayTennis=No \end{aligned} \]

这意味着：

- 一条路径对应多个条件的 AND（合取）。
    
- 多条通向同一类别的路径可以用 OR（析取）连接。
    

因此，决策树能够表示 Disjunction of Conjunctions（合取式的析取）。

这也是决策树可解释性强的重要原因。

### 2. Continuous-Valued Attributes（连续特征）

最初的 ID3 主要处理离散特征，但现实中很多特征是连续数值。

例如：

\[ Temperature=25.6 \]

决策树可以通过阈值把连续特征变成二元判断：

\[ Temperature\leq t \]

或者：

\[ Temperature>t \]

讲义给出的温度例子：

|Temperature|40|48|60|72|80|90|
|---|---|---|---|---|---|---|
|PlayTennis|No|No|Yes|Yes|Yes|No|

可以考虑的候选阈值包括：

\[ t_1=\frac{48+60}{2}=54 \]

\[ t_2=\frac{80+90}{2}=85 \]

因为这些位置相邻样本的类别发生了变化。

接下来分别计算不同阈值对应的信息增益，选择效果最好的阈值。

这里需要理解：

- 离散特征可以按不同类别建立分支。
    
- 连续特征通常采用二元阈值划分。
    
- 同一个连续特征可以在一棵树的不同节点中反复使用。
    

### 3. Axis-Parallel Splitting（轴平行划分）

标准决策树的划分通常形如：

\[ x_1<5 \]

或者：

\[ x_2>10 \]

这意味着每次只检查一个特征。

在二维平面中，产生的是水平或垂直的分割线。

Axis-parallel

多次分裂形成阶梯状边界

Oblique split

线性组合可以形成斜边界

讲义第 58 页进一步介绍 Splitting on Linear Combinations of Features：

\[ w_1x_1+w_2x_2<c \]

这样可以生成斜线决策边界，有时能够使用更少的节点完成分类。

### 4. Attributes with Costs（特征获取成本）

并非所有特征的获取成本都一样。

例如：

- 年龄：获取成本低。
    
- 血液检查：可能需要支付 150 美元。
    
- 机器人传感器计算：可能需要 23 秒。
    

讲义提出一种考虑成本的指标：

\[ \frac{Gain(S,A)^2}{Cost(A)} \]

这样可以偏好信息量较高且获取成本较低的特征。

这里的平方是讲义给出的一种启发式设计，并非所有代价敏感决策树都必须使用这个公式。

### 5. Misclassification Costs（误分类成本）

不同错误可能造成不同后果。

例如医学诊断中：

- False Positive：实际没病，却预测有病。
    
- False Negative：实际有病，却预测没病。
    

这两种错误的代价可能不同。

因此模型不仅需要考虑 Accuracy，还可能需要考虑 Expected Loss（期望损失）。

讲义介绍的思路是：先使用信息增益等指标构建树，再在后剪枝阶段考虑错误成本。

### 6. Unknown Attribute Values（缺失特征）

如果某个样本缺少需要判断的特征值，可以采用：

- 用当前节点中最常见的特征值代替。
    
- 按不同特征取值的概率，将样本以不同权重分配到多个分支。
    

例如某个节点有 70% 的样本走左分支、30% 走右分支，那么缺失该特征的样本可以按 0.7 和 0.3 的权重分配。

讲义还简要介绍了 Windowing：先用部分训练样本构建树，再根据未正确分类的样本逐步扩充训练窗口，主要用于早期内存受限的场景。

## 十、Hypothesis Space 和 Inductive Bias

讲义后半部分：Hypothesis Space Search、Inductive Bias

这一部分偏理论，但对于理解 ID3 为什么这样设计很重要。

### 1. Hypothesis Space（假设空间）

Hypothesis Space 指模型可能选择的所有候选函数的集合。

例如，有两个布尔特征 \(X_1,X_2\)，每个特征都只能取 0 或 1。

一共有：

\[ 2^2=4 \]

种输入组合。

每种输入组合可以独立指定输出 0 或 1，所以总共有：

\[ 2^4=16 \]

种不同的布尔分类函数。

决策树能够表示所有这些函数。

因此讲义指出，针对有限个离散特征，决策树的假设空间具有很强的表达能力。

### 2. ID3 如何搜索假设空间？

ID3 使用 Greedy Search（贪心搜索）。

每次选择当前信息增益最大的特征，而不是尝试所有可能的树并找到全局最优。

这意味着：

- 计算相对高效。
    
- 不需要穷举所有决策树。
    
- 不会回溯修改之前的选择。
    
- 不保证得到全局最优的树。
    

Greedy 的核心含义是：当前最优，不一定是整体最优。

### 3. Inductive Bias（归纳偏置）

归纳偏置是指学习算法在训练数据之外使用的假设或偏好。

为什么需要它？

因为训练数据通常无法唯一确定真实的预测函数。可能有很多模型都能正确分类训练样本。

算法必须有某种标准，决定优先选择哪一种模型。

讲义区分了两类偏置：

|类型|含义|
|---|---|
|Restriction Bias|限制算法可以考虑哪些假设|
|Preference Bias|不排除候选假设，但更偏好某些假设|

ID3 主要体现的是 Preference Bias。

它倾向于：

- 选择信息增益较大的特征。
    
- 优先形成较简单的决策结构。
    

这有助于解释为什么 ID3 使用信息增益进行贪心搜索，而不是随机选择划分特征。

## 十一、Regression Tree：回归树

讲义 PDF 后半部分：Regression Tree、CART

前面讨论的都是分类问题。

现在考虑一个不同的任务：

根据药物剂量预测药物有效率。

输入：

\[ X=\text{Dosage (mg)} \]

输出：

\[ Y=\text{Effectiveness (\%)} \]

因为 \(Y\) 是连续数值，所以需要 Regression Tree（回归树）。

### 1. 分类树和回归树的区别

||Classification Tree|Regression Tree|
|---|---|---|
|预测目标|离散类别|连续数值|
|叶节点输出|类别|数值，通常是均值|
|常见划分标准|Entropy、Gini|MSE、Variance|
|评价指标|Accuracy 等|MSE、MAE 等|

### 2. 回归树的工作方式

假设药物剂量与有效率的关系如下：

|Dosage|Effectiveness|
|---|---|
|10 mg|10%|
|15 mg|12%|
|25 mg|70%|
|30 mg|75%|
|40 mg|90%|
|50 mg|95%|

回归树可能学到：

Dosage ≤ 20?

Yes

# 11%

预测有效率

No

Dosage ≤ 35?

72.5%

92.5%

根据上方示例数据构造的简化回归树

回归树本质上把输入空间分成若干区域，每个区域输出一个数值。

所以普通回归树预测的是一种 Piecewise Constant Function（分段常数函数）。

### 3. 回归树为什么使用 MSE？

分类树希望划分后类别更纯净。

回归树希望划分后数值更加接近。

因此使用 Mean Squared Error（均方误差）：

\[ \boxed{MSE(S)=\frac1m\sum_{i=1}^{m}(y_i-\bar y)^2} \]

其中：

- \(m\)：当前节点中的样本数。
    
- \(y_i\)：每个样本的真实数值。
    
- \(\bar y\)：该节点所有目标值的平均值。
    

这个 MSE 恰好等于使用分母 \(m\) 定义的总体方差。

### 4. 例题：如何计算回归树的 MSE？

假设某个节点包含：

\[ Y=[2,4,6] \]

平均值：

\[ \bar y=\frac{2+4+6}{3}=4 \]

MSE：

\[ \begin{aligned} MSE&=\frac{(2-4)^2+(4-4)^2+(6-4)^2}{3}\\ &=\frac{4+0+4}{3}\\ &=\boxed{2.667} \end{aligned} \]

回归树尝试不同划分阈值，找到使划分后加权 MSE 最小的阈值。

\[ \boxed{ MSE_{\text{split}}= \sum_{j=1}^{k}\frac{|S_j|}{|S|}MSE(S_j) } \]

例如：

- 左分支有 3 个样本，MSE = 2
    
- 右分支有 7 个样本，MSE = 5
    

则：

\[ MSE_{\text{split}} =\frac3{10}(2)+\frac7{10}(5) =\boxed{4.1} \]

对不同的特征和阈值重复计算，选择加权 MSE 最小的划分。

### 5. 分类树与回归树的共同本质

这两种算法看起来不同，但思想完全一致：

\[ \boxed{\text{选择能够最大程度降低节点不纯度的划分}} \]

只是衡量不纯度的指标不同。

分类树使用 Entropy、Gini 等。

回归树使用 MSE、Variance 等。

讲义还使用 Hammond 风琴二手交易价格的例子，比较 Model、Condition、Leslie 等特征划分后的方差，说明如何一步一步建立回归树。

## 十二、Model Tree：模型树

讲义 PDF 第 84–90 页附近

Model Tree（模型树）是 Regression Tree 的进一步扩展。

### 1. 与普通回归树有什么不同？

普通回归树在叶节点预测一个固定数值：

\[ \hat y=\bar y \]

模型树则可以在叶节点放置一个线性回归模型：

\[ \boxed{\hat y=w_0+w_1x_1+\cdots+w_dx_d} \]

也就是说：

- Regression Tree：每个区域输出一个常数。
    
- Model Tree：每个区域使用一个回归函数进行预测。
    

### 2. 为什么需要模型树？

讲义给出一个例子：

\[ y=\cos(\pi x),\quad -1\leq x\leq1 \]

如果使用一条直线拟合整个区间，效果很差。

但可以把数据分成：

\[ -1\leq x<0 \]

和

\[ 0\leq x\leq1 \]

再分别拟合线性回归。

这样每个区域可以使用不同的直线，更好地逼近非线性函数。

### 3. Standard Deviation Reduction（标准差下降）

讲义介绍使用 SDR 作为模型树的划分标准：

\[ \boxed{ SDR=sd(T)-\sum_i\frac{|T_i|}{|T|}sd(T_i) } \]

其中：

- \(sd(T)\)：划分前目标值的标准差。
    
- \(sd(T_i)\)：第 \(i\) 个子集的标准差。
    
- \(|T_i|/|T|\)：子集权重。
    

SDR 越大，意味着划分后数值的离散程度降低得越多。

模型树也可能过拟合，因此同样需要剪枝。讲义讨论了基于线性回归估计误差、自底向上的剪枝策略。

## 十三、重点公式汇总

这是复习时最值得熟记的公式表。

|知识点|公式|用途|
|---|---|---|
|Entropy|\(H(S)=-\sum_i p_i\log_2p_i\)|衡量类别不纯度|
|Information Gain|\(H(S)-\sum_v\frac{\|S_v\|}{\|S\|}H(S_v)\)|选择分类树划分特征|
|Split Entropy|\(-\sum_v q_v\log_2q_v\)|衡量分支分布|
|Gain Ratio|\(\frac{Gain}{SplitEntropy}\)|减少信息增益的高基数偏好|
|MSE|\(\frac1m\sum_i(y_i-\bar y)^2\)|衡量回归节点的数值离散程度|
|Weighted MSE|\(\sum_j\frac{\|S_j\|}{\|S\|}MSE(S_j)\)|选择回归树划分|
|SDR|\(sd(T)-\sum_i\frac{\|T_i\|}{\|T\|}sd(T_i)\)|模型树划分|

## 十四、检查一下自己是否理解了

5 道核心概念题

已回答 0/5

1. 在 ID3 中，通常选择哪个特征作为当前节点的划分特征？

A. Entropy 最大的特征

B. Information Gain 最大的特征

C. 特征取值最多的特征

D. 样本数量最少的特征

2. 二分类中，哪种情况的 Entropy 最大？

A. 100% Yes

B. 90% Yes，10% No

C. 50% Yes，50% No

D. 100% No

3. 为什么决策树需要 Pruning？

A. 为了增加训练集准确率

B. 为了减少过拟合、改善泛化

C. 为了让树包含更多叶节点

D. 为了使所有节点的熵为零

4. 回归树通常选择哪种划分？

A. 最大化子节点平均 MSE

B. 最小化子节点加权 MSE

C. 最大化分类准确率

D. 最大化树的深度

5. 为什么 XOR 是预剪枝可能失败的经典例子？

A. XOR 无法用决策树表示

B. XOR 需要连续特征

C. 单个特征的信息增益为零，但组合特征可以分类

D. XOR 的所有样本类别相同

提交答案并查看解析

## 十五、如何复习这份讲义？

建议按照以下顺序掌握，而不是逐页死记：

第一阶段：理解决策树原理

能画出 PlayTennis 决策树，理解 Root、Branch、Leaf、TDIDT 和 ID3。

第二阶段：熟练计算

能手算 Entropy、Information Gain、Gain Ratio，以及回归树的加权 MSE。这部分最适合通过练习题巩固。

第三阶段：理解泛化与剪枝

能解释 Overfitting、Pre-pruning、Post-pruning、XOR Early Stopping，以及交叉验证选择树大小的原理。

第四阶段：掌握扩展与回归树

理解连续特征阈值选择、Inductive Bias、Regression Tree 和 Model Tree。

最后，把这份讲义最核心的思想浓缩成三句话：

1. 决策树通过不断划分数据来进行预测。

2. 分类树选择让类别更加纯净的划分，回归树选择让数值更加集中的划分。

3. 树不是越复杂越好，需要通过剪枝控制过拟合，提高对新数据的预测能力。

如果是为了 COMP9417 的考试或作业，最应该优先掌握的是：Entropy → Information Gain → ID3 建树 → Overfitting/Pruning → Regression Tree 的 MSE 计算。这五个知识点构成了整份讲义最主要的计算与推理链条。