#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Project  : python 
# @File     : run_service.py 
# @Author   : 稻草人
# @Time     : 2022/6/18 16:04
# from os import getcwd, sep, mkdir
# from os.path import exists
from pprint import pprint
from config.config import ConfigCTPFutureMDApi
from static_data import update_static_data
from core.api.quote_engine.ctp_future.app_quote_engine import run_quote_engine

log_file = r"clogs/quote_engine.log"

static_data = update_static_data()
universe = static_data["InstrumentID"].values.tolist()
pprint(universe)

run_quote_engine(front_address=ConfigCTPFutureMDApi.ip,
                 universe=universe,
                 log_file=log_file,
                 level="info",
                 path="quote_engine.store")
