#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Project  : data_recorder 
# @File     : task.py 
# @Author   : 稻草人
# @Time     : 2022/6/16 22:26
from config.clickhouse import DockerClickhouseConfig
from config.ctp import CTPFutureMarketDataConfig
from data_recorder import run_data_recorder
from static_data import update_static_data

if __name__ == "__main__":
    data = update_static_data(host=DockerClickhouseConfig.host)
    universe = data["InstrumentID"].values.tolist()
    universe = list(set(universe))
    run_data_recorder(universe=universe,
                      ip=CTPFutureMarketDataConfig.ip,
                      host=DockerClickhouseConfig.host,
                      log_level="info")
