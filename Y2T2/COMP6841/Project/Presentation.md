
### 0:00 - 0:20 | Introduction & Background

"Hello, my project is : **Analyzing Minecraft Protocol and Client-Server Verification mechanism via a Custom JS MitM Proxy.**"

### 0:20 - 3:00 | Architecture & PoC Experiments

"I deployed a MitM Proxy between the client and the server. When the server runs in Offline Mode, network packets are transmitted in plaintext. 
So I can connect the client to the proxy then transmit to server instead of connect client directly to server. Then I can parse packets using the `node-minecraft-protocol` library. 
I selected three representative packet types to analyze and modify, conducting three Proof-of-Concept (PoC) attacks: Chat Manipulation, Position Spoofing, and Fake Inventory.

Here is a short demo video:

_(Play video)_

In this demo, we can see the results of these three attack executions:

1. **Chat Manipulation**:
    as we can see
    the player type "test message" in the chat box, but the server receive message "Your message is modified"  
    When a player sends a message, the proxy tampers with the content in transit. As a result, both the server and all other players see the altered text.
    
2. **Position Spoofing (`#port` Command)**:
    
    I send a position packets into the client via the proxy. If teleported only **10 blocks** away, the player successfully teleports. However, when attempting a **100-block** teleport, the server console logs: `Player moved too quickly!`. This indicates that the speed cap was triggered, and the player will stay in origin position
    
1. **Fake Inventory (`#give` Command)**:
    
     Here when player type `#give diamond_pickaxe 36` the Proxy will send a fake `set_slot` packet to the client, granting the player a 'diamond pickaxe'. 
     
     Then as we can see client successfully shows player holding the pickaxe, and when player try to use this pickaxe to mine a stone, client also shows mining animations as fast as player really has a diamond pickaxe. However, after the animation shows finish mining, the stone didn't disappear immediately, it broke only after we mine the stone for seconds , which is same as we mine with out a pickaxe, and after the stone Destroyed, it dropping no items. 
     
     and when player try to move the pickaxe inside the inventory, the pickaxe will disapp ear
    

### 3:00 - 4:45 | Core Security Analysis

"These three simple experiments reveal that **Minecraft enforces distinctly different validation tiers for different packet types**:

- **Tier 1: Full Trust (Chat Packets)**
    
    The server will not verify what the player _actually_ typed. Thus, a Man-in-the-Middle attack can tamper packet data.
    
- **Tier 2: Threshold-Based Trust (Position Packets)**
    
    Although movement data is reported by the client, the server **does not trust it blindly**. The server will calculates displacement and velocity in real time. Once physically unreasonable thresholds are exceeded, the Server Authority rejects the packet.
    
- **Tier 3: Zero Trust / Absolute Authority (Inventory Packets)**
    
    Item ownership is **strictly governed by the server**. While fake packets can deceive client-side rendering and alter the player's visual perception, they cannot compromise the authoritative game state maintained by the server.
    

**In network protocol attacks, even we successfully modifying a packet , do not means we executing a successful attack.**"

### 4:30 - 5:00 | Conclusion

"In summary, by building a JS MitM proxy, this project not only demonstrates the feasibility of network man-in-the-middle attacks, but also visually illustrates the design philosophy behind 'Server Authority' and 'Trust Boundaries' in modern C/S game architecture using Minecraft as a case study.

The core takeaway: **Never trust client-side data**, and never underestimate the importance of encrypted transport channels."