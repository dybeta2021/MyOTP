//
// Created by 观鱼 on 2022/2/9.
//

#include "create_folder.h"
#include "ctp_quote_api.h"
#include "logger.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "spdlog/spdlog.h"
#include <vector>

namespace py = pybind11;

// replace nan
inline double nan_to_num(const double &x) {
    if (x > 1e20) {
        return 0.;
    }
    return x;
}

void timing_ms(int ms) {
    auto us = ms * 1000;
    auto start = std::chrono::system_clock::now();
    while (true) {
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (duration.count() > us) break;
    }
}

py::dict get_last_data(
        std::string &ip,
        const std::vector<std::string> &universe) {
    bool init_log = flow::utils::init_logger("info", "clogs/last_data.log", false, false, false);
    SPDLOG_INFO("CTP-Future获取股指和商品期权最新行情数据截面！");

    std::string dir_path = "ctp_future_md_flow";
    create_folder(dir_path);

    SPDLOG_INFO("{}:{}", "当前API版本号", CThostFtdcMdApi::GetApiVersion());
    auto *client = new CtpQuoteApi;
    client->set_config(ip);
    client->set_universe(universe);

    client->Init();
    client->ReqUserLogin();
    client->SubscribeMarketData();
    timing_ms(5000);
    client->ReqUserLogout();
    client->Release();

    std::unordered_map<std::string, CThostFtdcDepthMarketDataField> contracts = client->get_contracts();
    SPDLOG_INFO("contracts size = {}", contracts.size());

    py::dict last_data;
    for (auto &contract: contracts) {
        py::dict data;
        data["TradingDay"] = contract.second.TradingDay;
        data["ExchangeID"] = contract.second.ExchangeID;
        data["LastPrice"] = contract.second.LastPrice;
        data["PreSettlementPrice"] = contract.second.PreSettlementPrice;
        data["PreOpenInterest"] = contract.second.PreOpenInterest;
        data["OpenPrice"] = contract.second.OpenPrice;
        data["HighestPrice"] = contract.second.HighestPrice;
        data["LowestPrice"] = contract.second.LowestPrice;
        data["Volume"] = contract.second.Volume;
        data["Turnover"] = contract.second.Turnover;
        data["OpenInterest"] = contract.second.OpenInterest;
        data["ClosePrice"] = contract.second.ClosePrice;
        data["SettlementPrice"] = contract.second.SettlementPrice;
        data["UpdateTime"] = contract.second.UpdateTime;
        data["UpdateMillisec"] = contract.second.UpdateMillisec;
        data["LowerLimitPrice"] = contract.second.LowerLimitPrice;
        data["BidPrice1"] = contract.second.BidPrice1;
        data["BidVolume1"] = contract.second.BidVolume1;
        data["AskPrice1"] = contract.second.AskPrice1;
        data["AskVolume1"] = contract.second.AskVolume1;
        data["BidPrice2"] = contract.second.BidPrice2;
        data["BidVolume2"] = contract.second.BidVolume2;
        data["AskPrice2"] = contract.second.AskPrice2;
        data["AskVolume2"] = contract.second.AskVolume2;
        data["BidPrice3"] = contract.second.BidPrice3;
        data["BidVolume3"] = contract.second.BidVolume3;
        data["AskPrice3"] = contract.second.AskPrice3;
        data["AskVolume3"] = contract.second.AskVolume3;
        data["BidPrice4"] = contract.second.BidPrice4;
        data["BidVolume4"] = contract.second.BidVolume4;
        data["AskPrice4"] = contract.second.AskPrice4;
        data["AskVolume4"] = contract.second.AskVolume4;
        data["BidPrice4"] = contract.second.BidPrice5;
        data["BidVolume5"] = contract.second.BidVolume5;
        data["AskPrice5"] = contract.second.AskPrice5;
        data["AskVolume5"] = contract.second.AskVolume5;
        data["ActionDay"] = contract.second.ActionDay;
        data["InstrumentID"] = contract.second.InstrumentID;
        data["ExchangeInstID"] = contract.second.ExchangeInstID;
        last_data[contract.second.InstrumentID] = data;
    }
    return last_data;
}


PYBIND11_MODULE(app_ctp_future_last_data, m) {
    m.def("get_last_data", &get_last_data, "get_last_data",
          py::arg("front_address"),
          py::arg("universe"));
}
