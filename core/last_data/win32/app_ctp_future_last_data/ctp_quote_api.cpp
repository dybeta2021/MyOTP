
#include "ctp_quote_api.h"
#include "encoding.h"
#include "logger.h"
#include "spdlog/spdlog.h"

CtpQuoteApi::CtpQuoteApi() {
#ifdef __WIN_SYS
    m_md_Release_signal = CreateEvent(NULL, false, false, NULL);
    m_md_Init_signal = CreateEvent(NULL, false, false, NULL);
    m_md_Join_signal = CreateEvent(NULL, false, false, NULL);
    m_md_ReqUserLogin_signal = CreateEvent(NULL, false, false, NULL);
    m_md_ReqUserLogout_signal = CreateEvent(NULL, false, false, NULL);
    m_md_SubscribeMarketData_signal = CreateEvent(NULL, false, false, NULL);
    m_md_UnSubscribeMarketData_signal = CreateEvent(NULL, false, false, NULL);
    m_md_SubscribeForQuoteRsp_signal = CreateEvent(NULL, false, false, NULL);
    m_md_UnSubscribeForQuoteRsp_signal = CreateEvent(NULL, false, false, NULL);
#elif defined(__UNIX_SYS)
    sem_init(&m_md_Release_signal, 0, 0);
    sem_init(&m_md_Init_signal, 0, 0);
    sem_init(&m_md_Join_signal, 0, 0);
    sem_init(&m_md_ReqUserLogin_signal, 0, 0);
    sem_init(&m_md_ReqUserLogout_signal, 0, 0);
    sem_init(&m_md_SubscribeMarketData_signal, 0, 0);
    sem_init(&m_md_UnSubscribeMarketData_signal, 0, 0);
    sem_init(&m_md_SubscribeForQuoteRsp_signal, 0, 0);
    sem_init(&m_md_UnSubscribeForQuoteRsp_signal, 0, 0);
#endif
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
#ifdef __WIN_SYS
    WaitForSingleObject(m_md_Init_signal, INFINITE);
#elif defined(__UNIX_SYS)
    sem_wait(&m_md_Init_signal);
#endif // 
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

#ifdef __WIN_SYS
    WaitForSingleObject(m_md_ReqUserLogin_signal, INFINITE);
#elif defined(__UNIX_SYS)
    sem_wait(&m_md_Im_md_ReqUserLogin_signalnit_signal);
#endif // 
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
#ifdef __WIN_SYS
    WaitForSingleObject(m_md_ReqUserLogout_signal, INFINITE);
#elif defined(__UNIX_SYS)
    sem_wait(&m_md_ReqUserLogout_signal);
#endif // __WIN_SYS
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

#ifdef __WIN_SYS
    WaitForSingleObject(m_md_SubscribeMarketData_signal, INFINITE);
#elif defined(__UNIX_SYS)
    sem_wait(&m_md_SubscribeMarketData_signal);
#endif // __WIN_SYS
}


[[maybe_unused]] void CtpQuoteApi::UnSubscribeMarketData() {
    SPDLOG_ERROR("UnSubscribeMarketData, 此函数不应该被调用！！.");
}


void CtpQuoteApi::OnFrontConnected() {
    SPDLOG_DEBUG("[CtpQuoteApi::OnFrontConnectedMD] Connected");
#ifdef __WIN_SYS
    SetEvent(m_md_Init_signal);
#elif defined(__UNIX_SYS)
    sem_post(&m_md_Init_signal);
#endif // __WIN_SYS
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
    if (bIsLast)
    {
#ifdef __WIN_SYS
        SetEvent(m_md_ReqUserLogin_signal);
#elif defined(__UNIX_SYS)
        sem_post(&m_md_ReqUserLogin_signal);
#endif // __WIN_SYS
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

    if (bIsLast)
    {
#ifdef __WIN_SYS
        SetEvent(m_md_ReqUserLogout_signal);
#elif defined(__UNIX_SYS)
        sem_post(&m_md_ReqUserLogout_signal);
#endif // __WIN_SYS
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

    if (bIsLast)
    {
#ifdef __WIN_SYS
        SetEvent(m_md_SubscribeMarketData_signal);
#elif defined(__UNIX_SYS)
        sem_post(&m_md_SubscribeMarketData_signal);
#endif // __WIN_SYS
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

    if (bIsLast)
    {
#ifdef __WIN_SYS
        SetEvent(m_md_UnSubscribeMarketData_signal);
#elif defined(__UNIX_SYS)
        sem_post(&m_md_UnSubscribeMarketData_signal);
#endif // __WIN_SYS
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
