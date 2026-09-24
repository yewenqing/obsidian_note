你的计划整体方向是对的，而且对于 **5 天 COMP6841 类安全项目**来说，范围控制得比较合理。但是我建议做几个调整，否则容易出现：

1. 功能很多但安全分析不足；
    
2. modifier 做太多导致调试时间爆炸；
    
3. report 没有足够理论深度。
    

你的项目最大价值不是“做一个外挂”，而是：

> **利用 MITM Proxy 分析 Minecraft client-server trust boundary，并展示 packet manipulation 风险。**

所以计划应该围绕这个主题组织。

---

## 目前计划评价

你的版本：

```
7/22
建立可持续连接的代理

7/23
完成数据包过滤方法
打印重要数据包
捕获特定数据包

7/23-7/24
modifier

7/24
修改测试
    chat
    position
    item
    block

7/25
report
```

问题：

### 问题1：modifier 时间太短

你现在已经遇到：

- keepAlive
    
- compression
    
- state
    
- error handling
    

这些 protocol 问题。

如果以后修改：

- entity packet
    
- chunk packet
    
- inventory packet
    

复杂度会上升。

---

### 问题2：缺少安全分析部分

现在看起来像：

> 我做了一个 proxy，可以改 packet

但是安全课老师更想看到：

> 为什么这些 packet 可以被修改？服务器为什么信任这些数据？如何防御？

所以应该增加：

- threat model
    
- attack scenario
    
- defense discussion
    

---

# 我建议改成：

## Day 1 (7/22)

### Proxy Infrastructure ✅

目标：

完成稳定 MITM proxy。

功能：

- Client → Proxy → Server
    
- Server → Proxy → Client
    
- packet forwarding
    
- error handling
    
- compression handling
    
- state synchronization
    

输出：

```
Working Minecraft MITM Proxy
```

---

## Day 2 (7/23)

### Packet Monitoring & Analysis

不要只是打印。

建议分类：

### Player action packets

Client → Server:

```
position
position_look
arm_animation
block_dig
block_place
chat
```

### Server information packets

Server → Client:

```
entity_velocity
entity_move
block_change
set_slot
window_items
```

建立：

```
Packet Analyzer
```

例如：

输出 JSON：

```json
{
 "timestamp":123456,
 "direction":"C->S",
 "packet":"position",
 "data":{
    "x":10,
    "y":64,
    "z":20
 }
}
```

这个对于 report 很重要。

---

## Day 3 (7/24 上午)

### Packet Modifier Framework

不要直接写：

```javascript
if(packet=="xxx")
```

建议设计：

```
modifier/

chat.js
movement.js
inventory.js
block.js
```

例如：

```javascript
modifier.apply(
    direction,
    packet,
    data
)
```

以后扩展容易。

---

## Day 3 (7/24 下午)

### Attack Demonstrations

这里我建议减少数量。

你的：

> 1. chat 修改
>     
> 2. position 修改
>     
> 3. item 数量修改
>     
> 4. block rendering 修改
>     

四个里面：

---

## 必做 1：Chat modification ⭐⭐⭐⭐⭐

简单，效果明显。

攻击：

Client:

```
hello
```

Proxy:

```
[MITM] hello
```

展示：

> Client data can be modified before server processing.

---

## 必做 2：Movement modification ⭐⭐⭐⭐⭐

这是最有安全价值的。

例如：

客户端：

```
position:
x=10
```

Proxy:

```
x=100
```

研究：

- speed hack
    
- fly hack
    
- position spoofing
    

对应防御：

server-side movement validation

---

## 可选 3：Inventory modification ⭐⭐⭐

你的想法：

> S→C item 数量修改

可行。

比如：

服务器：

```
diamond x1
```

Proxy:

```
diamond x64
```

但是问题：

Minecraft inventory 有很多同步机制：

- click window
    
- transaction
    
- confirm transaction
    

容易花时间。

---

## 不建议 4：Block rendering modification

原因：

chunk 数据非常复杂。

涉及：

- chunk_data
    
- palette
    
- block states
    
- compression
    

5 天项目风险高。

替代：

做：

```
block_change
```

简单：

服务器：

```
stone block
```

Proxy:

```
diamond block
```

效果类似。

---

# 最终 Demo 建议

保留三个：

|攻击|Packet|安全意义|
|---|---|---|
|Chat spoofing|chat|数据完整性|
|Movement manipulation|position|client trust|
|Block/item manipulation|block_change/set_slot|server validation|

三个足够拿高分。

---

# Report 结构建议

你的报告不要按开发过程写。

按安全研究写：

---

## 1. Introduction

问题：

Minecraft Client-Server trust model

---

## 2. Architecture

图：

```
Minecraft Client

      |

MITM Proxy

      |

Minecraft Server
```

说明：

Proxy 可以：

- observe
    
- modify
    
- replay
    

---

## 3. Threat Model

攻击者：

```
Network attacker controlling proxy
```

能力：

- read packets
    
- modify packets
    
- delay packets
    

---

## 4. Experiments

### Experiment 1

Chat manipulation

### Experiment 2

Movement spoofing

### Experiment 3

Block state manipulation

---

## 5. Security Analysis

讨论：

为什么成功？

因为：

- client sends untrusted information
    
- server accepts some client state
    

防御：

- server-side validation
    
- movement checks
    
- inventory verification
    

---

# 我会调整你的时间表：

|日期|任务|
|---|---|
|7/22|稳定 Proxy + protocol handling|
|7/23 上午|Packet logger/analyzer|
|7/23 下午|Modifier framework|
|7/24 上午|Chat + movement attack|
|7/24 下午|Block/item experiment + screenshots|
|7/25|Report + diagrams|

---

总体评价：

你的方向选得很好。相比开发 Minecraft hack client，这个方案更像真正的安全研究项目，而且 5 天可控。

最大的改进点：

> 不要追求修改很多 packet，而要设计几个有代表性的攻击实验，并解释背后的 trust boundary 问题。

这样报告会比“我实现了一个外挂”高级很多。