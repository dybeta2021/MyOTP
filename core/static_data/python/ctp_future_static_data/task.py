#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Project  : ctp_future_static_data 
# @File     : task.py 
# @Author   : 稻草人
# @Time     : 2022/6/14 19:32

from app_ctp_future_static_data import get_static_data

ip = r"tcp://180.168.146.187:10201"
broker_id = r"9999"
user_id = r""
password = r""
app_id = r"simnow_client_test"
auth_code = r"0000000000000000"

data = get_static_data(ip=ip,
                       broker_id=broker_id,
                       user_id=user_id,
                       password=password,
                       app_id=app_id,
                       auth_code=auth_code)
print(data)
