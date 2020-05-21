#include <IFPyShared.h>

template<typename F> ListCopyableWrapper<F>::ListCopyableWrapper(const F& other) : F(other){};
template ListCopyableWrapper<ListCopyable<dpoint>>::ListCopyableWrapper(const ListCopyable<dpoint>& other);
template ListCopyableWrapper<TurnAnalyzer<dpoint>>::ListCopyableWrapper(const TurnAnalyzer<dpoint>& other);//call to member

template<typename F> ListCopyableWrapper<F>::ListCopyableWrapper(py::array_t<sp::timecode<double>, py::array::c_style> other) : F()
{
    auto mod = py::module::import("stopeight.matrix");
    auto data = (mod.attr("Vectors")(other)).cast<Vectors<std::vector<sp::timecode<double>>>>();
    std::transform(std::begin(data), std::end(data), std::back_inserter(*this), [](sp::timecode<double> &it_in) {
        return typename F::value_type(qreal(it_in.coords[0]), qreal(it_in.coords[1]));
    });
}
template ListCopyableWrapper<ListCopyable<dpoint>>::ListCopyableWrapper(py::array_t<sp::timecode<double>, py::array::c_style> other);
template ListCopyableWrapper<TurnAnalyzer<dpoint>>::ListCopyableWrapper(py::array_t<sp::timecode<double>, py::array::c_style> other);

template<typename F> py::array_t<sp::timecode<double>, py::array::c_style> ListCopyableWrapper<F>::toPyArray(){
    auto result = Vectors<std::vector<sp::timecode<double>>>(this->size());
    std::transform(std::begin(*this),std::end(*this),std::begin(result),[](dpoint& point){
        auto tc = sp::timecode<double>();
        tc.set_x(double(point.x()));
        tc.set_y(double(point.y()));
        return tc;
    });
    return py::cast(result);
}
template py::array_t<sp::timecode<double>, py::array::c_style> ListCopyableWrapper<TurnAnalyzer<dpoint>>::toPyArray();
template py::array_t<sp::timecode<double>, py::array::c_style> ListCopyableWrapper<ListCopyable<dpoint>>::toPyArray();

/*TurnAnalyzerWrapper::TurnAnalyzerWrapper(const ListCopyable<dpoint>& other) : TurnAnalyzer<dpoint>(static_cast<const TurnAnalyzer<dpoint>&>(other)) {//Hack ListCopyable should not be cast
}
TurnAnalyzerWrapper::TurnAnalyzerWrapper(ListCopyable<dpoint>&& other) : TurnAnalyzer<dpoint>{ std::move(static_cast<TurnAnalyzer<dpoint>&&>(other)) } {//Hack ListCopyable should not be cast
}*/

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