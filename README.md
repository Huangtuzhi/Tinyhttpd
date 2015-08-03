##Tinyhttpd 
A tiny http server with multi-port monitoring. 


##目录结构

```
[src]
├── LICENSE               #MIT许可证
├── README.md             #使用说明
├── tinyhttpd.pro         #工程文件
#主程序
├── main.cpp              #启动多端口监听
├── serverthread.cpp      #QThread子类线程，设置IP，port及启动Server
├── server.cpp            #QTcpServer子类,多线程，每个线程对应一个port监听
├── request.cpp           #接受client请求，多线程，每个线程对应一个请求
├── response.cpp          #构造返回Request Headers
├── responsefile.cpp      #返回网页
├── responsedictionary.cpp#列举url对应目录
├── mime.cpp              #设定扩展应用
├── common.cpp            #获取当前时间
├── log.cpp               #日志系统
├── database.cpp          #Redis数据库
├── monitorui.cpp         #UI界面
├── starter.cpp           #UI界面控制逻辑
├── ips.cpp               #UI子界面控制逻辑
#配置
├── httpstatus.h          #状态码
├── tinyhttpd.ini         #服务器配置文件
├── tinyhttpd.log         #服务器日志
├── mime.txt              #mime配置
├── monitorui.ui          #UI界面配置
├── ip.ui                 #UI子界面配置
[www]                     #网站根目录
├──static
├──index.html
[response]                #网页返回状态网页
├── 301.html              #301 Permanently Moved
├── 304.html              #304 Not Modified
├── 403.html              #403 Forbidden
└── 404.html              #404 Not Found
[resource] 
├── black.png             #QT界面用到图片
├── blue.png 
[assets]           
├── database.png          
├── monitor.png
└── ip.png
```

##Todo

* <del>加入Redis数据库支持，存储访问数据</del>
* <del>加入QT界面，显示服务器配置参数</del>
* <del>界面逻辑中加入开始和停止</del>
* <del>加入QT子界面，实现界面转换。显示实时连接情况</del>
* 尝试其它的进程模型:单线程或多线程

##运行环境
+ Linux/Mac OS X
+ QT4/QT5
+ Redis/Hiredis

##使用

- 安装Redis及Hiredis

```
git clone https://github.com/antirez/hiredis.git && cd hiredis 
make 
sudo make install 
sudo ldconfig
```

- 打开配置文件tinyhttpd.ini配置服务器选项

```
[httpd]
port=1234|1235|1236   #配置服务器监听的多个端口，用|隔开
ipv6=true             #配置ipv6支持
logfile=tinyhttpd.log
show_log=true

[site]
root_path=/home/huangyi/Practice/QT/tinyhttpd/www  #网站根目录
dir_listing=true                  #是否允许获取文件树，否则返回403 forbidden
#index="index.html", "index.htm"  #配置后，直接跳到网页index.html,不列出文件树

[request]
buffer_size=1048576        #为网页文件分配的内存空间
keep_alive_enable=true     #是否打开长连接
keep_alive_default=true
keep_alive_timeout=30      #长连接timeout
keep_alive_timeout_max=300

```

- 修改Redis配置文件`/etc/redis.conf`

```
daemonize yes
```

使Redis服务器运行在daemon模式

```
redis-server /etc/redis.conf
```

##界面

QT运行界面

![image](/assets/monitor.png)

QT显示来访数据

![image](/assets/ip.png)

Redis存储数据

![image](/assets/database.png)

##原理

封装层次

```
Tinyhttpd
    |
QTcpServer
    |                                      
QTcpSocket                             
```             

多线程模型

```             

                                  fork ┌──Request A
                   ┌──Server(Port)—————├──Request B
                   |                   └──Request C 
              fork |                    
  ServerThread—————├──Server(Port)...
                   |
                   |
                   └──Server(Port)...

```

##说明

本repo参考

+ https://github.com/BYVoid/byvhttpd

+ https://github.com/awwit/httpserver

在项目基础上进行更改，感谢项目作者。

具体细节参见博客[HTTP服务器实现](http://tuzhii.com/2015/05/09/httpserver)。
