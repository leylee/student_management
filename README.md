 Homework of CS31902

# CS31902 哈工大 C语言程序设计B 实验大作业

学生管理系统

1. 数据结构的难度

   使用链表结构, 见 `student.h`和 `student.c` 中的 `List` 相关实现;

2. 算法

   - 使用了枚举, 迭代, 分类统计;
   - 排序, 见 `list.c` 中的 `sortList` 和 `heapSortList` 函数;
   - 模糊匹配, 见 `list.c` 中的 `searchById`, `searchByName` 等函数;
   - 文件操作, 见 `file_util.c` 中的相关函数;
   - 加入音效, 见 `ui.c` 中的 `errorSound` 函数;
   - 递归, 见 `list.c` 中的 `heapUp` 和 `heapDown` 函数;
   - **树形数据结构**实现的优先队列, 见 `list.h` 和 `list.c` 中的 `Heap` 相关实现

3. 程序设计质量

   - 模块化设计, 按照相关功能分为若干文件, 封装输入输出函数, 可复用性好;
   - 所有来自 `stdin` 的输入均有非法输入检查, 字符串输入避免缓冲区溢出, 代码健壮
   - 函数和变量命名清晰, 代码缩进规范, 函数均有注释
   - 学生数据支持**多轮查找**, 并可以按照**任意关键字**对已查找的记录进行排序和**重新排名**, 设计新颖;
   - 使用**二叉树**实现的**堆排序**, 使排序算法的时间复杂度降至 $O(n\lg n)$;

