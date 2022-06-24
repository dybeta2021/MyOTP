//
// Created by 稻草人 on 2022/2/9.
//

#include "create_folder.h"
#include "ctp_quote_api.h"
#include "logger.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "readerwriterqueue.h"
#include "spdlog/spdlog.h"
#include <clickhouse/client.h>
#include <thread>
#include <vector>

namespace py = pybind11;

// replace nan
inline double nan_to_num(const double &x) {
    if (x > 1e20) {
        return 0.;
    }
    return x;
}


void tick_to_ck(moodycamel::BlockingReaderWriterQueue<TickData> &task_queue, std::string &table_name, int64_t &end_time_num) {
    SPDLOG_TRACE("tick_to_ck start!");
    clickhouse::Client client(clickhouse::ClientOptions()
                                      .SetHost("single-clickhouse-server")
                                      .SetPort(9000)
                                      .SetUser("default")
                                      .SetPassword("default")
                                      .SetPingBeforeQuery(true));
    SPDLOG_TRACE("clickhouse::Client");

    long counter = 0;
    constexpr long counter_limit = 8192 * 10;
    auto time_limit = kungfu::yijinjing::time::now_in_nano() + 1000000000;
    TickData tick_data{};
    while (true) {
        // 声明客户端
        auto local_time = std::make_shared<clickhouse::ColumnInt64>();
        auto TradingDay = std::make_shared<clickhouse::ColumnString>();
        auto LastPrice = std::make_shared<clickhouse::ColumnFloat64>();
        auto PreSettlementPrice = std::make_shared<clickhouse::ColumnFloat64>();
        auto PreClosePrice = std::make_shared<clickhouse::ColumnFloat64>();
        auto PreOpenInterest = std::make_shared<clickhouse::ColumnInt64>();
        auto OpenPrice = std::make_shared<clickhouse::ColumnFloat64>();
        auto HighestPrice = std::make_shared<clickhouse::ColumnFloat64>();
        auto LowestPrice = std::make_shared<clickhouse::ColumnFloat64>();
        auto Volume = std::make_shared<clickhouse::ColumnInt64>();
        auto Turnover = std::make_shared<clickhouse::ColumnFloat64>();
        auto OpenInterest = std::make_shared<clickhouse::ColumnInt64>();
        auto ClosePrice = std::make_shared<clickhouse::ColumnFloat64>();
        auto SettlementPrice = std::make_shared<clickhouse::ColumnFloat64>();
        auto UpperLimitPrice = std::make_shared<clickhouse::ColumnFloat64>();
        auto LowerLimitPrice = std::make_shared<clickhouse::ColumnFloat64>();
        auto UpdateTime = std::make_shared<clickhouse::ColumnString>();
        auto UpdateMillisec = std::make_shared<clickhouse::ColumnInt64>();
        auto BidPrice1 = std::make_shared<clickhouse::ColumnFloat64>();
        auto BidVolume1 = std::make_shared<clickhouse::ColumnInt64>();
        auto AskPrice1 = std::make_shared<clickhouse::ColumnFloat64>();
        auto AskVolume1 = std::make_shared<clickhouse::ColumnInt64>();
        auto BidPrice2 = std::make_shared<clickhouse::ColumnFloat64>();
        auto BidVolume2 = std::make_shared<clickhouse::ColumnInt64>();
        auto AskPrice2 = std::make_shared<clickhouse::ColumnFloat64>();
        auto AskVolume2 = std::make_shared<clickhouse::ColumnInt64>();
        auto BidPrice3 = std::make_shared<clickhouse::ColumnFloat64>();
        auto BidVolume3 = std::make_shared<clickhouse::ColumnInt64>();
        auto AskPrice3 = std::make_shared<clickhouse::ColumnFloat64>();
        auto AskVolume3 = std::make_shared<clickhouse::ColumnInt64>();
        auto BidPrice4 = std::make_shared<clickhouse::ColumnFloat64>();
        auto BidVolume4 = std::make_shared<clickhouse::ColumnInt64>();
        auto AskPrice4 = std::make_shared<clickhouse::ColumnFloat64>();
        auto AskVolume4 = std::make_shared<clickhouse::ColumnInt64>();
        auto BidPrice5 = std::make_shared<clickhouse::ColumnFloat64>();
        auto BidVolume5 = std::make_shared<clickhouse::ColumnInt64>();
        auto AskPrice5 = std::make_shared<clickhouse::ColumnFloat64>();
        auto AskVolume5 = std::make_shared<clickhouse::ColumnInt64>();
        auto ActionDay = std::make_shared<clickhouse::ColumnString>();
        auto InstrumentID = std::make_shared<clickhouse::ColumnString>();
        clickhouse::Block block;

        while (true) {
            counter += 1;
            if (counter > counter_limit) {
                counter = 0;
                break;
            }

            if (kungfu::yijinjing::time::now_in_nano() > time_limit) {
                time_limit = kungfu::yijinjing::time::now_in_nano() + 1000000000;
                break;
            }

            if (task_queue.wait_dequeue_timed(tick_data, std::chrono::seconds(60))) {
                local_time->Append(tick_data.local_time);
                TradingDay->Append(tick_data.TradingDay);
                LastPrice->Append(nan_to_num(tick_data.LastPrice));
                PreSettlementPrice->Append(nan_to_num(tick_data.PreSettlementPrice));
                PreClosePrice->Append(nan_to_num(tick_data.PreClosePrice));
                PreOpenInterest->Append(tick_data.PreOpenInterest);
                OpenPrice->Append(nan_to_num(tick_data.OpenPrice));
                HighestPrice->Append(nan_to_num(tick_data.HighestPrice));
                LowestPrice->Append(nan_to_num(tick_data.LowestPrice));
                Volume->Append(tick_data.Volume);
                Turnover->Append(nan_to_num(tick_data.Turnover));
                OpenInterest->Append(tick_data.OpenInterest);
                ClosePrice->Append(nan_to_num(tick_data.ClosePrice));
                SettlementPrice->Append(nan_to_num(tick_data.SettlementPrice));
                UpperLimitPrice->Append(nan_to_num(tick_data.UpperLimitPrice));
                LowerLimitPrice->Append(nan_to_num(tick_data.LowerLimitPrice));
                UpdateTime->Append(tick_data.UpdateTime);
                UpdateMillisec->Append(tick_data.UpdateMillisec);
                BidPrice1->Append(nan_to_num(tick_data.BidPrice1));
                BidVolume1->Append(tick_data.BidVolume1);
                AskPrice1->Append(nan_to_num(tick_data.AskPrice1));
                AskVolume1->Append(tick_data.AskVolume1);
                BidPrice2->Append(nan_to_num(tick_data.BidPrice2));
                BidVolume2->Append(tick_data.BidVolume2);
                AskPrice2->Append(nan_to_num(tick_data.AskPrice2));
                AskVolume2->Append(tick_data.AskVolume2);
                BidPrice3->Append(nan_to_num(tick_data.BidPrice3));
                BidVolume3->Append(tick_data.BidVolume3);
                AskPrice3->Append(nan_to_num(tick_data.AskPrice3));
                AskVolume3->Append(tick_data.AskVolume3);
                BidPrice4->Append(nan_to_num(tick_data.BidPrice4));
                BidVolume4->Append(tick_data.BidVolume4);
                AskPrice4->Append(nan_to_num(tick_data.AskPrice4));
                AskVolume4->Append(tick_data.AskVolume4);
                BidPrice5->Append(nan_to_num(tick_data.BidPrice5));
                BidVolume5->Append(tick_data.BidVolume5);
                AskPrice5->Append(nan_to_num(tick_data.AskPrice5));
                AskVolume5->Append(tick_data.AskVolume5);
                ActionDay->Append(tick_data.ActionDay);
                InstrumentID->Append(tick_data.InstrumentID);
            } else {
                if (kungfu::yijinjing::time::now_in_nano() >= end_time_num) {
                    SPDLOG_INFO("行情收录结束，程序退出！");
                    break;
                }
            }
        }

        // 写入clickhouse
        block.AppendColumn("local_time", local_time);
        block.AppendColumn("TradingDay", TradingDay);
        block.AppendColumn("LastPrice", LastPrice);
        block.AppendColumn("PreSettlementPrice", PreSettlementPrice);
        block.AppendColumn("PreClosePrice", PreClosePrice);
        block.AppendColumn("PreOpenInterest", PreOpenInterest);
        block.AppendColumn("OpenPrice", OpenPrice);
        block.AppendColumn("HighestPrice", HighestPrice);
        block.AppendColumn("LowestPrice", LowestPrice);
        block.AppendColumn("Volume", Volume);
        block.AppendColumn("Turnover", Turnover);
        block.AppendColumn("OpenInterest", OpenInterest);
        block.AppendColumn("ClosePrice", ClosePrice);
        block.AppendColumn("SettlementPrice", SettlementPrice);
        block.AppendColumn("UpperLimitPrice", UpperLimitPrice);
        block.AppendColumn("LowerLimitPrice", LowerLimitPrice);
        block.AppendColumn("UpdateTime", UpdateTime);
        block.AppendColumn("UpdateMillisec", UpdateMillisec);
        block.AppendColumn("BidPrice1", BidPrice1);
        block.AppendColumn("BidVolume1", BidVolume1);
        block.AppendColumn("AskPrice1", AskPrice1);
        block.AppendColumn("AskVolume1", AskVolume1);
        block.AppendColumn("BidPrice2", BidPrice2);
        block.AppendColumn("BidVolume2", BidVolume2);
        block.AppendColumn("AskPrice2", AskPrice2);
        block.AppendColumn("AskVolume2", AskVolume2);
        block.AppendColumn("BidPrice3", BidPrice3);
        block.AppendColumn("BidVolume3", BidVolume3);
        block.AppendColumn("AskPrice3", AskPrice3);
        block.AppendColumn("AskVolume3", AskVolume3);
        block.AppendColumn("BidPrice4", BidPrice4);
        block.AppendColumn("BidVolume4", BidVolume4);
        block.AppendColumn("AskPrice4", AskPrice4);
        block.AppendColumn("AskVolume4", AskVolume4);
        block.AppendColumn("BidPrice5", BidPrice5);
        block.AppendColumn("BidVolume5", BidVolume5);
        block.AppendColumn("AskPrice5", AskPrice5);
        block.AppendColumn("AskVolume5", AskVolume5);
        block.AppendColumn("ActionDay", ActionDay);
        block.AppendColumn("InstrumentID", InstrumentID);
        client.Insert(table_name, block);

        if (kungfu::yijinjing::time::now_in_nano() >= end_time_num) {
            SPDLOG_INFO("行情收录结束，程序退出！");
            break;
        }
    }
}


void run_data_recorder(std::string &front_address,
                      const std::vector<std::string> &universe,
                      std::string &log_file_name,
                      std::string &level,
                      std::string &table_name) {
    flow::utils::init_logger(level, log_file_name, false, false, false);
    std::string dir_path = "ctp_future_md_flow";
    create_folder(dir_path);

    moodycamel::BlockingReaderWriterQueue<TickData, 512> task_queue;
    SPDLOG_INFO("创建单写单读多线程无锁队列");

    SPDLOG_INFO("{}:{}", "当前API版本号", CThostFtdcMdApi::GetApiVersion());
    auto *client = new CtpQuoteApi;
    client->set_queue(task_queue);
    client->set_config(front_address);
    client->set_universe(universe);

    client->Init();
    client->ReqUserLogin();
    client->SubscribeMarketData();

    //日盘时间差 28800000000000， 夜盘时间差 25200000000000
    auto end_time_num = kungfu::yijinjing::time::now_in_nano() + 28800000000000;
    SPDLOG_INFO("end_time_num: {}", end_time_num);
    std::thread t(tick_to_ck, std::ref(task_queue), std::ref(table_name), std::ref(end_time_num));

    t.join();
    SPDLOG_INFO("自动退出.");
}


PYBIND11_MODULE(app_ctp_future_data_recorder, m) {
    m.def("run_data_recorder", &run_data_recorder, py::call_guard<py::gil_scoped_release>(),
          py::arg("front_address"),
          py::arg("universe"),
          py::arg("log_file_name") = "clogs/ctp_future_quote_engine.log",
          py::arg("level") = "info",
          py::arg("table_name") = "tick_option.buffer_tick_data");
}
