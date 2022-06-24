//
// Created by 杨东 on 2022/6/18.
//
#include "logger.h"
#include "create_folder.h"
#include "encoding.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include <memory>
#include <semaphore.h>
#include <unistd.h>
#include <utility>
#include <vector>

#include "ThostFtdcMdApi.h"
#include "create_folder.h"
#include "yijinjing/journal/FrameHeader.h"
#include "yijinjing/journal/JournalWriter.h"
#include "yijinjing/journal/PageProvider.h"
#include <cmath>
#include <cstring>

namespace py = pybind11;


class CtpQuoteApi : public CThostFtdcMdSpi {
public:
    CtpQuoteApi();

    ~CtpQuoteApi();

public:
    void Init();

    void Release();

    void Join();

    void ReqUserLogin();

    void ReqUserLogout();

    void SubscribeMarketData();

    void UnSubscribeMarketData();

    void OnFrontConnected() override;

    void OnFrontDisconnected(int nReason) override;

    void OnHeartBeatWarning(int nTimeLapse) override;

    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                        bool bIsLast) override;

    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                         bool bIsLast) override;

    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

    void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo,
                            int nRequestID, bool bIsLast) override;

    void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo,
                              int nRequestID, bool bIsLast) override;

    void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) override;

private:
    CThostFtdcMdApi *api{};
    std::string ip;
    yijinjing::JournalWriterPtr ptr;

public:
    void set_config(const std::string &front_address);

    void set_universe(const std::vector<std::string> &sub_list);

    void set_database(yijinjing::JournalWriterPtr writer);

private:
    std::vector<std::string> sub_list_;
    int counter = 0;

    sem_t m_md_Release_signal{};
    sem_t m_md_Init_signal{};
    sem_t m_md_Join_signal{};
    sem_t m_md_ReqUserLogin_signal{};
    sem_t m_md_ReqUserLogout_signal{};
    sem_t m_md_SubscribeMarketData_signal{};
    sem_t m_md_UnSubscribeMarketData_signal{};
    sem_t m_md_SubscribeForQuoteRsp_signal{};
    sem_t m_md_UnSubscribeForQuoteRsp_signal{};
};


CtpQuoteApi::CtpQuoteApi() {
    sem_init(&m_md_Release_signal, 0, 0);
    sem_init(&m_md_Init_signal, 0, 0);
    sem_init(&m_md_Join_signal, 0, 0);
    sem_init(&m_md_ReqUserLogin_signal, 0, 0);
    sem_init(&m_md_ReqUserLogout_signal, 0, 0);
    sem_init(&m_md_SubscribeMarketData_signal, 0, 0);
    sem_init(&m_md_UnSubscribeMarketData_signal, 0, 0);
    sem_init(&m_md_SubscribeForQuoteRsp_signal, 0, 0);
    sem_init(&m_md_UnSubscribeForQuoteRsp_signal, 0, 0);
}

CtpQuoteApi::~CtpQuoteApi() {
    ReqUserLogout();
    Release();
}


void CtpQuoteApi::Init() {
    api = CThostFtdcMdApi::CreateFtdcMdApi(".//ctp_future_md_flow/");
    api->RegisterSpi(this);
    api->RegisterFront(const_cast<char *>(ip.c_str()));
    api->Init();
    SPDLOG_INFO("m_FrontMdAddr: {}", ip);
    sem_wait(&m_md_Init_signal);
}

void CtpQuoteApi::Release() {
    api->Release();
    SPDLOG_INFO("<Release>");
}


void CtpQuoteApi::Join() {
    api->Join();
}


void CtpQuoteApi::ReqUserLogin() {
    CThostFtdcReqUserLoginField pReqUserLoginField{};
    memset(&pReqUserLoginField, 0, sizeof(CThostFtdcReqUserLoginField));

    SPDLOG_INFO("<ReqUserLogin>");
    SPDLOG_INFO("\tTradingDay {}", pReqUserLoginField.TradingDay);
    SPDLOG_INFO("\tBrokerID {}", pReqUserLoginField.BrokerID);
    SPDLOG_INFO("\tUserID {}", pReqUserLoginField.UserID);
    SPDLOG_INFO("\tPassword {}", pReqUserLoginField.Password);
    SPDLOG_INFO("\tUserProductInfo {}", pReqUserLoginField.UserProductInfo);
    SPDLOG_INFO("\tInterfaceProductInfo {}", pReqUserLoginField.InterfaceProductInfo);
    SPDLOG_INFO("\tProtocolInfo {}", pReqUserLoginField.ProtocolInfo);
    SPDLOG_INFO("\tMacAddress {}", pReqUserLoginField.MacAddress);
    SPDLOG_INFO("\tOneTimePassword {}", pReqUserLoginField.OneTimePassword);
    SPDLOG_INFO("\tClientIPAddress {}", pReqUserLoginField.ClientIPAddress);
    SPDLOG_INFO("\tLoginRemark {}", pReqUserLoginField.LoginRemark);
    SPDLOG_INFO("\tClientIPPort {}", pReqUserLoginField.ClientIPPort);
    SPDLOG_INFO("</ReqUserLogin>");

    int a = api->ReqUserLogin(&pReqUserLoginField, 1);
    if (a == 0) {
        SPDLOG_INFO("用户登录请求......发送成功{}", a);
    } else {
        SPDLOG_INFO("用户登录请求......发送失败，错误序号={}", a);
    }

    sem_wait(&m_md_ReqUserLogin_signal);
}

void CtpQuoteApi::ReqUserLogout() {
    CThostFtdcUserLogoutField pUserLogout{};
    memset(&pUserLogout, 0, sizeof(CThostFtdcUserLogoutField));

    SPDLOG_INFO("<ReqUserLogout>\n");
    SPDLOG_INFO("\tBrokerID [%s]\n", pUserLogout.BrokerID);
    SPDLOG_INFO("\tUserID [%s]\n", pUserLogout.UserID);
    SPDLOG_INFO("</ReqUserLogout>\n");

    int a = api->ReqUserLogout(&pUserLogout, 1);
    if (a == 0) {
        SPDLOG_INFO("用户登出请求......发送成功[%d]\n", a);
    } else {
        SPDLOG_INFO("用户登出请求......发送失败，错误序号=[%d]\n", a);
    }
    sem_wait(&m_md_ReqUserLogout_signal);
}


void CtpQuoteApi::SubscribeMarketData() {
    std::vector<char *> char_list;
    for (const auto &p: sub_list_) char_list.emplace_back(const_cast<char *>(p.c_str()));
    int ret = api->SubscribeMarketData(char_list.data(), char_list.size());
    if (ret == 0) {
        SPDLOG_INFO("请求订阅行情......发送成功{}", ret);
    } else {
        SPDLOG_INFO("请求订阅行情......发送失败，错误序号={}", ret);
    }

    sem_wait(&m_md_SubscribeMarketData_signal);
}


void CtpQuoteApi::UnSubscribeMarketData() {
    SPDLOG_ERROR("UnSubscribeMarketData, 此函数不应该被调用！！");
}


void CtpQuoteApi::OnFrontConnected() {
    SPDLOG_DEBUG("[CtpQuoteApi::OnFrontConnectedMD] Connected");
    sem_post(&m_md_Init_signal);
}

void CtpQuoteApi::OnFrontDisconnected(int nReason) {
    SPDLOG_ERROR("[CtpQuoteApi::OnFrontDisconnectedMD] Disconnected, tnReason{}", nReason);
}

void CtpQuoteApi::OnHeartBeatWarning(int nTimeLapse) {
    SPDLOG_WARN("[CtpQuoteApi::OnHeartBeatWarningMD] Warn. No packet received for a period of time, {}", nTimeLapse);
}


void CtpQuoteApi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo,
                                 int nRequestID, bool bIsLast) {
    SPDLOG_INFO("<OnRspUserLogin>");
    if (pRspUserLogin) {
        SPDLOG_INFO("\tTradingDay {}", pRspUserLogin->TradingDay);
        SPDLOG_INFO("\tLoginTime {}", pRspUserLogin->LoginTime);
        SPDLOG_INFO("\tBrokerID {}", pRspUserLogin->BrokerID);
        SPDLOG_INFO("\tUserID {}", pRspUserLogin->UserID);
        SPDLOG_INFO("\tSystemName {}", pRspUserLogin->SystemName);
        SPDLOG_INFO("\tMaxOrderRef {}", pRspUserLogin->MaxOrderRef);
        SPDLOG_INFO("\tSHFETime {}", pRspUserLogin->SHFETime);
        SPDLOG_INFO("\tDCETime {}", pRspUserLogin->DCETime);
        SPDLOG_INFO("\tCZCETime {}", pRspUserLogin->CZCETime);
        SPDLOG_INFO("\tFFEXTime {}", pRspUserLogin->FFEXTime);
        SPDLOG_INFO("\tINETime {}", pRspUserLogin->INETime);
        SPDLOG_INFO("\tFrontID {}", pRspUserLogin->FrontID);
        SPDLOG_INFO("\tSessionID {}", pRspUserLogin->SessionID);
    }
    if (pRspInfo) {
        SPDLOG_ERROR("\tErrorMsg {}", gbk2utf8(pRspInfo->ErrorMsg));
        SPDLOG_ERROR("\tErrorID {}", pRspInfo->ErrorID);
    }
    SPDLOG_INFO("\tnRequestID {}", nRequestID);
    SPDLOG_INFO("\tbIsLast {}", bIsLast);
    SPDLOG_INFO("</OnRspUserLogin>");
    if (bIsLast) {
        sem_post(&m_md_ReqUserLogin_signal);
    }
}

void CtpQuoteApi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                                  bool bIsLast) {
    SPDLOG_INFO("<OnRspUserLogout>\n");
    if (pUserLogout) {
        SPDLOG_INFO("\tBrokerID [%s]\n", pUserLogout->BrokerID);
        SPDLOG_INFO("\tUserID [%s]\n", pUserLogout->UserID);
    }
    if (pRspInfo) {
        SPDLOG_ERROR("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
        SPDLOG_ERROR("\tErrorID [%d]\n", pRspInfo->ErrorID);
    }
    SPDLOG_INFO("\tnRequestID [%d]\n", nRequestID);
    SPDLOG_INFO("\tbIsLast [%d]\n", bIsLast);
    SPDLOG_INFO("</OnRspUserLogout>\n");

    if (bIsLast) {
        sem_post(&m_md_ReqUserLogout_signal);
    }
}

void CtpQuoteApi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    SPDLOG_ERROR("<OnRspError>");
    if (pRspInfo) {
        SPDLOG_ERROR("\tErrorMsg{}", pRspInfo->ErrorMsg);
        SPDLOG_ERROR("\tErrorID {}", pRspInfo->ErrorID);
    }
    SPDLOG_ERROR("\tnRequestID {}", nRequestID);
    SPDLOG_ERROR("\tbIsLast {}", bIsLast);
    SPDLOG_ERROR("</OnRspError>");
}

void CtpQuoteApi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                     CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    SPDLOG_INFO("<OnRspSubMarketData>");
    if (pSpecificInstrument) {
        SPDLOG_INFO("\tInstrumentID ={}", pSpecificInstrument->InstrumentID);
    }
    if (pRspInfo) {
        SPDLOG_ERROR("\tErrorMsg ={}", pRspInfo->ErrorMsg);
        SPDLOG_ERROR("\tErrorID = {}", pRspInfo->ErrorID);
    }
    SPDLOG_INFO("\tnRequestID = {}", nRequestID);
    SPDLOG_INFO("\tbIsLast = {}", bIsLast);
    SPDLOG_INFO("</OnRspSubMarketData>");

    if (bIsLast) {
        sem_post(&m_md_SubscribeMarketData_signal);
    }
}

void CtpQuoteApi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument,
                                       CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    SPDLOG_INFO("<OnRspSubMarketData>");
    if (pSpecificInstrument) {
        SPDLOG_INFO("\tInstrumentID ={}", pSpecificInstrument->InstrumentID);
    }
    if (pRspInfo) {
        SPDLOG_ERROR("\tErrorMsg ={}", pRspInfo->ErrorMsg);
        SPDLOG_ERROR("\tErrorID = {}", pRspInfo->ErrorID);
    }
    SPDLOG_INFO("\tnRequestID = {}", nRequestID);
    SPDLOG_INFO("\tbIsLast = {}", bIsLast);
    SPDLOG_INFO("</OnRspSubMarketData>");

    if (bIsLast) {
        sem_post(&m_md_UnSubscribeMarketData_signal);
    }
}

void CtpQuoteApi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
    counter += 1;
    if (pDepthMarketData != nullptr) {
        SPDLOG_TRACE("OnRtnDepthMarketData, symbol:{}", pDepthMarketData->InstrumentID);
        ptr->write_data(pDepthMarketData, 0, 0);

        if (counter > 1024) {
            SPDLOG_INFO("OnRtnDepthMarketData, symbol:{}", pDepthMarketData->InstrumentID);
            counter = 0;
        }
    }
}


void CtpQuoteApi::set_config(const std::string &front_address) {
    ip = front_address;
}

void CtpQuoteApi::set_universe(const std::vector<std::string> &sub_list) {
    sub_list_ = sub_list;
}

void CtpQuoteApi::set_database(yijinjing::JournalWriterPtr writer) {
    ptr = std::move(writer);
}


int run_quote_engine(
        const std::string &front_address,
        const std::vector<std::string> &universe,
        const std::string &log_file,
        const std::string &level,
        const std::string &yjj_folder) {
    const int _ret = create_logger(log_file, level, false, false, true, 1, 1);

    std::string stop_time_point;
    auto writer = yijinjing::JournalWriter::create(yjj_folder, "quote_engine", "ctp_future");
    SPDLOG_INFO("getPageNum:{}", writer->getPageNum());

    std::string dir_path = "ctp_future_md_flow";
    create_folder(dir_path);
    auto *client = new CtpQuoteApi;
    client->set_config(front_address);
    client->set_universe(universe);
    client->set_database(writer);
    SPDLOG_INFO("{}:{}", "当前API版本号", CThostFtdcMdApi::GetApiVersion());

    client->Init();
    client->ReqUserLogin();
    client->SubscribeMarketData();

    //日盘时间差 28800000， 夜盘时间差 25200000
    constexpr int sleep_seconds = 7 * 60 * 60;
    sleep(sleep_seconds);
    SPDLOG_INFO("自动退出.");
    return 0;
}


PYBIND11_MODULE(app_ctp_future_quote_engine, m) {
    m.def("run_quote_engine",
          &run_quote_engine,
          py::call_guard<py::gil_scoped_release>(),
          py::arg("front_address"),
          py::arg("universe"),
          py::arg("log_file") = "clogs/ctp_future_quote_engine.log",
          py::arg("level") = "trace",
          py::arg("yjj_folder") = "yjj/journal/");
}
