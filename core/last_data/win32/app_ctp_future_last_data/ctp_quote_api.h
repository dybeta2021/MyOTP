//
// Created by 观鱼 on 2022/2/9.
//

#ifndef CTPFUTURE_QUOTE_ENGINE_CTP_QUOTE_API_H
#define CTPFUTURE_QUOTE_ENGINE_CTP_QUOTE_API_H
#define __WIN_SYS
#include "ThostFtdcMdApi.h"
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#ifdef __WIN_SYS
#include <Windows.h>
#elif defined(__UNIX_SYS)
#include <semaphore.h>
#endif 

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


#ifdef __WIN_SYS
    HANDLE m_md_Release_signal;
    HANDLE m_md_Init_signal;
    HANDLE m_md_Join_signal;
    HANDLE m_md_ReqUserLogin_signal;
    HANDLE m_md_ReqUserLogout_signal;
    HANDLE m_md_SubscribeMarketData_signal;
    HANDLE m_md_UnSubscribeMarketData_signal;
    HANDLE m_md_SubscribeForQuoteRsp_signal;
    HANDLE m_md_UnSubscribeForQuoteRsp_signal;

#elif defined(__UNIX_SYS)
    sem_t m_md_Release_signal;
    sem_t m_md_Init_signal;
    sem_t m_md_Join_signal;
    sem_t m_md_ReqUserLogin_signal;
    sem_t m_md_ReqUserLogout_signal;
    sem_t m_md_SubscribeMarketData_signal;
    sem_t m_md_UnSubscribeMarketData_signal;
    sem_t m_md_SubscribeForQuoteRsp_signal;
    sem_t m_md_UnSubscribeForQuoteRsp_signal;
#endif
};


#endif//CTPFUTURE_QUOTE_ENGINE_CTP_QUOTE_API_H
