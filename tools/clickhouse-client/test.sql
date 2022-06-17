CREATE DATABASE IF NOT EXISTS test_db;

CREATE TABLE IF NOT EXISTS test_db.test_table
(
    TradingDay   String,
    InstrumentID String,
    LastPrice    Float64,
    Volume       Int64,
    Turnover     Float64,
    local_time   Int64
) ENGINE = MergeTree ORDER BY (InstrumentID, local_time, TradingDay);

SELECT TradingDay, InstrumentID, LastPrice, Volume, local_time FROM test_db.test_table;

DROP TABLE IF EXISTS test_db.test_table;
DROP DATABASE IF EXISTS test_db;