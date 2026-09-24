**UNSW COMP3231/9201/3891/9283 操作系统 2026/T2 —— 第 9 周辅导课（Tutorial Week 9）**

  

  

**问题与解答**

  

  

**作业 3 练习题（Assignment 3 Exercises）**

  

  

**本部分的答案请参见 Wiki。**

  

  

到目前为止，你应该已经足够熟悉内核源代码的导航，能够自行找到以下问题的答案（提示：使用源代码浏览器或 _grep_ 实用工具）。你可能还会发现 [MIPS r3000 参考手册](https://www.google.com/search?q=http://www.cse.unsw.edu.au/~cs3231/doc/mips.php) 很有用。

  

1. **不同 MIPS 地址空间段之间有什么区别？每个段的作用是什么？**
    
      
    
      
    
2. **有哪些函数可用于帮助管理 TLB？请描述它们的作用。（提示：查看 `kern/arch/mips/include/tlb.h`）**
    
      
    
      
    
3. **使用什么宏来将物理地址转换为内核虚拟地址？**
    
      
    
      
    
4. **初始用户栈指针应该是什么地址？**
    
      
    
      
    
5. **什么是 `entryhi` 和 `entrylo` 协处理器寄存器？请描述它们的内容。**
    
      
    
      
    
6. **`as_*` 系列函数的作用是什么？为什么我们需要 `as_prepare_load()` 和 `as_complete_load()`？**
    
      
    
      
    
7. **`vm_fault()` 的作用是什么？它在什么时候被调用？**
    
      
    
      
    
8. **假设采用两级分层页表（4KB 页面大小），针对以下虚拟地址分别展示：**
    
      
    
      
    
    1. 页号与页内偏移量（offset）；
        
          
        
    2. 转换后的物理地址（在完成任何页面分配之后）；以及
        
          
        
    3. 发生 TLB 未命中（miss）后页表的内容。
        
          
        
    
    _页表初始为空，且没有二级（L2）页面。你可以假设分配器按顺序返回页框（frame），即首先分配的页框是 frame 1，接下来是 frames 2, 3, 4 等。_
    
      
    
      
    - `0x100008`
        
          
        
          
        
    - `0x101008`
        
          
        
          
        
    - `0x1000f0`
        
          
        
          
        
    - `0x41000`
        
          
        
          
        
    - `0x41b00`
        
          
        
          
        
    - `0x410000`
        
          
        
          
        

**C 语言位运算温故（C bitwise operations refresher）**

  

  

给定源代码中的以下常量定义：

  

C

```
#define TLBHI_VPAGE   0xfffff000
#define TLBLO_PPAGE   0xfffff000
#define TLBLO_NOCACHE 0x00000800
#define TLBLO_DIRTY   0x00000400
#define TLBLO_VALID   0x00000200
```

  

以及 32 位页表项（PTE）与 32 位虚拟地址的定义：

  

C

```
uint32_t pte;
vaddr_t vaddr;
```

  

9. **你会使用什么 C 语言表达式来设置（set）或重置（reset）页表项中的有效位（valid bit）？**
    
      
    
      
    

C

```
pte = pte | TLBLO_VALID   /* 置位 (set) */
pte = pte & ~TLBLO_VALID  /* 复位 (reset) */
```

  

10. **你会使用什么 C 语言表达式来测试有效位是否已设置？**
    
      
    
      
    

C

```
if (pte & TLBLO_VALID)
```

  

11. **你如何从虚拟地址中提取 12 位的页内偏移量（bits 0 - 11）？**
    
      
    
      
    

C

```
offset = vaddr & ~TLBHI_VPAGE
```

  

12. **你如何将虚拟地址中最高的 10 位（bits 22 - 31）转换为索引？**
    
      
    
      
    

C

```
index = vaddr >> 22
```

  

13. **你如何将接下来的 10 个最高有效位（bits 12 - 21）转换为索引？**
    
      
    
      
    

C

```
index = (vaddr << 10) >> 22
```

  

14. **你如何将一个虚拟地址向下对齐（round down）到页基地址？**
    
      
    
      
    

C

```
vaddr = vaddr & TLBHI_VPAGE
```