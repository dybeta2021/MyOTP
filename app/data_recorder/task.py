#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Project  : data_recorder 
# @File     : task.py 
# @Author   : 稻草人
# @Time     : 2022/6/16 22:26
from config.config import ConfigClickhouse, ConfigCTPFutureMDApi

from data_recorder import run_data_recorder
from static_data import update_static_data

if __name__ == "__main__":
    data = update_static_data(host=ConfigClickhouse.host)
    universe = data["InstrumentID"].values.tolist()
    universe = list(set(universe))
    run_data_recorder(universe=universe,
                      ip=ConfigCTPFutureMDApi.ip,
                      host=ConfigClickhouse.host,
                      log_level="info")
