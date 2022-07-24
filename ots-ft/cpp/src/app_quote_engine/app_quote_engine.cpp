//
// Created by 稻草人 on 2022/6/18.
//
#include "ots/utils/logger.h"
#include "ctp_quote_api.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

namespace py = pybind11;


int run_quote_engine(
        const std::string &front_address,
        const std::vector<std::string> &universe,
        const std::string &log_file,
        const std::string &level,
        const std::string &path) {
    const int _ret = ots::utils::create_logger(log_file, level, true, false, false, 1, 1);

    auto shm = disruptor::Disruptor<CThostFtdcDepthMarketDataField>(disruptor::wait::YIELDING_WAIT);
    shm.Init(path, 1024 * 1024 * 16);

    std::string dir_path = "ctp_future_md_flow";
    ots::utils::create_folder(dir_path);
    auto *client = new CtpQuoteApi;
    client->set_config(front_address);
    client->set_universe(universe);
    client->set_disruptor(&shm);
    SPDLOG_INFO("{}:{}", "当前API版本号", CThostFtdcMdApi::GetApiVersion());

    client->Init();
    client->ReqUserLogin();
    client->SubscribeMarketData();

    //日盘时间差 28800000， 夜盘时间差 25200000
    constexpr int sleep_seconds = 7 * 60 * 60;
    sleep(sleep_seconds);
    return 0;
}


PYBIND11_MODULE(app_quote_engine, m) {
    m.def("run_quote_engine",
          &run_quote_engine,
          "run_quote_engine",
          py::call_guard<py::gil_scoped_release>(),
          py::arg("front_address"),
          py::arg("universe"),
          py::arg("log_file") = "clogs/quote_engine.log",
          py::arg("level") = "trace",
          py::arg("path") = "test.store");
}


