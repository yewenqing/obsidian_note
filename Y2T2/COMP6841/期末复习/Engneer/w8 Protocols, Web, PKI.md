这份讲义是新南威尔士大学（UNSW）2026年第二学期 **COMP6441 / COMP6841** 的 **第 8 周工程专题课件（Week 8 Engineering Lecture）**，主题为 **《PKI 与应用安全》（PKI & Application Security）**，主讲人为 Rahat Masood。

  

本讲义系统地梳理了 **从明文互联网到现代加密传输的演进历程（SSL $\to$ TLS 1.2 $\to$ TLS 1.3）、降级/回退攻击机制、信任模型（信任网 Web of Trust vs 公钥基础设施 PKI）、现代应用授权与认证协议（OAuth vs OpenID）以及针对认证与令牌的常见攻击手法**。以下是讲义的核心知识点与结构化解析：

  

### 一、 课程管理与道德倡议（Admin Reminders & Ethics）

- **项目提交截止时间**：第 8 周周五（7 月 24 日）下午 4:00 于 Moodle 提交。
    
      
    
- **AI 规则与善意守则（Good Faith Policy）**：严禁直接使用 AI 生成作业内容；课程中涉及的技术与攻防概念严禁用于任何破坏性用途，必须遵守专业道德底线。
    
      
    

### 二、 未加密的早期互联网与 SSL/HTTPS 的诞生（1990s）

#### 1. 狂野西部时代的明文网络（The "Wild West" Web）

- **早期环境**：1993 年 Mosaic 浏览器让 Web 图形化，但当时的 HTTP 0.9/1.0 以及 Telnet、FTP 全部采用 **纯明文（Plaintext）传输**。
    
      
    
- **安全隐患**：在共享局域网（Hub 架构）中，任何人使用抓包工具（如 tcpdump）即可捕获并看清网络上的所有密码、Cookie、表单和邮件内容。
    
      
    
- **缺失三大属性**：无机密性（No confidentiality）、无完整性（No integrity）、无身份认证（No authentication）。
    
      
    

#### 2. 自制加密的混乱与行业觉醒

- **早期 DIY 加密**：各网站尝试使用 Java Applet、CGI 封装或专有 Socket 插件自行加密，导致 **严重的协议碎片化、可用性极差且互不兼容**。
    
      
    
- **商业推动（1994）**：随着在线电子商务与信用卡网上支付的兴起（如 Pizza Hut、Netscape Mall），行业意识到必须由浏览器原生支持标准化的传输加密层。
    
      
    

#### 3. SSL 与 HTTPS 的诞生

- **Netscape 的贡献**：由 Taher Elgamal 等密码学家主导设计了 **安全套接字层（SSL, Secure Socket Layer）**，作为 Berkeley Socket 之上的抽象安全层，使用户无感获得加密保护。
    
      
    
- **核心创新**：引入 X.509 数字证书与证书颁发机构（CA）、通过非对称公钥交换协商对称会话密钥、在浏览器端引入安全“挂锁（Padlock）”图标。
    
      
    
- **HTTP + SSL = HTTPS**：将加密机制植入传输层而非网页应用本身。
    
      
    

### 三、 从 SSL 到 TLS 的演进与版本对比

#### 1. SSL/TLS 历史发展脉络

- **SSL 1.0（1994）**：内部草案，因存在严重安全缺陷从未公开发布。
    
      
    
- **SSL 2.0（1995）**：随 Netscape 1.1 发布，存在缺乏完整性校验、易遭受降级攻击等重大漏洞。
    
      
    
- **SSL 3.0（1996）**：改进了设计，但仍保留了不安全的向后兼容性；最终在 2014-2015 年因 **POODLE 攻击** 被正式废弃（RFC 7568）。
    
      
    
- **TLS 1.0（1999, RFC 2256）与 TLS 1.1（2006, RFC 4346）**：IETF 正式标准化并更名为 TLS（Transport Layer Security），后因支持 RC4、MD5 等破损算法于约 2020 年被全面废弃。
    
      
    

#### 2. TLS 1.2（2008）vs TLS 1.3（2018）全面对比

讲义对现代主流的 TLS 1.2 与现代标准 TLS 1.3 进行了深度剖析与对比：

  

|**比较维度**|**TLS 1.2 PDF**|**TLS 1.3（现代黄金标准） PDF**|
|---|---|---|
|**握手延迟**|**2 个往返（2-RTT）**，较慢|**1 个往返（1-RTT）**，支持 0-RTT 快速恢复，连接速度提升高达 75%|
|**密钥交换**|支持 RSA 或 (EC)DHE；静态 RSA **不提供**前向安全性（PFS）|**强制使用 (EC)DHE**；彻底废除静态 RSA，**默认强制启用前向安全性（PFS）**|
|**加密套件**|庞大繁杂，遗留大量弱加密模式（如 CBC 模式、RC4、3DES、Export 弱密钥）|**大幅精简**，仅允许现代 **AEAD 认证加密**（如 AES-GCM、ChaCha20-Poly1305）|
|**隐私保护**|ClientHello 与握手阶段暴露过多明文元数据|支持 **加密握手扩展与加密 SNI（Encrypted ClientHello）**，防止主机名泄露|
|**抗降级能力**|容易受到协议回退攻击（Fallback Attacks）|内置强大的抗降级机制|

### 四、 协议回退/降级攻击（Fallback / Downgrade Attacks）

- **核心机制**：攻击者在客户端和服务器之间充当中间人（MitM），故意阻断高版本协议（如 TLS 1.2）的握手尝试，迫使兼容旧版本的客户端**自动回退（Fall back）到有漏洞的旧版本（如 SSL 3.0）**。
    
      
    
- **危害与典型案例**：
    
      
    - **POODLE 攻击**：迫使通信回退至 SSL 3.0，利用其 CBC 模式的填充预言机漏洞（Padding Oracle）解密敏感会话 Cookie。
        
          
        
    - **核心启示**：攻击者往往不需要暴力破解新型强加密算法，只需利用系统的“向后兼容性”强制其降级使用已破损的旧加密。
        
          
        

### 五、 HTTPS 安全连接的底层三要素与握手流程

HTTPS 通过密码学保障三大安全支柱：

  

1. **机密性（Confidentiality）**：握手完成后，使用协商出的对称密钥（AES-GCM 等）加密所有应用层数据（密码、表单、URL 路径等）。注：IP、端口、流量大小与时序等元数据仍可见。
    
      
    
2. **完整性（Integrity）**：通过 AEAD 模式或 MAC 标签确保传输数据未被第三方篡改。
    
      
    
3. **身份认证（Authentication）**：客户端通过数字证书（X.509）验证服务器真实身份，防止中间人冒充。
    
      
    

#### 证书验证六步闭环（Certificate Validation）

浏览器在接收到服务器证书后执行以下链条验证：

  

$$\text{获取证书} \to \text{使用受信任 CA 公钥验证数字签名} \to \text{检查颁发机构（CA）是否在内置受信任库中} \to \text{比对访问域名是否匹配} \to \text{检查有效期（未过期/未生效）} \to \text{判定是否可信}$$

### 六、 信任模型对比：信任网（WoT）vs 公钥基础设施（PKI）

讲义系统对比了两种解决“公钥归属真实性”的信任模型：

  

#### 1. 信任网（Web of Trust - WoT）

- **机制**：去中心化、基于对等信任（Peer-to-peer）。用户相互签署对方的公钥（“我认为这个密钥属于 Alice”），信任可传递。
    
      
    
- **代表应用**：PGP（Pretty Good Privacy）、GnuPG、极客“密钥签名派对（Key signing parties）”。
    
      
    
- **缺陷**：扩展性极差（Scalability 差，无法服务全球数十亿网民）、缺乏统一信任标准、撤销透明度低。
    
      
    

#### 2. 公钥基础设施（Public Key Infrastructure - PKI）

- **机制**：中心化、分层树状信任架构。
    
      
    - **根 CA（Root CA / 信任锚）**：预装在操作系统和浏览器内部。
        
          
        
    - **中间 CA（Intermediate CA）**：由根 CA 签发并代理信任。
        
          
        
    - **终端证书（End-entity Certificate）**：具体网站或服务使用的证书。
        
          
        
- **PKI 的现实挑战与风险**：
    
      
    - **单点信任漏洞**：系统默认信任受信任库中的所有 CA，任何一家合规性差的 CA 被黑客攻破或误签发证书，都可能导致针对任意域名的中间人攻击。
        
          
        
    - **撤销管理成本高**：依赖 CRL（证书吊销列表）或 OCSP 查询。
        
          
        

### 七、 应用层授权与认证：OAuth 与 OpenID

#### 1. OAuth（开放授权 - 授权与委托访问）

- **核心理念**：**“代理钥匙（Valet Key）”模型**。允许用户授权第三方应用访问其受保护资源（如让应用读取 Google 联系人），而**无需将主密码透露给该应用**。
    
      
    
- **交互机制**：用户登录授权服务器（如 Google）并同意授权 $\to$ 授权服务器向客户端发放短期 Access Token $\to$ 客户端凭借 Token 访问资源服务器。
    
      
    
- **OAuth 常见安全风险**：
    
      
    - **钓鱼伪造登录页（Phishing）**；
        
          
        
    - **过度授权（Over-scoped tokens）**：申请了超出业务需要的权限（如仅需读取个人资料却申请了 Drive 读写权限）；
        
          
        
    - **令牌泄露与重放（Token Leakage & Replay）**：Token 被 XSS 或网络嗅探窃取后被攻击者复用；
        
          
        
    - **不安全的回调重定向（Insecure Redirect URIs）**。
        
          
        

#### 2. OAuth vs OpenID（授权 vs 身份认证）

- **OpenID（身份认证 Authentication）**：“_请给我一份公证信，证明你是谁_” $\to$ 关注**身份识别（Identity）**。
    
      
    
- **OAuth（授权 Authorization）**：“_请给我一把有限权限的代客钥匙，以便我帮你开门取东西_” $\to$ 关注**资源访问权限（Delegation）**。
    
      
    

### 八、 认证攻击与渗透测试（Authentication Attacks & Pen Testing）

1. **认证攻击形态**：
    
      
    - **协议降级攻击（Downgrade Attacks）**；
        
          
        
    - **令牌窃取与重放（Token Replay）**：利用 XSS、不安全本地存储或日志泄露窃取 JWT / OAuth Token 并重放；
        
          
        
    - **会话劫持与 MitM / 浏览器中间人（MitB，如恶意插件/木马）**；
        
          
        
    - **MFA 疲劳轰炸（Push Bombing）与凭证钓鱼**。
        
          
        
2. **渗透测试与众包安全（Penetration Testing）**：
    
      
    - **定义**：对系统进行模拟攻击以主动发现安全隐患。
        
          
        
    - **众包安全**：通过公开的 **漏洞赏金计划（Bug Bounty Programs）** 邀请安全社区共同测试加固系统。