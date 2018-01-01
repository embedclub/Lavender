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
