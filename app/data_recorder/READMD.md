## Data-Recorder 行情收录系统

启动方式配置config目录下账户密码，使用`python task.py`启动程序。
```
# SimNow ctp-future交易接口设置
class ConfigCTPFutureTDApi:
    ip = r"tcp://180.168.146.187:10202"
    broker_id = r"9999"
    user_id = r""
    password = r""
    app_id = r"simnow_client_test"
    auth_code = r"0000000000000000"
```

在coder-server内启动程序
![](https://github.com/dybeta2021/MyOTP/blob/main/app/data_recorder/images/fig1.png)

，正常运行的状态，tick数据写入clickhouse的buffer-table，数据库自行管理buffer异步落地。

![](https://github.com/dybeta2021/MyOTP/blob/main/app/data_recorder/images/fig2.png)