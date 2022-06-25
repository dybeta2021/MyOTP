#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Project  : quote_engine 
# @File     : config.py 
# @Author   : yangdong
# @Time     : 2022/6/18 17:41
# http://122.51.136.165:50080/detail.html
# http://122.51.136.165:50080/report/Tick%20Trading%20System%20%28TTS%297x24%BB%B7%BE%B3process%BD%BB%D2%D7.html

# 实盘接口
class ConfigCTPFutureTDApi:
    ip = r"tcp://122.51.136.165:20002"
    broker_id = r""
    user_id = r"2815"
    password = r"123456"
    app_id = r""
    auth_code = r""


class ConfigCTPFutureMDApi:
    ip = r"tcp://122.51.136.165:20004"