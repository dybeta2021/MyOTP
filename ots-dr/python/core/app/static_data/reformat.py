#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Project  : data_recorder 
# @File     : reformat.py 
# @Author   : Gavin
# @Time     : 2022/6/15 16:51
# @Desc     :
import re
from datetime import datetime

from pandas import DataFrame, concat

_columns_list = ["CombinationType", "MaxMarginSideAlgorithm", "DeliveryYear", "DeliveryMonth",
                 "StartDelivDate", "EndDelivDate", "ProductClass", "InstLifePhase", "IsTrading", "PositionType",
                 "PositionDateType", "CreateDate", "OpenDate"]


def reformat_data(data: DataFrame):
    """

    :param data:
    :return:
    """
    data = data.copy(deep=True)
    insert_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    insert_date = datetime.now().strftime("%Y-%m-%d")
    data["InsertDate"] = insert_date
    data["InsertTime"] = insert_time

    df = []
    # 中金所期权
    tmp = data.copy(deep=True)
    tmp = tmp.loc[tmp["ExchangeID"] == r"CFFEX"]
    tmp = tmp.loc[tmp["ProductClass"] == "6"]
    tmp = tmp.loc[tmp["ProductID"] == "IO"]
    tmp = tmp.drop(columns=_columns_list, axis=1)
    tmp["ProductClass"] = "StockIndexOption"
    tmp["OptionsType"] = tmp["InstrumentID"].map(lambda x: "Call" if "-C-" in x else "Put")
    # tmp.reset_index(drop=True, inplace=True)
    df.append(tmp)

    # 中金所股指期货
    tmp = data.copy(deep=True)
    tmp = tmp.loc[tmp["ExchangeID"] == r"CFFEX"]
    tmp = tmp.loc[tmp["ProductClass"] == "1"]
    tmp = tmp.drop(columns=_columns_list, axis=1)
    # tmp.reset_index(drop=True, inplace=True)
    tmp["ProductClass"] = "StockIndexFuture"
    tmp["OptionsType"] = "Future"
    df.append(tmp)

    # 上期所商品期货
    tmp = data.copy(deep=True)
    tmp = tmp.loc[tmp["ExchangeID"] == r"SHFE"]
    tmp = tmp.loc[tmp["ProductClass"] == "1"]
    tmp = tmp.drop(columns=_columns_list, axis=1)
    tmp["ProductClass"] = "CommodityFuture"
    tmp["OptionsType"] = "Future"
    # tmp.reset_index(drop=True, inplace=True)
    df.append(tmp)

    # 上期所商品期权
    tmp = data.copy(deep=True)
    tmp = tmp.loc[tmp["ExchangeID"] == r"SHFE"]
    tmp = tmp.loc[tmp["ProductClass"] == "2"]
    tmp = tmp.drop(columns=_columns_list, axis=1)
    tmp["ProductClass"] = "CommodityOption"
    tmp["OptionsType"] = tmp["OptionsType"].map(lambda x: "Call" if x == "1" else "Put")
    tmp["ProductID"] = tmp["ProductID"].map(lambda x: x.replace("_o", ""))
    # tmp.reset_index(drop=True, inplace=True)
    df.append(tmp)

    # 上海国际能源交易中心商品期货
    tmp = data.copy(deep=True)
    tmp = tmp.loc[tmp["ExchangeID"] == r"INE"]
    tmp = tmp.loc[tmp["ProductClass"] == "1"]
    tmp = tmp.drop(columns=_columns_list, axis=1)
    tmp["ProductClass"] = "CommodityFuture"
    tmp["OptionsType"] = "Future"
    # tmp.reset_index(drop=True, inplace=True)
    df.append(tmp)

    # 上海国际能源交易中心商品期权
    tmp = data.copy(deep=True)
    tmp = tmp.loc[tmp["ExchangeID"] == r"INE"]
    tmp = tmp.loc[tmp["ProductClass"] == "2"]
    tmp = tmp.drop(columns=_columns_list, axis=1)
    tmp["ProductClass"] = "CommodityOption"
    tmp["OptionsType"] = tmp["OptionsType"].map(lambda x: "Call" if x == "1" else "Put")
    tmp["ProductID"] = tmp["ProductID"].map(lambda x: x.replace("_o", ""))
    # tmp.reset_index(drop=True, inplace=True)
    df.append(tmp)

    # 大商所商品期货
    tmp = data.copy(deep=True)
    tmp = tmp.loc[tmp["ExchangeID"] == r"DCE"]
    tmp = tmp.loc[tmp["ProductClass"] == "1"]
    tmp = tmp.drop(columns=_columns_list, axis=1)
    tmp["ProductClass"] = "CommodityFuture"
    tmp["OptionsType"] = "Future"
    tmp["UnderlyingInstrID"] = tmp["InstrumentID"].map(lambda x: re.sub(r'[0-9]+', '', x))
    # tmp.reset_index(drop=True, inplace=True)
    df.append(tmp)

    # 大商所商品期权
    tmp = data.copy(deep=True)
    tmp = tmp.loc[tmp["ExchangeID"] == r"DCE"]
    tmp = tmp.loc[tmp["ProductClass"] == "2"]
    tmp = tmp.drop(columns=_columns_list, axis=1)
    tmp["ProductClass"] = "CommodityOption"
    tmp["OptionsType"] = tmp["OptionsType"].map(lambda x: "Call" if x == "1" else "Put")
    tmp["ProductID"] = tmp["ProductID"].map(lambda x: x.replace("_o", ""))
    # tmp.reset_index(drop=True, inplace=True)
    df.append(tmp)

    # 郑商所商品期货
    tmp = data.copy(deep=True)
    tmp = tmp.loc[tmp["ExchangeID"] == r"CZCE"]
    tmp = tmp.loc[tmp["ProductClass"] == "1"]
    tmp = tmp.drop(columns=_columns_list, axis=1)
    tmp["ProductClass"] = "CommodityFuture"
    tmp["OptionsType"] = "Future"
    tmp["UnderlyingInstrID"] = tmp["InstrumentID"].map(lambda x: re.sub(r'[0-9]+', '', x))
    # tmp.reset_index(drop=True, inplace=True)
    df.append(tmp)

    # 郑商所商品期权
    tmp = data.copy(deep=True)
    tmp = tmp.loc[tmp["ExchangeID"] == r"CZCE"]
    tmp = tmp.loc[tmp["ProductClass"] == "2"]
    tmp = tmp.drop(columns=_columns_list, axis=1)
    tmp["ProductClass"] = "CommodityOption"
    tmp["OptionsType"] = tmp["OptionsType"].map(lambda x: "Call" if x == "1" else "Put")
    tmp["ProductID"] = tmp["ProductID"].map(lambda x: x[:-1])
    # tmp.reset_index(drop=True, inplace=True)
    df.append(tmp)
    return concat(df, axis=0).reset_index(drop=True)
