#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Project  : data_recorder 
# @File     : to_db.py
# @Author   : Gavin
# @Time     : 2022/6/16 14:48
# @Desc     :

from warnings import filterwarnings

from clickhouse_driver import Client
from dateutil.parser import parse
from pandas import DataFrame

filterwarnings('ignore')


def to_ck(data: DataFrame, host: str = 'single-clickhouse-server'):
    """
    静态数据写入数据库

    :param data:
    :param host:
    :return:
    """
    data = data.copy(deep=True)
    data["InsertTime"] = data["InsertTime"].map(parse)
    data["InsertDate"] = data["InsertDate"].map(lambda x: parse(x).date())
    data["UnderlyingMultiple"] = data["UnderlyingMultiple"].astype(int)
    data["StrikePrice"] = data["StrikePrice"].astype(int)

    with Client(host=host, port=9000, user='default', password='default') as client:
        sql = r"""CREATE DATABASE IF NOT EXISTS tick_data;"""
        client.execute(sql)

        sql = r"""
        CREATE TABLE IF NOT EXISTS tick_data.static_data
        (
            InsertDate           DATE,
            InsertTime           DATETIME64,
            InstrumentID         String,
            ExchangeID           String,
            InstrumentName       String,
            ExchangeInstID       String,
            ProductID            String,
            MaxMarketOrderVolume Int32,
            MinMarketOrderVolume Int32,
            MaxLimitOrderVolume  Int32,
            MinLimitOrderVolume  Int32,
            VolumeMultiple       Int32,
            PriceTick            Float32,
            ExpireDate           String,
            LongMarginRatio      Float32,
            ShortMarginRatio     Float32,
            StrikePrice          Int32,
            UnderlyingMultiple   Int32,
            UnderlyingInstrID    String,
            ProductClass         String
        ) ENGINE = MergeTree ORDER BY (InsertTime, ExchangeID, InstrumentID);
        """
        client.execute(sql)
        client.execute(r"""INSERT INTO tick_data.static_data VALUES""", data.to_dict(orient='records'))
