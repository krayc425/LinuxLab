# 作业 1

以下作业在 `Ubuntu 16.04.2 LTS 64bit` 版本系统下完成

## 第 1 题

##### 要求

* 用命令完成以下功能
* 写出对应的命令，要求命令尽可能简单
* 能一行命令完成的尽量一行命令完成, 不能使用课上教的Shell脚本或者编程方法

#### 1. 将当前目录下所有文件备份并压缩成`tar.gz`，如果成功再将备份拷贝到`/backup`目录下

```bash
mkdir /backup && tar -czvf backup.tar.gz . && cp ./backup.tar.gz /backup
```

#### 2. 将上述备份压缩后的文件解压到原来的目录

```bash
tar -xzvf /backup -C .
```

#### 3. 将当前目录下所有后缀为`.html`的文件的后缀改为`.htm`

```bash
rename 's/.html/.htm/' ./*
```

#### 4. 将当前目录下所有子目录下以`a`开头的`.cpp`文件改名为以`b`开头的`.c`文件

```bash
find -name "a*.cpp" | xargs -i rename 's/(.*\/)a(.*)\.cpp$/$1b$2\.c/' {}```
    
## 第 2 题

#### 1. 请简要叙述 DOS/Windows 中的文本文件，UNIX/Linux 中的文本文件以及 Mac 中的文本文件有何不同之处，并给出至少一种你认为较为实用的转换方案（需要两两给出转换方案）

##### 主要不同是换行符不同

| DOS/Windows | UNIX/Linux | Mac |
| :-: | :-: | :-: |
| /r/n | /n | /r |

##### 转换方案

* DOS/Windows -> UNIX/Linux: 

```bash
sed -i 's/\r$//' file.txt
```

* UNIX/Linux -> DOS/Windows:

```bash
sed -i 's/$/\r/' file.txt
```

* DOS/Windows -> Mac:

```bash
cat file.txt | tr -d "\n" > new_file.txt
```

* Mac -> DOS/Windows:

```bash
cat file.txt | tr "\r" "\n" | sed 's/$/\r/' > new_file.txt
```
 
* UNIX/Linux -> Mac: 

```bash
cat file.txt | tr "\n" "\r" > new_file.txt 
```

* Mac -> UNIX/Linux: 

```bash
cat file.txt | tr "\r" "\n" > new_file.txt
```

#### 2. 请查阅Linux系统中`/etc/fstab`文件各字段功能，并对你自己安装的Linux系统中`/etc/fstab`的各个字段做出解释

`/etc/fstab`文件包含了如下字段，通过空格或 Tab 分隔：

```bash
<file system>	<dir>	<type>	<options>	<dump>	<pass>
```

* `<file systems>` - 要挂载的分区或存储设备.
* `<dir>` - `<file systems>`的挂载位置。
* `<type>` - 要挂载设备或是分区的文件系统类型，支持许多种不同的文件系统：ext2, ext3, ext4, reiserfs, xfs, jfs, smbfs, iso9660, vfat, ntfs, swap 及 auto。 设置成 auto 类型，mount 命令会猜测使用的文件系统类型，对 CDROM 和 DVD 等移动设备是非常有用的。
* `<options>` - 挂载时使用的参数，注意有些参数是特定文件系统才有的。一些比较常用的参数有：
    * auto - 在启动时或键入了 `mount -a` 命令时自动挂载。
    * noauto - 只在你的命令下被挂载。
    * exec - 允许执行此分区的二进制文件。
    * noexec - 不允许执行此文件系统上的二进制文件。
    * ro - 以只读模式挂载文件系统。
    * rw - 以读写模式挂载文件系统。
    * user - 允许任意用户挂载此文件系统，若无显示定义，隐含启用 noexec, nosuid, nodev 参数。
    * users - 允许所有 users 组中的用户挂载文件系统.
    * nouser - 只能被 root 挂载。
    * owner - 允许设备所有者挂载.
    * sync - I/O 同步进行。
    * async - I/O 异步进行。
    * dev - 解析文件系统上的块特殊设备。
    * nodev - 不解析文件系统上的块特殊设备。
    * suid - 允许 suid 操作和设定 sgid 位。这一参数通常用于一些特殊任务，使一般用户运行程序时临时提升权限。
    * nosuid - 禁止 suid 操作和设定 sgid 位。
    * noatime - 不更新文件系统上 inode 访问记录，可以提升性能。
    * nodiratime - 不更新文件系统上的目录 inode 访问记录，可以提升性能。
    * relatime - 实时更新 inode access 记录。只有在记录中的访问时间早于当前访问才会被更新。（与 noatime 相似，但不会打断如 mutt 或其它程序探测文件在上次访问后是否被修改的进程），可以提升性能。
    * flush - vfat 的选项，更频繁的刷新数据，复制对话框或进度条在全部数据都写入后才消失。
    * defaults - 使用文件系统的默认挂载参数，例如 ext4 的默认参数为:rw, suid, dev, exec, auto, nouser, async.
* `<dump>` dump 工具通过它决定何时作备份. dump 会检查其内容，并用数字来决定是否对这个文件系统进行备份。 允许的数字是 0 和 1 。0 表示忽略， 1 则进行备份。大部分的用户是没有安装 dump 的，对他们而言 <dump> 应设为 0。
* `<pass>` fsck 读取 `<pass>` 的数值来决定需要检查的文件系统的检查顺序。允许的数字是 0, 1 和 2。 根目录应当获得最高的优先权 1, 其它所有需要被检查的设备设置为 2。 0 表示设备不会被 fsck 所检查。

下面是我的`/etc/fstab`文件内容：

```
krayc425@ubuntu:~/Desktop/LinuxTest$ cat /etc/fstab# /etc/fstab: static file system information.## Use 'blkid' to print the universally unique identifier for a# device; this may be used with UUID= as a more robust way to name devices# that works even if disks are added and removed. See fstab(5).## <file system> <mount point>   <type>  <options>       <dump>  <pass># / was on /dev/sda1 during installationUUID=df02e927-e963-497d-8130-0eeb82d530c3 /               ext4    errors=remount-ro 0       1# swap was on /dev/sda5 during installationUUID=802d9867-8a82-48c4-9033-f44123bfb455 none            swap    sw              0       0UUID=802d9867-8a82-48c4-9033-f44123bfb455 none            swap    sw              0       0```

* 每行前带`#`的为注释。
* 下面第一行表示`/dev/sda1`分区被挂载在根目录`/`下，分区格式为`ext4`，后面的`errors=remount-ro`定义了当发生错误时，系统将会重新以只读模式挂载分区。
* 第二、三行表示`/dev/sda5`分区没有被挂载在任何目录下，因为他们是`swap`分区，后面的`sw`表示自动挂载的可读写分区。
* 由于没安装`dump`，所以`dump`字段都为0，表示忽略。
* `pass`字段都为0，表示设备不会被`fsck`检查。

#### 3. 用命令行实现： 从光盘制作一个`.iso`文件，如果成功将光盘弹出

```bash
dd if=/dev/cdrom of=test.iso && umount /dev/cdrom && eject
```

## 附加题

假设当前Linux系统的目录`/tmp/gsl`下的文件结构如下图所示，其中有很多`Makefile`分散在各个子目录下(但并非每个子目录都存在`Makefile`，例如`block`目录下就没有)

```
.
|-- INSTALL
|-- Makefile
|-- NEWS
|-- ...
|-- blas
|   |-- ChangeLog
|   |-- Makefile
|   |-- TODO
|   |-- blas.c
|   |-- ...
|-- block
|   |-- ChangeLog
|   |-- block.c
|-- bspline
|   |-- Makefile
|   |-- ...
|-- ...

```

要求将这些`Makefile`拷贝到目录`/home/usrname/gsl`的对应子目录下(假设`/home/usrname/gsl`下已经存在`blas`，`bspline`等子目录)，使得拷贝后`/home/usrname/gsl`下的文件如下图所示：

```
.
|-- Makefile
|-- blas
|   |-- Makefile
|-- bspline
|   |-- Makefile
|-- ...
```

##### 解法

1. 找到`/tmp/gsl`目录中所有名为`Makefile`的文件
2. 将输出结果每一条的`/tmp`部分替换成空串
3. 以第2步结果的每一条输出为参数，替换到`{}`中，然后执行`cp /gsl/.../Makefile /home/usrname/gsl/.../Makefile`
4. 用`sh`运行脚本

```bash
find /tmp/gsl -name 'Makefile' | sed 's/^\/tmp//' | xargs -i cp {}  /tmp/{} /home/usrname/{} | sh
```

