#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Project  : ctp_future_static_data
# @File     : task.py
# @Author   : 稻草人
# @Time     : 2022/6/14 19:32

from app_ctp_spot_static_data import get_static_data

ip = r""
broker_id = r""
user_id = r""
password = r""
app_id = r""
auth_code = r""

data = get_static_data(ip=ip,
                       broker_id=broker_id,
                       user_id=user_id,
                       password=password,
                       app_id=app_id,
                       auth_code=auth_code)
print(data)
