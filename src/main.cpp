#include <pybind11/pybind11.h>
#include <sstream>
#include <tuple>

//------------------------------------------------------------------------------//

/*******************************************************************************
 * A dumb wrapper around a tuple, to demonstrate the binding of templated code *
 *******************************************************************************/

template <class... Ts>
class Tuple
{
public:
    template <typename T>
    T& get()
    {
        return std::get<T>(_tuple);
    }

    template <typename T>
    T const& get() const
    {
        return std::get<T>(_tuple);
    }

    template <typename T>
    void set(T const& val)
    {
        this->get<T>() = val;
    }

private:
    std::tuple<Ts...> _tuple{};
};

//------------------------------------------------------------------------------//

namespace py = pybind11;

/***************************************
 * Output customized pretty type names *
 ***************************************/

template <typename T>
std::string pretty_name()
{
    std::ostringstream o;
    o << typeid(T).name();
    return o.str();
}

template <> std::string pretty_name<int>        (){ return "int";      }
template <> std::string pretty_name<std::string>(){ return "str";      }
template <> std::string pretty_name<double>     (){ return "double";   }
template <> std::string pretty_name<Tuple<int>> (){ return "TupleInt"; }
template <> std::string pretty_name<Tuple<double, std::string>> (){ return "TupleDoubleStr"; }

/***********************************************************************
 * Bind the member template of Tuple for all types in a parameter pack *
 ***********************************************************************/

template <class C>
void bind_member_template_for_all_T(py::class_<C>&){}

template <class C, class T, class... Ts>
void bind_member_template_for_all_T(py::class_<C>& c)
{
    c.def(("get_" + pretty_name<T>()).c_str(), py::overload_cast<>(&C::template get<T>))
     .def(("get_" + pretty_name<T>()).c_str(), py::overload_cast<>(&C::template get<T>, py::const_))
     .def(("set_" + pretty_name<T>()).c_str(), &C::template set<T>);

    // recursively bind the member for each type
    bind_member_template_for_all_T<C, Ts...>(c);
}

/**************************************************
 * Bind the Tuple class for a given pack of types *
 **************************************************/

template <class... Ts>
void bindTuple(py::module& m, std::string const& name)
{
    using Class = Tuple<Ts...>;
    py::class_<Class> c(m, name.c_str());
    c.def(py::init<>());

    //bind set, set const and get
    bind_member_template_for_all_T<Class, Ts...>(c);

}

/*********************************************************
 * Actually bind some realizations of the Tuple template *
 *********************************************************/

PYBIND11_MODULE(template_example, m)
{
    bindTuple<int>(m, "TupleInt");
    bindTuple<double, std::string>(m, "TupleDoubleString");
    bindTuple<Tuple<int>, Tuple<double, std::string>>(m, "WeirdNestedTuple");
}
