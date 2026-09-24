

## Introduction
本项目通过开发了一个轻量级的JS Minecraft MitM proxy。该代理可以对传输中未开启online 加密模式的Minecraft Java edition 数据包进行解析，拦截或改写。基于此工具，本项目实现了三种PoC：通过修改聊天数据包实现篡改聊天消息内容、通过伪造位置数据包实现短距离瞬移，以及向客户端发送虚假数据包使客户端误以为获得指定物品。本报告将基于此代理和以上功能以及实验结果分析和探讨MitM 攻击和客户端-服务端信任边界的基本概念。

灵感来源：
我在查看作业说明时一开始的想法是想做Minecraft 的gamehacking 但和导师汇报了这个想法后我发现了一些问题，因为Minecraft 的Mod社区非常活跃，其中也包括一些作弊Mod, 如果我选择单纯的Game Hacking 可能与制作一款Mod 没有区别，也很难在项目中体现课程所涉及到的知识点。于是在和导师讨论后我觉得将项目目标改为开发一个Minecraft proxy， 通过研究和修改Minecraft的协议数据包达成某些Game Hacking的功能，并同时研究MitM 攻击和客户端-服务端信任边界问题。

## Background

### MitM
Minecraft 是典型的 Client-Server 架构游戏，客户端负责输入操作和渲染游戏界面，服务器则负责同步世界和玩家状态，客户端和服务器之间通过TCP协议建立连接.

MitM 的核心原理是攻击者秘密插入两个通信端点之间，让双方误以为在直接对话，从而实现拦截，窃听或篡改数据。在本项目中，我通过设置了一个proxy实现了拦截，窃听，伪造或篡改客户端与服务器之间的TCP数据包的功能，如果开启了Minecraft Server 的online mode 数据包会被加密，此时如果想建立proxy 则需要为proxy 也进行正版认证，而如果关闭了online mode 数据包则将以明文传输，这种情况下建立代理和进行中间人攻击将变得简单许多。

### Minecraft Protocol
Minecraft 的 协议数据包种类非常多样且复杂，我使用了开源库node-minecraft-protocol 和minecraft-data 来处理和解析协议，本项目主要聚焦于以下3种比较有代表性的数据包：
用于发送chat 的 `chat_message`
用于更新位置的 `position`
用于设置客户端物品栏的 `set_slot`

### Trust Boundary
在 Minecraft 的网络通信中，对于服务器来说信任边界画在**客户端和服务端的通信接口**上，因为客户端的代码运行在玩家本地电脑上，玩家可以随意修改内存、反编译游戏代码，或者使用外挂。所以服务器对所有从客户端发来的数据包都会根据数据包的类型进行不同程度的权限认证和合法性验证，但对于offline mode 的客户端来说却并不会对从服务器发来的数据包进行太多的校验，这在本项目中进行的几个实验中也有体现。

## Design and Implementation
### 项目架构
本项目实现的是一个介于Minecraft 客户端和服务端之间的代理
`Client <--> Proxy <--> Server`
从客户端发往服务器的数据包和从服务器发往客户端的数据包都会经过proxy转手，此时proxy可以对经过的数据包进行记录，拦截，篡改或伪造。

本项目使用了开源库`node-minecraft-protocol` 和 `minecraft-data`

Proxy的具体项目架构如下：
```
./src
├── C2Smodifier.js
├── command.js
├── filter.js
├── log.js
├── modifier.js
├── proxy.js

```
其中 `proxy.js` 为proxy主程序，运行后会启动proxy，监听客户端和服务器的端口并转发和分析收到的包。
`modifier.js` 和 `C2Smodifier.js` 分别实现了从服务端到客户端和从客户端到服务端的数据包构建和发送逻辑，使其可以在`proxy.js` 和 `command.js` 中被调用。
`command.js` 实现了如果玩家在游戏内聊天 输入 `# <command> <args>` 就可以调用`modifier.js` 和 `C2Smodifier.js` 构造并发送数据包以达成一些命令效果，在本项目中我实现了两个命令：通过伪造`position` 数据包实现短距离瞬移，以及向客户端发送虚假`set_slot`数据包使客户端误以为获得指定物品，以及可以修改玩家的`chat_message` 数据包实现篡改玩家发言的效果
```
Packet Listener

↓

Command Dispatcher

↓

Modifier

↓


Packet write
```

### Module design
- **`proxy`**:  

  - **功能**: 监听客户端连接`mc.createServer`，为每个客户端创建对应到目标服务器的 `mc.createClient` 连接。  

  - **接口/交互**: 监听 `client.on('packet', (data, meta) => ...)` 与 `server.on('packet', ...)`，并通过 `server.write(meta.name, data)` / `client.write(meta.name, data)` 转发。参见 proxy.js。  

![[Pasted image 20260726094158.png]]
  

- **`ModifierFramework` modifier.js**:  

  - **功能**: 为服务端->客户端方向提供封装 API，并做协议层面数据构造
  - **主要方法**: `sendPacket(name, payload)`, `sendChat()`, `sendPosition()`, `grantItem()` 等。  
![[Pasted image 20260726094759.png]]

  

- **`command` (command.js)**:  

  - **功能**: 为了更方便的游戏内演示，在这里设置了基于游戏内聊天消息的命令接口，从聊天包中解析以 `#` 开头的命令（如 `#port <distance>`、`#give <item> <slot>`），并调用`ModifierFramework` 构造并发送对应包以执行相关命令
 ![[Pasted image 20260726095258.png]]

![[Pasted image 20260726095157.png]]

## Experimental Evaluation
All experiments were conducted using Minecraft Java Edition 1.20.1. A Minecraft server was configured in **offline mode**, allowing network traffic to remain unencrypted. The developed JavaScript proxy was deployed between the client and the server, forwarding packets transparently while selectively intercepting and modifying packets according to the implemented proof-of-concept .

The client connected to the proxy instead of directly connecting to the server. During gameplay, the proxy logged all packets exchanged between both parties and modified selected packets to evaluate different aspects of Minecraft's client-server trust model.

### Proxy
First we start Minecraft server and proxy
![[Pasted image 20260726100047.png]]![[Pasted image 20260726100105.png]]

Then, we connect client to proxy's host and port 
![[Pasted image 20260726100240.png]]
When a player joins the game, the proxy forwards data packets and prints them in the terminal.
![[Pasted image 20260726100458.png]]


### Chat Manipulation
#### Objective: 
Evaluate whether a MitM attacker can modify a player's chat message without server detecting the modification.
#### Method:  
The proxy intercepted every outgoing `chat_message` packet before forwarding it to the server. When the message content matched a predefined string, the payload was modified before transmission.
#### Example:
```
Original:
test message

Modified:
Your message is modified!
```

#### Result
![[Pasted image 20260726100922.png]]
![[Pasted image 20260726102858.png]]
![[Pasted image 20260726100934.png]]
![[Pasted image 20260726115757.png]]
The server and every connected player received the modified message instead of the message typed by the player.
#### Analysis:  
The experiment demonstrates that chat packets can be modified transparently during transmission. Since chat messages originate entirely from the client, the server has no mechanism to determine what the player originally typed. Consequently, the modified packet is treated as legitimate user input.

This experiment confirms that a MitM attacker is capable of altering application-layer data without modifying either the client or the server.

### Position Spoofing
#### Objective: 
  Investigate whether player position packets can be modified to perform teleportation.
#### Method:
Implemented a custom proxy command `#port <distance>`. After receiving the command, the proxy will create a S-->C position packet send to client, after the client updates its location information, it will send the new location information to the server.

Two distances were tested:

* 10 blocks
* 100 blocks
#### Result:

#####  Short-distance teleport (10 blocks)
`#port 10`
![[Pasted image 20260726102453.png]]
After executing `#port 10`, the player was successfully teleported approximately 10 blocks forward.
![[Pasted image 20260726102511.png]]
#####  Long-distance teleport (100 blocks)
![[Pasted image 20260726103447.png]]
Executing `#port 100` initially caused the client to appear at the target location for a brief moment. Shortly afterwards, the player was returned to the original position.
![[Pasted image 20260726103528.png]]
The server log reported

```
Player moved too quickly!
```
![[Pasted image 20260726103652.png]]

#### Analysis:
Unlike chat messages, movement packets are not blindly trusted by the server. The server continuously validates player movement by checking displacement and movement speed. Small coordinate changes remain within the acceptable threshold and are accepted, whereas larger jumps exceed the validation threshold and are rejected.


### Fake Inventory Injection
#### Objective:
Investigate whether forged inventory packets can convince the client that it owns an item which does not exist on the server.
#### Method:
The proxy generated a forged `set_slot` packet and sent it directly to the client without informing the server.
#### Result:
Try command `give diamond_axe 37`
![[Pasted image 20260726104941.png]]
Immediately after executing the command, a diamond axe appeared in the selected inventory slot.
![[Pasted image 20260726104953.png]]
![[Pasted image 20260726111555.png]]
The client also displayed the normal diamond axe mining animation and mining speed prediction.

However, actual gameplay behaviour remained unchanged.

* Mining speed was equivalent to using an empty hand.
* Stone blocks were not instantly broken.
* No cobblestone was dropped.

When attempting to move the forged item inside the inventory, the item immediately disappeared.
#### Analysis:
The fake item only existed within the client's local inventory view. Since the server never recorded ownership of the injected item, gameplay calculations continued to use the authoritative server inventory.

Moving the item triggered a `Container Click` packet from the client. The server then responded with a `Container Set Content` packet containing the authoritative inventory state, causing the forged item to disappear.

This experiment demonstrates that inventory rendering is client-controlled, while inventory ownership remains entirely server-authoritative.
![[Pasted image 20260726113617.png]]

## Security Analysis
### MitM attack
The developed proxy demonstrates that when Minecraft communication is unencrypted, an attacker positioned between the client and server can transparently inspect, modify, and inject protocol packets.

Unlike memory or game modification, MitM attacks do not require modification of either party's endpoint. The attacker exploits the communication channel itself. This highlights the importance of encrypted communication and endpoint authentication in multiplayer games.

While this project only implemented three proof-of-concept attacks, theoretically, the same framework can be extended to manipulate many other types of packets.
### Trust boundary
The three experiments reveal that Minecraft does not apply the same trust model to every packet type.
* Chat: The server assumes that chat messages are legitimate user input and therefore accepts modified packets without additional verification.
* Position: Player movement is accepted only after validation. Although the client proposes its current position, the server independently checks whether the reported movement is physically reasonable.
* Inventory: Inventory ownership is never determined by the client. Even though the client displays the injected item correctly, all gameplay logic continues to rely on the server's inventory state.
These results illustrate that Minecraft employs different levels of trust depending on the gameplay feature being synchronised.

### Security Implications

First, disabling encryption significantly lowers the barrier to entry for network-based attacks. Without encrypted communication, publicly available protocol libraries can be used to inspect and modify application-layer packets.

Second, not every successful packet modification constitutes a successful attack. Manipulating client rendering might alter a user's perception of the game but doesn't necessarily affect the authoritative game state maintained by the server.

Finally, experiments demonstrate the effectiveness of the server-authoritative architecture. Critical game information is protected because the server independently maintains the authoritative state, rather than relying on information provided by the client.

## Reflection
### What could have been improved
The proxy was evaluated only in offline mode. Servers using online mode were not studied.

Only three representative packet types were evaluated. Other protocol components, such as state synchronization, block updates, and combat mechanics, may have different trust characteristics.

Because the project underwent several direction changes during implementation, the project content and analysis may be somewhat scattered and weak.


### What challenge I faced
The main challenge of this project lies in understanding the Minecraft protocol. The Minecraft protocol varies depending on the version, making data packets difficult to construct. During development, I repeatedly encountered bottlenecks due to different data packet names or invalid data packets. Furthermore, careful handling of protocol states and connection management is necessary to ensure that the proxy can selectively modify data packets while forwarding normal game traffic.

## Conclusion 

This project investigated the feasibility of MitM attacks against Minecraft Java Edition by developing a lightweight JavaScript proxy. This proxy can intercept and modify unencrypted network traffic. The project does not focus on implementing game hacking functionality, but rather uses packet manipulation as a practical method to study Minecraft's client-server trust model.

We successfully implemented three proof-of-concept attacks: chat messages were transparently modified before reaching the server; movement packets were manipulated to achieve limited delivery; and forged inventory packets caused the client to display items not present on the server. These demonstrations show that different types of packets have different security properties and verification mechanisms.

Experimental results indicate that Minecraft applies different levels of trust mechanisms based on the type of synchronization information. Client-generated chat messages are generally accepted without verification, movement packets require server-side verification, and inventory ownership is entirely determined by the server. These findings suggest that a successful man-in-the-middle attack does not necessarily mean the leakage of authoritative game state, but may only affect the client's perception of the game.

Although this implementation focuses on a limited number of packet types and offline server configurations, the project demonstrates how protocol analysis can be used to explore practical network security concepts, including network protocol security, man-in-the-middle attacks, and client-server trust boundaries. Future work could extend the proxy to more packet types, investigate encrypted online communication, or apply similar techniques to other multiplayer games.