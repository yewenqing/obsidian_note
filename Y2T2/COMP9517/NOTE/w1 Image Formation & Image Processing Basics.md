
## 第一份讲义：`Image Formation`（图像成像机制）

本讲义主要探讨从三维物理世界到二维数字图像的映射过程，涵盖**光学几何、颜色科学与数字离散化**三大核心。

  

### 1. 成像模型的演变

- **无光阑胶片（Idea 1）**：若直接将胶片置于物体前，空间中物体的每个点都会向胶片的所有位置辐射光线，导致成像完全模糊（All-to-all 投影）。
    
      
    
- **针孔相机（Pinhole Camera / Idea 2）**：加入带小孔（Aperture）的遮光板，仅允许特定方向的光线通过，使三维空间中的物点与像平面上的像点形成唯一的一一对应，从而消除模糊。
    
      
    
- **透镜引入（Lens / Idea 3）**：针孔过小会导致进光量极少；透镜通过光的折射聚焦光线，既能保持清晰聚焦（类似针孔效果），又极大增加了进光量。
    
      
    

### 2. 投影几何与透视特性

- **降维本质**：成像本质上是将 3D 世界降维映射到 2D 图像平面的过程。
    
      
    
- **不变量与丢失量**：
    
      
    - **不保留**：长度（Length）、面积（Area）、角度（Angles）、平行性（Parallelism）和垂直性均会被破坏（远小近大）。
        
          
        
    - **保留**：直线的共线性（3D 直线投影后依然是 2D 直线）。
        
          
        
- **消失点与消失线（Vanishing Points & Lines）**：3D 空间中平行的直线，在透视投影下会在 2D 图像上相交于“消失点”（如铁轨向远处收敛）；平行平面族的消失点汇聚构成“消失线”（地平线）。
    
      
    

### 3. 投影数学与近似模型

- **透视投影公式（Perspective Projection）**：
    
      
    - 设相机中心为原点 $(0,0,0)$，焦距为 $f$，世界坐标点为 $\mathbf{p} = (x, y, z)$。
        
          
        
    - 像平面实际坐标为：$x' = -f\frac{x}{z}, \quad y' = -f\frac{y}{z}$（负号表示倒像）。
        
          
        
    - 虚拟正像（Virtual Image）忽略镜像与负号后：$x' = f\frac{x}{z}, \quad y' = f\frac{y}{z}$。
        
          
        
- **弱透视投影与正交投影（Affine / Weak Perspective / Orthographic）**：
    
      
    - 当场景深度变化相对于物体到相机的平均距离 $z_0$ 很小时（即场景内深度差可忽略），放大率 $m = \frac{f}{z_0}$ 近似为常数，退化为弱透视：$(x', y') = (mx, my)$。
        
          
        
    - 当 $m = 1$ 时，退化为正交投影：$(x', y') = (x, y)$。
        
          
        

### 4. 径向畸变与人类视觉

- **透镜径向畸变（Radial Distortion）**：实际光学透镜会引入桶形畸变（Barrel Distortion）或枕形畸变（Pincushion Distortion），需通过畸变校正算法进行几何校正。
    
      
    
- **人眼结构对比**：人眼的晶状体、视网膜与三种锥状细胞（S/M/L 分别对应短/中/长波长，即蓝/绿/红响应）是现代相机与色彩模型设计的仿生学基础。
    
      
    

### 5. 颜色模型（Colour Spaces）

- **RGB**：基于加色三基色，是硬件采集和显示的默认空间，但 **R、G、B 三通道间存在高度相关性**（改变光照会同时影响三个通道）。
    
      
    
- **YCbCr**：分离亮度（$Y$）与色度（$Cb, Cr$），计算速度快且便于压缩（可对色度进行降采样），广泛用于电视广播与 JPEG 图像压缩。
    
      
    
- **HSV**：包含色调（Hue）、饱和度（Saturation）、明度（Value），符合人类对色彩的直观认知，常用于色彩选择与人机交互。
    
      
    
- **CIELAB ($L^*a^*b^*$)**：感知均匀（Perceptually Uniform）的色彩空间，$L^*$ 为亮度，$a^*$ 为红-绿通道，$b^*$ 为黄-蓝通道。在此空间中的欧几里得距离与人眼主观感知差异一致。
    
      
    

### 6. 数字图像形成

- **空间采样（Spatial Sampling）**：将连续坐标离散化为网格（矩阵行与列），决定了**空间分辨率（Resolution）**。
    
      
    
- **幅度量化（Intensity Quantisation）**：将连续的亮度/灰度值离散化为有限个整数级别，决定了**每个像素的位深（Bits per pixel）**（如 8-bit 提供 256 级灰度）。
    
      
    

## 第二份讲义：`Image Processing Basics`（图像处理基础）

本讲义主要探讨在**空间域（Spatial Domain）**上对图像像素进行的基本变换与预处理技术，重点在于**点运算（Point Operations）**与**直方图处理（Histogram Processing）**。

  

### 1. 图像处理的范畴与分类

- **概念区别**：
    
      
    - **图像处理（Image Processing）**：输入图像 $\to$ 输出图像（旨在消除退化、增强特征）。
        
          
        
    - **图像分析（Image Analysis）**：输入图像 $\to$ 输出特征/测量值。
        
          
        
    - **计算机视觉（Computer Vision）**：输入图像 $\to$ 输出高层语义理解。
        
          
        
- **操作空间划分**：
    
      
    - **点运算（Point Operations）**：$g(x, y) = T(f(x, y))$，输出像素值仅取决于当前输入像素自身的灰度值。
        
          
        
    - **邻域运算（Neighbourhood Operations）**：输出像素值取决于输入像素及其周围一组像素的加权组合（如空间滤波/卷积）。
        
          
        

### 2. 经典灰度点运算

- **对比度拉伸（Contrast Stretching）**：设定上下阈值 $[L, H]$，将低于 $L$ 的截断为最小（黑），高于 $H$ 的截断为最大（白），中间区间进行线性拉伸，从而提升图像动态范围。
    
      
    
- **灰度反转（Intensity Inversion）**：$s = (L-1) - r$，反转黑白，常用于增强暗背景下微小细节（如医学微钙化灶检测）。
    
      
    
- **对数变换（Log Transformation）**：$s = c \log(1 + r)$，**将低灰度区域的较窄输入范围扩展为较宽输出范围**，同时压缩高灰度区域，常用于压缩高动态范围图像（如傅里叶频谱图的可视化显示）。
    
      
    
- **幂律 / Gamma 变换（Power-Law / Gamma Transformation）**：$s = c r^\gamma$。
    
      
    - $\gamma < 1$：效果类似对数变换（拉伸暗部、压缩亮部）。
        
          
        
    - $\gamma > 1$：效果类似反对数变换（拉伸亮部、压缩暗部）。
        
          
        
    - 广泛应用于显示器伽马校正（Gamma Correction）与通用对比度调整。
        
          
        
- **分段线性变换与分层（Piecewise Linear & Slicing）**：
    
      
    - **灰度分层（Gray-level Slicing）**：高亮特定灰度范围（可二值化或保留背景）。
        
          
        
    - **位平面分层（Bit-plane Slicing）**：提取 8-bit 图像中各个二进制位（从低位 Bit 0 到高位 Bit 7），高位平面包含主要结构信息，低位平面包含细节和噪声，可用于图像压缩。
        
          
        

### 3. 图像阈值化（Thresholding / 图像分割）

- **手动阈值化**：设定单一灰度阈值，大于等于阈值置为白，小于置为黑，输出二值图像。
    
      
    
- **自动阈值化算法**：
    
      
    1. **大津法（Otsu's Method）**：通过穷举搜索使**类间方差最大化（Maximise inter-class variance）**（等价于类内方差最小化），自动寻找前景与背景的最佳分割阈值。
        
          
        
    2. **迭代均值法（IsoData Method）**：从初始阈值开始，分别计算阈值两侧的像素均值 $\mu_0$ 和 $\mu_1$，迭代更新阈值为 $t = \frac{\mu_0 + \mu_1}{2}$ 直至收敛。
        
          
        
    3. **三角形法（Triangle Method）**：在直方图峰值点与最高灰度点之间连线，寻找直方图距离该直线垂直距离最大的灰度值作为阈值，适合单峰长尾分布。
        
          
        
- **多级阈值化（Multilevel Thresholding）**：使用多个阈值将图像划分为多个不同灰度级的区域。
    
      
    

### 4. 直方图处理技术

- **灰度直方图（Histogram）**：统计各灰度级出现的像素频次，归一化后表示灰度出现的概率分布 $p(r)$。
    
      
    
- **直方图均衡化（Histogram Equalization）**：
    
      
    - **原理**：利用累积分布函数（CDF）作为变换函数 $T(r) = (L-1)\int_0^r p_r(\xi)d\xi$（离散形式为累加求和），将原始图像的灰度分布转换为**近似均匀分布**。
        
          
        
    - **效果**：自动拉伸直方图峰值区域的对比度，压缩谷值区域对比度，最大化图像的信息熵和整体对比度。
        
          
        
- **直方图规定化 / 匹配（Histogram Matching / Specification）**：
    
      
    - 将输入图像的直方图变换为**指定的某种目标直方图形状**（先通过 CDF 映射到均匀空间，再通过目标 CDF 的逆映射转换得到）。
        
          
        

### 5. 多图代数/逻辑运算与降噪

- **代数与逻辑运算**：像素级相加、相减（用于运动检测/背景消除）、掩膜与（AND）/或（OR）操作。
    
      
    
- **多帧平均降噪（Image Averaging）**：
    
      
    - 假设真实图像为 $g(x,y)$，观测图像叠加了零均值、独立同分布（i.i.d.）的随机噪声 $n_i(x,y)$（方差为 $\sigma^2$）。
        
          
        
    - 对 $N$ 帧图像取平均后，噪声方差下降为 $\frac{\sigma^2}{N}$（标准差变为 $\frac{\sigma}{\sqrt{N}}$），能有效平滑随机噪声且不模糊图像边缘。
        
          
        

## 课件末尾自测题解析

  

  

### 1. `Image Formation` 第 47 页习题

  

  

> **Question:** Which one of the following statements about colour spaces is incorrect?
> 
>   
> 
> - **A.** The R, G, and B channels of the RGB colour space are often correlated.
>     
>       
>     
> - **B.** The H and the S channel of the HSV colour space are confounded.
>     
>       
>     
> - **C.** The Y channel of the YCbCr colour space represents the brightness.
>     
>       
>     
> - **D.** The a* channel of the L*a*b* colour space is the green-blue component.
>     
>       
>     
> 
> **正确答案：D** **解析**：在 CIELAB ($L^*a^*b^*$) 色彩空间中，$a^*$ 通道代表的是**红-绿（Green-Red）**分量，而 $b^*$ 通道代表的是**蓝-黄（Blue-Yellow）**分量，因此 D 选项表述错误。
> 
>   

  

  

### 2. `Image Processing Basics` 第 49 页习题

  

  

> **Question:** Which one of the following statements about intensity transformations is incorrect?
> 
>   
> 
> - **A.** Contrast stretching linearly maps intensities between two values to the full output range.
>     
>       
>     
> - **B.** Log transformation maps a narrow range of high intensities to a wider range of output values.
>     
>       
>     
> - **C.** Power transformation can map intensities similar to log and inverse log transformations.
>     
>       
>     
> - **D.** Piecewise linear transformations can achieve contrast stretching and intensity slicing.
>     
>       
>     
> 
> **正确答案：B** **解析**：对数变换（Log transformation）的作用是将较窄范围的**低灰度值（暗部 / Low intensities）**扩展为较宽范围的输出值，并压缩高灰度值，B 选项将其误说为 high intensities。