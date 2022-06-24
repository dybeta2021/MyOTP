//
// Created by 观鱼 on 2022/2/9.
//

#ifndef CTPFUTURE_QUOTE_ENGINE_CTP_QUOTE_API_H
#define CTPFUTURE_QUOTE_ENGINE_CTP_QUOTE_API_H

#include "ThostFtdcMdApi.h"
#include <iostream>
#include <memory>
#include <semaphore.h>
#include <string>
#include <unordered_map>
#include <vector>

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


#endif//CTPFUTURE_QUOTE_ENGINE_CTP_QUOTE_API_H
