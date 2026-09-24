

# UNSW COMP6441/6841 Week 8 课程综合笔记

## 第一部分：安全、人为错误与公正文化 (Accidents & Just Culture)

### 1. 安全 (Safety) 与 网络安全 (Security)

- **概念对比**：
    
    - **Safety（安全/安全性）**：关注**非故意事件**、系统或人为失效、以及系统运行的可靠性（Reliability）。
        
    - **Security（网络安全/保密性）**：关注来自**威胁者/对手**（Adversaries）的故意攻击、恶意软件（Malware）等威胁。
        
    - **共同点**：均涉及隐私（Privacy）、信任（Trust）、韧性（Resilience）和可用性（Availability）。
        
- **核心逻辑**：系统安全（Safety）是系统可靠性、用户信任及长期普及的基石。
    

### 2. 组织文化与心理安全 (Organizational Culture & Psychological Safety)

- **环境塑造安全**：
    
    - **心理安全（Psychological Safety）**：是物理安全的基石。恐惧会导致风险被隐藏。
        
    - 健康的文化鼓励：提早报告（在隐患变成事故前上报）、透明度（关注系统而非责备个人）以及从错误中学习。
        
- **真实案例教训**：
    
    - **Boeing (737 MAX)**：工程师的担忧未得到有效回应，阻碍层层上报的文化导致安全隐患积累。
        
    - **NASA (Challenger 挑战者号)**：对 O 型环隐患的警告逐渐被习惯化（违规常态化），最终导致灾难。
        
    - **Optus 数据泄露**：过度关注个人失误而忽略了组织和系统层面的控制。
        
- **不安全环境的预警信号**：
    
    - 认为访问限制是麻烦事。
        
    - BYOD 成为常态。
        
    - 桌面贴满便签密码。
        
    - 隐式信任而非验证用户（缺乏零信任意识）。
        

### 3. 人为错误模型：GEMS 与认知偏误

- **压力-绩效曲线 (The Stress Performance Curve)**：
    
    - 外部压力过高会导致认知失效（Rushed decisions, Missed alerts）。
        
    - 攻击者常利用制造紧迫感（Urgency）来促使防守方做出错误决策。
        
- **James Reason 的 GEMS 模型 (Generic Error-Modelling System)**：
    
    1. **Skill-Based (SB) 基于技能**：产生 Slip（失误）与 Lapse（遗忘），多因注意力不集中或自动驾驶模式引起（如误点击钓鱼链接）。
        
    2. **Rule-Based (RB) 基于规则**：误用规则或模式匹配错误（如分类错误事件）。
        
    3. **Knowledge-Based (KB) 基于知识**：缺乏理解、认知过载（如面对零日漏洞或 AI 恶意的推演失误）。
        
- **易得性启发式 (Availability Heuristics)**：
    
    - 人们倾向于过度依赖最容易在脑海中浮现的信息（如最近发生、频繁发生、极端的事件）。
        
    - 会导致将新问题硬套入旧方案、延迟或错误的响应。
        

### 4. 系统失效与公正文化 (Just Culture)

- **契诃夫之枪 (Chekhov's Gun) 在安全分析中的局限**：
    
    - 现实中充满了噪声和干扰信息，并非所有细节都是线索。分析师需区分信号与噪声，不能带着戏剧化预期分析事故。
        
- **违规常态化 (Normalization of Deviance)**：
    
    - 风险或非标准操作因短期内未引发灾难而逐渐被视为“新常态”，最终导致隐患积聚。
        
- **三哩岛核事故 (Three Mile Island, 1979)**：
    
    - 系统复杂性（Complexity）与紧密耦合（Tight Coupling）使得多个小故障连环放大，导致操作员认知过载。
        
- **公正文化 (Just Culture)**：
    
    - **核心理念**：承认人为错误不可避免，重点在于查明导致错误的“系统失效”（System Failures）而非惩罚个人（问“发生了什么”而不是“谁搞砸了”）。
        
    - **替代测试 (Substitution Test)**：评估同等条件下的其他人是否也会做出类似行为，以划分是系统诱导的错误还是有意的违规/破坏。
        

## 第二部分：PKI 与应用安全 (PKI & Application Security)

### 1. Web 加密演进史

- **早期 Web (1990s)**：HTTP、Telnet、FTP 均以明文（Plaintext）传输。网络包可被轻易抓包（Packet Sniffing），无保密性、完整性及身份验证。
    
- **SSL 与 HTTPS 的诞生**：
    
    - 1994 年 Netscape 开发 SSL（Secure Socket Layer），引入 X.509 证书与 CA 机制。
        
    - HTTP over SSL 演变成为 HTTPS。
        
- **协议演进**：
    
    - **SSL 2.0 / 3.0**：早期版本，存在缺乏完整性校验等重大缺陷，现已废弃（如 POODLE 攻击利用了 SSL 3.0 的填充 oracle 漏洞）。
        
    - **TLS 1.0 / 1.1**：1999 年起标准化的 TLS 协议，支持了 RC4、MD5 等破损算法，已被废弃。
        
    - **TLS 1.2 (2008)**：引入了 AES-GCM，但仍保留了静态 RSA 密钥交换（无完美前向安全性 PFS）和 CBC 模式。
        
    - **TLS 1.3 (2018)**：现代标准。移除了所有不安全算法（RC4, MD5, CBC），**强制启用前向安全性 (ECDHE)**，握手更高效（1 RTT），加密 SNI 保护隐私。
        

### 2. HTTPS 安全三要素与握手流程

- **三大目标**：
    
    1. **Confidentiality（保密性）**：通过对称加密（如 AES）保护传输数据。
        
    2. **Integrity（完整性）**：通过 AEAD（如 AES-GCM, ChaCha20-Poly1305）或 MAC 防篡改。
        
    3. **Authentication（身份验证）**：通过 X.509 数字证书验证服务器身份。
        
- **TLS 握手核心步骤**：
    
    1. **ClientHello**：客户端发送支持的 TLS 版本、加密套件列表及 SNI。
        
    2. **ServerHello + Certificate**：服务器选择套件并下发数字证书。
        
    3. **Verify**：客户端校验证书合法性（CA 签名、域名匹配、有效期等）。
        
    4. **Key Exchange**：利用 Diffie-Hellman (DH/ECDHE) 生成共享会话密钥。
        
    5. **Encrypted Session**：后续通信全面使用对称加密。
        

### 3. 信任模型对比：Web of Trust vs. PKI

|**特性 / 维度**|**Web of Trust (信任网) PDF**|**PKI (公钥基础设施) PDF**|
|---|---|---|
|**信任结构**|去中心化、基于同伴签名|中心化、树状层级结构|
|**核心机制**|用户互相交叉签署公钥（如 PGP / GPG）|由根 CA 及中间 CA 签发数字证书|
|**可扩展性**|较差，依赖手动/局部信任网络|极高，适合全球互联网使用|
|**应用场景**|PGP 邮件加密、极客社区|HTTPS / TLS、X.509 证书|
|**主要风险**|难以验证陌生公钥、吊销管理困难|错误签发证书、CA 被黑客攻破|

### 4. 授权与认证 (OAuth vs OpenID)

- **OAuth (Open Authorization)**：
    
    - **定位**：授权（Delegation / Authorization）协议。
        
    - **作用**：允许第三方应用在不获取用户密码的前提下获取有限的数据访问权限（通过发放 Temporary Token/Valet Key）。
        
    - **常见风险**：Token 泄露、权限范围（Scope）过大、钓鱼攻击、重定向 URI 不安全。
        
- **OpenID**：
    
    - **定位**：身份认证（Authentication）协议。
        
    - **作用**：解决“你是谁”的问题（类似于证明信）。
        

### 5. 身份验证攻击与渗透测试

- **常见攻击类型**：
    
    - **降级攻击 (Fallback / Downgrade Attack)**：中间人干预握手阶段，迫使客户端与服务器降级使用有缺陷的老旧协议（如 POODLE 攻击）。
        
    - **Session Hijacking & Token Replay**：攻击者通过 XSS、存储漏洞或网络拦截盗取 Access Token/Cookie 并重放。
        
    - **MFA Fatigue / Push Bombing**：通过连续发送多因素认证弹窗骚扰用户以促使其误触同意。
        
- **渗透测试 (Penetration Testing)**：
    
    - 通过模拟黑客攻击主动发现漏洞；结合公众 Bug Bounty 机制实现众包式网络安全。