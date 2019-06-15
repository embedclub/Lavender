## git使用记录

### git初始化部分

```
git config --global user.email "XXX@gmail.com"
git config --global user.name "nano"

git clone 网址
```

### 修改后操作步骤
```
git status
git add .
git commit -m "modified the dir"
git pull
git push -u origin mystruct
```

### 常用命令

```
git branch

```

```
git log
#### 显示当前仓库更新的记录

git log --oneline
#### 一行显示log信息

git log --author=xxx
#### 查看某个作者提交的更新记录（代码提交记录）

```




### git代理设置

#### 设置
```
git config --global http.proxy http://127.0.0.1:1080
git config --global https.proxy https://127.0.0.1:1080
git config --global http.proxy 'socks5://127.0.0.1:1080' 
git config --global https.proxy 'socks5://127.0.0.1:1080'
```

#### 取消
```
git config --global --unset http.proxy
git config --global --unset https.proxy
```
.gitignore 文件使用说明
> 我们在使用 Git 进行版本控制的时候，有些文件是无需纳入 Git 管理的，通常都是些自动 生成的文件，像日志或者编译过程中创建的文件。我们可以创建一个名为 .gitignore 的文件，列出要忽略的文件来解决这个问题。
```
    # cat .gitignore
    *.[oa]
    *~
```
第一行告诉 Git 忽略所有以 .o 或 .a 结尾的文件。一般这类对象文件和存档文件都是编译过程中出现的，我们用不着跟踪它们的版本。
第二行告诉 Git 忽略所有以波浪符（~）结尾的文件，许多文本编辑软件（比如 Emacs）都用这样的文件名保存副本。此外，你可能还需要忽略 log，tmp 或者 pid 目录，以及自动生成的文档等等。要养成一开始就设置好 .gitignore 文件的习惯，以免将来误提交这类无用的文件。

文件 .gitignore 的格式规范如下：
<pre>
所有空行或者以注释符号 ＃ 开头的行都会被 Git 忽略。
可以使用标准的 glob 模式匹配。
匹配模式最后跟反斜杠（/）说明要忽略的是目录。
要忽略指定模式以外的文件或目录，可以在模式前加上惊叹号（!）取反。

所谓的 glob 模式是指 shell 所使用的简化了的正则表达式。
星号（*）匹配零个或多个任意字符；
[abc] 匹配任何一个列在方括号中的字符（这个例子要么匹配一个 a，要么匹配一个 b，要么匹配一个 c）；
问号（?）只匹配一个任意字符；
如果在方括号中使用短划线分隔两个字符，表示所有在这两个字符范围内的都可以匹配（比如 [0-9] 表示匹配所有 0 到 9 的数字）。
</pre>
