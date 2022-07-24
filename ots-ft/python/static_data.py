#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Project  : data_recorder 
# @File     : static_data.py
# @Author   : 稻草人
# @Time     : 2022/6/15 16:34
# @Desc     :
from datetime import datetime
from os import getcwd, sep

from core.api.static_data.ctp_future.app_static_data import get_static_data
from dateutil.parser import parse
from pandas import DataFrame

from config.config import ConfigClickhouse, ConfigCTPFutureTDApi
from core.app.static_data.reformat import reformat_data
# from core.app.static_data.to_db import to_ck


def update_static_data():
    """

    :param host:
    :return:
    """
    data = get_static_data(ip=ConfigCTPFutureTDApi.ip,
                           broker_id=ConfigCTPFutureTDApi.broker_id,
                           user_id=ConfigCTPFutureTDApi.user_id,
                           password=ConfigCTPFutureTDApi.password,
                           app_id=ConfigCTPFutureTDApi.app_id,
                           auth_code=ConfigCTPFutureTDApi.auth_code)

    data = DataFrame(data).T.reset_index(drop=True)
    data = reformat_data(data)
    # to_ck(data=data, host=host)

    date = datetime.now().strftime("%Y%m%d")
    if parse("{} 06:00:00".format(date)) <= datetime.now() <= parse("{} 18:00:00".format(date)):
        file_name = "am_{}.csv".format(date)
    else:
        file_name = "pm_{}.csv".format(date)
    path = getcwd() + sep + r"access" + sep + r"static_data" + sep + file_name
    data.to_csv(path_or_buf=path, encoding="utf-8")
    return data


if __name__ == "__main__":
    data = update_static_data()
    print(data.tail().T)
