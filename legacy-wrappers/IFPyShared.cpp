#include <IFPyShared.h>

ListCopyableWrapper::ListCopyableWrapper(ListCopyable<dpoint>&& other) : ListCopyable<dpoint>{std::move(other)}{};

ListCopyableWrapper::ListCopyableWrapper(py::array_t<sp::timecode<double>, py::array::c_style> other) : ListCopyable<dpoint>()
{
    auto mod = py::module::import("stopeight.matrix");
    auto data = (mod.attr("Vectors")(other)).cast<Vectors<std::vector<sp::timecode<double>>>>();
    std::transform(std::begin(data), std::end(data), std::back_inserter(*this), [](sp::timecode<double> &it_in) {
        return dpoint(qreal(it_in.coords[0]), qreal(it_in.coords[1]));
    });
}

py::array_t<sp::timecode<double>, py::array::c_style> ListCopyableWrapper::toPyArray(){
    auto result = Vectors<std::vector<sp::timecode<double>>>(this->size());
    std::transform(std::begin(*this),std::end(*this),std::begin(result),[](dpoint& point){
        auto tc = sp::timecode<double>();
        tc.set_x(double(point.x()));
        tc.set_y(double(point.y()));
        return tc;
    });
    return py::cast(result);
}

TurnAnalyzerWrapper::TurnAnalyzerWrapper(const ListCopyable<dpoint>& other) : TurnAnalyzer<dpoint>(static_cast<const TurnAnalyzer<dpoint>&>(other)) {//Hack ListCopyable should not be cast
}
TurnAnalyzerWrapper::TurnAnalyzerWrapper(ListCopyable<dpoint>&& other) : TurnAnalyzer<dpoint>{ std::move(static_cast<TurnAnalyzer<dpoint>&&>(other)) } {//Hack ListCopyable should not be cast
}

ListSwitchableWrapper::ListSwitchableWrapper(ListSwitchable<dpoint>&& other) : ListSwitchable<dpoint>{std::move(other)}{};

ListSwitchableWrapper::ListSwitchableWrapper(py::array_t<sp::timecode<double>, py::array::c_style> other) : ListSwitchable<dpoint>()
    {
        auto mod = py::module::import("stopeight.matrix");
        auto data = (mod.attr("Vectors")(other)).cast<Vectors<std::vector<sp::timecode<double>>>>();
        std::transform(std::begin(data), std::end(data), std::back_inserter(*this), [](sp::timecode<double> &it_in) {
            return dpoint(qreal(it_in.coords[0]), qreal(it_in.coords[1]));
        });
    }

py::array_t<sp::timecode<double>, py::array::c_style> ListSwitchableWrapper::toPyArray(){
    auto result = Vectors<std::vector<sp::timecode<double>>>(this->size());
    std::transform(std::begin(*this),std::end(*this),std::begin(result),[](dpoint& point){
        auto tc = sp::timecode<double>();
        tc.set_x(double(point.x()));
        tc.set_y(double(point.y()));
        return tc;
    });
    return py::cast(result);
}