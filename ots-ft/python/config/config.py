#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Project  : data_recorder 
# @File     : clickhouse.py 
# @Author   : 稻草人
# @Time     : 2022/6/16 22:10
# https://github.com/krenx1983/openctp

class ConfigClickhouse:
    host = r"single-clickhouse-server"


# open-ctp
class ConfigCTPFutureTDApi:
    ip = r"tcp://122.51.136.165:20002"
    broker_id = r"1234"
    user_id = r"2815"
    password = r"123456"
    app_id = r"open_ctp"
    auth_code = r"open_ctp"


class ConfigCTPFutureMDApi:
    ip = r"tcp://122.51.136.165:20004"
