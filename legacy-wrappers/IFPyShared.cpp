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

py::array_t<sp::timecode<double>, py::array::c_style> QListWrapper::toPyArray(){
    //Hack Copy
    auto result = std::vector<sp::timecode<double>>(this->size());
    std::transform(std::begin(*this),std::end(*this),std::begin(result),[](dpoint& point){
        return sp::timecode<double>(double(point.x()),double(point.y()));
    });
    return py::cast(result);
}

template<class inType> TurnAnalyzerWrapper::TurnAnalyzerWrapper(inType &other) : TurnAnalyzer<dpoint>(other) {}
template TurnAnalyzerWrapper::TurnAnalyzerWrapper(QListWrapper& list);