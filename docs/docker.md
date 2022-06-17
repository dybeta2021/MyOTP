## Docker设置

### 启动容器

```
docker pull ubuntu
docker run --name iubuntu -t -i -d -p 4100:22 ubuntu
docker exec -t -i iubuntu /bin/bash
```

### SSH

```
apt-get update
apt-get dist-upgrade -y 
apt-get install -y sudo vim git net-tools rsync sudo iputils-ping 
apt-get install -y openssh-client openssh-server

# 启动SSH
/etc/init.d/ssh start
ps -e|grep ssh

# 在表头添加
vim /etc/ssh/sshd_config
PermitRootLogin yes

service ssh restart
passwd root
```

### VSCode-Web

```
apt-get install -y curl

# 首次运行生成配置文件
code-server 

# 修改配置文件
vim  ~/.config/code-server/config.yaml
bind-addr: 0.0.0.0:7101
auth: password
password: 1234567890
cert: false

# 或命令行启动
code-server --port 7101 --host 0.0.0.0 --auth password 1234567890
```

### Docker-Ubunut设置时区

```
apt-get install tzdata
tzselect
```

- Run 'dpkg-reconfigure tzdata' if you wish to change it.

### 配置Docker-Ubuntu的中文环境

- [Docker容器中添加中文字符的支持](https://zhuanlan.zhihu.com/p/31078295)   

```shell
locale -a
apt-get update
apt-get install -y locales
apt-get install language-pack-zh-hans
locale-gen zh_CN
locale-gen zh_CN.utf8
locale-gen zh_CN.UTF-8
locale-gen zh_CN.GB18030

#看看当前启用的本地支持
locale -a
export LANG=zh_CN.UTF-8
export LC_ALL=zh_CN.UTF-8
export LANGUAGE=zh_CN.UTF-8

#现在来看看当前的字符集
locale

sudo update-locale LANG=zh_CN.UTF-8 LC_ALL=zh_CN.UTF-8 LANGUAGE=zh_CN.UTF-8
cat /etc/default/locale
```

### C++

```
apt-get install -y build-essential cmake gdb gdbserver
```

### Python Env

```
cd opt
wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh

bash Miniconda3-latest-Linux-x86_64.sh 
/opt/miniconda3
bash
```

### Python库

```
pip install numpy
pip install pandas
```


### 生成镜像

```
docker commit iubuntu ubuntu-simnow
docker save ubuntu-simnow > ubuntu-simnow.tar
docker run --name ubuntu-simnow -t -i -d -p 7100:22  -p 7101:7101 ubuntu-simnow /usr/sbin/sshd -D

docker exec -t -i ubuntu-simnow /bin/bash
code-server --port 7101 --host 0.0.0.0 --auth password 1234567890
```