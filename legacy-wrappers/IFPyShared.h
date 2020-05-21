#undef NDEBUG
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
namespace py = pybind11;

#include "turnanalyzer.h"
#include "corneranalyzer.h"
#include <stopeight-clibs/shared_types.h>
#include <stopeight-clibs/Matrix.h>

class ListCopyableWrapper : public ListCopyable<dpoint>
{
  public:
    ListCopyableWrapper(py::array_t<sp::timecode<double>, py::array::c_style> other);
    ListCopyableWrapper(ListCopyable<dpoint>&& other);
    //using ListCopyable<dpoint>::ListCopyable;

    py::array_t<sp::timecode<double>, py::array::c_style> toPyArray();
};

//template TurnAnalyzer<dpoint>::TurnAnalyzer(QListWrapper& list);
class TurnAnalyzerWrapper : public TurnAnalyzer<dpoint>
{
  public:
      using TurnAnalyzer<dpoint>::TurnAnalyzer;
      TurnAnalyzerWrapper(const ListCopyable<dpoint>& other);
      TurnAnalyzerWrapper(ListCopyable<dpoint>&& other);

};

class ListSwitchableWrapper : public ListSwitchable<dpoint>{
  public:
    ListSwitchableWrapper(py::array_t<sp::timecode<double>, py::array::c_style> other);
    ListSwitchableWrapper(ListSwitchable<dpoint>&& other);
    //using ListSwitchable<dpoint>::ListSwitchable;

    py::array_t<sp::timecode<double>, py::array::c_style> toPyArray();
};