//
// Created by 稻草人 on 2022/2/8.
//
#include "ots/utils/logger.h"
#include "ThostFtdcTraderApi.h"
#include "ots/utils/create_folder.h"
#include "ots/utils/encoding.h"
#include "ots/utils/timing.h"
#include "pybind11/pybind11.h"
#include <unordered_map>

namespace py = pybind11;
using ots::utils::timing_ms;

// replace nan
inline double nan_to_num(const double &x) {
    if (x > 1e20) {
        return 0.;
    }
    return x;
}


class TraderClient : public CThostFtdcTraderSpi {
private:
    CThostFtdcTraderApi *ptr{};
    int request_id = 0;
    bool is_last = true;
    std::unordered_map<std::string, CThostFtdcInstrumentField> contracts;

public:
    // 连接
    void connect(char frontAddress[]);

    // 客户端认证
    int authenticate(char brokerID[], char userID[], char appID[], char authCode[]);

    // 释放
    void release();

    //登陆
    void login(char brokerID[], char userID[], char password[]);

    //结算单确认
    void settlementInfoConfirm(char brokerID[], char userID[]);

public:
    // 查询持仓
    void qry_instrument();

    bool qry_instrument_is_finished() const;

    std::unordered_map<std::string, CThostFtdcInstrumentField> get_contracts();

    int get_nRequestID() {
        request_id++;
        return request_id;
    }

public:
    //前置连接响应
    //当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
    void OnFrontConnected() override;

    //当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
    //@param nReason 错误原因
    //        0x1001 网络读失败
    //        0x1002 网络写失败
    //        0x2001 接收心跳超时
    //        0x2002 发送心跳失败
    //        0x2003 收到错误报文
    void OnFrontDisconnected(int nReason) override;

    //客户端认证响应
    void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo,
                           int nRequestID, bool bIsLast) override;

    //登录请求响应
    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                        bool bIsLast) override;

    //结算单确认响应
    void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,
                                    CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

    //错误应答
    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) override;

    //请求查询合约响应
    void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID,
                            bool bIsLast) override;
};


// 连接
void TraderClient::connect(char frontAddress[]) {
    ptr = CThostFtdcTraderApi::CreateFtdcTraderApi(".//ctp_future_td_flow/");//必须提前创建好flow目录
    ptr->RegisterSpi(this);
    ptr->SubscribePublicTopic(THOST_TERT_QUICK);
    ptr->SubscribePrivateTopic(THOST_TERT_QUICK);//设置私有流订阅模式
    ptr->RegisterFront(frontAddress);
    SPDLOG_INFO("注册交易前置机: {} ", frontAddress);
    ptr->Init();
    //输出API版本信息
    SPDLOG_INFO("CTPMini-TdApi版本信息: {}", ptr->GetApiVersion());
}

// 客户端认证请求
int TraderClient::authenticate(char brokerID[], char userID[], char appID[], char authCode[]) {
    CThostFtdcReqAuthenticateField pReqAuthenticateField = {0};
    strcpy(pReqAuthenticateField.BrokerID, brokerID);
    strcpy(pReqAuthenticateField.UserID, userID);
    strcpy(pReqAuthenticateField.AppID, appID);
    strcpy(pReqAuthenticateField.AuthCode, authCode);

    return ptr->ReqAuthenticate(&pReqAuthenticateField, 1);
}

//释放
void TraderClient::release() {
    ptr->Release();
}


//登陆
void TraderClient::login(char brokerID[], char userID[], char password[]) {
    CThostFtdcReqUserLoginField t = {0};
    strcpy(t.BrokerID, brokerID);
    strcpy(t.UserID, userID);
    strcpy(t.Password, password);
    while (ptr->ReqUserLogin(&t, 1) != 0) timing_ms(100);
}


//结算单确认
void TraderClient::settlementInfoConfirm(char brokerID[], char userID[]) {
    CThostFtdcSettlementInfoConfirmField t = {0};
    strcpy(t.BrokerID, brokerID);
    strcpy(t.InvestorID, userID);
    while (ptr->ReqSettlementInfoConfirm(&t, 2) != 0) timing_ms(100);
    SPDLOG_INFO("设定默认自动确认结算单");
}


void TraderClient::OnFrontConnected() {
    SPDLOG_INFO("交易服务器连接成功");
}

void TraderClient::OnFrontDisconnected(int nReason) {
    SPDLOG_ERROR("交易服务器连接失败: {}", nReason);
}

//客户端认证响应
void TraderClient::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo,
                                     int nRequestID, bool bIsLast) {
    SPDLOG_INFO("客户端认证响应");
    if (pRspInfo != nullptr && pRspInfo->ErrorID == 0) {
        // printf("认证成功,ErrorID=0x%04x, ErrMsg=%s\n\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        SPDLOG_INFO("认证成功,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
    } else {
        // printf("认证失败,ErrorID=0x%04x, ErrMsg=%s\n\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        SPDLOG_ERROR("认证失败,ErrorID={}, ErrMsg={}", pRspInfo->ErrorID, ots::utils::gbk2utf8(pRspInfo->ErrorMsg));
    }
}


void TraderClient::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo,
                                  int nRequestID, bool bIsLast) {
    SPDLOG_INFO("交易账户登录成功");
    SPDLOG_INFO("交易日:{}", pRspUserLogin->TradingDay);
    SPDLOG_INFO("登录时间: {}", pRspUserLogin->LoginTime);
    SPDLOG_INFO("交易帐户: {}", pRspUserLogin->UserID);
}

//结算单确认响应
void TraderClient::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm,
                                              CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    SPDLOG_INFO("程序自动确认结算单，请通过交易终端核对结算单");
    SPDLOG_INFO("确认日期：{}", pSettlementInfoConfirm->ConfirmDate);
    SPDLOG_INFO("确认时间：{}", pSettlementInfoConfirm->ConfirmTime);
}

//错误应答
void TraderClient::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
    SPDLOG_ERROR("OnRspError");
}

// 请求查询合约响应，当执行ReqQryInstrument后，该方法被调用。
void TraderClient::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument,
                                      CThostFtdcRspInfoField *pRspInfo,
                                      int nRequestID,
                                      bool bIsLast) {
    contracts.insert(std::pair<std::string, CThostFtdcInstrumentField>(pInstrument->InstrumentID, *pInstrument));
    is_last = bIsLast;
}

// 查询持仓
void TraderClient::qry_instrument() {
    SPDLOG_INFO("请求获取股指期权和商品期权静态数据！");
    CThostFtdcQryInstrumentField t = {0};
    is_last = false;
    while (ptr->ReqQryInstrument(&t, get_nRequestID()) != 0) timing_ms(100);
}

bool TraderClient::qry_instrument_is_finished() const {
    return is_last;
}

std::unordered_map<std::string, CThostFtdcInstrumentField> TraderClient::get_contracts() {
    return contracts;
}


py::dict get_static_data(
        std::string &ip,
        std::string &broker_id,
        std::string &user_id,
        std::string &password,
        std::string &app_id,
        std::string &auth_code) {
    bool init_log = ots::utils::create_logger("clogs/static_data.log", "info", false, false, false);
    SPDLOG_INFO("CTP-Future获取股指和商品期权静态数据！");

    std::string dir_path = "ctp_future_td_flow";
    ots::utils::create_folder(dir_path);

    auto *client = new TraderClient();
    SPDLOG_INFO("连接交易前置机");
    client->connect(const_cast<char *>(ip.c_str()));
    timing_ms(1000);
    // 终端认证 容易失败！
    int counter = 0;
    while (true) {
        counter++;
        if (counter > 100) {
            py::dict static_data;
            return static_data;
        }
        int intAuthRet = client->authenticate(const_cast<char *>(broker_id.c_str()),
                                              const_cast<char *>(user_id.c_str()),
                                              const_cast<char *>(app_id.c_str()),
                                              const_cast<char *>(auth_code.c_str()));
        SPDLOG_INFO("发送终端认证请求：" + std::to_string(intAuthRet));
        timing_ms(500);
        if (intAuthRet == 0) {
            break;
        }
    }

    // 账户登录
    client->login(const_cast<char *>(broker_id.c_str()),
                  const_cast<char *>(user_id.c_str()),
                  const_cast<char *>(password.c_str()));
    timing_ms(500);

    client->settlementInfoConfirm(const_cast<char *>(broker_id.c_str()),
                                  const_cast<char *>(user_id.c_str()));
    timing_ms(500);

    client->qry_instrument();
    while (!client->qry_instrument_is_finished()) timing_ms(100);

    std::unordered_map<std::string, CThostFtdcInstrumentField> contracts = client->get_contracts();
    SPDLOG_INFO("contracts size = {}", contracts.size());

    py::dict static_data;
    for (auto &contract: contracts) {
        py::dict data;
        data["InstrumentID"] = ots::utils::gbk2utf8(contract.second.InstrumentID);
        data["ExchangeID"] = ots::utils::gbk2utf8(contract.second.ExchangeID);
        data["InstrumentName"] = ots::utils::gbk2utf8(contract.second.InstrumentName);
        data["ExchangeInstID"] = ots::utils::gbk2utf8(contract.second.ExchangeInstID);
        data["ProductID"] = ots::utils::gbk2utf8(contract.second.ProductID);
        data["ProductClass"] = contract.second.ProductClass;
        data["DeliveryYear"] = contract.second.DeliveryYear;
        data["DeliveryMonth"] = contract.second.DeliveryMonth;
        data["MaxMarketOrderVolume"] = contract.second.MaxMarketOrderVolume;
        data["MinMarketOrderVolume"] = contract.second.MinMarketOrderVolume;
        data["MaxLimitOrderVolume"] = contract.second.MaxLimitOrderVolume;
        data["MinLimitOrderVolume"] = contract.second.MinLimitOrderVolume;
        data["VolumeMultiple"] = contract.second.VolumeMultiple;
        data["PriceTick"] = contract.second.PriceTick;
        data["CreateDate"] = ots::utils::gbk2utf8(contract.second.CreateDate);
        data["OpenDate"] = ots::utils::gbk2utf8(contract.second.OpenDate);
        data["ExpireDate"] = ots::utils::gbk2utf8(contract.second.ExpireDate);
        data["StartDelivDate"] = ots::utils::gbk2utf8(contract.second.StartDelivDate);
        data["EndDelivDate"] = ots::utils::gbk2utf8(contract.second.EndDelivDate);
        data["InstLifePhase"] = contract.second.InstLifePhase;
        data["IsTrading"] = contract.second.IsTrading;
        data["PositionType"] = contract.second.PositionType;
        data["PositionDateType"] = contract.second.PositionDateType;
        data["LongMarginRatio"] = nan_to_num(contract.second.LongMarginRatio);
        data["ShortMarginRatio"] = nan_to_num(contract.second.ShortMarginRatio);
        data["MaxMarginSideAlgorithm"] = contract.second.MaxMarginSideAlgorithm;
        data["StrikePrice"] = nan_to_num(contract.second.StrikePrice);
        data["OptionsType"] = contract.second.OptionsType;
        data["UnderlyingMultiple"] = nan_to_num(contract.second.UnderlyingMultiple);
        data["CombinationType"] = contract.second.CombinationType;
        data["UnderlyingInstrID"] = ots::utils::gbk2utf8(contract.second.UnderlyingInstrID);

        static_data[contract.second.InstrumentID] = data;
    }

    client->release();
    return static_data;
}


PYBIND11_MODULE(app_static_data, m) {
    m.def("get_static_data",
          &get_static_data,
          "get_static_data",
          py::arg("ip"),
          py::arg("broker_id"),
          py::arg("user_id"),
          py::arg("password"),
          py::arg("app_id"),
          py::arg("auth_code"));
}
