
# COMP6441 Week 9 - Risk & Threat Modelling Notes

## 1. Governance, Risk, and Compliance (GRC)

- **Governance（治理）**：确保以符合道德规范且高效的方式实现业务目标（如制定政策和程序）。
    
- **Risk（风险）**：识别并减轻对资产与运营的潜在威胁（如风险评估、风险管理）。
    
- **Compliance（合规）**：遵守法律法规、标准和内部政策（如 GDPR、ISO27001、SOC2、NIST、PCI DSS）。
    

## 2. Engineering vs. GRC

- **工程团队（战术/系统导向）**：负责构建安全可扩展的系统、实施控制措施、事件响应与性能保障。
    
- **GRC 团队（战略/政策导向）**：负责将系统与法律/政策对齐、供应商风险管理、合规审计及培训。
    
- **共同责任（Shared Ownership）**：每一项控制措施（Control）都需要明确的所有者、实施者以及生产环境证明（Evidence）。
    

## 3. Failure-Aware Design & Protocols（防故障设计与协议）

- **Fail-Safe 原则**：默认拒绝策略（Default Deny）、自动化恢复流程、测试故障保护条件。
    
- **测量正确的属性**：借鉴三哩岛事故教训，系统应直接测量关心的核心属性，而非替代指标（Proxy）。
    
- **失能开关（Dead Man Switch）**：确保人员失能或故障发生时系统自动进入安全状态。
    
- **Horton 原则**：验证消息/指令真正意图与实际状态（State），而不仅仅是信号本身（Signal）。
    
- **可观测性（Observability）**：包含监控（Monitoring）、日志（Logging）、追踪（Tracing）和可视化（Visualization）。
    
- **移安全于早期（Shift-Left Security）**：在架构设计阶段融入安全思考，避免后期补丁式安全（Bolt-On Security）。
    

## 4. Common Security Design Framework & STRIDE

- **Step 1: 枚举资产（Enumerate Assets）**：包含数据（Data）、系统（Systems）、人员（People）和运营流程（Operations）。
    
- **Step 2: 明确威胁模型与信任边界（Threat Model & Trust Boundaries）**：识别潜在攻击者并应用 **STRIDE** 框架分析数据流：
    
    - **S**poofing（身份欺骗）
        
    - **T**ampering（篡改）
        
    - **R**epudiation（抵赖）
        
    - **I**nformation Disclosure（信息泄露）
        
    - **D**enial of Service（拒绝服务）
        
    - **E**levation of Privilege（特权提升）
        
- **Step 3: 风险评估与处理（List Risks & Treatments）**：依据可能性（Likelihood）与影响（Impact）对风险分类；处理策略包含降低（Mitigate）、接受（Accept）、转移（Transfer）和规避（Avoid）。
    
- **Step 4: 实施控制措施与安全原则（Controls & Principles）**：落实最小权限（Least Privilege）、纵深防御（Defense in Depth）、默认安全（Fail-safe defaults）和职责分离（Separation of duties）。
    

![](https://www.gstatic.com/images/branding/productlogos/keep_2026/v2/web-96dp/logo_keep_2026_color_2x_web_96dp.png)Google Keep

COMP6441 Week 9 - Risk & Threat Modelling Notes

UNSW COMP6441/COMP6841 Week 9 Lecture Notes: Risk & Threat Modelling 1. Governance, Risk, and Compliance (GRC) - Governance: Ensuring business objectives are met ethically and efficiently (e.g., policies, procedures). - Risk: Identifying and mitigating potential threats to assets and operations (e.g., risk assessment, management). - Compliance: Adhering to laws, regulations, and standards (e.g., GDPR, ISO27001, SOC2, NIST, PCI DSS). 2. Engineering vs. GRC - Engineering (Tactical/Systems-focused): Builds secure systems, implements controls, handles incident response, and ensures scalability. - GRC (Strategic/Policy-focused): Aligns systems with legal frameworks, manages vendor risks, conducts audits, and oversees training. - Shared Ownership: Every control needs an owner, an implementer, and verifiable production evidence. 3. Failure-Aware Design & Protocols - Fail-Safe Principles: Default-deny policies, automated recovery, and testing fail-safe conditions. - Measure the Right Property: Lessons from Three Mile Island highlight measuring the actual state of interest rather than a proxy signal. - Dead Man Switch: Ensures failures result in a safe state. - The Horton Principle: Authenticate what is meant (the actual state/outcome) rather than what is being said (the signal/command). - Observability: Incorporates monitoring, logging, tracing, and visualization to ensure failures are visible. - Shift-Left Security: Engage early in design discussions using soft power; avoid "bolt-on" security. 4. Common Security Design Framework & Threat Modelling - Step 1: Enumerate Assets: Data, Systems, People, and Operations. - Step 2: Define Threat Model & Trust Boundaries: Identify threat actors, trust boundaries, and use STRIDE (Spoofing, Tampering, Repudiation, Information Disclosure, Denial of Service, Elevation of Privilege). - Step 3: List & Prioritize Risks: Matrix of Likelihood vs. Impact. Risk Treatments: Mitigate, Accept, Transfer, Avoid. - Step 4: Controls & Principles: Apply Least Privilege, Defense in Depth, Fail-Safe Defaults, and Separation of Duties.