//
// Created by 稻草人 on 2022/7/13.
//
#include "ctp_quote_api.h"
#include "ots/data.h"


CtpQuoteApi::CtpQuoteApi() {
    signal_init_ = new nut::Semaphore(0);
    signal_login_ = new nut::Semaphore(0);
    signal_logout_ = new nut::Semaphore(0);
    signal_subscribe_ = new nut::Semaphore(0);
    signal_unsubscribe_ = new nut::Semaphore(0);
}

CtpQuoteApi::~CtpQuoteApi() {
    ReqUserLogout();
    Release();

    delete signal_init_;
    delete signal_login_;
    delete signal_logout_;
    delete signal_subscribe_;
    delete signal_unsubscribe_;
}


int CtpQuoteApi::Init() {
    api = CThostFtdcMdApi::CreateFtdcMdApi(".//ctp_future_md_flow/");
    api->RegisterSpi(this);
    api->RegisterFront(const_cast<char *>(ip.c_str()));
    api->Init();
    SPDLOG_INFO("QuoteIP: {}", ip);

    if (signal_init_->timedwait(5, 0)) {
        return 0;
    } else {
        SPDLOG_ERROR("Network Error.");
        return -1;
    }
}

void CtpQuoteApi::Release() {
    SPDLOG_INFO("Release");
    api->Release();
}


void CtpQuoteApi::Join() {
    SPDLOG_INFO("Join");
    api->Join();
}


int CtpQuoteApi::ReqUserLogin() {
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

    int a = api->ReqUserLogin(&pReqUserLoginField, request_id++);
    if (a == 0) {
        SPDLOG_INFO("用户登录请求......发送成功{}", a);
    } else {
        SPDLOG_INFO("用户登录请求......发送失败，错误序号={}", a);
    }

    if (signal_login_->timedwait(5, 0)) {
        return 0;
    } else {
        SPDLOG_ERROR("Network Error.");
        return -1;
    }
}

int CtpQuoteApi::ReqUserLogout() {
    CThostFtdcUserLogoutField pUserLogout{};
    memset(&pUserLogout, 0, sizeof(CThostFtdcUserLogoutField));

    SPDLOG_INFO("<ReqUserLogout>\n");
    SPDLOG_INFO("\tBrokerID [%s]\n", pUserLogout.BrokerID);
    SPDLOG_INFO("\tUserID [%s]\n", pUserLogout.UserID);
    SPDLOG_INFO("</ReqUserLogout>\n");

    int a = api->ReqUserLogout(&pUserLogout, request_id++);
    if (a == 0) {
        SPDLOG_INFO("用户登出请求......发送成功[%d]\n", a);
    } else {
        SPDLOG_INFO("用户登出请求......发送失败，错误序号=[%d]\n", a);
    }

    if (signal_logout_->timedwait(5, 0)) {
        return 0;
    } else {
        SPDLOG_ERROR("Network Error.");
        return -1;
    }
}


int CtpQuoteApi::SubscribeMarketData() {
    std::vector<char *> char_list;
    for (const auto &p: sub_list_) char_list.emplace_back(const_cast<char *>(p.c_str()));
    int ret = api->SubscribeMarketData(char_list.data(), (int32_t) char_list.size());
    if (ret == 0) {
        SPDLOG_INFO("请求订阅行情......发送成功{}", ret);
    } else {
        SPDLOG_INFO("请求订阅行情......发送失败，错误序号={}", ret);
    }

    if (signal_subscribe_->timedwait(5, 0)) {
        return 0;
    } else {
        SPDLOG_ERROR("Network Error.");
        return -1;
    }
}


int CtpQuoteApi::UnSubscribeMarketData() {
    std::vector<char *> char_list;
    for (const auto &p: sub_list_) char_list.emplace_back(const_cast<char *>(p.c_str()));
    int ret = api->UnSubscribeMarketData(char_list.data(), (int32_t) char_list.size());
    if (ret == 0) {
        SPDLOG_INFO("退阅行情......发送成功{}", ret);
    } else {
        SPDLOG_INFO("退阅行情......发送失败，错误序号={}", ret);
    }

    if (signal_unsubscribe_->timedwait(5, 0)) {
        return 0;
    } else {
        SPDLOG_ERROR("Network Error.");
        return -1;
    }
}


void CtpQuoteApi::OnFrontConnected() {
    SPDLOG_DEBUG("[CtpQuoteApi::OnFrontConnectedMD] Connected");
    signal_init_->post();
}

void CtpQuoteApi::OnFrontDisconnected(int nReason) {
    SPDLOG_ERROR("[CtpQuoteApi::OnFrontDisconnectedMD] Disconnected, tnReason{}", nReason);
}

void CtpQuoteApi::OnHeartBeatWarning(int nTimeLapse) {
    SPDLOG_WARN("[CtpQuoteApi::OnHeartBeatWarningMD] Warn. No packet received for a period of time, {}", nTimeLapse);
}


void CtpQuoteApi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo,
                                 int nRequestID, bool bIsLast) {
    SPDLOG_INFO("<OnRspUserLogin> :{}.", nRequestID);
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
        signal_login_->post();
    }
}

void CtpQuoteApi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                                  bool bIsLast) {
    SPDLOG_INFO("<OnRspUserLogout>: {}.", nRequestID);
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
        signal_logout_->post();
    }
}

void CtpQuoteApi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    SPDLOG_ERROR("<OnRspError> :{}.", nRequestID);
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
    if (pRspInfo != nullptr && pRspInfo->ErrorID != 0) {
        SPDLOG_ERROR("\tErrorMsg ={}", pRspInfo->ErrorMsg);
        SPDLOG_ERROR("\tErrorID = {}", pRspInfo->ErrorID);
    }
    SPDLOG_TRACE("\tnRequestID = {}", nRequestID);
    SPDLOG_TRACE("\tbIsLast = {}", bIsLast);
    SPDLOG_TRACE("</OnRspSubMarketData>");

    if (bIsLast) {
        signal_subscribe_->post();
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
        signal_unsubscribe_->post();
    }
}


inline int64_t nanosecond_from_ctp_time(const char *date, const char *update_time, int millisec = 0) {
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

//// https://github.com/DuckDuckDuck0/ft/blob/96cb746b86787d3a0e9081db1b25d908220824f3/src/trader/gateway/ctp/ctp_common.h
//template<class PriceType>
//inline PriceType adjust_price(PriceType price) {
//    PriceType ret = price;
//    if (price >= std::numeric_limits<PriceType>::max() - PriceType(1e-6)) ret = PriceType(0);
//    return ret;
//}

inline double adjust_price(const double &price) {
    if (price > 1e12 or price < -1e12) {
        return 0.;
    } else {
        return price;
    }
}

void CtpQuoteApi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
    counter += 1;
    if (pDepthMarketData != nullptr) {
        ots::data::Quote quote{};
        strcpy(quote.source_id, "ctp_future");
        strcpy(quote.symbol, pDepthMarketData->InstrumentID);
        quote.source_time = nanosecond_from_ctp_time(pDepthMarketData->ActionDay, pDepthMarketData->UpdateTime,
                                                     pDepthMarketData->UpdateMillisec);
        quote.insert_time = kungfu::yijinjing::time::now_in_nano();
        quote.pre_open_interest = (int64_t) pDepthMarketData->PreOpenInterest;
        quote.volume = pDepthMarketData->Volume;
        quote.turnover = pDepthMarketData->Turnover;
        quote.open_interest = (int64_t) pDepthMarketData->OpenInterest;
        quote.last_price = adjust_price(pDepthMarketData->LastPrice);
        quote.pre_settlement_price = adjust_price(pDepthMarketData->PreSettlementPrice);
        quote.pre_close_price = adjust_price(pDepthMarketData->PreClosePrice);
        quote.open_price = adjust_price(pDepthMarketData->OpenPrice);
        quote.high_price = adjust_price(pDepthMarketData->HighestPrice);
        quote.low_price = adjust_price(pDepthMarketData->LowestPrice);
        quote.close_price = adjust_price(pDepthMarketData->ClosePrice);
        quote.settlement_price = adjust_price(pDepthMarketData->SettlementPrice);
        quote.upper_limit_price = pDepthMarketData->UpperLimitPrice;
        quote.lower_limit_price = pDepthMarketData->LowerLimitPrice;
        quote.bid_price[0] = adjust_price(pDepthMarketData->BidPrice1);
        quote.bid_price[1] = adjust_price(pDepthMarketData->BidPrice2);
        quote.bid_price[2] = adjust_price(pDepthMarketData->BidPrice3);
        quote.bid_price[3] = adjust_price(pDepthMarketData->BidPrice4);
        quote.bid_price[4] = adjust_price(pDepthMarketData->BidPrice5);
        quote.ask_price[0] = adjust_price(pDepthMarketData->AskPrice1);
        quote.ask_price[1] = adjust_price(pDepthMarketData->AskPrice2);
        quote.ask_price[2] = adjust_price(pDepthMarketData->AskPrice3);
        quote.ask_price[3] = adjust_price(pDepthMarketData->AskPrice4);
        quote.ask_price[4] = adjust_price(pDepthMarketData->AskPrice5);

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

        SPDLOG_TRACE("OnRtnDepthMarketData, symbol:{}, last_price:{}, ask_price:{}, {}, {}, {}, {}", quote.symbol,
                     quote.last_price, quote.ask_price[0], quote.ask_price[1], quote.ask_price[2], quote.ask_price[3],
                     quote.ask_price[4]);
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
