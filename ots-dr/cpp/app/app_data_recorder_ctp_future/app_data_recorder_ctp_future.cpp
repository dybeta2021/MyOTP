//
// Created by 观鱼 on 2022/2/9.
//

#include "../../ots/utils/logger.h"
#include "../../ots/utils/create_folder.h"
#include "../../ots/utils/encoding.h"
#include "../../deps/ctp_future/ThostFtdcMdApi.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "readerwriterqueue.h"
#include <clickhouse/client.h>
#include "kftime.h"
#include <thread>
#include <vector>
#include "kftime.h"
#include <iostream>
#include <memory>
#include <semaphore.h>
#include <string>
#include <vector>

namespace py = pybind11;

// replace nan
inline double nan_to_num(const double &x) {
    if (x > 1e20) {
        return 0.;
    }
    return x;
}


///深度行情
struct TickData {
    ///交易日
    TThostFtdcDateType TradingDay;
    ///交易所代码
    TThostFtdcExchangeIDType ExchangeID;
    ///最新价
    TThostFtdcPriceType LastPrice;
    ///上次结算价
    TThostFtdcPriceType PreSettlementPrice;
    ///昨收盘
    TThostFtdcPriceType PreClosePrice;
    ///昨持仓量
    TThostFtdcLargeVolumeType PreOpenInterest;
    ///今开盘
    TThostFtdcPriceType OpenPrice;
    ///最高价
    TThostFtdcPriceType HighestPrice;
    ///最低价
    TThostFtdcPriceType LowestPrice;
    ///数量
    TThostFtdcVolumeType Volume;
    ///成交金额
    TThostFtdcMoneyType Turnover;
    ///持仓量
    TThostFtdcLargeVolumeType OpenInterest;
    ///今收盘
    TThostFtdcPriceType ClosePrice;
    ///本次结算价
    TThostFtdcPriceType SettlementPrice;
    ///涨停板价
    TThostFtdcPriceType UpperLimitPrice;
    ///跌停板价
    TThostFtdcPriceType LowerLimitPrice;
    ///最后修改时间
    TThostFtdcTimeType UpdateTime;
    ///最后修改毫秒
    TThostFtdcMillisecType UpdateMillisec;
    ///申买价一
    TThostFtdcPriceType BidPrice1;
    ///申买量一
    TThostFtdcVolumeType BidVolume1;
    ///申卖价一
    TThostFtdcPriceType AskPrice1;
    ///申卖量一
    TThostFtdcVolumeType AskVolume1;
    ///申买价二
    TThostFtdcPriceType BidPrice2;
    ///申买量二
    TThostFtdcVolumeType BidVolume2;
    ///申卖价二
    TThostFtdcPriceType AskPrice2;
    ///申卖量二
    TThostFtdcVolumeType AskVolume2;
    ///申买价三
    TThostFtdcPriceType BidPrice3;
    ///申买量三
    TThostFtdcVolumeType BidVolume3;
    ///申卖价三
    TThostFtdcPriceType AskPrice3;
    ///申卖量三
    TThostFtdcVolumeType AskVolume3;
    ///申买价四
    TThostFtdcPriceType BidPrice4;
    ///申买量四
    TThostFtdcVolumeType BidVolume4;
    ///申卖价四
    TThostFtdcPriceType AskPrice4;
    ///申卖量四
    TThostFtdcVolumeType AskVolume4;
    ///申买价五
    TThostFtdcPriceType BidPrice5;
    ///申买量五
    TThostFtdcVolumeType BidVolume5;
    ///申卖价五
    TThostFtdcPriceType AskPrice5;
    ///申卖量五
    TThostFtdcVolumeType AskVolume5;
    ///业务日期
    TThostFtdcDateType ActionDay;
    ///合约代码
    TThostFtdcInstrumentIDType InstrumentID;
    ///合约在交易所的代码
    TThostFtdcExchangeInstIDType ExchangeInstID;
    ///本地时间戳
    int64_t local_time;
};


////// ref:https://github.com/cameron314/readerwriterqueue
//namespace lq = moodycamel;
////lq::BlockingReaderWriterQueue<TickData> task_queue;


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
    CThostFtdcMdApi *m_pMdapi{};
    std::string m_FrontMdAddr;
    moodycamel::BlockingReaderWriterQueue<TickData> *ptr_task_queue = nullptr;


public:
    void set_queue(moodycamel::BlockingReaderWriterQueue<TickData> &task_queue);

    void set_config(const std::string &front_address);

    void set_universe(const std::vector<std::string> &sub_list);

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
    //m_FrontMdAddr = getConfig("config", "FrontMdAddr");
    //m_InstrumentID = getConfig("config", "InstrumentID");

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
    m_pMdapi = CThostFtdcMdApi::CreateFtdcMdApi(".//ctp_future_md_flow/");
    m_pMdapi->RegisterSpi(this);
    m_pMdapi->RegisterFront(const_cast<char *>(m_FrontMdAddr.c_str()));
    m_pMdapi->Init();
    SPDLOG_INFO("m_FrontMdAddr: {}", m_FrontMdAddr);
    sem_wait(&m_md_Init_signal);
}

void CtpQuoteApi::Release() {
    m_pMdapi->Release();
    SPDLOG_INFO("<Release>");
}


void CtpQuoteApi::Join() {
    m_pMdapi->Join();
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

    int a = m_pMdapi->ReqUserLogin(&pReqUserLoginField, 1);
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

    int a = m_pMdapi->ReqUserLogout(&pUserLogout, 1);
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
    int ret = m_pMdapi->SubscribeMarketData(char_list.data(), char_list.size());
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

void
CtpQuoteApi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
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
    if (pDepthMarketData) {
        if (counter > 1024) {
            SPDLOG_INFO("OnRtnDepthMarketData, symbol:{}", pDepthMarketData->InstrumentID);
            counter = 0;
        }
        SPDLOG_TRACE("OnRtnDepthMarketData, symbol:{}", pDepthMarketData->InstrumentID);

        TickData tick_data = {};
        tick_data.local_time = kungfu::yijinjing::time::now_in_nano();
        strcpy(tick_data.TradingDay, pDepthMarketData->TradingDay);
        strcpy(tick_data.ExchangeID, pDepthMarketData->ExchangeID);
        tick_data.LastPrice = pDepthMarketData->LastPrice;
        tick_data.PreSettlementPrice = pDepthMarketData->PreSettlementPrice;
        tick_data.PreClosePrice = pDepthMarketData->PreClosePrice;
        tick_data.PreOpenInterest = pDepthMarketData->PreOpenInterest;
        tick_data.OpenPrice = pDepthMarketData->OpenPrice;
        tick_data.HighestPrice = pDepthMarketData->HighestPrice;
        tick_data.LowestPrice = pDepthMarketData->LowestPrice;
        tick_data.Volume = pDepthMarketData->Volume;
        tick_data.Turnover = pDepthMarketData->Turnover;
        tick_data.OpenInterest = pDepthMarketData->OpenInterest;
        tick_data.ClosePrice = pDepthMarketData->ClosePrice;
        tick_data.SettlementPrice = pDepthMarketData->SettlementPrice;
        tick_data.UpperLimitPrice = pDepthMarketData->UpperLimitPrice;
        tick_data.LowerLimitPrice = pDepthMarketData->LowerLimitPrice;
        strcpy(tick_data.UpdateTime, pDepthMarketData->UpdateTime);
        tick_data.UpdateMillisec = pDepthMarketData->UpdateMillisec;
        tick_data.BidPrice1 = pDepthMarketData->BidPrice1;
        tick_data.BidVolume1 = pDepthMarketData->BidVolume1;
        tick_data.AskPrice1 = pDepthMarketData->AskPrice1;
        tick_data.AskVolume1 = pDepthMarketData->AskVolume1;
        tick_data.BidPrice2 = pDepthMarketData->BidPrice2;
        tick_data.BidVolume2 = pDepthMarketData->BidVolume2;
        tick_data.AskPrice2 = pDepthMarketData->AskPrice2;
        tick_data.AskVolume2 = pDepthMarketData->AskVolume2;
        tick_data.BidPrice3 = pDepthMarketData->BidPrice3;
        tick_data.BidVolume3 = pDepthMarketData->BidVolume3;
        tick_data.AskPrice3 = pDepthMarketData->AskPrice3;
        tick_data.AskVolume3 = pDepthMarketData->AskVolume3;
        tick_data.BidPrice4 = pDepthMarketData->BidPrice4;
        tick_data.BidVolume4 = pDepthMarketData->BidVolume4;
        tick_data.AskPrice4 = pDepthMarketData->AskPrice4;
        tick_data.AskVolume4 = pDepthMarketData->AskVolume4;
        tick_data.BidPrice5 = pDepthMarketData->BidPrice5;
        tick_data.BidVolume5 = pDepthMarketData->BidVolume5;
        tick_data.AskPrice5 = pDepthMarketData->AskPrice5;
        tick_data.AskVolume5 = pDepthMarketData->AskVolume5;
        strcpy(tick_data.ActionDay, pDepthMarketData->ActionDay);
        strcpy(tick_data.InstrumentID, pDepthMarketData->InstrumentID);
        strcpy(tick_data.ExchangeInstID, pDepthMarketData->ExchangeInstID);

        ptr_task_queue->enqueue(tick_data);
    }
}


void CtpQuoteApi::set_config(const std::string &front_address) {
    m_FrontMdAddr = front_address;
}

void CtpQuoteApi::set_queue(moodycamel::BlockingReaderWriterQueue<TickData> &task_queue) {
    ptr_task_queue = &task_queue;
}

void CtpQuoteApi::set_universe(const std::vector<std::string> &sub_list) {
    sub_list_ = sub_list;
}


void tick_to_ck(moodycamel::BlockingReaderWriterQueue<TickData> &task_queue, std::string &table_name,
                int64_t &end_time_num) {
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
    ots::utils::create_logger(log_file_name, level, true, false, false);
    std::string dir_path = "ctp_future_md_flow";
    ots::utils::create_folder(dir_path);

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
}


PYBIND11_MODULE(app_data_recorder_ctp_future, m) {
    m.def("run_data_recorder", &run_data_recorder, py::call_guard<py::gil_scoped_release>(),
          py::arg("front_address"),
          py::arg("universe"),
          py::arg("log_file_name") = "clogs/ctp_future_quote_engine.log",
          py::arg("level") = "info",
          py::arg("table_name") = "tick_option.buffer_tick_data");
}
