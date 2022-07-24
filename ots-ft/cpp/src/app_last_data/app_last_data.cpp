//
// Created by 观鱼 on 2022/2/9.
//
#include "ots/utils/logger.h"
#include "ThostFtdcMdApi.h"
#include "ots/utils/create_folder.h"
#include "ots/utils/encoding.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include <memory>
#include <semaphore.h>
#include <unordered_map>
#include <vector>

namespace py = pybind11;

// replace nan
inline double nan_to_num(const double &x) {
    if (x > 1e20) {
        return 0.;
    }
    return x;
}

inline void timing_ms(int ms) {
    auto us = ms * 1000;
    auto start = std::chrono::system_clock::now();
    while (true) {
        auto end = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (duration.count() > us) break;
    }
}


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

    [[maybe_unused]] static void UnSubscribeMarketData();

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


public:
    void set_config(const std::string &front_address);
    void set_universe(const std::vector<std::string> &sub_list);
    std::unordered_map<std::string, CThostFtdcDepthMarketDataField> get_contracts();

private:
    CThostFtdcMdApi *ptr{};
    std::string ip;

    std::vector<std::string> sub_list_;
    std::unordered_map<std::string, CThostFtdcDepthMarketDataField> contracts;

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


/// <summary>
/// 析构函数 退出登录
/// </summary>
CtpQuoteApi::~CtpQuoteApi() {
    ReqUserLogout();
    Release();
}


void CtpQuoteApi::Init() {
    ptr = CThostFtdcMdApi::CreateFtdcMdApi(".//ctp_future_md_flow/");
    ptr->RegisterSpi(this);
    ptr->RegisterFront(const_cast<char *>(ip.c_str()));
    ptr->Init();
    SPDLOG_INFO("m_FrontMdAddr: {}", ip);
    sem_wait(&m_md_Init_signal);
}

void CtpQuoteApi::Release() {
    ptr->Release();
    SPDLOG_INFO("<Release>");
}


void CtpQuoteApi::Join() {
    ptr->Join();
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

    int a = ptr->ReqUserLogin(&pReqUserLoginField, 1);
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

    int a = ptr->ReqUserLogout(&pUserLogout, 1);
    if (a == 0) {
        SPDLOG_INFO("用户登出请求......发送成功[%d]\n", a);
    } else {
        SPDLOG_INFO("用户登出请求......发送失败，错误序号=[%d]\n", a);
    }
    //TODO:openctp 这里回调这个接口
//    sem_wait(&m_md_ReqUserLogout_signal);
}


void CtpQuoteApi::SubscribeMarketData() {
    std::vector<char *> char_list;
    for (const auto &p: sub_list_) char_list.emplace_back(const_cast<char *>(p.c_str()));
    int ret = ptr->SubscribeMarketData(char_list.data(), char_list.size());
    if (ret == 0) {
        SPDLOG_INFO("请求订阅行情......发送成功{}", ret);
    } else {
        SPDLOG_INFO("请求订阅行情......发送失败，错误序号={}", ret);
    }

    sem_wait(&m_md_SubscribeMarketData_signal);
}


[[maybe_unused]] void CtpQuoteApi::UnSubscribeMarketData() {
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
    if (pRspInfo != nullptr && pRspInfo->ErrorID != 0){
        SPDLOG_ERROR("\tErrorMsg {}", ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
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
    SPDLOG_TRACE("<OnRspSubMarketData>");
    if (pSpecificInstrument) {
        SPDLOG_TRACE("\tInstrumentID ={}", pSpecificInstrument->InstrumentID);
    }
    if (pRspInfo != nullptr && pRspInfo->ErrorID != 0){
        SPDLOG_ERROR("\tErrorMsg ={}", pRspInfo->ErrorMsg);
        SPDLOG_ERROR("\tErrorID = {}", pRspInfo->ErrorID);
    }
    SPDLOG_TRACE("\tnRequestID = {}", nRequestID);
    SPDLOG_TRACE("\tbIsLast = {}", bIsLast);
    SPDLOG_TRACE("</OnRspSubMarketData>");

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
    contracts.insert(std::pair<std::string, CThostFtdcDepthMarketDataField>(pDepthMarketData->InstrumentID, *pDepthMarketData));
}


void CtpQuoteApi::set_config(const std::string &front_address) {
    ip = front_address;
}

void CtpQuoteApi::set_universe(const std::vector<std::string> &sub_list) {
    sub_list_ = sub_list;
}

std::unordered_map<std::string, CThostFtdcDepthMarketDataField> CtpQuoteApi::get_contracts() {
    return contracts;
}


py::dict get_last_data(
        std::string &ip,
        const std::vector<std::string> &universe) {
    bool init_log = ots::utils::create_logger("clogs/last_data.log", "info", false, false, false);
    SPDLOG_INFO("CTP-Future获取股指和商品期权最新行情数据截面！");

    std::string dir_path = "ctp_future_md_flow";
    ots::utils::create_folder(dir_path);

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
        data["UpperLimitPrice"] = contract.second.UpperLimitPrice;
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


PYBIND11_MODULE(app_last_data, m) {
    m.def("get_last_data", &get_last_data, "get_last_data",
          py::arg("front_address"),
          py::arg("universe"));
}
