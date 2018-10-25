#include <IFPyShared.h>

QListWrapper::QListWrapper(py::array_t<sp::timecode<double>, py::array::c_style> other) : ListCopyable<dpoint>()
    {
        auto mod = py::module::import("stopeight.grapher");
        auto data = (mod.attr("np_to_tc")(other)).cast<std::vector<sp::timecode<double>>>();
        //Hack Copy
        std::transform(std::begin(data), std::end(data), std::back_inserter(*this), [](sp::timecode<double> &it_in) {
            return dpoint(qreal(it_in.coords[0]), qreal(it_in.coords[1]));
        });
    }

//template TurnAnalyzer<dpoint>::TurnAnalyzer(QListWrapper& list);
TurnAnalyzerWrapper::TurnAnalyzerWrapper(QListWrapper &other) : TurnAnalyzer<dpoint>(dynamic_cast<ListCopyable<dpoint> &>(other)) {}
