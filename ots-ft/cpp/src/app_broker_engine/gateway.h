//
// Created by Gavin on 2022/6/29.
//

#ifndef CPP_GATEWAY_H
#define CPP_GATEWAY_H
#include "ThostFtdcTraderApi.h"
#include "ots/utils/encoding.h"
#include "ots/utils/logger.h"
#include "ots/utils/timing.h"
#include <atomic>

extern class BrokerCTP;

class CtpTradeClient : public CThostFtdcTraderSpi {
private:
    CThostFtdcTraderApi *ptr{};
    std::atomic<int> request_id = 0;
    BrokerCTP *broker_ = nullptr;

public:
    void SetBroker(BrokerCTP *broker);
    // 连接
    void Connect(char frontAddress[]);

    // 客户端认证
    int Authenticate(char brokerID[], char userID[], char appID[], char authCode[]);

    // 释放
    void Release();

    //登陆
    void Login(char brokerID[], char userID[], char password[]);

    void Logout(char brokerID[], char userID[]);

    //结算单确认
    void SettlementInfoConfirm(char brokerID[], char userID[]);

    // 查询账户资金
    bool QueryAccount(char brokerID[], char InvestorID[]);

    // 请求查询投资者持仓
    bool QueryPosition(char brokerID[], char InvestorID[]);

    //                	///请求查询投资者持仓
    //	virtual int ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID) = 0;


    //        // order
    //        bool insert_order();
    //        bool cancel_order();
    //        bool query_contract();
    //        bool query_position();
    //
    //        bool query_trade();

public:
    ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
    void OnFrontConnected() override;

    ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
    ///@param nReason 错误原因
    ///        0x1001 网络读失败
    ///        0x1002 网络写失败
    ///        0x2001 接收心跳超时
    ///        0x2002 发送心跳失败
    ///        0x2003 收到错误报文
    void OnFrontDisconnected(int nReason) override;

    ///心跳超时警告。当长时间未收到报文时，该方法被调用。
    ///@param nTimeLapse 距离上次接收报文的时间
    void OnHeartBeatWarning(int nTimeLapse) override;

    ///客户端认证响应
    void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField,
                           CThostFtdcRspInfoField *pRspInfo,
                           int nRequestID,
                           bool bIsLast) override;

    ///登录请求响应
    void
    OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                   CThostFtdcRspInfoField *pRspInfo,
                   int nRequestID,
                   bool bIsLast) override;


    //        ///请求查询投资者结算结果响应
    //        void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo,
    //                                    int nRequestID, bool bIsLast) override;

    ///投资者结算结果确认响应
    void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,
                                    CThostFtdcRspInfoField *pRspInfo,
                                    int nRequestID,
                                    bool bIsLast) override;

    ///登出请求响应
    void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout,
                         CThostFtdcRspInfoField *pRspInfo,
                         int nRequestID,
                         bool bIsLast) override;
    //
    //        ///报单录入请求响应
    //        void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
    //                              bool bIsLast) override;
    //
    //        ///报单操作请求响应
    //        void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo,
    //                              int nRequestID, bool bIsLast) override;
    //
    //        ///报单通知
    //        void OnRtnOrder(CThostFtdcOrderField *pOrder) override;
    //
    //        ///成交通知
    //        void OnRtnTrade(CThostFtdcTradeField *pTrade) override;
    //
    //        ///请求查询合约响应
    //        void
    //        OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
    //                           bool bIsLast) override;
    //
    ///请求查询投资者持仓响应
    void
    OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition,
                             CThostFtdcRspInfoField *pRspInfo,
                             int nRequestID,
                             bool bIsLast) override;

    ///请求查询资金账户响应
    void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount,
                                CThostFtdcRspInfoField *pRspInfo,
                                int nRequestID,
                                bool bIsLast) override;
    //
    //        ///请求查询报单响应
    //        void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
    //                           bool bIsLast) override;
    //
    //        ///请求查询成交响应
    //        void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
    //                           bool bIsLast) override;

    ///错误应答
    void OnRspError(CThostFtdcRspInfoField *pRspInfo,
                    int nRequestID,
                    bool bIsLast) override;
};


#endif//CPP_GATEWAY_H
