# Analyzing Minecraft Protocol Integrity and Client-Server Trust Boundaries via a Custom JavaScript MitM Proxy

## 1.Introduction
This project developed a lightweight JS Minecraft MitM proxy. This proxy can parse, intercept, or rewrite Minecraft Java Edition data packets that are not in online encryption mode during transmission. Based on this tool, this project implemented three Proofs of Concept (PoCs): modifying chat data packets to tamper with chat message content, forging location data packets to achieve short-distance teleportation, and sending fake data packets to the client to mislead the client into believing they have obtained a specific item. This report will analyze and discuss the basic concepts of MitM attacks and client-server trust boundaries based on this proxy, the above functions, and experimental results.

Inspiration: When reviewing the assignment instructions, my initial idea was to do game hacking in Minecraft. However, after reporting this idea to my tutor, I discovered some problems. Because the Minecraft mod community is very active, including some cheat mods, if I chose pure game hacking, it might be no different from creating a mod, and it would be difficult to reflect the knowledge points covered in the course within the project. After discussing with my supervisor, I decided to change the project goal to developing a Minecraft proxy. This would involve studying and modifying Minecraft's protocol data packets to achieve certain game hacking functions, while also researching MitM attacks and client-server trust boundary issues.
## 2.Background
### 2.1 MitM
Minecraft is a typical client-server architecture game. The client is responsible for input and rendering the game interface, while the server is responsible for synchronizing the world and player state. The client and server establish a connection via the TCP protocol.

The core principle of MitM is that an attacker secretly inserts themselves between two communication endpoints, making both parties believe they are communicating directly, thereby intercepting, eavesdropping, or tampering with data. In this project, I implemented the function of intercepting, eavesdropping, forging, or tampering with TCP packets between the client and server by setting up a proxy. If Minecraft Server's online mode is enabled, the data packets are encrypted. In this case, if you want to establish a proxy, you also need to authenticate the proxy. If online mode is disabled, the data packets are transmitted in plaintext. In this case, establishing a proxy and carrying out man-in-the-middle attacks becomes much simpler.

### 2.2 Minecraft Protocol
Minecraft's protocol data packets are highly diverse and complex. I used the open-source libraries node-minecraft-protocol and minecraft-data to process and parse the protocol. This project mainly focuses on the following three representative data packets:
* `chat_message` for sending chat
* `position` for updating position
* `set_slot` for setting the client's inventory

Before implementing each proof-of-concept attack, it was first necessary to determine which Minecraft packets controlled the desired behaviour. Although the Minecraft protocol is publicly documented, it contains hundreds of packet types, making it impractical to inspect every packet manually.

To identify relevant packets, the proxy was initially configured to log the name and direction of every packet exchanged between the client and server during gameplay. Specific in-game actions, such as sending a chat message, moving the player or opening the inventory, were then performed individually while observing the corresponding packet sequence.

By correlating gameplay actions with logged packet names, candidate packets responsible for each action were identified. These packets were subsequently modified or replayed inexperiments to verify their behaviour before implementing the final proof-of-concept attacks.
### 2.3 Trust Boundary
In Minecraft network communication, the trust boundary for the server is drawn at the client-server communication interface. Because the client's code runs on the player's local computer, the player can freely modify memory, decompile game code, or use cheats. Therefore, the server performs different levels of authorization and validity verification on all data packets sent from the client, depending on the data packet type. 
## 3.Design and Implementation
### 3.1 Project Architecture

This project implements a proxy between the Minecraft client and server.

`Client <--> Proxy <--> Server`
Data packets sent from the client to the server and from the server to the client are handled by the proxy. The proxy can record, intercept, tamper with, or forge these packets.

This project uses the open-source libraries `node-minecraft-protocol` and `minecraft-data`.

The specific project architecture of the proxy is as follows:

```
./src
├── C2Smodifier.js
├── command.js
├── filter.js
├── log.js
├── modifier.js
├── proxy.js

```
The `proxy.js` is the main proxy program. Running it starts the proxy, listens on the client and server ports, and forwards and analyzes received packets.

`modifier.js` and `C2Smodifier.js` implement the logic for constructing and sending data packets from the server to the client and from the client to the server, respectively, allowing them to be called from `proxy.js` and `command.js`.

`command.js` implements a feature where typing `# <command> <args>` in in-game chat calls `modifier.js` and `C2Smodifier.js` to construct and send data packets to achieve command effects. In this project, I implemented two commands: short-distance teleportation via a forged `position` data packet, sending a fake `set_slot` data packet to the client to mislead them into thinking they've obtained a specific item, and modifying the player's `chat_message` data packet to tamper with their messages.

```
Packet Listener
↓
Command Dispatcher
↓
Modifier
↓
Packet write
```

### 3.2 Module design

- **`proxy`** **proxy.js**:
- **Function**: Listens for client connections to `mc.createServer` and creates a corresponding `mc.createClient` connection to the target server for each client. - **Interface/Interaction**: Listens for `client.on('packet', (data, meta) => ...)` and `server.on('packet', ...)`, and forwards the request via `server.write(meta.name, data)` / `client.write(meta.name, data)`. See proxy.js.

![[Pasted image 20260726094158.png]]

- **`ModifierFramework` modifier.js**:
- **Functionality**: Provides a wrapper API for the server-to-client direction and performs protocol-level data construction.

- **Main Methods**: `sendPacket(name, payload)`, `sendChat()`, `sendPosition()`, `grantItem()`. ![[Pasted image 20260726094759.png]]

- **`command` command.js**:

- **Function**: For easier in-game demonstration, a command interface based on in-game chat messages is set up here. It parses commands starting with `#` from chat packets (such as `#port <distance>`, `#give <item> <slot>`), and calls `ModifierFramework` to construct and send the corresponding packets to execute the relevant commands.

![[Pasted image 20260726095258.png]]

![[Pasted image 20260726095157.png]]
## 4.Experimental Evaluation
All experiments were conducted using Minecraft Java Edition 1.20.1. A Minecraft server was configured in offline mode, allowing network traffic to remain unencrypted. The developed JavaScript proxy was deployed between the client and the server, forwarding packets transparently while selectively intercepting and modifying packets according to the implemented proof-of-concept .

The client connected to the proxy instead of directly connecting to the server. During gameplay, the proxy logged all packets exchanged between both parties and modified selected packets to evaluate different aspects of Minecraft's client-server trust model.

### 4.1 Proxy
First we start Minecraft server and proxy
![[Pasted image 20260726100047.png]]![[Pasted image 20260726100105.png]]

Then, we connect client to proxy's host and port 
![[Pasted image 20260726100240.png]]
When a player joins the game, the proxy forwards data packets and prints them in the terminal.
![[Pasted image 20260726100458.png]]


### 4.2 Chat Manipulation
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

### 4.3 Position Spoofing
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


### 4.4 Fake Inventory Injection
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

## 5.Security Analysis

### 5.1 MitM attack
The developed proxy demonstrates that when Minecraft communication is unencrypted, an attacker positioned between the client and server can transparently inspect, modify, and inject protocol packets.

Unlike memory or game modification, MitM attacks do not require modification of either party's endpoint. The attacker exploits the communication channel itself. This highlights the importance of encrypted communication and endpoint authentication in multiplayer games.

While this project only implemented three proof-of-concept attacks, theoretically, the same framework can be extended to manipulate many other types of packets.
### 5.2 Trust boundary
The three experiments reveal that Minecraft does not apply the same trust model to every packet type.
* Chat: The server assumes that chat messages are legitimate user input and therefore accepts modified packets without additional verification.
* Position: Player movement is accepted only after validation. Although the client proposes its current position, the server independently checks whether the reported movement is physically reasonable.
* Inventory: Inventory ownership is never determined by the client. Even though the client displays the injected item correctly, all gameplay logic continues to rely on the server's inventory state.
These results illustrate that Minecraft employs different levels of trust depending on the gameplay feature being synchronised.

### 5.3 Security Implications

First, disabling encryption significantly lowers the barrier to entry for network-based attacks. Without encrypted communication, publicly available protocol libraries can be used to inspect and modify application-layer packets.

Second, not every successful packet modification constitutes a successful attack. Manipulating client rendering might alter a user's perception of the game but doesn't necessarily affect the authoritative game state maintained by the server.

Finally, experiments demonstrate the effectiveness of the server-authoritative architecture. Critical game information is protected because the server independently maintains the authoritative state, rather than relying on information provided by the client.

## 6.Reflection

### 6.1 What could have been improved
The proxy was evaluated only in offline mode. Servers using online mode were not studied.

Only three representative packet types were evaluated. Other protocol components, such as state synchronization, block updates, and combat mechanics, may have different trust characteristics.

Because the project underwent several direction changes during implementation, the project content and analysis may be somewhat scattered and weak.


### 6.2 What challenge I faced
The main challenge of this project lies in understanding the Minecraft protocol. The Minecraft protocol varies depending on the version, making data packets difficult to construct. During development, I repeatedly encountered bottlenecks due to different data packet names or invalid data packets. Furthermore, careful handling of protocol states and connection management is necessary to ensure that the proxy can selectively modify data packets while forwarding normal game traffic.

## 7.Conclusion 
This project investigated the feasibility of MitM attacks against Minecraft Java Edition by developing a lightweight JavaScript proxy. This proxy can intercept and modify unencrypted network traffic. The project does not focus on implementing game hacking functionality, but rather uses packet manipulation as a practical method to study Minecraft's client-server trust model.

We successfully implemented three proof-of-concept attacks: chat messages were transparently modified before reaching the server; movement packets were manipulated to achieve limited delivery; and forged inventory packets caused the client to display items not present on the server. These demonstrations show that different types of packets have different security properties and verification mechanisms.

Experimental results indicate that Minecraft applies different levels of trust mechanisms based on the type of synchronization information. Client-generated chat messages are generally accepted without verification, movement packets require server-side verification, and inventory ownership is entirely determined by the server. These findings suggest that a successful man-in-the-middle attack does not necessarily mean the leakage of authoritative game state, but may only affect the client's perception of the game.

Although this implementation focuses on a limited number of packet types and offline server configurations, the project demonstrates how protocol analysis can be used to explore practical network security concepts, including network protocol security, man-in-the-middle attacks, and client-server trust boundaries. Future work could extend the proxy to more packet types, investigate encrypted online communication, or apply similar techniques to other multiplayer games.

## 8. References
https://minecraft.wiki/w/Java_Edition_protocol
https://minecraft.wiki/w/Java_Edition_protocol/Command_data
https://minecraft.wiki/w/Java_Edition_protocol/Data_types
https://github.com/PrismarineJS/node-minecraft-protocol
https://github.com/PrismarineJS/node-minecraft-data
### Use of Generative AI
This project used generative artificial intelligence tools as auxiliary resources for some code development, documentation translation, and improving the clarity of technical writing.

## 9.Appendix
### My project code repository:
https://github.com/yewenqing/COMP6841-Project