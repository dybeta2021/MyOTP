//
// Created by 稻草人 on 2022/7/13.
//

#ifndef OTS_FT_CTP_QUOTE_API_H
#define OTS_FT_CTP_QUOTE_API_H
#include "ThostFtdcMdApi.h"
#include "kftime.h"
#include "nut/signal/sem.h"
#include "ots/ipc/disruptor/disruptor.h"
#include "ots/utils/create_folder.h"
#include "ots/utils/encoding.h"
#include <atomic>
#include <cmath>
#include <cstring>
#include <memory>
#include <unistd.h>
#include <utility>
#include <vector>

class CtpQuoteApi : public CThostFtdcMdSpi {
public:
    explicit CtpQuoteApi();

    ~CtpQuoteApi();

    int Init();

    void Release();

    void Join();

    int ReqUserLogin();

    int ReqUserLogout();

    int SubscribeMarketData();

    int UnSubscribeMarketData();

public:
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
    std::atomic<int> request_id = 0;
    disruptor::Disruptor<CThostFtdcDepthMarketDataField> *shm_ptr_{};

public:
    void set_config(const std::string &front_address);

    void set_universe(const std::vector<std::string> &sub_list);

    void set_disruptor(disruptor::Disruptor<CThostFtdcDepthMarketDataField> *ptr) { shm_ptr_ = ptr; }

private:
    std::vector<std::string> sub_list_;
    int counter = 0;

    nut::Semaphore *signal_init_ = nullptr;
    nut::Semaphore *signal_login_ = nullptr;
    nut::Semaphore *signal_logout_ = nullptr;
    nut::Semaphore *signal_subscribe_ = nullptr;
    nut::Semaphore *signal_unsubscribe_ = nullptr;
};

#endif//OTS_FT_CTP_QUOTE_API_H
