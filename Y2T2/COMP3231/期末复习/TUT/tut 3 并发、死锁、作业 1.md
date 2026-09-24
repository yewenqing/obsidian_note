  

  

### 第 3 周 辅导课教程：COMP3231/9201/3891/9283 操作系统 2026/T2

  

  

  

  

### 问题与解答

  

  

  

  

#### 作业 1（Assignment 1）

  

  

欢迎大家利用第 3 周辅导课的一些时间讨论作业 1 的规范要求、任何相关疑问，以及机器人问题（robot problem）的总体轮廓。下周的辅导课将更具体地探讨系统调用（System Calls）。

  

  

  

#### 同步问题（Synchronisation Problems）

  

  

以下题目旨在帮助你熟悉并发编程中出现的一些典型问题，并学会识别和解决它们。

  

  

  

##### 协调活动（Coordinating activities）

  

  

1. **若要让一个线程等待另一个线程更新某个状态，可以采取什么同步机制或方法？**
    
      
    
      
    
    > **基于信号量（Semaphore）的解答**（信号量 `updated`，计数值初始化为 0）：
    > 
    >   
    > 
    > C
    > 
    > ```
    > wait_for_update()
    > {
    >    P(updated);
    > }
    > 
    > signal_update_occurred()
    > {
    >    V(updated);
    > }
    > ```
    > 
    > **基于条件变量（Condition Variable, CV）的解答**（变量 `flag = 0`，互斥锁 `l`，条件变量 `cv`）：
    > 
    >   
    > 
    > C
    > 
    > ```
    > wait_for_update()
    > {
    >    lock_acquire(l);
    >    while (flag == 0)
    >        cv_wait(cv, l);
    >    lock_release(l);
    > }
    > 
    > signal_update_occurred()
    > {
    >    lock_acquire(l);
    >    flag = 1;
    >    cv_signal(cv, l);
    >    lock_release(l);
    > }
    > ```
    

2. **某种特定抽象要求在任何时间点最多只允许 10 个线程进入“房间（room）”。试图进入房间的其他线程必须在门外等待，直到另一个线程离开房间。该如何实现同步方案来强制执行上述限制？**
    
      
    
      
    
    > **基于信号量的解答**（信号量 `room`，计数值初始化为 10）：
    > 
    >   
    > 
    > C
    > 
    > ```
    > enter_room()
    > {
    >    P(room);
    > }
    > 
    > leave_room()
    > {
    >    V(room);
    > }
    > ```
    > 
    > **基于条件变量的解答**（变量 `occupants = 0`，互斥锁 `room_lock`，条件变量 `room_cv`）：
    > 
    >   
    > 
    > C
    > 
    > ```
    > enter_room()
    > {
    >    lock_acquire(room_lock);
    >    while (occupants == 10)
    >        cv_wait(room_cv, room_lock);
    >    occupants = occupants + 1;
    >    lock_release(room_lock);
    > }
    > 
    > leave_room()
    > {
    >    lock_acquire(room_lock);
    >    occupants = occupants - 1;
    >    if (occupants == 9) 
    >        cv_signal(room_cv, room_lock);
    >    lock_release(room_lock);
    > }
    > ```
    

3. **多个线程正在等待同一件事情发生（例如某个磁盘块从磁盘读取完成）。请编写伪代码，用于同步并唤醒等待同一事件的多个线程。**
    
      
    
      
    
    > **基于信号量的解答**（变量 `waiters_count = 0`, `disk_block_status = NOT_READY`，信号量 `block_mutex` 初始值为 1，信号量 `block_sem` 初始值为 0）：
    > 
    >   
    > 
    > C
    > 
    > ```
    > wait_block()
    > {
    >    P(block_mutex);
    >    if (disk_block_status == READY) {
    >        V(block_sem);
    >    } else {
    >        waiters_count = waiters_count + 1;
    >    }
    >    V(block_mutex);
    >    P(block_sem);
    > }
    > 
    > make_block_ready()
    > {
    >    P(block_mutex);
    >    disk_block_status = READY;
    >    while (waiters_count != 0) {
    >        waiters_count = waiters_count - 1;
    >        V(block_sem);
    >    }
    >    V(block_mutex);
    > }
    > ```
    > 
    > **基于条件变量的解答**（变量 `disk_block_status = NOT_READY`，互斥锁 `block_lock`，条件变量 `block_cv`）：
    > 
    >   
    > 
    > C
    > 
    > ```
    > wait_block()
    > {
    >    lock_acquire(block_lock);
    >    while (disk_block_status != READY)
    >        cv_wait(block_cv, block_lock);
    >    lock_release(block_lock);
    > }
    > 
    > make_block_ready()
    > {
    >    lock_acquire(block_lock);
    >    disk_block_status = READY;
    >    cv_broadcast(block_cv, block_lock);
    >    lock_release(block_lock);
    > }
    > ```
    

  

  

##### 识别死锁（Identify Deadlocks）

  

  

4. **以下是使用信号量（计数值初始化为 1）的两个线程的代码示例。请给出一个执行与上下文切换序列，使得这两个线程发生死锁。**
    
      
    
      
    
    **请提出对其中一个或两个线程的修改方案以杜绝死锁。原本的线程违反了什么通用原则导致了死锁？（注：该“通用原则”在第 3 周讲义中尚未正式介绍，仅作非正式讨论。）**
    
      
    
      
    
    C
    
    ```
    semaphore *mutex, *data;
    
    void me() {
        P(mutex);
        /* 执行某些操作 */
    
        P(data);
        /* 执行其他操作 */
    
        V(mutex);
    
        /* 清理工作 */
        V(data);
    }
    
    void you() {
        P(data);
        P(mutex);
    
        /* 执行某些操作 */
    
        V(data);
        V(mutex);
    }
    ```
    
    > 左侧插入的数字标记了导致死锁的执行顺序：
    > 
    >   
    > 
    > C
    > 
    > ```
    > semaphore *mutex, *data;
    >  
    > void me() {
    > 1:    P(mutex);
    >       /* 执行某些操作 */
    >       
    > 4:    P(data);
    >       /* 执行其他操作 */
    >       
    >       V(mutex);
    >       
    >       /* 清理工作 */
    >       V(data);
    > }
    >  
    > void you() {
    > 2:    P(data);
    > 3:    P(mutex);
    >       
    >       /* 执行某些操作 */
    >       
    >       V(data);
    >       V(mutex);
    > }
    > ```
    > 
    > **解决方案**：为防止死锁，确保所有信号量以**相同的顺序**被获取。
    > 
    >   
    > 
    > C
    > 
    > ```
    > semaphore *mutex, *data;
    >  
    > void me() {
    >     P(mutex);
    >     /* 执行某些操作 */
    >     
    >     P(data);
    >     /* 执行其他操作 */
    >     
    >     V(mutex);
    >     
    >     /* 清理工作 */
    >     V(data);
    > }
    >  
    > void you() {
    >     P(mutex);
    >     P(data);
    >     
    >     /* 执行某些操作 */
    >     
    >     V(data);
    >     V(mutex);
    > }
    > ```
    

  

  

##### 同步机制（Synchronisation Mechanisms）

  

  

5. **一个程序存储了一张键/值对表格。考虑以下等待条件：**
    
      
    
      
    
    - 等待没有其他任务访问表格的时间点。
        
          
        
    - 等待表格中包含至少 1 个元素。
        
          
        
    - 等待表格中包含至少 4 个元素。
        
          
        
    
    **上述等待条件中，哪些可以通过以下并发原语实现：**
    
      
    
      
    
    - 锁（Locks）。
        
          
        
    - 信号量（Semaphores）。
        
          
        
    - 条件变量（Condition Variables）。
        
          
        
    
    _（注意：需要忙等待（busy-waiting）或需要在数据结构中添加线程队列的做法不计入有效“实现”。）_
    
      
    
      
    
    > - **等待排他性访问**通常使用**锁**实现。信号量也可以用来实现锁。条件变量通常需要依赖已存在的互斥机制，因此不适合单独用于此场景。
    >     
    >       
    >     
    > - **等待表格包含至少一个元素**无法单靠锁优雅地完成，因为当表格为空时，可能没有特定的锁“持有者”。该问题可以通过**信号量**（用于对表格中对象数量进行计数）或**条件变量**解决。
    >     
    >       
    >     
    > - **等待 4 个对象**适合使用**条件变量**。单独的锁同样无法解决该问题。信号量在此处行为较怪异：一个线程可以尝试获取 4 次信号量，但如果两个线程同时这样尝试，它们可能各自“持有”2 个资源而均无法继续向前推进。
    >     
    >       
    >     
    

  

  

##### 更多死锁识别（More Deadlock Identification）

  

  

6. **以下是另外两个线程。它们是否会发生死锁？如果会，请给出一个产生死锁的并发执行过程，并提出对其中一个或两个线程的修改建议以避免死锁。**
    
      
    
      
    
    C
    
    ```
    lock *file1, *file2, *mutex;
    
    void laurel() {
        lock_acquire(mutex);
        /* 执行某些操作 */
    
        lock_acquire(file1);
        /* 写入文件 1 */
    
        lock_acquire(file2);
        /* 写入文件 2 */
    
        lock_release(file1);
        lock_release(mutex);
    
        /* 执行某些操作 */
    
        lock_acquire(file1);
    
        /* 从文件 1 读取 */
        /* 写入文件 2 */
    
        lock_release(file2);
        lock_release(file1);
    }
    
    void hardy() {
        /* 执行操作 */
    
        lock_acquire(file1);
        /* 从文件 1 读取 */
    
        lock_acquire(file2);
        /* 写入文件 2 */
    
        lock_release(file1);
        lock_release(file2);
    
        lock_acquire(mutex);
        /* 执行某些操作 */
        lock_acquire(file1);
        /* 写入文件 1 */
        lock_release(file1);
        lock_release(mutex);
    }
    ```
    
    > 在此示例中排查死锁可能性的方法是记录两个线程的加锁顺序并寻找不一致之处：
    > 
    >   
    > 
    > - `laurel`: `mutex` $\to$ `file1` $\to$ `file2`; `file2` $\to$ `file1`
    >     
    >       
    >     
    >       
    >     
    > - `hardy`: `file1` $\to$ `file2`; `mutex` $\to$ `file1`
    >     
    >       
    >     
    >       
    >     
    > 
    > 注意 `file1` 和 `file2` 可能以两种不同的顺序被获取，这会导致死锁。产生死锁的执行时序如下所示：
    > 
    >   
    > 
    > C
    > 
    > ```
    > lock *file1, *file2, *mutex;
    >  
    > void laurel() {
    > 1:    lock_acquire(mutex);
    >       /* 执行某些操作 */
    >       
    > 2:    lock_acquire(file1);
    >       /* 写入文件 1 */
    >  
    > 3:    lock_acquire(file2);
    >       /* 写入文件 2 */
    >  
    > 4:    lock_release(file1);
    > 7:    lock_release(mutex);
    >  
    >       /* 执行某些操作 */
    >       
    > 8:    lock_acquire(file1);
    >  
    >       /* 从文件 1 读取 */
    >       /* 写入文件 2 */
    >  
    >       lock_release(file2);
    >       lock_release(file1);
    > }
    >  
    > void hardy() {
    >       /* 执行操作 */
    >       
    > 5:    lock_acquire(file1);
    >       /* 从文件 1 读取 */
    >  
    > 6:    lock_acquire(file2);
    >       /* 写入文件 2 */
    >       
    >       lock_release(file1);
    >       lock_release(file2);
    >  
    >       lock_acquire(mutex);
    >       /* 执行某些操作 */
    >       lock_acquire(file1);
    >       /* 写入文件 1 */
    >       lock_release(file1);
    >       lock_release(mutex);
    > }
    > ```
    > 
    > **防止死锁的方法**是定义一个全局加锁顺序，并确保所有线程都遵循该顺序。在此例中，我们选择 `mutex` $\to$ `file1` $\to$ `file2` 的加锁顺序。这意味着我们应当调整 `laurel`。以下是两种消除死锁的 `laurel` 实现版本（亦有其他修改方式）：
    > 
    >   
    > 
    > **版本一：**
    > 
    >   
    > 
    >   
    > 
    > C
    > 
    > ```
    > lock *file1, *file2, *mutex;
    >  
    > void laurel() {
    >     lock_acquire(mutex);
    >     /* 执行某些操作 */
    >     
    >     lock_acquire(file1);
    >     /* 写入文件 1 */
    >  
    >     lock_acquire(file2);
    >     /* 写入文件 2 */
    >  
    >     lock_release(mutex);
    >  
    >     /* 执行某些操作 */
    >     
    >     /* 从文件 1 读取 */
    >     /* 写入文件 2 */
    >  
    >     lock_release(file2);
    >     lock_release(file1);
    > }
    > ```
    > 
    > **版本二：**
    > 
    >   
    > 
    >   
    > 
    > C
    > 
    > ```
    > void laurel() {
    >     lock_acquire(mutex);
    >     /* 执行某些操作 */
    >     
    >     lock_acquire(file1);
    >     /* 写入文件 1 */
    >     
    >     lock_acquire(file2);
    >     /* 写入文件 2 */
    >  
    >     lock_release(file1);
    >     lock_release(mutex);
    >  
    >     /* 执行某些操作 */
    > 
    >     lock_release(file2);
    >     lock_acquire(file1);
    >     lock_acquire(file2);
    >  
    >     /* 从文件 1 读取 */
    >     /* 写入文件 2 */
    >  
    >     lock_release(file2);
    >     lock_release(file1);
    > }
    > ```
    

  

  

##### 同步链表（Synchronised Lists）

  

  

7. 基于 OS/161 代码库中的线程链表代码（`kern/thread/threadlist.c`），描述（并给出伪代码）一个同步双向链表结构。你可以按需使用信号量、互斥锁和条件变量。你必须说明（无需严格证明）为什么你的算法不会产生死锁。
    
      
    
    通常该同步链表的接口定义如下：
    
      
    
    C
    
    ```
    init(list_t *);
    add_head(list_t *list, node_t *node);
    add_tail(list_t *list, node_t *node);
    remove_head(list_t *list, node_t **node);
    remove_tail(list_t *list, node_t **node);
    insert_after(node_t *in_list, node_t *new_node);
    insert_before(node_t *in_list, node_t *new_node);
    remove(node_t *in_list);
    ```
    
    请务必明确阐述关于访问该数据结构时限制条件的假设，以及你如何确保这些限制得到满足。
    
      
    
    除了单全局锁方案外，请考虑为链表中每个节点配备一把独立锁（node-level lock）的方案。最具启发性的案例是 `insert_after()`、`insert_before()` 和 `remove()`。
    
      
    
    **OS/161 中的线程子系统使用线程链表管理部分状态（`kern/thread/threadlist.c`），该结构并未做同步处理，为什么？**
    
      
    
      
    
    > - 在 OS/161 中，`threadlist` 是一个双向链表，其所有代码均在**互斥执行**的假设下编写；在单处理器上，这在实践中是通过**禁用中断（interrupt disabling）**来保证的。因此，`threadlist` 代码本身没有包含同步原语。
    >     
    >       
    >     
    > - 编写通用链表管理的同步版本，可以使用**单把全局锁**，在对链表本身及节点进行所有更新时均获取该锁。但这将无法支持对链表中不同独立节点的并行更新。
    >     
    >       
    >     
    > - 可以尝试为链表中的**每个节点分配一把锁**以提升并发度，并在单次更新需要多把锁时**仅沿链表的单一方向加锁**。这并不像看上去那么简单：从示例代码可以看出，细粒度加锁会让某些操作变得非常复杂。鉴于所需的锁数量较多，且为了避免死锁所有操作都必须从头节点开始逐个传递加锁（Hand-over locking），这种细粒度锁在此场景下甚至比单锁方案更差，因为它单纯增加了获取锁的开销。
    >     
    >       
    >     
    
    C
    
    ```
    #include <types.h>
    #include <lib.h>
    #include <synch.h>
    #include "list.h"
    
    bool node_init(node_t *node)
    {
            struct lock *lock;
            lock = lock_create("node lock");
            if (lock == NULL)
                    return false;
            node->lock = lock;
            node->next = NULL;
            node->prev = NULL;
            return true;
    }
    
    void node_cleanup(node_t *node)
    {
            lock_destroy(node->lock);
    }
    
    bool list_init(list_t *list)
    {
            bool r;
            r = node_init(&list->head);
            if (!r)
                    return false;
            r = node_init(&list->tail);
            if (!r) {
                    node_cleanup(&list->head);
                    return false;
            }
            list->head.next = &list->tail;
            list->tail.prev = &list->head;
            return true;
    }
    
    void list_cleanup(list_t *list)
    {
            /* 待实现 */
            (void) list;
    }
    
    void add_head(list_t *list, node_t *node)
    {
            insert_after(&list->head, node);
    }
    
    void add_tail(list_t *list, node_t *node)
    {
            insert_before(list, &list->tail, node);
    }
    
    void insert_after(node_t *in_list, node_t *new_node)
    {
            /* 假设：in_list 在成功插入前不会被移除（仅对哨兵头节点严格成立） */
    
            lock_acquire(new_node->lock); /* 新节点以加锁状态开始 */
    
            /* 严格按照 head -> tail 顺序获取锁 */
            lock_acquire(in_list->lock);
            lock_acquire(in_list->next->lock);
    
            /* 执行插入操作 */
            new_node->next = in_list->next;
            new_node->prev = in_list;
    
            in_list->next = new_node;
            new_node->next->prev = new_node;
    
            lock_release(new_node->next->lock);
            lock_release(new_node->lock);
            lock_release(in_list->lock);
    }
    
    static bool hand_over_locking(list_t *list, node_t *target)
    {
            /* 采用交替传递加锁（Hand-over locking），直到找到目标节点 */
            /* 若找到目标，返回 true 并保持目标节点及其前驱节点处于加锁状态；未找到则返回 false */
    
            node_t *p, *t;
    
            p = &list->head;
            lock_acquire(p->lock);
    
            t = p->next;
            lock_acquire(t->lock);
            while (t != target) {
                    if (t == &list->tail) {
                            /* 未找到目标节点 */
                            lock_release(p->lock);
                            lock_release(t->lock);
                            return false;
                    }
                    lock_release(p->lock);
                    p = t;
                    t = t->next;
                    lock_acquire(t->lock);
            }
            return true;
    }
    
    bool insert_before(list_t *list, node_t *in_list, node_t *new_node)
    {
            /* 假设：in_list 在开始前不会被移除（仅对哨兵尾节点严格成立） */
            bool r;
    
            lock_acquire(new_node->lock); /* 同样以加锁状态开始 */
    
            /* 修改函数原型以传入 list，并利用 hand_over_locking 锁定 in_list 及其前驱节点 */
            r = hand_over_locking(list, in_list);
    
            if (!r) {
                    lock_release(new_node->lock);
                    return r;
            }
    
            /* 此时已同时持有 prev 和 in_list 的锁，执行插入 */
            new_node->prev = in_list->prev;
            new_node->next = in_list;
    
            in_list->prev = new_node;
            new_node->prev->next = new_node;
    
            lock_release(new_node->prev->lock);
            lock_release(new_node->lock);
            lock_release(in_list->lock);
            return true;
    }
    
    static void remove_with_locks_held(node_t *in_list)
    {
            in_list->prev->next = in_list->next;
            in_list->next->prev = in_list->prev;
    }
    
    void remove_head(list_t *list, node_t **node)
    {
            node_t *n;
            lock_acquire(list->head.lock);       /* 哨兵头节点 */
            lock_acquire(list->head.next->lock); /* 待移除的目标候选节点 */
    
            if (list->head.next == &list->tail) {
                    /* 链表为空，无元素可移除 */
                    lock_release(list->head.next->lock); 
                    lock_release(list->head.lock); 
                    *node = NULL;
                    return;
            }
    
            lock_acquire(list->head.next->next->lock); /* 依赖上面持有的锁安全访问指针 */
    
            n = list->head.next;
            remove_with_locks_held(n);
    
            lock_release(list->head.lock);       /* 释放哨兵头节点 */
            lock_release(n->lock);               /* 释放已移除的节点 */
            lock_release(list->head.next->lock); /* 释放新的首节点 */
    
            *node = n;
    }
    
    void remove_tail(list_t *list, node_t **node)
    {
            /* 留作练习：涉及三个节点的传递加锁，其中最后一个节点为尾节点 */
            (void) list;
            (void) node;
    }
    
    bool remove(list_t *list, node_t *in_list)
    {
            bool r;
            r = hand_over_locking(list, in_list);
    
            if (!r)
                    return r;
    
            /* 此时 in_list 及其前驱已锁定，再获取后继节点的第三把锁 */
            lock_acquire(in_list->next->lock);
    
            /* 执行移除 */
            remove_with_locks_held(in_list);
    
            lock_release(in_list->prev->lock);
            lock_release(in_list->next->lock);
            lock_release(in_list->lock);
            return true;
    }
    ```
    

  

  

#### 并发与死锁（Concurrency and Deadlock）

  

  

_(注：以下题目涉及死锁相关内容，对应第 4 周讲义。)_

  

  

8. **在以下各场景中，有一位或多位哲学家正在挨饿。哲学家们遭遇了什么状况？**
    
      
    
      
    
    - a. 桌上的每位哲学家都拿起了左手边的叉子，并正在等待右手边的叉子。
        
          
        
    - b. 规定同一时间只允许一位哲学家就餐。当有多位哲学家饥饿时，最年轻的哲学家优先进餐。最年长的哲学家永远吃不上饭。
        
          
        
    - c. 每位哲学家拿起左手叉子后，若无法立即拿起右手叉子，便会主动放下左手叉子给他人就餐机会。尽管左手叉子被频繁拿起放下，却没有哲学家能够成功进餐。
        
          
        
    
    > a. **死锁（Deadlock）**
    > 
    >   
    > 
    >   
    > 
    > b. **饥饿（Starvation）**
    > 
    >   
    > 
    >   
    > 
    > c. **活锁（Livelock）**
    > 
    >   
    > 
    >   
    

9. **什么是饥饿（Starvation）？请给出一个例子。**
    
      
    
      
    
    > **饥饿**是指系统根据某种策略分配资源，虽然系统整体仍在向前推进，但由于该策略的偏向性，导致一个或多个进程永远无法获得其所需的资源。
    > 
    >   
    > 
    > **示例**：打印机按照“最短打印作业优先（Shortest Job First）”的策略进行任务调度，以提升小作业的响应速度。在繁忙的系统上，一个庞大的打印作业可能永远排不上队，从而发生**饥饿**。
    > 
    >   
    

10. **两个进程尝试从磁盘读取独立的块，该操作涉及发出一条 _seek（寻道）_ 指令与一条 _read（读取）_ 指令。每个进程在执行 _seek_ 和 _read_ 之间都会被另一个进程中断。当进程发现另一个进程移动了磁头后，会重新发出初始的 _seek_ 来重新定位磁头，但在执行 _read_ 之前再次被中断。这种交替寻道的过程无限持续，两个进程都无法从磁盘读出数据。这是死锁、饥饿还是活锁？你将如何修改系统以防止此问题？**
    
      
    
      
    

> 这是**活锁（Livelock）**。
> 
>   
> 
> **修改方案**：允许每个进程对磁盘加锁，以互斥的方式将 _seek_ 和 _read_ 两条指令作为一个整体原子执行，完成后再释放锁。
> 
>   

11. **请通过破坏发生死锁所需的必要条件，描述四种*预防（Prevent）*死锁的方法。**
    
      
    
      
    

> - **破坏互斥条件（Mutual Exclusion）**：
>     
>       
>     - 将资源设为可共享（例如允许多个进程并发读取只读文件）。但通常某些物理/逻辑资源本质上不可共享，必须互斥。
>         
>           
>         
> - **破坏占有并等待条件（Hold and Wait）**：
>     
>       
>     - 规定任何时候只能持有一件资源（不太实用）。
>         
>           
>         
>     - 要求进程在开始时一次性申请全部所需资源；若某项资源不可用，则必须释放已持有的所有资源后再重试（易引发活锁）。
>         
>           
>         
> - **破坏不可抢占条件（No Preemption）**：
>     
>       
>     - 强行剥夺资源（从持有者手中夺走资源），但这并非对所有资源都适用。
>         
>           
>         
> - **破坏循环等待条件（Circular Wait）**：
>     
>       
>     - 对所有资源进行全局编号，规定所有进程必须严格按资源编号递增顺序申请资源。
>         
>           
>         

12. **根据下表回答问题：**
    
      
    
      
    
    **初始可用资源向量（Available）**：
    
      
    
    |**r1**|**r2**|**r3**|**r4**|
    |---|---|---|---|
    |2|1|0|0|
    
    **进程资源分配与最大需求表**：
    
      
    
    |**进程 (Process)**|**当前已分配 (Current Allocation)r1, r2, r3, r4**|**最大需求 (Maximum Demand)r1, r2, r3, r4**|**尚需资源 (Still Needs)r1, r2, r3, r4**|
    |---|---|---|---|
    |**p1**|0, 0, 1, 2|0, 0, 1, 2|_(a)_|
    |**p2**|2, 0, 0, 0|2, 7, 5, 0|_(a)_|
    |**p3**|0, 0, 3, 4|6, 6, 5, 6|_(a)_|
    |**p4**|2, 3, 5, 4|4, 3, 5, 6|_(a)_|
    |**p5**|0, 3, 3, 2|0, 6, 5, 2|_(a)_|
    
    - **a. 计算各进程仍可能请求的资源量，并填入“尚需资源（still needs）”栏。**
        
          
        
          
        
    - **b. 系统处于安全状态还是不安全状态？为什么？**
        
          
        
          
        
        > **安全状态**，存在可行安全序列：`p1, p4, p5, p2, p3`。
        > 
        >   
        
    - **c. 系统是否发生死锁？为什么？**
        
          
        
          
        
        > **否**。按照安全调度序列 `p1, p4, p5, p2, p3` 执行完毕后，没有进程遗留受阻。
        > 
        >   
        
    - **d. 哪些进程已经或可能陷入死锁？**
        
          
        
          
        
        > **无（None）**。
        > 
        >   
        
    - **e. 假设收到来自 p3 对 (0, 1, 0, 0) 的资源请求：**
        
          
        
          
        1. 是否可以立即安全地满足该请求？
            
              
            
            > **否**。
            > 
            >   
            
        2. 立即满足该请求会使系统处于何种状态（死锁、安全、不安全）？
            
              
            
            > **不安全状态（Unsafe）**。
            > 
            >   
            
        3. 若立即满足该请求，哪些进程（如果有）已经或可能会陷入死锁？
            
              
            
            > **p2, p3**。
            > 
            >   
            
    
    > **计算完成后的完整表格（Still Needs = Maximum Demand - Current Allocation）**：
    > 
    >   
    > 
    > |**进程**|**当前已分配(r1, r2, r3, r4)**|**最大需求(r1, r2, r3, r4)**|**尚需资源 (Still Needs)(r1, r2, r3, r4)**|
    > |---|---|---|---|
    > |**p1**|0, 0, 1, 2|0, 0, 1, 2|**0, 0, 0, 0**|
    > |**p2**|2, 0, 0, 0|2, 7, 5, 0|**0, 7, 5, 0**|
    > |**p3**|0, 0, 3, 4|6, 6, 5, 6|**6, 6, 2, 2**|
    > |**p4**|2, 3, 5, 4|4, 3, 5, 6|**2, 0, 0, 2**|
    > |**p5**|0, 3, 3, 2|0, 6, 5, 2|**0, 3, 2, 0**|
    

13. **使用互斥锁并通过不同于讲义中展示的策略，解决如下哲学家就餐问题。**
    
      
    
      
    
    C
    
    ```
    void take_both_forks(unsigned long phil_num)
    {
    /*
     * 确保哲学家对所关联的两把叉子拥有互斥访问权。
     * 
     * 左手叉子编号 = phil_num
     * 右手叉子编号 = (phil_num + 1) % NUM_PHILOSOPHERS
     */
    }
    
    void release_forks(unsigned long phil_num)
    {
    /*
     * 释放哲学家对叉子的互斥访问。
     */
    }
    ```
    
    > **策略**：为每把叉子分配一把锁。为避免死锁，必须**始终先获取编号较小的叉子锁**（包括正确处理环形回绕情况）。
    > 
    > C
    > 
    > ```
    > struct lock *fork_locks[NUM_PHILOSOPHERS];
    > 
    > void take_both_forks(unsigned long phil_num)
    > {
    >     int lower, higher;
    > 
    >     lower = phil_num;                                /* 左手叉子 */
    >     higher = (phil_num + 1) % NUM_PHILOSOPHERS;       /* 右手叉子 */
    > 
    >     if (lower > higher) {
    >         /* 交换 lower 与 higher 确保严格升序加锁，避免死锁 */
    >         lower = higher;
    >         higher = phil_num;
    >     }
    > 
    >     lock_acquire(fork_locks[lower]);
    >     lock_acquire(fork_locks[higher]);
    > }
    > 
    > void release_forks(unsigned long phil_num)
    > {
    >     lock_release(fork_locks[phil_num]);
    >     lock_release(fork_locks[(phil_num + 1) % NUM_PHILOSOPHERS]);
    > }
    > ```