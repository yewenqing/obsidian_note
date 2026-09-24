这两份讲义来自 UNSW **COMP9517（计算机视觉）Week 9** 的核心课程内容，主题聚焦于视频序列中的动态分析：

  

- **Part 1-1**：**运动估计（Motion Estimation）**
    
      
    
      
    
- **Part 1-2**：**目标跟踪（Object Tracking）**
    
      
    
      
    

## 第一份讲义：Motion Estimation（运动估计）

讲义首先引入时间维度（$3\text{D} = 2\text{D} + t$），系统讲解了如何从连续图像序列中提取、量化与估计物体及相机的运动。核心内容包含三大方法体系：

  

### 1. 变化检测（Change Detection / 图像差分法）

- **基本原理**：当目标在静止背景前移动时，目标的前后边缘在帧间仅移动几个像素。通过对相邻帧 $I_t - I_{t-1}$ 或当前帧与静态背景模板 $I_t - I_{\text{bg}}$ 作差分，可定位发生变化的区域。
    
      
    
- **处理算法流程**：
    
      
    1. **像素差分阈值化**：如果 $\vert{}I_t(x, y) - I_{t-\Delta t}(x, y)\vert{} > \tau$，则二值输出 $I_{\text{out}}(x, y) = 1$，否则置 $0$。
        
          
        
    2. **连通分量提取**（Connected Components Extraction）。
        
          
        
    3. **去噪**：剔除面积过小的伪变化区域。
        
          
        
    4. **形态学闭运算**（Closing）：使用小圆形结构元素连接断开的邻近区域并填补内部孔洞。
        
          
        
    5. **生成边界框**（Bounding Boxes）输出目标检测位置。
        
          
        

### 2. 稀疏运动估计（Sparse Motion Estimation / 特征点匹配）

稀疏运动估计旨在寻找稀疏关键点在 $t$ 到 $t+\Delta t$ 之间的位移向量（运动场/运动矢量）。

  

- **基本假设**：特征点及其邻域的灰度强度在短时间内保持近似恒定。
    
      
    
- **两步法流程**：
    
      
    1. **检测特征点（Interesting Points）**：利用边缘/角点检测算子（如 Canny、Harris、SIFT、CNN）或**兴趣算子（Interest Operator）**。兴趣算子在水平、垂直和两个对角线 4 个方向计算邻域方差，取其最小值 $\min(v_1, v_2, v_3, v_4) \ge t$ 作为特征点。
        
          
        
    2. **模板匹配（Template Matching）**：在限定的搜索区域 $R$ 内寻找最佳匹配邻域。
        
          
        
- **相似度度量准则**：
    
      
    - **互相关（Cross-Correlation, CC）**：寻找最大值。
        
          
        
    - **绝对差之和（SAD）与平方差之和（SSD）**：寻找最小值。
        
          
        
    - **互信息（Mutual Information, MI）**：基于联合概率与边缘概率分布熵最大化匹配。
        
          
        

$$\text{SSD}(\Delta x, \Delta y) = \sum_{(x, y) \in T} \left( I_t(x, y) - I_{t+\Delta t}(x+\Delta x, y+\Delta y) \right)^2$$

### 3. 稠密运动估计（Dense Motion Estimation / 光流法 Optical Flow）

计算图像上每个像素的瞬时速度向量 $(v_x, v_y)$。

  

- **光流三大基本假设**：
    
      
    1. 光源强度和属性在 $\Delta t$ 内恒定；
        
          
        
    2. 目标与相机距离不剧烈变化；
        
          
        
    3. 物体表面外观特征保持恒定（灰度守恒假设：$f(x+\Delta x, y+\Delta y, t+\Delta t) = f(x, y, t)$）。
        
          
        
- **光流基本约束方程（Optical Flow Constraint Equation）**：
    
    对多元函数进行一阶泰勒展开，可推导出：
    
      
    
    $$f_x v_x + f_y v_y + f_t = 0 \iff \nabla f \cdot \mathbf{v} = -f_t$$
    
    其中 $\nabla f = (f_x, f_y)$ 为空间图像梯度，$f_t$ 为时间导数，$\mathbf{v} = (v_x, v_y)$ 为光流速度。
    
      
    
- **孔径问题（Aperture Problem）与求解**：
    
      
    - 单个像素点只有 1 个方程却有 2 个未知数（$v_x, v_y$），存在病态不可解性。
        
          
        
    - **Lucas-Kanade (LK) 算法**：假设局部邻域内 $n$ 个像素具有相同的运动速度，构建超定方程组 $A\mathbf{v} = \mathbf{b}$，利用最小二乘法（Least Squares）求解：
        
          
        
        $$\mathbf{v} = (A^T A)^{-1} A^T \mathbf{b}$$
        

## 第二份讲义：Object Tracking（目标跟踪）

目标跟踪旨在跨时间序列推断物体的连续状态轨迹。讲义从概率状态估计（贝叶斯滤波）视角出发，深入讲解了线性与非线性环境下的跟踪算法。

  

### 1. 跟踪问题定义与三大步骤

- **状态与观测**：设系统状态为随机变量 $X_i$（包含位置、速度、尺度等），观测为 $Y_i$（图像中提取的特征）。
    
      
    
- **三大核心步骤**：
    
      
    1. **预测（Prediction）**：利用截至上一时刻的历史数据 $Y_{0:i-1}$ 预测当前状态 $X_i$。
        
          
        
    2. **数据关联（Association）**：从当前图像特征中筛选出与目标对应的观测 $Y_i$。
        
          
        
    3. **校正/更新（Correction）**：结合最新观测 $Y_i$ 修正状态预测，获得后验概率。
        
          
        

### 2. 贝叶斯推断框架（Bayesian Inference Tracking）

- **隐马尔可夫模型（HMM）独立性假设**：
    
      
    1. **一阶马尔可夫性**：当前状态仅取决于上一时刻状态 $P(X_i \mid X_{0:i-1}, Y_{0:i-1}) = P(X_i \mid X_{i-1})$；
        
          
        
    2. **观测独立性**：当前测量仅取决于当前状态 $P(Y_i \mid X_{0:i}, Y_{0:i-1}) = P(Y_i \mid X_i)$。
        
          
        
- **递推迭代公式**：
    
      
    - **预测步（Chapman-Kolmogorov 方程）**：
        
          
        
        $$P(X_i \mid Y_{0:i-1}) = \int P(X_i \mid X_{i-1}) P(X_{i-1} \mid Y_{0:i-1}) dX_{i-1}$$
        
          
        
    - **校正步（贝叶斯准则更新）**：
        
          
        
        $$P(X_i \mid Y_{0:i}) \propto P(Y_i \mid X_i) P(X_i \mid Y_{0:i-1})$$
        
          
        
- **点估计方法**：
    
      
    - **MAP（最大后验估计）**：$\hat{x}_i = \arg\max_{x} P(X_i = x \mid Y_{0:i})$（后验概率峰值点）；
        
          
        
    - **EAP（期望后验估计）**：$\hat{x}_i = \int x P(X_i = x \mid Y_{0:i}) dx$（后验概率分布均值）。
        
          
        

### 3. 卡尔曼滤波（Kalman Filtering / 线性高斯模型）

- **假设前提**：运动动态转移模型与观测模型均为**线性**，且噪声服从**加性零均值高斯分布**（$x_i = A x_{i-1} + q_{i-1}, y_i = H x_i + r_i$）。此时所有概率密度函数均严格保持为单峰高斯分布 $N(\mu, \Sigma)$。
    
      
    
- **递推五大方程**：
    
      
    - **预测**：
        
          
        1. 状态预测：$x_i^- = A x_{i-1}$
            
              
            
        2. 协方差预测：$P_i^- = A P_{i-1} A^T + Q$
            
              
            
    - **校正**：
        
        3. 计算卡尔曼增益：$K_i = P_i^- H^T (H P_i^- H^T + R)^{-1}$
        
        4. 状态修正：$x_i = x_i^- + K_i (y_i - H x_i^-)$
        
        5. 协方差修正：$P_i = (I - K_i H) P_i^-$
        
          
        

### 4. 粒子滤波（Particle Filtering / 非线性非高斯模型）

- **动机与原理**：在存在遮挡、杂乱背景（Clutter）或多模态分布时，高斯单峰假设失效。粒子滤波采用一组带权重的随机样本（粒子集 $\{s_i^{(n)}, \pi_i^{(n)}\}_{n=1}^N$）来**近似任意复杂的非线性/非高斯后验概率密度**。
    
      
    
- **算法（CONDENSATION 算法 / 顺序蒙特卡洛 SMC）**：
    
      
    1. **重采样（Select）**：根据上一时刻粒子的权重 $\pi_{t-1}^{(n)}$（累积概率分布）有放回地抽取粒子样本；
        
          
        
    2. **状态预测（Predict）**：利用系统的动态转移概率 $P(x_t \mid x_{t-1})$ 对粒子加入随机扰动进行传播漂移；
        
          
        
    3. **权重更新与归一化（Measure & Weight）**：利用当前图像特征观测模型似然 $P(z_t \mid x_t = s_t^{(n)})$ 计算新粒子的匹配得分并归一化权重 $\sum \pi_t^{(n)} = 1$。
        
          
        

## 讲义末尾自测题解析

  

  

### 1. Motion Estimation 讲义例题（第 32 页）

  

  

> **Which one of the following statements about motion analysis is incorrect?**
> 
>   
> 
>   
> 
> - A. Detection of moving objects by subtraction of successive images in a video works best if the background is constant.
>     
>       
>     
> - B. Sparse motion estimation in a video can be done by template matching and **minimising** the mutual information measure.
>     
>       
>     
> - C. Dense motion estimation using optical flow assumes that each small neighbourhood remains constant over time.
>     
>       
>     
> - D. Optical flow provides an equation for each pixel but requires further constraints to solve the equation uniquely.
>     
>       
>     

- **正确答案：B**
    
      
    
      
    
- **解析**：互信息（Mutual Information）衡量的是两个子区域的相关程度，匹配时应当最大化（Maximise）互信息而不是最小化。
    
      
    

  

  

### 2. Object Tracking 讲义例题（第 32 页）

  

  

> **Which one of the following statements about object tracking is incorrect?**
> 
>   
> 
>   
> 
> - A. The particle filtering method assumes that the dynamics model and the measurement model can be parameterized.
>     
>       
>     
> - B. The hidden Markov model assumes that the measurements depend only on the current state of the objects.
>     
>       
>     
> - C. The prediction step of Bayesian inference assumes that the current state of the objects depends only on the previous state.
>     
>       
>     
> - D. The Kalman filtering method assumes that the dynamics and measurement noise are additive Gaussian.
>     
>       
>     

- **正确答案：A**
    
      
    
      
    
- **解析**：粒子滤波（Particle Filtering）属于**非参数化（Non-parametric）方法**，它通过蒙特卡洛离散采样点来逼近任意形式的概率密度，不需要假设模型可以被特定的参数化分布（如高斯分布的参数 $\mu, \Sigma$）所完全描述。