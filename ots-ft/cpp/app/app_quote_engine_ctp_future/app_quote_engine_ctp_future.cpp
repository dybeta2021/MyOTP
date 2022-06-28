//
// Created by 稻草人 on 2022/6/18.
//
#include "ots/utils/logger.h"
#include "ots/utils/create_folder.h"
#include "ots/utils/encoding.h"
#include "ots/data/quote.h"
#include "ots/ipc/disruptor/disruptor.h"

#include "ThostFtdcMdApi.h"
#include "kftime.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include <cmath>
#include <cstring>
#include <memory>
#include <semaphore.h>
#include <unistd.h>
#include <utility>
#include <vector>

namespace py = pybind11;
const char *source_id = "ctp_future";


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
    disruptor::Disruptor<CThostFtdcDepthMarketDataField> *shm_ptr_;

public:
    void set_config(const std::string &front_address);
    void set_universe(const std::vector<std::string> &sub_list);
    void set_disruptor(disruptor::Disruptor<CThostFtdcDepthMarketDataField> *ptr) { shm_ptr_ = ptr; }

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
    int ret = api->SubscribeMarketData(char_list.data(), (int32_t)char_list.size());
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

inline int64_t nsec_from_ctp_time(const char *date, const char *update_time, int millisec = 0) {
    static char datetime[21];
    memset(datetime, 0, 21);
    memcpy(datetime, date, 4);
    datetime[4] = '-';
    memcpy(datetime + 5, date + 4, 2);
    datetime[7] = '-';
    memcpy(datetime + 8, date + 6, 2);
    datetime[10] = ' ';
    memcpy(datetime + 11, update_time, 8);
    int64_t nano_sec = kungfu::yijinjing::time::strptime(std::string(datetime), "%Y-%m-%d %H:%M:%S");
    nano_sec += millisec * kungfu::yijinjing::time_unit::NANOSECONDS_PER_MILLISECOND;
    return nano_sec;
}

// https://github.com/DuckDuckDuck0/ft/blob/96cb746b86787d3a0e9081db1b25d908220824f3/src/trader/gateway/ctp/ctp_common.h
template<class PriceType>
inline PriceType adjust_price(PriceType price) {
    PriceType ret = price;
    if (price >= std::numeric_limits<PriceType>::max() - PriceType(1e-6)) ret = PriceType(0);
    return ret;
}

void CtpQuoteApi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
    counter += 1;
    if (pDepthMarketData != nullptr) {
        ots::data::Quote quote{};
        strcpy(quote.source_id, source_id);
        strcpy(quote.symbol, pDepthMarketData->InstrumentID);
        quote.source_time = nsec_from_ctp_time(pDepthMarketData->ActionDay, pDepthMarketData->UpdateTime, pDepthMarketData->UpdateMillisec);
        quote.insert_time = kungfu::yijinjing::time::now_in_nano();
        quote.pre_open_interest = (int64_t) pDepthMarketData->PreOpenInterest;
        quote.volume = pDepthMarketData->Volume;
        quote.turnover = pDepthMarketData->Turnover;
        quote.open_interest = (int64_t) pDepthMarketData->OpenInterest;
        quote.last_price = (float) adjust_price(pDepthMarketData->LastPrice);
        quote.pre_settlement_price = (float) adjust_price(pDepthMarketData->PreSettlementPrice);
        quote.pre_close_price = (float) adjust_price(pDepthMarketData->PreClosePrice);
        quote.open_price = (float) adjust_price(pDepthMarketData->OpenPrice);
        quote.high_price = (float) adjust_price(pDepthMarketData->HighestPrice);
        quote.low_price = (float) adjust_price(pDepthMarketData->LowestPrice);
        quote.close_price = (float) adjust_price(pDepthMarketData->ClosePrice);
        quote.settlement_price = (float) adjust_price(pDepthMarketData->SettlementPrice);
        quote.upper_limit_price = (float) pDepthMarketData->UpperLimitPrice;
        quote.lower_limit_price = (float) pDepthMarketData->LowerLimitPrice;
        quote.bid_price[0] = (float) adjust_price(pDepthMarketData->BidPrice1);
        quote.bid_price[1] = (float) adjust_price(pDepthMarketData->BidPrice2);
        quote.bid_price[2] = (float) adjust_price(pDepthMarketData->BidPrice3);
        quote.bid_price[3] = (float) adjust_price(pDepthMarketData->BidPrice4);
        quote.bid_price[4] = (float) adjust_price(pDepthMarketData->BidPrice5);
        quote.ask_price[0] = (float) adjust_price(pDepthMarketData->AskPrice1);
        quote.ask_price[1] = (float) adjust_price(pDepthMarketData->AskPrice2);
        quote.ask_price[2] = (float) adjust_price(pDepthMarketData->AskPrice3);
        quote.ask_price[3] = (float) adjust_price(pDepthMarketData->AskPrice4);
        quote.ask_price[4] = (float) adjust_price(pDepthMarketData->AskPrice5);

        quote.bid_volume[0] = pDepthMarketData->BidVolume1;
        quote.bid_volume[1] = pDepthMarketData->BidVolume2;
        quote.bid_volume[2] = pDepthMarketData->BidVolume3;
        quote.bid_volume[3] = pDepthMarketData->BidVolume4;
        quote.bid_volume[4] = pDepthMarketData->BidVolume5;
        quote.ask_volume[0] = pDepthMarketData->AskVolume1;
        quote.ask_volume[1] = pDepthMarketData->AskVolume2;
        quote.ask_volume[2] = pDepthMarketData->AskVolume3;
        quote.ask_volume[3] = pDepthMarketData->AskVolume4;
        quote.ask_volume[4] = pDepthMarketData->AskVolume5;

        SPDLOG_TRACE("OnRtnDepthMarketData, symbol:{}, last_price:{}, ask_price:{}, {}, {}, {}, {}", quote.symbol, quote.last_price, quote.ask_price[0], quote.ask_price[1], quote.ask_price[2], quote.ask_price[3], quote.ask_price[4]);
        shm_ptr_->set_data(pDepthMarketData);

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


PYBIND11_MODULE(app_quote_engine_ctp_future, m) {
    m.def("run_quote_engine",
          &run_quote_engine,
          py::call_guard<py::gil_scoped_release>(),
          py::arg("front_address"),
          py::arg("universe"),
          py::arg("log_file") = "clogs/ctp_future_quote_engine.log",
          py::arg("level") = "trace",
          py::arg("path") = "test.store");
}
