# Linux 程序设计复习

# Ch1

# Linux 定义

A free Unix-type operating system developed under the GNU General Public License.

* Open source
* Popular
* Support most of the platforms available

# 主要发行版本

* Redhat -> Fedora 
* Debian
* SuSe
* Mandrake
* Ubuntu

# GNU 和 Linux

![](https://ws3.sinaimg.cn/large/006tNc79gy1fq0u9njq7nj30e407a752.jpg)

* Linux 只是一个操作系统内核而已，而 GNU 提供了大量的自由软件来丰富在其之上各种应用程序。

# 安装

## 方式

* Live CD
* Virtual machine

## 过程

* Boot system from bootable media
* All installation programs need to perform essentially the same steps:
    1. Choose language, keyboard type, mouse type 
    2. **Create partitions**
    3. **Setup a boot loader**
    4. Configure network
    5. Configure user and authentication
    6. Select package groups
    7. Configure X
    8. Install packages
    9. Create boot disk

# [MBR 和 GPT](http://www.eassos.cn/jiao-cheng/ying-pan/mbr-vs-gpt.php)

![](https://ws2.sinaimg.cn/large/006tNc79gy1fq2zqp84yhj30ty0h6myb.jpg)

# 文件系统

* 操作系统中负责存取和管理文件的部分
* A collection of files and certain of their attributes. It provides a name space for file serial numbers referring to those files. (susv3)
* File System in Linux
    * VFS
    * EXT2
    * EXT3
    * FAT32
    
# 启动过程（理解）

上电自检→BIOS→Boot Loader→Linux 内核→init→系统准备就绪

# Boot Loader

* A boot loader loads and starts the Linux kernel.
* 常用的：LILO（古老）和**GRUB**

## GRUB

* Program stored in MBR (first stage) and in `/boot/grub` (1.5th and second stage)
* Understand file system structure; no need to activate a configuration as with LILO
* Configuration file `/boot/grub/grub.conf`
* Installed in MBR with grub-install

```bash
title       Ubuntu, kernel2.6.20-16-generic
root        (hd0,1)
kernel      /boot/initrd.img-2.6.20-16-generic root=UUID=3f784cd9-516f-4808-a601-b19356f6bdea ro quiet splash locale=zh_CN vga=0x318
initrd      /boot/initrd.img-2.6.20-16-generic
```

# 命令行的优势

1. 利用命令行可以对系统进行各种配置
2. 有助于初学者了解系统的运行情况和计算机的各种设备
3. 操作具有更好的稳定性与安全性

# 编译软件的过程

From a `tarball`

```bash
tar zxvf application.tar.gz
cd application
./configure
make
su -
make install
```

命令：`apt-get`

# 虚拟终端

* VT 1-6: text mode logins
* VT 7: graphical mode login prompt (if enabled)
* 字符界面中用`Alt+F1-6`切换
* 图形界面中用`Ctrl+Alt+Fn`切换

# 目录结构

* All Linux directories are contained in one, virtual, “unified file system”.
* Physical devices are mounted on mount points.
* 没有盘符号如 C:, A:

![](https://ws3.sinaimg.cn/large/006tNc79ly1fq0ve0lw3mj311q0diq59.jpg)

|目录|说明|
|---|---|
|`/bin`|必要的命令二进制文件。包含了会被系统管理者和用户使用的命令，但是需要在没有任何文件系统挂载时使用。也可能会在脚本文件中间接使用||`/boot`|Boot Loader 相关的静态文件。 包含了所有需要在加载阶段使用的文件(不含一些不需要在启动阶段用到的配置文件)。保存了所有内核在执行用户态程序之前用到的数据||`/dev`|设备文件。是一些特殊或设备的文件||`/etc`|主机相关的系统配置。主要包含了配置文件||`/lib`|必要的共享二进制文件或内核模块。比如在 `/bin` 或 `/sbin` 里需要用到的库||`/media`|可删除 media 的挂载点。如软盘等||`/mnt`|临时文件系统的挂载点||`/opt`|额外的应用软件包安装目录||`/sbin`|必要的系统二进制文件||`/srv`|系统提供的有关服务的数据||`/tem`|临时文件||`/usr`|第二级层次树。`/usr`是共享的、只读的数据。大型的软件包不应该使用 `/usr` 下的层次||`/var`|可变数据||`/home`|用户 home 目录|
|`/lib<qual>`|必要共享二进制文件的可选格式||`/root`|Root 用户的 HOME 目录|

# 文件权限

* 文件权限分为三个层次：用户(`u`)、组(`g`)、其他用户(`o`)，所有用户(`a`)
* 三个类型：读(`r`)、写(`w`)、执行(`x`)
* 三个操作：增加(`+`)、减少(`-`)、赋值(`=`)

##### 例

```bash
chmod 765 file
```

其中:

```bash
user    = 7 = 111b = rwx
group   = 6 = 110b = rw-
other   = 5 = 101b = r-x
```

默认权限：

* 文件 `-rw-r--r-- 644`
* 目录 `drwxr-xr-x 755`

# `ls -l`

文件类型+权限+链接计数+所有者+组群+文件大小+修改时间+文件名

![](https://ws1.sinaimg.cn/large/006tNc79ly1fq0vl78fekj31bc0mcgry.jpg)

# 进程

* 进程是一个正在执行的程序实例。由执行程序、它的当前值、状态信息以及通过操作系统管理此进程执行情况的资源组成。
* Shell 也是一个进程

# UNIX

* 早期的 UNIX
    * 一个简单的文件系统
    * 一个进程子系统和一个 Shell
* 内核和核外程序

![](https://ws4.sinaimg.cn/large/006tNc79ly1fq0vmv0desj30wi1cgdq9.jpg)

# 重定向

|       | 标准输入  |  标准输出  |  标准错误  |
| :---: | :---: | :----: | :----: |
| 文件描述符 |   0   |   1    |   2    |
| C语言变量 | stdin | stdout | stderr |

* <, >, >>, 2>
    * `>` 输出重定向到一个文件或设备 覆盖原来的文件
    * `>!` 输出重定向到一个文件或设备 强制覆盖原来的文件
    * `>>` 输出重定向到一个文件或设备 追加原来的文件
    * `<` 输入重定向到一个程序
将显示的结果输出到 `list.txt` 文件中，若该文件已存在则覆盖    

```   bash 
ls -al > list.txt
``` 将显示的结果输出到 `list.txt` 文件中，若该文件已存在则追加

```bashls -al >> list.txt```
将显示的数据，正确的输出到 `list.txt` 错误的数据输出到 `list.err`

```bashls –al 1> list.txt 2> list.err
```

```bash
kill –HUP 1234 > killout.txt 2> killerr.txt
kill –HUP 1234 > killout.txt 2>& 1
```

# 管道

一个进程的输出作为另一个进程的输入，`|`

##### 例

```bash
ls | wc –l
ls –lF | grep ^d
ar t /usr/lib/libc.a | grep printf | pr -4 -t
grep 'tree' < a.txt  # 查找a.txt中的tree
```

> 重定向和管道是命令行的进程

在两个命令之间使用管道 `|` 操作符将第一个命令的 stdout 指向第二个命令的 stdin。

# Ch2

# Shell

* A command interpreter and programming environment
* 用户和操作系统之间的接口
* 作为核外程序而存在
* 有许多不同的 Shell（ash,bsh,bash,sh,csh,tcsh,ksh）     

## 脚本文件

* 注释（包括开头的`#!/bin/bash`）
* 退出码`exit 0`
* `;`可以在一行内连接多条命令

# 执行脚本文件

```bash
$ sh script_file
```

使用 `sh test.sh` 来执行 script 文件，该方法标明使用 sh 这种 Shell 来执行`test.sh`文件，sh 已经是一种被 bash 替代的 Shell，尽管我们在`test.sh`中声明使用`#!/bin/bash`来执行我们的文件，但此时使用 sh 而不是 bash，则`#!/bin/bash`已不起作用。

```bash
chmod +x script_file (chown, chgrp optionally) 
./script_file
```

添加完执行权限之后，便可以使用 `./test.sh` 来执行脚本，该方式与 `bash test.sh` 是一样的 ，默认使用 `bin/bash` 来执行我们的脚本。

只有该种执行方式需要对文件添加执行权限，其他方式并不需要。

当我们使用 `sh test.sh`、`bash test.sh`、`./test.sh`执行脚本的时候，该`test.sh`运行脚本都会使用一个新的 Shell 环境来执行脚本内的命令，也就是说，使用这 3 种方式时，其实 script 是在**子进程的 Shell 内**执行，当子进程完成后，子进程内的各项变量和操作将会结束而不会传回到父进程中。

```bash
source script_file
. script_file
```
source 方法执行脚本是在父进程中执行的，`test.sh`的各项操作都会在原本的 Shell 内生效，这也是为什么不注销系统而要让某些写入 `~/.bashrc` 的设置生效时，需要使用 `source ~/.bashrc` 而不能使用 `bash ~/.bashrc`。

# 变量

## 用户变量

用户在 Shell 脚本里定义的变量

### 变量的赋值和使用 

```bash
var=value
echo $var
```

### read命令

`read var` 或 `read`

```
read -p "Enter a number"
echo $REPLY
```

使用 `read` 从标准输入中读取一行数据 

```bash
read name
```

可以使用提示

```bash
read –p “Enter your name:” name
```

更多内容参照命令 read

### 引号的用法

双引号，单引号，转义符“`\`”

单引号内的所有字符都保持它本身字符的意思，而不会被 bash 进行解释，例如，`$`就是`$`本身而不再是 bash 的变量引用符，`\`就是`\`本身而不再是 bash 的转义字符。

除了`$`、反引号和`\`外，双引号内的所有字符将保持字符本身的含义而不被 bash 解释。

## 环境变量

Shell 环境提供的变量，通常使用大写字母做名字。

|环境变量|说明|
|---|---|
|`$HOME`|当前用户的登陆目录|
|`$PATH`|以冒号分隔的用来搜索命令的目录清单|
|`$PS1`|命令行提示符，通常是`$`字符|
|`$PS2`|辅助提示符，用来提示后续输入，通常是`>`字符|
|`$IFS`|输入区分隔符；看作是单词之间分隔符的一组字符（空格、制表符、换行符等）|

* 查看和设置环境变量
    * `echo`：显示环境变量 `echo $PATH`
    * `env`：显示系统所有的环境变量
    * `set`：显示本地定义的 Shell 变量
    * `export`：设置新的环境变量 `export HELLO=”hello”`

```bash
echo $PATH 
/usr/local/bin:/bin:/usr/bin:/usr/X11R6/bin:/home/song/bin 
PATH=$PATH:.
export PATH
```

## 参数变量和内部变量

调用脚本程序时如果带有参数，对应的参数和额外产生的一些变量。

|参数变量|说明|
|---|---|
|`$#`|传递到脚本程序的参数个数|
|`$0`|脚本程序的名字|
|`$1,$2,...`|脚本程序的参数|
|`$*`|一个全体参数组成的清单，它是一个独立的变量， 各个参数之间用环境变量 IFS 中的第一个字符分隔开|
|`$@`|`$*`的一种变体，它不使用 IFS 环境变量。|

# 条件测试

`test expression`或`[ expression ]`（注意expression**前后需要有空格**）或`((expression))`，但是`(())`里只能使用 C 风格的比较（< <= > >= !=，无法使用 `-eq` 等比较命令）

![](https://ws2.sinaimg.cn/large/006tNc79ly1fq0w8mt2d2j311g1a4wtn.jpg)

# 基本算术运算

需要计算`var1=var2+-*/var3`这种

* 使用 `let` 命令
    * `let result=num1+num2`（变量前不需要添加`$`）
* 使用`$[]`操作符 
    * `result=$[num1+num2]`
* 使用`$(())`
    * `result=$((num1+num2))`

##### 例

以下脚本输出三个 3

```
#!/bin/sh
a=1
b=2
echo $((a + b))
echo $[a + b]
let c=a+b
echo $c
```

# 条件语句
    
## if

```bash
if [ expression ]
then
    statements
elif [ expression ]
then
    statements
elif ...
else
    statements
fi
```

**Shell 中表达式为 0 表示真，expression 为 0 时经过 then（与 C 相反），在使用函数确定真假是注意返回值为 0 的时候表示真**

##### 例

```bash
#!/bin/sh
echo "Is this morning? Please answer yes or no."
read answer
if [ "$answer" = "yes" ]; then
    echo “Good morning”
elif [ "$answer" = "no" ]; then
    echo "Good afternoon"
else
    echo "Sorry, $answer not recognized. Enter yes or no"
    exit 1 
fi
exit 0
```

## case

每个执行的语句后面一定是双分号

```bash
case str in
    str1 | str2) statements;;
    str3 | str4) statements;;
    *) statements;;
esac
```

##### 例

```bash
#!/bin/sh
echo "Is this morning? Please answer yes or no."
read answer
case "$answer" in
    yes | y | Yes | YES) echo "Good morning!" ;; 
    no | n | No | NO) echo "Good afternoon!" ;; 
    *) echo "Sorry, answer not recognized." ;;
esac 
exit 0
```

# 循环语句

## for

```bash
for var in list
do 
    statements
done
```

这种类型适合对一系列字符串进行处理，通常会结合一些基本命令

##### 例

```bash
#!/bin/sh
for file in $(ls f*.sh); do 
    lpr $file
done 
exit 0
```

## while

```bash
while condition
do
    statements
done
```

##### 例1

```bash
quit=n
while [ "$quit" != "y" ]; do 
    read menu_choice
    case "$menu_choice" in
        a) do_something;;
        b) do_anotherthing;;
        ...
        q|Q) quit=y;;
        *) echo "Sorry, choice not recognized.";;
    esac 
done
```

##### 例2

```bash
a=0
while [ "$a" -le "$LIMIT" ] 
do
    a=$(($a+1))
        if [ "$a" -gt 2 ] 
        then
            break # Skip entire rest of loop. 
        fi
    echo -n "$a"
done
```

## until

不建议使用

```bash
until condition
do
    statements
done
```

## select

生成菜单列表

```bash
select item in itemlist
do
    statements
done
```

##### 例

```bash
#!/bin/sh
clear
select item in Continue Finish
do
    case "$item" in
        Continue) ;;
        Finish) break ;;
        *) echo "Wrong choice! Please select again!" ;;
    esac 
done
```

# 命令组合

## 分号串联

依次执行

`command1;command2`

## 条件组合

短路特性

### AND 命令

`command1&&command2` 执行 command1 成功之后才执行 command2

### OR 命令

`command1||command2` 执行 command1 失败之后才执行 command2

# 杂项命令

* `break`：跳出当前循环 
* `continue`：调到下一次循环
* `exit n`：以退出码 n 退出脚本执行
* `return`：函数返回
* **export**：将变量导出到 Shell，使之成为 Shell 的环境变量 
* **set**：为 Shell 设置参数变量
* **unset**：从环境中删除变量或函数
* `trap`：指定在收到操作系统信号后执行的动作 
    * trap 之后跟随一条命令，如：`trap 'echo something' INT` 意为脚本在收到 INT 信号（`Ctrl+C`）时执行`echo something`
* “`:`”（冒号命令）：空命令
* “`.`”（句点命令）或 `source`：在当前 Shell 中执行命令

# 捕获命令输出

```bash
$(command)
`command`
```

##### 例

```bash
#!/bin/sh
echo "The current directory is $PWD"
echo "The current directory is $(pwd)"
exit 0
```

# 算术扩展

`$((...))`扩展

```bash
#!/bin/sh
x=0
while [ "$x" –ne 10 ]; do
    echo $x
    x=$(($x+1))
done
exit 0
```

# 参数扩展

* 问题：批处理`1_tmp, 2_tmp, ...`
* 方法 

```bash
#!/bin/sh
i=0
while [ "$i" –ne 10 ]; do
    touch “${i}_tmp”
    i=$(($i+1)) 
done
exit 0
```

![](https://ws1.sinaimg.cn/large/006tNc79ly1fq0w6h142nj31kw0d1qn8.jpg)

##### 例：将文件更换扩展名

  ```bash
  "${file%.*}".obj
  ```

# 即时文档

在 Shell 脚本中向一条命令传送输入数据
定义一个结束符，只有在捕获到结束符（串）时输入才被认为结束

##### 例

```bash
#!/bin/bash
cat >> file.txt << !CATINPUT! 
Hello, this is a here document. 
!CATINPUT!
```

# Ch3

# 编译链接

![](https://ws3.sinaimg.cn/large/006tNc79ly1fq0x5yqoujj310i0mmn7x.jpg)

* 头文件和`#include`（预处理 – 编译时处理）
* 为什么要做链接?（link）
    * 编译的时候源代码和目标文件是一一对应的，连接的时候目标文件和可执行文件不是一一对应的，最终多个目标文件生成的可执行文件只有一个。
    * 连接时再进行重组, 目标文件里已经是 native binary 了，但是只有对应源代码文件的机器码，但是执行不起来，因为可能缺少调用其他源代码文件的代码。
* 静态库（`.a`）与动态库（`.so`）
    * 静态库的代码在**编译**过程中已经被载入可执行程序，因此体积比较大
    * 动态库的代码在**可执行程序运行**时才载入内存，在编译过程中仅简单的引用，因此代码体积比较小

# 编译器分前端和后端

* 前面处理语言差异
* 后面统一分析、编译

# gcc

## 最常用命令

```
gcc -c          #（编译）
gcc             #（链接或者编译+链接）
g++             #（C++ 对应的命令，其实就是换了前端）       
```

## 选项

```
gcc [options] [filename]
```

|选项|含义|
|---|---|
|`-E`|只对源程序进行预处理（调用 cpp 预处理器）|
|`-S`|只对源程序进行预处理、编译|
|`-c`|执行预处理、编译、汇编，而不链接|
|`-o output_file`|指定输出文件名
|`-g`|产生调试工具必须的符号信息|
|`-O/On`|在编译、链接过程中进行优化处理|
|`-Wall`|显示所有警告信息|
|`-Idir`|指定额外的头文件搜索路径|
|`-Ldir`|指定额外的库文件搜索路径|
|`-lname`|链接时搜索指定的库文件|
|`-DMACRO[=DEFN]`|定义`MACRO`宏|

# makefile

只需要一个`make`命令，整个工程完全自动编译。make 是一个命令工具，是一个解释 makefile 中指令的命令工具。

[参考](https://blog.csdn.net/ruglcc/article/details/7814546/)

* makefile 描述模块间的依赖关系
* `make`命令根据 makefile 对程序进行管理和维护
* make 判断被维护文件的时序关系

```
make [-f Makefile] [option] [target]
```

## 规则结构

```makefile
target ... : prerequisites ... 
    command
    ... 
    ...
```

* target 是一个目标文件，可以是 object File，也可以是执行文件
* prerequisites 是要生成 target 所需要的文件或是目标
* command 是 make 需要执行的命令（可以是任意的 Shell 命令）

## 执行次序

1. `make`会在当前目录下找名字叫 `Makefile` 或 `makefile` 的文件。
2. 查找文件中的**第一个目标文件**（target），举例中的`hello`。
3. 如果`hello`文件不存在，或是`hello`所依赖的文件修改时间要比`hello`新，就会执行后面所定义的命令来生成`hello`文件。
4. 如果`hello`所依赖的`.o`文件不存在，那么`make`会在当前文件中找目标为`.o`文件的依赖性，如果找到则再根据那一个规则生成`.o`文件。(类似一个堆栈的过程)
5. `make` 根据`.o`文件的规则生成 `.o` 文件，然后再用 `.o` 文件生成`hello`文件。

##### 例

```makefile
hello : main.o kbd.o
    gcc -o hello main.o kbd.o 
main.o : main.c defs.h
    cc -c main.c
kbd.o : kbd.c defs.h command.h
    cc -c kbd.c 
clean :
    rm edit main.o kbd.o
```

# 文件和文件系统

## 文件

* An object that can be written to, or read from, or both. 
* A file has certain attributes, including access permissions and type.

## 文件系统

* 文件系统是文件及其属性的集合。
* 文件系统提供了指向这些文件的序列号。

# 7 种文件类型

|文件类型|判断类型宏|说明|
|:-:|:-:|:-:|
|普通文件|`S_ISREG()`|纯文本文档、二进制文件、数据格式文件等|
|字符设备|`S_ISCHAR()`|与设备进行交互的文件。Linux 中所有的设备都被抽象为了对应的文件。字符设备是按字符读取。|
|块设备|`S_ISBLK()`|同字符设备文件，但是是按块读取。|
|FIFO（管道）|`S_ISFIFO()`|主要的目的在解决多个程序同时存取一个文件所造成的错误问题。|
|socket（套接字）|`S_ISSOCK()`|我们可以启动一个程序来监听客户端的要求，而客户端就可以通过这个 socket 来进行数据的沟通。如启动 MySQL 服务会创建一个对应的 socket 文件。一般在 `/var/run` 目录中。|
|符号链接|`S_ISLNK()`||
|目录|`S_ISDIR()`||

# VFS

VFS 在内核中与其他的内核模块的协同关系

![](https://www.ibm.com/developerworks/cn/linux/l-cn-vfs/3.jpg)

## 结构

![](https://ws1.sinaimg.cn/large/006tNc79ly1fq0xbqttucj310s0k07as.jpg)

![](https://ws1.sinaimg.cn/large/006tNc79ly1fq0xcki8oaj30vg0kc47a.jpg)

## 功能

- 文件的统一管理和抽象
- 将对应的用户的**文件操作转换成对应的系统级操作**
- 虚拟的，只存在于内存中

## 组成部分

### 超级块

- 描述当前的文件系统
- 来标识文件系统/分区的
- 标定当前所要访问的文件系统
- 进程要打开的文件在哪个分区上，是什么文件系统，以及文件系统的信息，需要什么方式来访问

### inode 对象

- 磁盘上的文件用 i-node 标识
- 全称 index-node，索引结点
- 索引结点相同表示是分区下的同一个文件
- 用来标识文件，只要知道索引结点就可以找到文件，Linux 可以同一个文件有几个不同的文件名
- 也就是说可以在目录项对象中对应两个文件名，但是其实索引节点只有一个，但是可以由两个文件名来访问它，指向它

### 文件对象

- 描述文件当前的打开状态
- 在一个进程还没运行时，超级块、索引节点、目录项对象都是有的，因为系统肯定会知道当前系统的文件系统信息，**但是文件对象是没有的**，只有在创建的进程启动之后，cp 调完 open 之后(之前可能有内存拷贝、变量赋值...)，也就是说只有把一个文件打开之后，VFS 才会在内核建立一个文件对象
- 进程结束之后一定要 close，这样才可以把文件对象释放掉
- 打开的文件一定要关闭，文件对象存在于打开和关闭之间
- 用来记录文件对象记录当前进程把这个文件读到哪，以什么方式在读
- 用于给进程提供访问文件

### 目录对象

- 描述文件的目录关系（inode号和文件名的对应关系），是路径的一部份
- 记录文件名
- 磁盘上的文件不以目录形式组织，由文件系统来决定由什么形式来组织
- 以上两种不同的组织形式之间的对应关系就放在目录项对象

# 硬链接和软链接

## 硬链接

- 不同文件名对应同一个 inode
- 不能跨越文件系统
- 对应**系统调用 link**
- `ls -l`的链接计数**只包括硬链接**

## 软链接/符号链接

- 存储被链接文件的文件名（不是 inode 号）来实现链接
- 可以跨越文件系统
- 对应**系统调用symlink**
- 软链接 类似于 Windows 下的快捷方式，删除原文件后（原文件也没有任何硬链接文件）软连接不可用

## 创建

* 硬链接

```bash
ln [原文件名] [连接文件名]
```

* 符号链接 

```bash
ln –s [原文件名] [连接文件名]
```

# 系统调用与库函数

都以 C 函数的形式出现

## 系统调用

* Linux 内核的对外接口
* 用户程序和内核之间**唯一**的接口
* 提供最小接口
    
## 库函数

* 依赖于系统调用
* 提供较复杂的功能

# 文件描述符

* `int fd`
* 一个小的**非负整数**

|流|文件描述符|
|:-:|:-:|
|标准输入（STDIN_FILENO）|0|
|标准输出（STDOUT_FILENO）|1|
|标准错误（STDERR_FILENO）|2|

# 基础 I/O 系统调用

一般的文件操作流程：`open`→`read/write`→`[lseek]`→`close`

##### 例

```C
#include <fcntl.h>
main() {
    int fd, nread; 
    char buf[1024];

    /*open file “data” for reading */ 
    fd = open(“data”, O_RDONLY);

    /* read in the data */
    nread = read(fd, buf, 1024);

    /* close the file */
    close(fd); 
}
```

## open/creat

打开、创建一个文件，并获得该文件的文件描述符

### 原型

```C
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode); 
int creat(const char *pathname, mode_t mode);
// (Return: a new file descriptor if success; -1 if failure) 
```

### 参数

* `pathname`：文件名
* `flags`：文件打开模式，表示以什么方式打开，可以是 `O_RDONLY`、`O_WRONLY`、`
O_RDWR`，依次表示只读、只写、读写中的一个。以上 3 个模式可以和一些附加模式做按位或（|）运算，添加其他的模式。如:
    * `O_APPEND`：以追加模式打开
    * `O_TRUNC`：若文件存在，则长度被截为 0，属性不变。（覆盖模式）
    * `O_CREAT`：如果文件不存在，则创建它
    * `O_EXCL`：同 `O_CREAT` 一起使用，使得当文件存在的时候会出现错误
    * `O_NONBLOCK`：对于设备文件，以 `O_NONBLOCK` 方式打开可以做非阻塞 I/O（Nonblock I/O）
    * 创建一个文件等价于用 `O_CREAT|O_WRONLY|O_TRUNC` 模式打开文件
* `mode`：当创建一个文件时指定文件的权限。值为一个无符号整数，低 9 位确定权限（同 `chmod` 里使用的值）

## close

关闭一个文件描述符

### 原型

```C
#include <unistd.h>

int close(int fd);
// (Return: 0 if success; -1 if failure) 
```

### 参数

* `fd`：需要关闭的文件描述符

## read/write

根据指定文件描述符的文件读取/写入文件内容

### 原型

```C
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
// (返回值: 读到的字节数，若已到文件尾为0，若出错为-1) 

ssize_t write(int fd, const void *buf, size_t count); 
// (返回值: 若成功为已写的字节数，若出错为-1) 
```

### 参数

* `fd`：对应的文件描述符
* `buf`：待读取/写入文件的缓冲区
* `count`：读取/写入文件的字节数

### 示例

```C
while ((n = read(STDIN_FILENO, buf, BUFSIZE)) > 0)  
    if (write(STDOUT_FILENO, buf, n) != n) 
        err_sys(“write error”); 
    if (n<0) 
        err_sys(“read error”);
```

## lseek

设置读写文件的偏移

### 原型

```C
#include <sys/types.h>
#include <unistd.h>

off_t lseek(int fildes, off_t offset, int whence);
// (Return: the resulting offset location if success; -1 if failure) 
```

### 参数

* `fildes`：对应的文件描述符
* `offset`：偏移量
* `whence`：偏移的方式，有 3 个取值
    * `SEEK_SET`：偏移到`offset`位置处（相对文件头）
    * `SEEK_CUR`：偏移到当前位置`+offset`位置处
    * `SEEK_END`：偏移到文件尾`+offset`位置处

## dup/dup2

复制文件描述符

* `dup` 产生一个相同的文件描述符指向同一个文件。
* `dup2` 复制一个旧的文件描述符到新的文件描述符，使得新的文件描述符与旧的文件描述符完全一样，过程主要是先关闭新的文件描述符对应的文件，然后进行复制。

### 原型

```C
#include <unistd.h>

int dup(int oldfd);
int dup2(int oldfd, int newfd);
// (Return: the new file descriptor if success; -1 if failure) 
```

### 参数

* `oldfd`：旧的文件描述符
* `newfd`：新的文件描述符（目标文件描述符）

### 使用

通常用于重定向，与 `STDERR_FILENO`、`STDIN_FILENO`、`STDOUT_FILENO` 结合使用。

```C
fd2=dup(STDOUT_FILENO);//保存标准输出
fd = open(filename, O_WRONLY|O_CREAT, fd_mode); //打开文件 
dup2(fd, STDOUT_FILENO); //把输出重定向到 fd 标识的文件 close(fd);
```

## fcntl

操作一个文件描述符，改变一个已经打开的文件的属性

### 原型

```C
#include <unistd.h>
#include <fcntl.h>

int fcntl(int fd, int cmd);
int fcntl(int fd, int cmd, long arg);
int fcntl(int fd, int cmd, struct flock *lock); 
// (返回值: 若成功则依赖于cmd，若出错为-1) 
```

### 参数

* `fd`：对应的文件描述符
* `cmd`：具体的操作，fcntl 进行的操作依赖于 cmd。有以下取值：
    * `F_DUPFD`：复制文件描述符，返回新的文件描述符。
    * `F_GETFD/F_SETFD`：获取/设置文件描述符标志（目前就只有 `close-on-exec` 标记）。这个标志的目的是解决 fork 子进程执行其他任务（使用 `exec`、`excel` 等命令）导致了父进程的文件描述符被复制到子进程中（实际子进程不需要），使得对应文件描述符无法被之后需要的进程获取。设置了这个标记后可以使得子进程在执行 `exce` 等命令时释放对应的文件描述符资源。
    * `F_GETFL/F_SETFL`：获得/设置文件状态标志（`open/creat` 中的 `flags` 参数），目前只能更改 `O_APPEND`, `O_ASYNC`, `O_DIRECT`, `O_NOATIME`, `O_NONBLOCK`
    * `F_GETOWN/F_SETOWN`： 管理 I/O 可用相关的信号。获得或设置当前文件描述符会接受 `SIGIO` 和 `SIGURG` 信号的进程或进程组编号
    * `F_GETLK/F_SETLK/F_SETLKW`： 获得/设置文件锁，设置为 `F_GETLK` 时需要传入 `flock *` 指针用于存放最后的锁信息。`S_SETLK` 需要传入 `flock *` 指针表示需要改变的锁的内容，如果不能被设置，则立即返回 `EAGAIN`。`S_SETLKW` 同 `S_SETLK`，但是在锁无法设置时会阻塞等待任务完成。

### 和 dup 的关系
    
* `fcntl(1，F_DUPFD)` 的效果就是 `dup(1)`
* `fcntl(50,F_DUPFD,1)` 的效果就是 `dup2(50,1)`

## ioctl

和驱动相关的，会调用驱动的代码

### 原型

```C
#include <sys/ioctl.h>

int ioctl(int d, int request, ...);
```

# 标准 I/O 库

* 使用 `FILE *` 指向文件流（类似于 `fd` 的作用）
* **预定义** 3 个指针：标准输入（stdin），标准输出（stdout），标准错误（stderr）

* 3 种缓冲
    * 块缓冲（全缓冲, full buffered, block buffered）
    * 行缓冲（line buffered）
    * 无缓冲（unbuffered）

## setbuf/setvbuf

设置文件缓冲区

### 原型

```C
#include <stdio.h>

void setbuf(FILE *stream, char *buf);
int setvbuf(FILE *stream, char *buf, int mode, size_t size);
// type：_IOFBF（满缓冲）_IOLBF（行缓冲）_IONBF（无缓冲）
```

### 参数

* `stream`：文件指针
* `buf`：对应的缓冲区
* `mode`：缓冲区类型
    * `_IOFBF`(满缓冲)
    * `_IOLBF`(行缓冲)
    * `_IONBF`(无缓冲)
* `size`：缓冲区内的字节数

## fopen/fclose

打开/关闭一个文件流

### 原型

```C
#include <stdio.h>

FILE *fopen(const char *filename, const char *mode); 
int fclose(FILE *stream);
// (Return: 0 if success; -1 if failure) 
```

### 参数

* `filename`：文件名
* `mode`：打开的模式
    * `r`：只读方式打开
    * `w`：以覆盖方式写
    * `a`：以追加方式写
    * `r+`：以读写方式打开
    * `w+`：以读写方式打开，文件不存在则创建；覆盖方式写
    * `a+`：以读写方式打开，文件不存在则创建；追加方式写
* `stream`：需要关闭的文件流

## getc/fgetc/getchar

从文件中读取下一个字符，若到文件尾或出错，则返回 `EOF`

* `getc` 是宏定义，`fgetc` 是实际的函数
* `getc` 的效率更高一点
* 使用 `getc` 的时候不能有副作用：`getc(f++)` 不可以，`fgetc` 可以

### 原型

```C
#include <stdio.h>

int getc(FILE *fp);
int fgetc(FILE *fp);
int getchar(void);
// (Result: Reads the next character from a stream and returns it as an unsigned char cast to an int, or EOF on end of file or error.) 
```

## putc/fputc/putchar

写入一个字符

### 原型

```C
#include <stdio.h>

int putc(int c, FILE *fp);
int fputc(int c, FILE *fp);
int putchar(int c);
// (Return: the character if success; -1 if failure) 
```

## fgets/gets

* 读取一行字符串
* `fgets` 最多读取 `size-1` 个字符，并将其保存在 `s` 指向的缓冲区中，遇到文件尾或换行符停止
* 在缓冲区的最后添加了 `\0` 字符

### 原型

```C
#include <stdio.h>

char *fgets(char *s, int size, FILE *stream); 
char *gets(char *s); //not recommended.
```

### 参数

* `s`：缓冲区指针
* `size`：大小
* `stream`：文件流

## fputs/puts

批量写入字符，写入字符串

### 原型

```C
#include <stdio.h>

int fputs(const char *s, FILE *stream); 
int puts(const char *s);
```

### I/O 效率问题（理解）

> 使用缓冲可以减少读取文件的时间。在缓冲区较小的时候，增加缓冲区大小可以显著减小读取时间，因为这时候上下文切换（切换内核/用户态）次数过多，是主要影响读取时间的因素。当缓冲区大小到一定大小时，读取时间几乎不变，这是因为上下文切换已经不是主要影响因素，而主要耗时的操作在数据的读取的固定时间上。

## fread/fwrite

读取、写入文件

### 原型

```C
#include <stdio.h>

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
// (Return: the number of a items successfully read or written.) 
```

### 参数

* `ptr`：缓冲区指针
* `size`：一次读取/写入的字节数
* `nmemb`：读取/写入的字节数
* `stream`：文件流

### 使用

* Read/write a binary array

```C
float data[10];
if (fwrite(&data[2], sizeof(float), 4, fp) != 4) {
    err_sys(“fwrite error”);
}
```

* Read/write a structure 

```C
struct {
    short count; 
    long total; 
    char name[NAMESIZE]; 
} item;
if (fwrite(&item, sizeof(item), 1, fp) != 1) {
    err_sys(“fwrite error”);
}
```

## scanf/fsacnf/sscanf

格式化输入

### 原型

```C
#include <stdio.h>

int scanf(const char *format, ...);
int fscanf(FILE *stream, const char *format, ...); 
int sscanf(const char *str, const char *format, ...);
```

## printf/fprintf/sprintf

格式化输出

### 原型

```C
#include <stdio.h>

int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...); 
int sprintf(char *str, const char *format, ...);
```

## fseek/ftell/rewind, fgetpos/fsetpos

重新设置流位置(`fseek` 类似 `lseek`)

### 原型

```C
#include <stdio.h>

int fseek(FILE *stream, long int offset, int whence); 
long ftell(FILE *stream);
void rewind(FILE *stream);
```

```C
#include <stdio.h>

int fgetpos(FILE *fp, fpos_t *pos);
int fsetpos(FILE *fp, const fpos_t *pos);
```

## fflush

刷新文件流，把流里的数据立刻写入文件

### 原型

```C
#include <stdio.h>

int fflush(FILE *stream);
```

## fileno/fdopen

进行底层文件描述符与文件流之间的操作

### 原型

确定流使用的底层文件描述符

```C
#include <stdio.h>

int fileno(FILE *fp);
```

根据已打开的文件描述符创建一个流

```C
#include <stdio.h>

FILE *fdopen(int fildes, const char *mode);
```

# 高级系统调用

## stat/fstat/lstat

获得文件的属性信息

### 原型

```C
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>

int stat(const char *filename, struct stat *buf); 
int fstat(int filedes, struct stat *buf);
int lstat(const char *file_name, struct stat *buf); 
// (Return: 0 if success; -1 if failure) 
```

```C
struct stat {
    mode_t st_mode;     /*file type & mode*/
    ino_t st_ino;       /*inode number (serial number)*/ 
    dev_t st_rdev;      /*device number (file system)*/ 
    nlink_t st_nlink;   /*link count*/
    uid_t st_uid;       /*user ID of owner*/
    gid_t st_gid;       /*group ID of owner*/
    off_t st_size;      /*size of file, in bytes*/
    time_t st_atime;    /*time of last access*/
    time_t st_mtime;    /*time of last modification*/
    time_t st_ctime;    /*time of last file status change*/
    long st_blksize;    /*Optimal block size for I/O*/
    long st_blocks;     /*number 512-byte blocks allocated*/
 };
```

`st_mode` 里保存了文件的类型、权限等信息。低 9 位保存权限信息，每一位依次为用户的读、写、执行，用户组的读、写、执行，其他用户的读、写、执行。 [9:11]位依次为 sticky、SGID、SUID，[12:17]保存了文件的类型。

## SUID，SGID 和粘滞位

[参考](https://blog.csdn.net/fouy_yun/article/details/9613167)

### SET 位权限

> 位权限多用于给可执行的程序或脚本文件进行设置，其中SUID表示对属主用户增加SET位权限，SGID表示对属组内 的用户增加SET位权限。执行未见被设置了SUID、SGID权限后，任何用户在执行该文件时，将获得该文件属主、属组账号对应的
> 为执行文件添加SET位权限一般使用chmod命令实现：
> 如使用“chmod u+s”设置SUID权限，使用“chmod g+s”设置SGID权限。
> 也可以使用数字形式，SUID对应八进制数字“4”、SGID对应八进制数字“2”:
> 如使用“chmod 4755”设置SUID权限，使用“chmod 2755”设置SGID权限，使用“chmod 6755”同时设置SUID和SGID权限
> 合理利用SUID、SGID设置SET位权限，可以在确保安全性的同时为linux系统的管理和使用带来方便。例如，linux系统中passwd命令的程序文件就被设置了SUID权限，正因为如此，尽管普通用户无法直接修改“/etc/shadow”文件，但仍然可以通过passwd命令修改自己的登录密码，从而以root用户的身份间接更新shadow文件中的密码信息。
> 另一方面，若没有确切的应用需要，不要轻易为可执行文件设置SET位权限，特别是那些属主、属组是root的执行程序，使用SET位权限时更应该谨慎。例如，若为vim编辑器程序设置SUID权限，将导致普通用户也可以使用vim编辑器修改系统中的任何配置文件。
> 需要去除SUID、SGID权限时，只需要使用“u-s”、“g-s”的权限模式即可。

### 粘滞位权限

> 粘滞位主要用于为目录设置特殊的附加权限，当目录被设置粘滞位权限后，即便用户对该目录有写入权限，也不能删除该目录中其他用户的文件数据。设置了粘滞位权限的目录，使用ls命令查看其属性时，其他用户权限处的“x”将变为“t”。
> 使用chmod命令设置目录权限时，“chmod +t”、“chmod -t”权限模式可分别用于添加、移除粘滞位权限。将数字权限模式“nnnn”中 的第1位数字改为“1”、“0”，也可以实现添加移除粘滞位权限。

### SUID

当设置了 SUID 位的文件被执行时，该文件将以所有者的身份运行，也就是说无论谁来执行这个文件，他都有文件所有者的特权。

#### 操作

```bash
chmod 4755 aa.sh
# 或
chmod u+s aa.sh
```

### SGID

与上面的内容类似，用于设置目录。一个目录被标上 `setgid` 位，此目录下创建的文件**继承**该目录的属性。文件运行时运行者将具有所属组的特权。

#### 操作

```bash
chmod 2755 aa
# 或
chmod g+s aa
```

### sticky-bit

该位可以理解为防删除位。设置 sticky bit 位后，就算用户对目录具有写权限，但也只能添加文件而不能删除其他用户创建的文件。

#### 操作

```bash
chmod 1755 aa
# 或
chmod o+t aa
```

粘滞位意味着**在这个文件夹里创建的文件是否具有用户的互斥性**

## access

按**实际用户 ID**和**实际组 ID**测试文件的存取权限

### 原型

```C
#include <unistd.h>

int access(const char *pathname, int mode);
// (Return: 0 if success; -1 if failure) 
```

### 参数

* `pathname`：文件路径
* `mode`：取值为 `R_OK`, `W_OK`, `X_OK`, `F_OK` 依次为测试读取、写入、执行权限和文件是否存在

## chmod/fchmod

更改一个文件的权限

### 原型

```C
#include <sys/types.h>
#include <sys/stat.h>

int chmod(const char *path, mode_t mode); 
int fchmod(int fildes, mode_t mode); 
// (Return: 0 if success; -1 if failure) 
```

### 参数

* `mode`：与 `st_mode` 中的低九位相同（普遍的权限格式）

## chown/fchown/lchown

改变一个文件的所有者

### 原型

```C
#include <sys/types.h> 
#include <unistd.h>

int chown(const char *path, uid_t owner, gid_t group); 
int fchown(int fd, uid_t owner, gid_t group);
int lchown(const char *path, uid_t owner, gid_t group); 
// (Return: 0 if success; -1 if failure) 
```

## umask

为进程设置文件存取权限屏蔽字，并返回以前的值

### 原型

```C
#include <sys/types.h>
#include <sys/stat.h>

mode_t umask(mode_t mask);
```

### 参数

* `mask`，对应的 mask 值（进程默认为 `022`，八进制）

## link/unlink

创建/删除一个文件的（硬）链接

### 原型

```C
#include <unistd.h>

int link(const char *oldpath, const char *newpath); 
int unlink(const char *pathname);
// (Return: 0 if success; -1 if failure) 
```

## symlink/readlink

创建/读取符号（软）链接的值

### 原型

```C
#include <unistd.h>

int symlink(const char *oldpath, const char *newpath); 
// (Return: 0 if success; -1 if failure) 

int readlink(const char *path, char *buf, size_t bufsiz);
// (Return: the count of characters placed in the buffer if success; -1 if failure) 
```

## mkdir/rmdir

创建/删除空目录

### 原型

```C
#include <sys/stat.h>
#include <sys/types.h>

int mkdir(const char *pathname, mode_t mode); 
int rmdir(const char *pathname);
// (Return: 0 if success; -1 if failure) 
```

## chdir/fchdir

改变当前的工作目录

### 原型

```C
#include <unistd.h>

int chdir(const char *path); 
int fchdir(int fd);
// (Return: 0 if success; -1 if failure) 
```

### 说明

当前工作目录是进程的属性，所以该函数只影响调用 `chdir` 的进程本身。

## getcwd

获得当前工作目录的绝对路径

### 原型

```C
#include <unistd.h>

char *getcwd(char *buf, size_t size);
// (返回值: 若成功则为 buf，若出错则为 NULL) 
```

## opendir/closedir/readdir/telldir/seekdir

目录的打开、关闭、读、定位

### 原型

```C
#include <sys/types.h>
#include <dirent.h>

DIR *opendir(const char *name); 
int closedir(DIR *dir);
struct dirent *readdir(DIR *dir); 
off_t telldir(DIR *dir);
void seekdir(DIR *dir, off_t offset);
```

##### 例

```C
DIR *dp;
struct dirent *entry;
if ((dp = opendir(dir)) == NULL)  
    err_sys(...);
while ((entry = readdir(dp)) != NULL) {
    lstat(entry->d_name, &statbuf);
    if (S_ISDIR(statbuf.st_mode))
        ...
    else
        ... 
}
closedir(dp);
```

# 文件锁

几个进程同时操作一个文件

* 记录锁
    * 可以精细的锁定文件的一个部分，多少多少字节锁
* 劝告锁
    * 劝告一下，别再往这写，但是不强制
    * 检查，加锁由应用程序自己控制
* 强制锁
    * 只要强制锁在，那么不管程序写成什么样，都打不开
    * 检查，加锁由内核控制
    * 影响`[open() read() write()]`等
* 共享锁
    * 可以读但是不能写
    * 来一个进程就可以给它加一个写锁，只读，再来一个可以再加一个读锁，依然可以读
* 排他锁
    * 既不能读也不能写
    * 来一个进程加了写锁之后，再来就不能读，除非释放之后再加一个个锁

## 标志位

```
mount -o mand /dev/sdb7 /mnt
```

* 把磁盘上的分区 `sdb7` 挂载到目录下 `/mnt` 
* 参数 `-o` 把超级块中的标志位 `s_flags` 
* 这样就可以对文件进行加锁解锁

* super_block
    * s_flags
* MS_MANDLOCK 

## fcntl 记录锁

用于记录锁的`fcntl`函数原型

### 原型

```C
#include <unistd.h>
#include <fcntl.h>

int fcntl(int fd, int cmd, struct flock *lock);
// (返回值: 若成功则依赖于 cmd，若出错为 -1) 
```

### `flock`结构体

```C
struct flock { 
    ...
    short l_type;   /* Type of lock: F_RDLCK, F_WRLCK, F_UNLCK */
    short l_whence; /* How to interpret l_start: SEEK_SET, SEEK_CUR, SEEK_END */
    off_t l_start;  /* Starting offset for lock */ 
    off_t l_len;    /* Number of bytes to lock */
    pid_t l_pid;    /* PID of process blocking our lock (F_GETLK only) */
    ...
}
```

### cmd 参数

* `F_GETLK`：获得文件的封锁信息
* `F_SETLK`：对文件的某个区域封锁或解除封锁
* `F_SETLKW`：功能同`F_SETLK`, wait方式

## lockf

对文件进行加/释放锁

### 原型

```C
#include <sys/file.h>

int lockf(int fd, int cmd, off_t len);
```

### 参数

* `fd`：对应的文件描述符
* `cmd`：指定的操作类型，取值为以下
    * `F_LOCK`：给文件加互斥锁，若文件以被加锁，则会一直阻塞到锁被释放。
    * `F_TLOCK`：同 `F_LOCK`，但若文件已被加锁，不会阻塞，而回返回错误。
    * `F_ULOCK`：解锁。
    * `F_TEST`：测试文件是否被上锁，若文件没被上锁则返回 0，否则返回 -1。
* `len`：为从文件当前位置的起始要锁住的长度。

`lockf` 是 `fcntl` 的一个库层次上的封装，但是不支持共享锁。

# Ch4

# 内核的概念

## 定义

操作系统是一系列程序的集合，其中最重要的部分构成了内核

## Linux 内核能力

内存管理，文件系统，进程管理，多线程支持，抢占式，多处理支持

## 层次结构

![](https://ws2.sinaimg.cn/large/006tNc79ly1fq0xpn6bhhj314w0jgwo2.jpg)

# 启动新内核

* `make install`（慎用）
    * 将编译好的内核copy到`/boot`
* **配置引导菜单**

# 驱动

* 许多常见驱动的源代码**集成在内核源码里**
* 也有第三方开发的驱动，可以单独编译成`模块.ko`
* 编译需要内核头文件的支持

# 加载模块的命令

- `insmod <module.ko> [module parameters]` 加载模块 
    - **只有超级用户才能使用这个命令！！！**
- `rmmod` 卸载 unload 模块
- `lsmod` 列出内核中所有加载的模块
    - 和`cat /proc/modules`等价
- `modprobe [-r] <module name>` 加载指定的模块和它依赖的模块

# 模块依赖

* 一个模块 A 引用另一个模块 B 所导出的符号，我们就说模块 B 被模块 A 引用。
* 如果要装载模块 A，必须先要装载模块 B。否则，模块 B 所导出的那些符号的引用就不可能被链接到模块 A 中。这种模块间的相互关系就叫做**模块依赖**。
* 自动按需加载
* 自动按需卸载
* moddep
* lsmod
* modinfo

# 模块之间的通讯

模块是为了完成某种特定任务而设计的。其功能比较的单一，为了丰富系统的功能，所以模块之间常常进行通信。其之间可以共享变量，数据结构，也可以调用对方提供的功能函数。

# 内核模块和应用程序的区别

|| C 语言程序  | Linux内核模块 |
| :-: | :-: | :-: |
| 运行   | 用户空间   | 内核空间 |
| 入口   | main() | module_init()指定 |
| 出口   | 无 | module_exit()指定 |
| 运行   | 直接运行 | insmod |
| 调试   | gdb | kdbug，kdb，kgdb等  |

# 注意点

* 不能使用 C 库开发驱动程序
* 没有内存保护机制
* 小内核栈
* 并发上的考虑


