

  

- **讲义 1（Part 2-1）**：**基于 CNN 的目标检测（Object Detection Using CNNs）**
    
      
    
      
    
- **讲义 2（Part 2-2）**：**图像分割与视觉-语言多模态（Segmentation & Vision + Language）**
    
      
    
      
    

### 第一份讲义（Part 2-1）：目标检测（Object Detection Using CNNs）

目标检测任务的核心目标是同时解决 **“What（分类，Classification）”** 与 **“Where（定位，Localization，即预测包围框坐标 $(x, y, w, h)$）”**。

  

#### 1. 核心基础与评估指标

- **损失函数（Multi-task Training）**：分类分支通常采用交叉熵损失（Cross-Entropy Loss），定位/边界框回归分支通常采用回归损失（如 L2 Loss / Smooth L1 Loss）。
    
      
    
- **交并比（Intersection over Union, IoU）**：衡量预测框与真实框重叠程度的指标，定义为 $\text{IoU} = \frac{\text{Area of Overlap}}{\text{Area of Union}}$。通常当 $\text{IoU} \ge 0.5$ 时视为定位正确。
    
      
    
- **多目标检测挑战**：单张图像中目标数量不固定，无法直接用固定维度的全连接层一次性输出所有框。早期暴力滑动窗口（Sliding Window）裁剪会导致计算量爆炸。
    
      
    

#### 2. 两阶段目标检测算法（Two-stage / Proposal-based）

两阶段检测的核心思想是：**第一步生成候选区域（Proposals），第二步对候选区域进行特征提取与分类回归**。

  

```
输入图像 
  └──> 阶段 1: 提取 ~2000 个候选区域 (Selective Search / RPN)
         └──> 阶段 2: 特征提取 -> RoI Pooling / Align -> 分类与边框回归
```

- **R-CNN (2014)**：
    
      
    
    1. 利用无监督聚类算法 **选择性搜索（Selective Search）** 在 CPU 上生成约 2000 个候选框。
        
          
        
    2. 将每个区域变形（Warp）到固定尺寸后分别输入 CNN 提取特征。
        
          
        
    3. 用独立训练的 **线性 SVM** 进行分类，并用独立的 **回归器** 微调边框。
        
          
        
    
    - _缺点_：训练分多阶段且无法端到端训练；中间特征需占用数百 GB 硬盘存储；测试速度极慢（每张图需运行 2000 次 CNN 前向传播，单图耗时约 47 秒）。
        
          
        
- **SPP-Net (2014) 与 Fast R-CNN (2015)**：
    
      
    - **整图卷积**：整张图像只通过一次骨干 CNN 提取全图特征图，然后将候选区域映射到特征图上。
        
          
        
    - **RoI Pooling**：将不同尺寸的特征图区域划分为固定网格（如 $7\times 7$）并做最大池化，输出固定维度特征，替代了全连接前图像的强制变形与多阶段存储。
        
          
        
    - **多任务端到端训练**：使用 Multi-task Loss 同时训练 Softmax 分类器与 Smooth L1 边界框回归器。
        
          
        
    - _瓶颈_：测试时间的大部分被 CPU 上的 Selective Search 占据。
        
          
        
- **Faster R-CNN (2015)**：
    
      
    - **区域提议网络（RPN, Region Proposal Network）**：彻底取代 Selective Search，利用全图卷积特征图直接生成候选框，实现全流程 GPU 加速与完全端到端检测。
        
          
        
    - **Anchor Boxes（锚框机制）**：在特征图每个像素点预设不同尺度（Scale）和长宽比（Aspect Ratio）的预设框（如 3 种尺度 $\times$ 3 种比例 = 9 个 Anchors）。
        
          
        
    - **非极大值抑制（NMS）**：按照置信度排序，循环剔除与最高分预测框重叠（$\text{IoU} > \text{阈值}$，如 0.7）的冗余候选框。
        
          
        
    - **在线难例挖掘（OHEM）与正负样本平衡**：限制正负样本比例（如 1:3）以缓解背景样本过多的类别不平衡问题。
        
          
        

#### 3. 单阶段目标检测算法（One-stage / Proposal-free）

抛弃候选区域生成步骤，直接将目标检测转化为密集的坐标回归与类别概率预测问题，速度显著提升。

  

- **YOLO (You Only Look Once, 2016)**：
    
      
    - 将输入图像划分为 $S \times S$（如 $7 \times 7$）的网格，每个网格直接预测 $B$ 个边界框的坐标、置信度（Objectness Score）以及类别条件概率（输出张量尺寸为 $7 \times 7 \times 30$）。
        
          
        
    - 测试速度比 R-CNN 快近 1000 倍，适合实时场景，但在密集/小目标检测上精度稍逊。
        
          
        
- **SSD (Single Shot MultiBox Detector, 2016)**：
    
      
    - 引入 **多尺度特征图预测**：在骨干网络不同深度的多层特征图上分别设置不同尺度的 Default Boxes（浅层特征图检测小物体，深层特征图检测大物体）。
        
          
        
    - 全卷积预测：使用小卷积核直接输出分类和偏置预测，取代全连接层。
        
          
        
- **RetinaNet 与 Focal Loss (2017)**：
    
      
    - **特征金字塔网络（FPN）**：结合自底向上、自顶向下与侧边连接（Lateral Connections），将浅层的高分辨率与深层的强语义特征融合。
        
          
        
    - **Focal Loss**：针对单阶段检测器中极度严重的“前景-背景类别不平衡”（约 10 万个候选位置中绝大部分是容易分类的背景）问题，通过给容易分类的样本施加衰减因子 $(1-p_t)^\gamma$，使模型聚焦于难分类样本的训练。
        
          
        

### 第二份讲义（Part 2-2）：分割与视觉-语言大模型

#### 1. 语义分割（Semantic Segmentation）

语义分割要求对图像中的**每一个像素进行类别预测（Pixel-wise Classification）**，不区分同类物体的不同个体。

  

```
输入图像 (3 x H x W)
  └──> 编码器 (下采样，提取高层抽象特征)
         └──> 解码器 (上采样，恢复原始 H x W 分辨率)
                └──> 预测图 (C x H x W，C 为类别数)
```

- **全卷积网络（FCN, 2015）**：
    
      
    - 将经典分类网络末端全连接层替换为卷积层，提出“编码器-解码器”结构（先下采样提取语义，再上采样恢复空间分辨率）。
        
          
        
- **网络内上采样方法对比**：
    
      
    1. **最近邻插值（Nearest Neighbour）/ 简单反池化（Unpooling）**：无参数的规则放大。
        
          
        
    2. **最大反池化（Max Unpooling）**：在下采样 Max Pooling 时记录最大值所在的空间索引位置（Switch variables），上采样时将数值填回原始索引位置，其余补 0。
        
          
        
    3. **转置卷积（Transpose Convolution / Deconvolution）**：可学习参数的上采样操作，步长控制放大倍数，重叠区域累加输出。
        
          
        
- **U-Net (2015) 及变体**：
    
      
    - 经典的 U 型对称编码-解码架构，引入了 **跳跃连接（Skip Connections）**，直接将浅层的高分辨率细节特征拼接到深层解码器中，解决了深层特征丢失边界定位信息的问题。
        
          
        
    - _主流变体_：**Attention U-Net**（在跳跃连接中引入注意力机制过滤噪声）、**ResUNet**（融入残差块）、**TransUNet**（使用 Vision Transformer 作为强编码器）。
        
          
        

#### 2. 实例分割（Instance Segmentation）与 Mask R-CNN

实例分割既要找出物体类别和包围框，又要区分同类别的不同个体（每个目标对应独立像素级掩膜）。

  

- **Mask R-CNN (2017)**：
    
      
    - 在 Faster R-CNN 基础上增加了一个小型的 FCN 掩膜预测分支（Mask Branch），多任务损失为 $\mathcal{L} = \mathcal{L}_{\text{cls}} + \mathcal{L}_{\text{box}} + \mathcal{L}_{\text{mask}}$。
        
          
        
    - **RoI Align 替代 RoI Pooling**：
        
          
        - _RoI Pooling 的问题_：量化操作（取整）会导致特征与原始像素位置发生亚像素级别的偏差，对目标检测影响较小，但会严重破坏精细的像素级掩膜质量。
            
              
            
        - _RoI Align 的方案_：取消所有量化取整操作，在采样子网格内使用 **双线性插值（Bilinear Interpolation）** 精确计算特征值，彻底消除特征对齐误差。
            
              
            

#### 3. 视觉与语言多模态基座模型（Vision + Language & Foundation Models）

- **基座模型（Foundation Models）**：在大规模数据上进行自监督预训练，具备极强泛化能力，可通过少量微调适应多种下游任务。
    
      
    
- **CLIP (Contrastive Language-Image Pre-training, OpenAI 2021)**：
    
      
    - **训练数据与目标**：采集约 4 亿图文对（Image-Text pairs），通过双向对齐的 **InfoNCE 对比学习损失**，将匹配的图文对在共享嵌入空间中拉近（最大化对角线相似度），非匹配对推远。
        
          
        
    - **Zero-Shot 预测**：无需额外训练分类头，将候选类别转为文本 Prompt（如 `"a photo of a [class]"`），计算图像特征与文本特征的余弦相似度即可完成零样本分类。
        
          
        
- **LLaVA (Large Language and Vision Assistant)**：
    
      
    - 通过线性映射层将视觉编码器（如 CLIP ViT）提取的图像特征转化为与文本 Token 兼容的 Image Tokens，直接输入自回归语言模型（LLM）实现多模态视觉指令问答。
        
          
        

### 两份讲义末尾测试题（Example Exam Questions）解析

  

  

#### 1. 讲义 Part 2-1（第 74 页）

  

  

**题目**：Which one of the following statements about data augmentation is correct?

  

- A. Augmentation increases the number of parameters in the model.
    
      
    
- B. Augmentation reduces the size of the dataset to speed up training.
    
      
    
- **C. Augmentation generates new training data by transforming the existing data.**
    
      
    
      
    
- D. Augmentation reduces the depth of the network for better performance.
    
      
    

**正确答案**：**C**

  

- **解析**：数据增强（Data Augmentation）通过对已有训练样本进行几何变换（旋转、翻转、裁剪）或颜色变换生成新的样本变体，提高数据集多样性并防止过拟合，不会改变模型的参数量或网络深度。
    
      
    

  

  

#### 2. 讲义 Part 2-2（第 62 页）

  

  

**题目**：What kind of neural network is most suited for image segmentation tasks?

  

- A. Multilayer perceptron (MLP)
    
      
    
- **B. Fully convolutional network (FCN)**
    
      
    
      
    
- C. Region proposal network (RPN)
    
      
    
- D. Recurrent neural network (RNN)
    
      
    

**正确答案**：**B**

  

- **解析**：全卷积网络（Fully Convolutional Network, FCN）能够接受任意尺寸输入并保留完整的 2D 空间几何结构，输出与原图尺寸一致的像素级类别预测图，是图像语义分割最适配的基础架构。