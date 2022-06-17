#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Project  : data_recorder 
# @File     : clickhouse.py 
# @Author   : 稻草人
# @Time     : 2022/6/16 22:10
class ConfigClickhouse:
    host = r"single-clickhouse-server"


# SimNow ctp-future交易接口设置
class ConfigCTPFutureTDApi:
    ip = r"tcp://180.168.146.187:10202"
    broker_id = r"9999"
    user_id = r""
    password = r""
    app_id = r"simnow_client_test"
    auth_code = r"0000000000000000"


class ConfigCTPFutureMDApi:
    ip = r"tcp://180.168.146.187:10211"
