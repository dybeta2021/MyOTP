from warnings import filterwarnings
from pprint import pprint
from ctpfuture_quote_engine import run_quote_engine
from datetime import datetime, timedelta
from dateutil.parser import parse
from clickhouse_driver import Client
from clickhouse_driver.errors import ServerException
filterwarnings('ignore')


def create_tick_data_table(table_name: str, host: str = "192.168.1.89"):
    """
    创建tick_table
    :param table_name:
    :param host:
    :return:
    """
    sql = r"""
CREATE TABLE IF NOT EXISTS tick_option.{0}
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


def create_buffer(table_name: str, host: str = "192.168.1.89"):
    """
    创建buffer缓存
    :param table_name:
    :param host:
    :return:
    """
    with Client(host=host, port='9000', user='default', password='default') as client:
        # sql = r"""CREATE DATABASE IF NOT EXISTS tick_option;"""
        # client.execute(sql)

        sql = r"""DROP TABLE IF EXISTS tick_option.buffer_tick_data;"""
        client.execute(sql)

        sql = r"""CREATE TABLE tick_option.buffer_tick_data AS tick_option.{0} ENGINE Buffer(tick_option, {0}, 16, 10, 100, 10000, 1000000,
                                                         10000000, 100000000);""".format(table_name)
        client.execute(sql)
    return


def get_table_name():
    """
    创建tick_data表名称
    :return:
    """
    now = datetime.now()
    date = now.strftime("%Y-%m-%d")
    if parse("{} 00:00:00".format(date)) <= now < parse("{} 06:00:00".format(date)):
        table_date = (now - timedelta(days=1)).strftime("%Y%m%d")
        table_label = "night"

    elif parse("{} 06:00:00".format(date)) <= now < parse("{} 18:00:00".format(date)):
        table_date = now.strftime("%Y%m%d")
        table_label = "day"
    else:
        table_date = now.strftime("%Y%m%d")
        table_label = "night"

    table_name = r"ctp_tick_commodity_option_{0}_{1}".format(table_label, table_date)
    return table_name


if __name__ == '__main__':
    host = "single-clickhouse-server"
    table_name = get_table_name()
    print(table_name)
    create_tick_data_table(table_name, host)
    create_buffer(table_name, host)

    front_address = "tcp://180.168.146.187:10211"
    universe = ["IF2202", "IF2203", "i2205"]
    level = "info"
    run_quote_engine(front_address=front_address, universe=universe, level=level)