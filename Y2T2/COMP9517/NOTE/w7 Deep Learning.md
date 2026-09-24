### 第一份讲义（Part 1-1）：深度学习演进与 CNN 基础构建块

Part 1-1 的核心是**打破传统线性分类器的局限，深入剖析卷积神经网络（CNN）的底层运算与空间特征提取机制**。

  

#### 1. 为什么需要深度学习与 CNN？

- **线性分类器的局限性**：线性分类器（$f(x, W) = Wx + b$）无法处理异或（XOR）、环形分布或多模态分布等线性不可分数据。
    
      
    
- **从 MLP 到深度学习**：引入非线性激活函数（如 ReLU）构建多层感知机（MLP）。但全连接网络用于图像时参数量过于庞大，且丢失了图像的空间网格邻域结构。
    
      
    
- **分层特征学习（Hierarchical Feature Learning）**：CNN 能够端到端自适应地提取特征，低层网络学习边缘/线条等低级特征，中层学习局部纹理/部件，高层学习抽象语义表征。
    
      
    

#### 2. CNN 的核心构建块（Building Blocks）

- **卷积层（Convolutional Layer）**：
    
      
    - **局部连接（Local Connectivity）与感受野（Receptive Field）**：每个神经元只与输入特征图的一个局部空间区域相连，极大地减少了参数。
        
          
        
    - **权值共享（Weight / Parameter Sharing）**：同一个卷积核在整张图上滑动卷积，赋予网络平移不变性（Translation / Spatial Invariance）并大幅节省内存与计算。
        
          
        
    - **多通道运算**：输入特征图有几个通道（如 RGB 为 3 通道），每个卷积核的深度就等于该通道数；使用 $K$ 个卷积核即可输出 $K$ 个通道的特征图。
        
          
        
- **激活函数（Activation Function）**：默认采用 **ReLU**（$f(z) = \max(0, z)$），将负值置 0、保留正值，引入非线性的同时避免梯度饱和。
    
      
    
- **池化层（Pooling / Subsampling Layer）**：在空间维度进行下采样，降低特征图分辨率与参数量，提取局部不变特征。
    
      
    
- **展平（Flattening）与全连接输出层**：将高维特征图展平成 1D 向量，通过 FC 层并经过 **Softmax** 归一化输出各类别的概率预测。
    
      
    

#### 3. 卷积超参数与特征图尺寸计算

- **关键参数**：通道数（Channels）、卷积核尺寸（Filter Size）、步长（Stride）、填充（Padding，如 Zero / Reflect / Replicate Padding）以及空洞率（Dilation，用于在不增加参数量的前提下扩大感受野）。
    
      
    
- **特征图尺寸计算公式**： 输入尺寸 $J \times K$、卷积核 $M \times N$、填充 $P$、步长 $s$，输出特征图尺寸为：
    
      
    
    $$\text{Output Size} = \left(1 + \frac{J + 2P - M}{s}\right) \times \left(1 + \frac{K + 2P - N}{s}\right)$$
    

### 第二份讲义（Part 1-2）：经典网络架构演进与模型训练方法

Part 1-2 重点探讨了**经典图像分类数据集、现代主流卷积及 Transformer 架构的演化史，以及深度神经网络训练的实战技巧与正则化方法**。

  

#### 1. 经典基准数据集（Datasets）

- **MNIST**：$28 \times 28$ 灰度手写数字，共 70,000 张图（10 分类）。
    
      
    
- **CIFAR-10 / CIFAR-100**：$32 \times 32$ 彩色图像，CIFAR-10 包含 10 类共 60,000 张图（50,000 训练，10,000 测试）。
    
      
    
- **ImageNet (ILSVRC)**：大规模视觉识别挑战赛基准，1000 类别、超百万带标注图像，推动了深度学习架构的数次飞跃。
    
      
    
- **MS COCO**：适用于目标检测、实例分割与图像描述的综合多任务数据集。
    
      
    

#### 2. 经典网络架构演进（Architecture Evolution）

- **LeNet-5 (1989/1998)**：Yann LeCun 提出，首次将反向传播应用于自动学习视觉特征，包含 2 个卷积层与 3 个全连接层。
    
      
    
- **AlexNet (2012)**：ILSVRC 2012 冠军，开启深度学习浪潮。引入 **ReLU 激活、Dropout 正则化、数据增强（Data Augmentation）以及双 GPU 并行训练**。
    
      
    - _参数量计算示例_：对于输入通道 $C_{in}$、卷积核 $W \times H$、输出通道 $C_{out}$，单层参数量为：$(W \times H \times C_{in} + 1) \times C_{out}$。
        
          
        
- **VGGNet (2014)**：**摒弃大卷积核**（如 $11\times 11, 5\times 5$），采用**多个连续的小尺寸 $3\times 3$ 卷积核堆叠**。3 个 $3\times 3$ 卷积具有与 1 个 $7\times 7$ 卷积相同的有效感受野，但拥有更少的参数（$27C^2 < 49C^2$）和更多的非线性激活层。
    
      
    
- **GoogLeNet / Inception (2014)**：提出 **Inception 模块**，在同层并行使用不同尺寸卷积（$1\times 1, 3\times 3, 5\times 5$）与池化并进行通道拼接；利用 $1\times 1$ 卷积降维；引入辅助损失（Auxiliary Loss）缓解梯度消失；使用全局平均池化（GAP）替代全连接层大幅精简参数。
    
      
    
- **ResNet (2015)**：
    
      
    - **网络退化问题**：单纯加深网络层数会导致训练与测试误差同时上升（非过拟合）。
        
          
        
    - **残差连接（Skip / Residual Connection）**：学习残差映射 $\mathcal{F}(x) = \mathcal{H}(x) - x$，即输出为 $\mathcal{F}(x) + x$。恒等映射使梯度能够无损反向传播，成功训练了 152 层以上的极深网络并在 ImageNet 上首次超越人类识别水平。
        
          
        
- **DenseNet (2017)**：跨层特征通道级拼接（Concatenation）实现特征复用，Dense Block 之间由过渡层（Transition Layer，含 $1\times 1$ 卷积与池化）降低维度。
    
      
    
- **SENet (2017)**：引入 **Squeeze-and-Excitation（通道注意力机制）**，自适应调整不同特征通道的权重。
    
      
    
- **EfficientNet (2019)**：提出复合缩放（Compound Scaling）法则，以固定比例协同缩放网络的深度（Depth）、宽度（Width）与输入分辨率（Resolution）。
    
      
    
- **Vision Transformer (ViT) & ConvNeXt**：
    
      
    - **ViT (2020)**：将图像切分为 Patch 并投影为序列 Token，结合位置编码（Positional Embedding）与多头自注意力机制（Multi-Head Self-Attention）完成图像分类。
        
          
        
    - **ConvNeXt (2022)**：吸纳 Transformer 设计理念（如 Patchify、大卷积核、LayerNorm 等）重新现代化的纯卷积网络。
        
          
        

#### 3. 深度学习训练与防过拟合策略（Training & Regularization）

- **损失函数与优化器**：分类任务常用**交叉熵损失（Categorical Cross-Entropy Loss）**，结合 SGD、Momentum、Adam、RMSProp 等优化算法更新权重。
    
      
    
- **过拟合与欠拟合判断**：训练集与验证集表现均差为欠拟合；训练集误差极低但验证集误差高为过拟合。
    
      
    
- **缓解过拟合的关键手段**：
    
      
    1. **数据增强（Data Augmentation）**：增加噪声、随机裁剪（Crop）、翻转（Flip）、旋转、缩放、平移、亮度/对比度调节等。
        
          
        
    2. **早停法（Early Stopping）**：监测验证集指标，在泛化性能开始恶化时提前停止训练。
        
          
        
    3. **正则化（Regularization）**：L1/L2 权重衰减（Weight Decay）、Dropout（训练时随机丢弃部分神经元连接）。
        
          
        
    4. **批归一化（Batch Normalization, BN）**：缓解内部协变量偏移（ICS），加速网络收敛并稳定训练。
        
          
        
- **迁移学习（Transfer Learning / Fine-tuning）**：在大规模通用数据集（如 ImageNet 源域）上预训练特征提取器，再在小样本目标任务上进行微调，解决特定场景标注数据不足的问题。
    
      
    

### 考点与核心速记总结

1. **CNN 相较于传统 MLP 的本质优势**：局部连接（减小参数）、权值共享（平移不变性）、自动学习层次化空间特征。
    
      
    
2. **为什么堆叠小卷积核优于大卷积核（如 3 个 $3\times 3$ vs 1 个 $7\times 7$）**：具有相同的有效感受野，参数量显著减少，且引入了更多非线性激活函数，增强了网络的表达能力。
    
      
    
3. **ResNet 的核心贡献**：利用 Skip Connection / Identity Mapping 解决了深层网络的退化（Degradation）与梯度消失问题，使得超百层甚至千层网络的训练成为可能。