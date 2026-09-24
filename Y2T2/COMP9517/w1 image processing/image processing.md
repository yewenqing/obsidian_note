
# COMP9517 Week 1 - Image Processing Basics

## 1. 什么是图像处理（Image Processing）

### Image Processing

输入：图像  
输出：图像

目标：

- 去除噪声和失真
    
- 增强有用信息
    
- 为后续分析做准备
    

```
Image → Image
```

### Image Analysis

输入：图像  
输出：特征或测量值

```
Image → Features / Measurements
```

### Computer Vision

输入：图像  
输出：语义解释

```
Image → Interpretation
```

例如：

|任务|输入|输出|
|---|---|---|
|图像处理|照片|增强后的照片|
|图像分析|照片|边缘、面积、纹理|
|计算机视觉|照片|"这是一只猫"|

---

# 2. 图像处理分类

## Spatial Domain（空间域）

直接在像素上操作。

一般形式：

[  
g(x,y)=T(f(x,y))  
]

其中：

- (f(x,y))：输入图像
    
- (g(x,y))：输出图像
    
- (T)：变换算子
    

---

## Transform Domain（变换域）

先变换到频域，再处理。

典型：

- Fourier Transform（傅里叶变换）
    

后续课程重点讨论。

---

# 3. 空间域操作

## Point Operations（点运算）

每个输出像素仅依赖对应输入像素：

[  
g(x,y)=T(f(x,y))  
]

特点：

- 简单
    
- 速度快
    
- 不考虑邻域信息
    

---

## Neighbourhood Operations（邻域运算）

输出像素依赖周围多个像素：

[  
g(x,y)=T(f(x,y),f(x+1,y),f(x-1,y),...)  
]

典型：

- 平滑
    
- 锐化
    
- 卷积滤波
    

---

# 4. Contrast Stretching（对比度拉伸）

## 目的

提高图像对比度。

---

## 思想

设：

- L：下阈值
    
- H：上阈值
    

变换规则：

### 小于 L

映射为黑色

[  
0  
]

---

### 大于 H

映射为白色

[  
255  
]

---

### L ~ H

线性拉伸：

[  
[L,H]  
\rightarrow  
[0,255]  
]

---

## 效果

原图：

```
灰度集中在中间
```

处理后：

```
充分利用全部灰度范围
```

提高视觉对比度。

---

# 5. Intensity Thresholding（阈值分割）

## 基本思想

选定阈值 (T)

[  
g(x,y)=  
\begin{cases}  
0 & f<T\  
255 & f\ge T  
\end{cases}  
]

---

## 输出

二值图像：

```
黑（0）
白（255）
```

---

## 应用

图像分割（Segmentation）

例如：

- 细胞检测
    
- 车牌识别
    
- 文档扫描
    

---

## 缺点

依赖阈值选择。

当：

- 前景和背景灰度接近
    

时效果很差。

---

# 6. 自动阈值选择

---

## 6.1 Otsu Method

经典自动阈值算法。

思想：

寻找最佳阈值，使：

### 类内方差最小

# [  
\sigma_W^2

p_0\sigma_0^2  
+  
p_1\sigma_1^2  
]

---

等价于：

### 类间方差最大

# [  
\sigma_B^2

p_0p_1(\mu_0-\mu_1)^2  
]

---

其中：

- (p_0,p_1)：两类像素比例
    
- (\mu_0,\mu_1)：均值
    

---

### 考试重点

Otsu：

> 最大化 Between-class Variance

---

## 6.2 IsoData Method

迭代算法。

步骤：

### Step 1

任选初始阈值

[  
t  
]

---

### Step 2

计算两类均值：

[  
\mu_0,\mu_1  
]

---

### Step 3

更新阈值

[  
t=  
\frac{\mu_0+\mu_1}{2}  
]

---

### Step 4

重复直到收敛

---

## 6.3 Triangle Method

基于直方图。

步骤：

1. 找峰值
    
2. 连线至最右端灰度
    
3. 找距离最大的点
    

该点即阈值。

---

# 7. Multi-level Thresholding

使用多个阈值：

例如：

[  
T_1,T_2  
]

把图像划分成：

- 黑
    
- 灰
    
- 白
    

三类区域。

---

# 8. Intensity Inversion（灰度反转）

## 定义

[  
s=L-1-r  
]

对于 8-bit：

[  
s=255-r  
]

---

## 效果

黑 ↔ 白

亮 ↔ 暗

---

## 应用

医学图像。

某些细节在反色后更容易观察。

---

# 9. Log Transformation

## 公式

s=c\log(1+r)

---

## 特点

扩大：

- 低灰度区域
    

压缩：

- 高灰度区域
    

---

## 用途

动态范围压缩（Dynamic Range Compression）。

例如：

- 天文图像
    
- 频谱图
    

---

# 10. Power Transformation

## 公式

s=cr^{\gamma}

---

## 参数

- (c)：常数
    
- (\gamma)：Gamma
    

---

## 特性

### γ < 1

图像变亮

---

### γ > 1

图像变暗

---

## Gamma Correction

显示器校正常见应用。

考试经常出现。

---

# 11. Piecewise Linear Transformations

## 思想

使用多段直线定义变换函数。

优点：

- 灵活
    
- 可定制
    

缺点：

- 需要人工设计
    

---

## Piecewise Contrast Stretching

局部增强某个灰度区间。

比普通 Contrast Stretching 更灵活。

---

# 12. Gray-Level Slicing

## 目的

突出某个灰度范围。

例如：

```
100~150
```

区域。

---

两种方法：

### 方法1

目标范围变白

其他变黑

（二值化）

---

### 方法2

目标范围增强

其他区域保留

---

# 13. Bit-Plane Slicing

## 思想

8-bit 图像：

```
b7 b6 b5 b4 b3 b2 b1 b0
```

可拆成：

- Bit-plane 0
    
- Bit-plane 1
    
- ...
    
- Bit-plane 7
    

---

## 特征

### 高位

包含主要结构

例如：

```
b7
b6
```

---

### 低位

更多是噪声和细节

例如：

```
b0
b1
```

---

## 应用

- 图像压缩
    
- 特征分析
    

---

# 14. Histogram（直方图）

## 定义

统计：

每个灰度值出现次数。

---

## 归一化直方图

# [  
p(r)

\frac{h(r)}{N}  
]

其中：

- (h(r))：像素数
    
- (N)：总像素数
    

---

## 意义

近似灰度概率分布。

---

# 15. Histogram Equalization

## 目标

使灰度分布尽可能均匀。

---

## 效果

增强对比度。

尤其是：

原本集中在少数灰度范围时。

---

## 核心思想

使用累积分布函数（CDF）：

[  
s=T(r)  
]

使输出接近均匀分布。

---

### 考试重点

Histogram Equalization：

> 利用 CDF 重新映射灰度

---

## 缺点

可能：

- 放大噪声
    
- 过度增强
    

---

# 16. Histogram Matching

又称：

Histogram Specification

---

## 目标

匹配到指定直方图。

不是均匀分布。

---

例如：

输入：

```
白天照片
```

匹配：

```
黄昏照片
```

---

## 过程

```text
Input
 ↓
Equalization
 ↓
Uniform Histogram
 ↓
Target Histogram
```

---

# 17. Arithmetic Operations

逐像素运算。

---

## Addition

[  
f+g  
]

应用：

- 图像融合
    

---

## Subtraction

[  
f-g  
]

应用：

- 变化检测
    
- 背景减除
    

---

# 18. Logical Operations

## AND

保留掩码区域。

```text
Image AND Mask
```

---

## OR

合并区域。

```text
Image OR Mask
```

---

## XOR

差异检测。

---

# 19. Image Averaging

## 目的

降低随机噪声。

---

假设：

[  
f_i=g+n_i  
]

其中：

- (g)：真实图像
    
- (n_i)：噪声
    

---

平均：

[  
\bar f=  
\frac1N  
\sum_{i=1}^{N}f_i  
]

---

得到：

[  
VAR=  
\frac{\sigma^2}{N}  
]

---

## 结论

标准差：

[  
\frac{\sigma}{\sqrt N}  
]

---

### 考试重点

平均 N 张独立噪声图：

- 信号保持不变
    
- 噪声标准差降为
    

[  
\frac1{\sqrt N}  
]

倍

---

# 考试速记表

|方法|作用|
|---|---|
|Contrast Stretching|提高对比度|
|Thresholding|二值化|
|Otsu|最大类间方差|
|IsoData|均值迭代|
|Triangle|直方图几何法|
|Inversion|黑白反转|
|Log Transform|强化暗部|
|Power Transform|Gamma校正|
|Gray-Level Slicing|强调特定灰度|
|Bit-Plane Slicing|位平面分析|
|Histogram Equalization|均衡直方图|
|Histogram Matching|匹配目标直方图|
|Addition|图像融合|
|Subtraction|变化检测|
|AND/OR|Mask操作|
|Averaging|降噪|

这份笔记基本覆盖了 Week 1 PPT 中所有可能出现在 Quiz、Assignment 和 Final Exam 的知识点。