//
// Created by 稻草人 on 2022/4/20.
//
#include "logger.h"
#include "pybind11/pybind11.h"
#include "yijinjing/paged/PageEngine.h"
#include <ctime>
#include <fstream>
#include <utility>


namespace py = pybind11;

YJJ_NAMESPACE_START

class PstTimeCtrl : public PstBase {
public:
    PstTimeCtrl(PageEngine *pe, std::string stopTimePt)
        : engine(pe), stop_time(std::move(stopTimePt)) {}

    void go() override {
        time_t raw_time = 0;
        ::time(&raw_time);

        struct tm *dt = ::localtime(&raw_time);

        char buffer[10];
        strftime(buffer, sizeof(buffer), "%H:%M:%S", dt);

        if (stop_time.compare(buffer) < 0) {
            SPDLOG_INFO("Auto stop with stop time {}.\n", stop_time);
            engine->stop();
        }
    }

    [[nodiscard]] std::string getName() const override { return "TimeCtrl"; }

private:
    PageEngine *engine;
    const std::string stop_time;
};

DECLARE_PTR(PstTimeCtrl);

YJJ_NAMESPACE_END

int run_page_service(std::string &log_file, std::string &journal_folder) {

    const int _ret = create_logger(log_file, "trace", false, false, true, 1, 1);

    int freq = 1;
    int cpu_id = -1;
    std::string stop_time_point;

    SPDLOG_INFO("PageEngine run with log_file {}, journal_folder {}, frequency {}.\n", log_file, journal_folder, freq);
    yijinjing::PageEngine engine(journal_folder + "/" + "PAGE_ENGINE_COMM", journal_folder + "/" + "TEMP_PAGE");

    if (!stop_time_point.empty()) {
        SPDLOG_INFO(">>> Add AutoTimeCtrl with stop time {}.\n", stop_time_point);
        yijinjing::PstTimeCtrlPtr task_control(new yijinjing::PstTimeCtrl(&engine, stop_time_point));
        engine.add_task(task_control);
    }
    engine.set_task_freq(freq);
    engine.start(cpu_id);
    return 0;
}


PYBIND11_MODULE(app_yijinjing_service, m) {
    m.def("run_page_service",
          &run_page_service,
          py::call_guard<py::gil_scoped_release>(),
          py::arg("log_file"),
          py::arg("journal_folder"));
}
