# 作业 2

Shell 脚本编写

## 第 1 题

编写一个 Shell 脚本显示 `HOME`、`PATH`、`SHLVL`、`LOGNAME` 变量的值。

#### 解答

```
#!/bin/sh
echo "PATH: $PATH"
echo "HOME: $HOME"
echo "SHLVL: $SHLVL"
echo "LOGNAME: $LOGNAME"
exit 0
```

#### 运行结果

```
➜  ~ source /Users/Kray/Documents/Software\ Engineering/Linux程序设计/LinuxLab/Homework2/2_1.sh
PATH: /anaconda3/bin:/Users/Kray/flutter/bin:/Users/Kray/.sdkman/candidates/gradle/current/bin:/Users/Kray/.rvm/gems/ruby-2.3.0/bin:/Users/Kray/.rvm/gems/ruby-2.3.0@global/bin:/Users/Kray/.rvm/rubies/ruby-2.3.0/bin:/opt/local/bin:/opt/local/sbin:/Library/Frameworks/Python.framework/Versions/2.7/bin:/Library/Frameworks/Python.framework/Versions/3.5/bin:/usr/local/maven/apache-maven-3.3.9/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/Library/TeX/texbin:/opt/X11/bin:/Library/Frameworks/Mono.framework/Versions/Current/Commands:/usr/local/mysql/bin:/Library/Tomcat/bin:/Users/Kray/.rvm/bin:/Users/Kray/Library/Python/3.5/bin
HOME: /Users/Kray
SHLVL: 1
LOGNAME: Kray

[进程已完成]
```
    
## 第 2 题

用 `while` 语句重写下列 Shell 脚本程序，以实现相同的功能：

```
#!/bin/sh
clear
select item in Continue Finish
do
case “$item” in
        Continue) ;;
        Finish) break ;;
        *) echo “Wrong choice! Please select again!” ;;
esac
done
```

#### 解答

```
#!/bin/sh
clear
echo '1) Continue'
echo '2) Finish'
echo –n '#?'

while read item
do 
	if [ "$item" = "1" ]
	then
		continue
	elif [ "$item" = "2" ]
	then 
		break
	else 
		echo 'Wrong choice! Please select again!'
	fi
done
exit 0
```

#### 运行结果

```
Last login: Fri Mar 16 15:15:02 on ttys000
➜  ~ source /Users/Kray/Documents/Software\ Engineering/Linux程序设计/LinuxLab/Homework2/2_2.sh
1) Continue
2) Finish
–n #?
1
1
1
3
Wrong choice! Please select again!
3
Wrong choice! Please select again!
3
Wrong choice! Please select again!
2

[进程已完成]
```

## 第 3 题
 
编写一个 Shell 脚本，显示 `Fibonacci` 数列的前10个数字。
(`Fibonacci`数列: `a[i+2]=a[i+1]+a[i]`, `a[1]=0`, `a[2]=1`, `i>=1`)

#### 解答

```
#!/bin/sh
echo 'Fibonacci 1 - 10:'
a=0
b=1
i=1
while [[ "$i" -le 10 ]]; do
	echo "$a"

	a=$(($a+$b))
	t=$a
	a=$b
	b=$t

	i=$(($i+1))
done
exit 0
```

#### 运行结果

```
➜  ~ source /Users/Kray/Documents/Software\ Engineering/Linux程序设计/LinuxLab/Homework2/2_3.sh
Fibonacci 1 - 10:
0
1
1
2
3
5
8
13
21
34

[进程已完成]
```

