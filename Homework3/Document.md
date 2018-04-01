# 作业 3

##### 141210026 宋奎熹

## 1. 要求

请使用程序设计语言（如 C 语言），编程实现`ls`和`wc`命令，要求实现如下参数与功能：

```
ls –l(-d, -R, -a, -i)‏
wc [filename]
```

完成实现后，查找原命令的源代码，对其进行阅读分析，与自己的版本作比较，看有何不同，并将不同之处写入文档。

## 2. ls

### 输出结果

```
➜  Homework3 git:(master) ✗ ./ls
/Users/Kray/Documents/Software Engineering/Linux程序设计/LinuxLab/Homework3
➜  Homework3 git:(master) ✗ ./ls -l
-rw-r--r-- 1 Kray staff  404 2018-04-01 10:27 Document.md
-rw-r--r-- 1 Kray staff 5836 2018-04-01 10:17 ls.c
-rw-r--r-- 1 Kray staff   89 2018-03-24 09:38 makefile
-rw-r--r-- 1 Kray staff 1086 2018-03-24 09:15 wc.c
-rwxr-xr-x 1 Kray staff 8840 2018-03-26 19:47 wc
-rw-r--r-- 1 Kray staff  638 2018-04-01 10:27 Homework3.md
-rwxr-xr-x 1 Kray staff 13596 2018-04-01 10:16 ls
➜  Homework3 git:(master) ✗ ./ls -d
/Users/Kray/Documents/Software Engineering/Linux程序设计/LinuxLab/Homework3
➜  Homework3 git:(master) ✗ ./ls -R
/Users/Kray/Documents/Software Engineering/Linux程序设计/LinuxLab/Homework3:
Document.md	ls.c	makefile	wc.c	wc	Homework3.md	ls	
➜  Homework3 git:(master) ✗ ./ls -a
.	..	Document.md	.DS_Store	ls.c	makefile	wc.c	wc	Homework3.md	ls	.idea	
➜  Homework3 git:(master) ✗ ./ls -i
8617523834 Document.md	8615996424 ls.c	8615857563 makefile	8615853179 wc.c8615996236 wc	8615858155 Homework3.md	8617523165 ls
```

### 设计

1. 声明`st`为`struct stat`类型结构体，获取文件信息，并保存在`st`所指的结构体`stat`中。
2. 若没有给定路径，则默认是当前目录路径。
3. 若没有附加参数（`-ldRai`），则直接输出目录/文件名。若有，则对应进行处理。
4. 通过`st.st_mode & S_IFMT`的值来判断是目录还是文件。
5. 主要还是了解`struct star`、`struct dirent`结构体的组成，大致如下：

```C
struct stat {
   dev_t         st_dev;       //文件的设备编号
   ino_t         st_ino;       //节点
   mode_t        st_mode;      //文件的类型和存取的权限
   nlink_t       st_nlink;     //连到该文件的硬连接数目，刚建立的文件值为1
   uid_t         st_uid;       //用户ID
   gid_t         st_gid;       //组ID
   dev_t         st_rdev;      //(设备类型)若此文件为设备文件，则为其设备编号
   off_t         st_size;      //文件字节数(文件大小)
   unsigned long st_blksize;   //块大小(文件系统的I/O 缓冲区大小)
   unsigned long st_blocks;    //块数
   time_t        st_atime;     //最后一次访问时间
   time_t        st_mtime;     //最后一次修改时间
   time_t        st_ctime;     //最后一次改变时间(指属性)
};

struct dirent {
   long            d_ino;                  //索引节点号
   off_t           d_off;                  //在目录文件中的偏移 
   unsigned short  d_reclen;               //文件名长 
   unsigned char   d_type;                 //文件类型
   char            d_name [NAME_MAX+1];    //文件名，最长255字符 
}  
```

### 与源码比较

1. 源码考虑了输出颜色、文件类型、软链接和硬链接等多种差异，实现较为详细复杂。
2. 源码在错误处理上使用`error()`函数，而不是简单地`printf()`。
3. 源码在格式化输出上做了较多的改善。

## 3. wc 

### 输出结果

```
➜  Homework3 git:(master) ✗ ./wc /Users/Kray/Documents/Software\ Engineering/Linux程序设计/LinuxLab/Homework3/wc.c
56	154	1244	/Users/Kray/Documents/Software Engineering/Linux程序设计/LinuxLab/Homework3/wc.c
```
### 设计

1. 声明三个变量，依次记录找到的字符数、单词数和行数。声明一个变量，记录之前读到的字符是否为分隔符。
2. 先用`fopen()`函数打开文件，打开后用`fgetc()`从文件流中逐个读取字符；或者从标准输入流中逐个读取字符。直到`EOF`为止。
3. 遇到一个字符，若不是分隔符，就设置之前不是分隔符，且将字符数变量+1；遇到分隔符（如空格，`\n`，`\t`，`\v`，`\r`，`\f`），如果之前字符就是分隔符，那不做操作，否则设置之前是分隔符，且将单词数变量+1；遇到换行符（`\n`），将行数变量+1。
4. 输出三个变量和文件名（如有）。

### 与源码比较

1. 源码支持多种参数输入，而非仅限于文件名和标准输入流。
2. 源码在错误处理上使用`error()`函数，而不是简单地`printf()`。
3. 源码考虑到非普通文件类型的处理。
4. 源码使用`wchar_t`，而不是`char`。


