这两份讲义来自新南威尔士大学（UNSW）计算机视觉课程 **COMP9517**（第5周），主题是**图像分割（Image Segmentation）**与相关的**数学形态学（Mathematical Morphology）**。

  

## 讲义一：Image Segmentation Part 1（图像分割基础、算法与评估）

第一部分系统地介绍了**图像分割的基本概念、常见算法以及分割结果的量化评估方法**。

  

### 1. 核心概念与挑战

- **图像分割的定义**：将图像划分为具有特定语义或物理意义的区域（Segments/Regions），便于后续分析。
    
      
    
- **视觉任务层级区分**：
    
      
    - **图像分类（Image Classification）**：给整张图像分配一个标签（如“图中有瓶子、杯子”）。
        
          
        
    - **目标定位/检测（Object Localisation）**：预测目标的外接矩形框（Bounding Box）。
        
          
        
    - **语义分割（Semantic Segmentation）**：对图像中的**每一个像素**分类（同类物体标记为相同类别，不区分个体）。
        
          
        
    - **实例分割（Instance Segmentation）**：精确分割出每个独立的目标个体（区分出“杯子1”、“杯子2”）。
        
          
        
- **分割难点**：现实图像中区域内部通常不均匀、不同区域灰度重叠、背景复杂，没有一种通用的分割算法适用于所有场景，通常需要结合特定领域知识。
    
      
    

### 2. 基础与进阶分割算法

#### ① 基础分割方法

- **阈值分割（Thresholding）**：适用于前景与背景灰度直方图呈明显双峰分布的情况；如果灰度分布严重重叠则失效。
    
      
    
- **K-means 聚类**：根据像素特征（颜色/灰度）聚类，但必须预先指定聚类簇数 $K$，且对异常值和初始点敏感。
    
      
    
- **基于特征的像素分类（Feature-based Pixel Classification）**：提取像素周围的图像块（Patch）特征，利用训练好的分类器对每个像素进行分类。
    
      
    

#### ② 进阶分割方法

1. **区域生长与分裂合并（Region Splitting and Merging / Region Growing）**：
    
      
    - **连通域分析（Connected Components）**：讲解了2D（4连通/8连通）与3D（6/18/26连通），以及经典的两遍扫描连通域标记算法（Two-pass Labeling）与等价标签合并。
        
          
        
    - **区域生长**：从种子点（Seed）出发，依据预设相似度准则将相邻像素逐步合并到区域中。
        
          
        
2. **分水岭算法（Watershed Segmentation）**：
    
      
    - 将图像灰度视为地形高程（Topographic Surface），模拟水流漫灌过程（Meyer's Flooding Algorithm）。容易产生**过度分割（Oversegmentation）**，需配合平滑预处理或基于标记（Marker-controlled）进行优化。
        
          
        
3. **最大稳定极值区域（MSER, Maximally Stable Extremal Regions）**：在连续变化的阈值下保持形状高度稳定的连通分量，常用于鲁棒特征提取。
    
      
    
4. **均值漂移（Mean Shift）**：
    
      
    - 无需预先指定簇数 $K$，通过核密度估计寻找特征空间中的局部极值点（Mode/峰值）并聚类，对异常值鲁棒。
        
          
        
5. **超像素分割（Superpixels / SLIC）**：
    
      
    - 将局部相邻且相似的像素聚合为“超像素”以提高后续计算效率。重点介绍了 **SLIC 算法**，在 5D 空间（CIELAB 颜色空间 + 图像坐标空间 $(x,y)$）定义归一化距离进行聚类。
        
          
        
6. **条件随机场与图割（CRF & Graph Cut）**：
    
      
    - 将分割建模为能量最小化问题：包含**一元势（Unary Potential，数据项/分类代价）**和**二元势（Pairwise Potential，平滑项/邻域一致性代价）**，利用最大流/最小割（Min-Cut / Max-Flow）算法求解。
        
          
        
7. **主动轮廓模型（Active Contour / Snakes）**：参数化模型，通过最小化由图像梯度力、轮廓平滑性等组成的能量函数，让控制点拟合目标边缘。
    
      
    
8. **水平集方法（Level-Set Segmentation）**：隐式轮廓表示法（将 2D 轮廓作为 3D 水平集函数的零等高线），通过偏微分方程（PDE）演化，能自然处理**拓扑结构变化（如分裂、合并）**。
    
      
    

### 3. 分割评估指标（Evaluation Metrics）

讲义系统列出了基于混淆矩阵（Ground Truth）的评估体系：

  

- **像素分类混淆矩阵**：$TP$（真正）、$TN$（真负）、$FP$（伪正/虚警）、$FN$（伪负/漏检）。
    
      
    
- **敏感度（Sensitivity / Recall / TPR）**：$\text{TPR} = \frac{TP}{TP + FN}$（真实目标被找出的比例）。
    
      
    
- **特异度（Specificity / TNR）**：$\text{TNR} = \frac{TN}{TN + FP}$（真实背景被正确识别的比例）。
    
      
    
- **ROC 曲线与 AUC**：以 $1-\text{Specificity}$（FPR）为横轴、$\text{Sensitivity}$（TPR）为纵轴绘制，曲线下面积（AUROC）越接近 1 算法表现越好。
    
      
    
- **精确率（Precision / PPV）**：$P = \frac{TP}{TP + FP}$。
    
      
    
- **F1-Score（F-measure）**：精确率与召回率的调和平均数 $F_1 = \frac{2 \cdot P \cdot R}{P + R}$。
    
      
    
- **Jaccard 相似系数（JSC / IoU）**：$\text{IoU} = \frac{TP}{TP + FP + FN} = \frac{\vert{}S \cap T\vert{}}{\vert{}S \cup T\vert{}}$。
    
      
    
- **Dice 相似系数（DSC）**：$\text{DSC} = \frac{2 \cdot TP}{2 \cdot TP + FP + FN} = \frac{2\vert{}S \cap T\vert{}}{\vert{}S\vert{} + \vert{}T\vert{}}$。
    
      
    

