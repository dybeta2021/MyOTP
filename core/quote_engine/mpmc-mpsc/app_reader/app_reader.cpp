#include "logger.h"
#include "disruptor/disruptor.h"
#include "ThostFtdcUserApiStruct.h"
#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

namespace py = pybind11;

int app_reader() {
    create_logger("clogs/consumer.log", "trace", false, false, false, 1, 1);
    auto shm = disruptor::Disruptor<CThostFtdcDepthMarketDataField>(disruptor::wait::YIELDING_WAIT);
    shm.Init("test.store", 1024 * 1024 * 16);

    // 获取当前最新的数据
    const int user_id = 0;
    int64_t user_last_cursor = -1;
    if (!shm.RegisterConsumer(user_id, user_last_cursor)) {
        return 1;
    }
    SPDLOG_DEBUG("user:{}, user_cursor:{}", user_id, user_last_cursor);

    CThostFtdcDepthMarketDataField *ptr = nullptr;
    auto ret_idx = shm.WaitFor(user_last_cursor);
    SPDLOG_DEBUG("user:{}, user_cursor:{}，ret_idx:{}", user_id, user_last_cursor, ret_idx);
    do {
        ptr = shm.GetData(user_last_cursor);
        shm.CommitRead(user_id, user_last_cursor);
        ret_idx = shm.WaitFor(++user_last_cursor);
        SPDLOG_TRACE("user:{}, user_cursor:{}，ret_idx:{}, symbol:{}, last_price:{}", user_id, user_last_cursor, ret_idx,
                     ptr->InstrumentID, ptr->LastPrice);
    } while (user_last_cursor <= ret_idx);

    return 0;
}

PYBIND11_MODULE(app_reader, m) {
    m.def("app_reader",
          &app_reader,
          py::call_guard<py::gil_scoped_release>());
}
