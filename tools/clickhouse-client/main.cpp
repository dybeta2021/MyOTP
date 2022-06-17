#include <clickhouse/client.h>
#include <iostream>

struct TickData {
    int64_t local_time;
    std::string TradingDay;
    std::string InstrumentID;
    double LastPrice;
    int64_t Volume;
};

void test_client() {
    std::cout << "hello world!" << std::endl;

    clickhouse::Client client(clickhouse::ClientOptions()
                                      .SetHost("single-clickhouse-server")
                                      .SetPort(9000)
                                      .SetUser("default")
                                      .SetPassword("default")
                                      .SetPingBeforeQuery(true));

    // Create a database.
    client.Execute("CREATE DATABASE IF NOT EXISTS test_db;");

    // Create a table.
    client.Execute("CREATE TABLE IF NOT EXISTS test_db.test_table\n"
                   "(\n"
                   "    TradingDay   String,\n"
                   "    InstrumentID String,\n"
                   "    LastPrice    Float64,\n"
                   "    Volume       Int64,\n"
                   "    local_time   Int64\n"
                   ") ENGINE = MergeTree ORDER BY (InstrumentID, local_time, TradingDay);");

    // Insert Data
    // tick-data
    TickData tick_data{};
    tick_data.local_time = 201808081111;
    tick_data.TradingDay = "20220617";
    tick_data.InstrumentID = "IF2212";
    tick_data.LastPrice = 4000.0;
    tick_data.Volume = 4000;

    // cur
    auto local_time = std::make_shared<clickhouse::ColumnInt64>();
    auto TradingDay = std::make_shared<clickhouse::ColumnString>();
    auto InstrumentID = std::make_shared<clickhouse::ColumnString>();
    auto LastPrice = std::make_shared<clickhouse::ColumnFloat64>();
    auto Volume = std::make_shared<clickhouse::ColumnInt64>();
    clickhouse::Block block;

    // data
    local_time->Append(tick_data.local_time);
    TradingDay->Append(tick_data.TradingDay);
    LastPrice->Append(tick_data.LastPrice);
    Volume->Append(tick_data.Volume);
    InstrumentID->Append(tick_data.InstrumentID);

    // to ck
    block.AppendColumn("local_time", local_time);
    block.AppendColumn("TradingDay", TradingDay);
    block.AppendColumn("LastPrice", LastPrice);
    block.AppendColumn("Volume", Volume);
    block.AppendColumn("InstrumentID", InstrumentID);
    client.Insert("test_db.test_table", block);

    // Query Data
    client.Select("SELECT TradingDay, InstrumentID, LastPrice, Volume, local_time FROM test_db.test_table;", [](const clickhouse::Block &block) {
        for (size_t i = 0; i < block.GetRowCount(); ++i) {
            std::cout << block[0]->As<clickhouse::ColumnString>()->At(i) << " "
                      << block[1]->As<clickhouse::ColumnString>()->At(i) << " "
                      << block[2]->As<clickhouse::ColumnFloat64>()->At(i) << " "
                      << block[3]->As<clickhouse::ColumnInt64>()->At(i) << " "
                      << block[4]->As<clickhouse::ColumnInt64>()->At(i) << " "
                      << "\n";
        }
    });

    // Drop
    client.Execute("DROP TABLE IF EXISTS test_db.test_table;");
    client.Execute("DROP DATABASE IF EXISTS test_db;");
}


int main() {
    test_client();
}