#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Project  : data_recorder 
# @File     : data_recorder.py 
# @Author   : 稻草人
# @Time     : 2022/6/16 22:15

from datetime import datetime
from warnings import filterwarnings

from clickhouse_driver import Client
from core.api.data_recorder.ctp_future.app_ctp_future_data_recorder import run_data_recorder as _run_data_recorder
from dateutil.parser import parse

filterwarnings('ignore')


def create_table(table_name: str, host: str = "single-clickhouse-server"):
    """
    创建tick_table
    :param table_name:
    :param host:
    :return:
    """
    sql = r"""
CREATE TABLE IF NOT EXISTS tick_data.{0}
(
    TradingDay         String,
    ExchangeID         String,
    LastPrice          Float64,
    PreSettlementPrice Float64,
    PreClosePrice      Float64,
    PreOpenInterest    Int64,
    OpenPrice          Float64,
    HighestPrice       Float64,
    LowestPrice        Float64,
    Volume             Int64,
    Turnover           Float64,
    OpenInterest       Int64,
    ClosePrice         Float64,
    SettlementPrice    Float64,
    UpperLimitPrice    Float64,
    LowerLimitPrice    Float64,
    UpdateTime         String,
    UpdateMillisec     Int64,
    BidPrice1          Float64,
    BidVolume1         Int64,
    AskPrice1          Float64,
    AskVolume1         Int64,
    BidPrice2          Float64,
    BidVolume2         Int64,
    AskPrice2          Float64,
    AskVolume2         Int64,
    BidPrice3          Float64,
    BidVolume3         Int64,
    AskPrice3          Float64,
    AskVolume3         Int64,
    BidPrice4          Float64,
    BidVolume4         Int64,
    AskPrice4          Float64,
    AskVolume4         Int64,
    BidPrice5          Float64,
    BidVolume5         Int64,
    AskPrice5          Float64,
    AskVolume5         Int64,
    ActionDay          String,
    InstrumentID       String,
    ExchangeInstID     String,
    local_time         Int64
) ENGINE = MergeTree ORDER BY (InstrumentID, local_time, TradingDay);
    """.format(table_name)

    with Client(host=host, port='9000', user='default', password='default') as client:
        client.execute(sql)
    return


def create_buffer(table_name: str, host: str = "single-clickhouse-server"):
    """
    创建buffer缓存
    :param table_name:
    :param host:
    :return:
    """
    with Client(host=host, port='9000', user='default', password='default') as client:
        sql = r"""CREATE DATABASE IF NOT EXISTS tick_data;"""
        client.execute(sql)

        sql = r"""DROP TABLE IF EXISTS tick_data.buffer_tick_data;"""
        client.execute(sql)

        sql = r"""CREATE TABLE tick_data.buffer_tick_data AS tick_data.{0} ENGINE Buffer(tick_data, {0}, 16, 10, 100, 10000, 1000000,10000000, 100000000);""".format(
            table_name)
        client.execute(sql)
    return


def get_table_name():
    """
    创建tick_data表名称
    :return:
    """
    now = datetime.now()
    date = datetime.now().strftime("%Y%m%d")
    if parse("{} 06:00:00".format(date)) <= datetime.now() <= parse("{} 18:00:00".format(date)):
        file_name = "tick_am_{}".format(date)
    else:
        file_name = "tick_pm_{}".format(date)

    return file_name


def run_data_recorder(universe: list, ip: str, host: str = "single-clickhouse-server", log_level: str = "info"):
    """

    :param host:
    :return:
    """
    table_name = get_table_name()
    create_table(table_name, host)
    create_buffer(table_name, host)
    _run_data_recorder(front_address=ip, universe=universe, log_file_name= "clogs/data_recorder.log", level=log_level, table_name = "tick_data.buffer_tick_data")
