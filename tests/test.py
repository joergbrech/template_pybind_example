import template_example as m

A = m.TupleInt()
assert isinstance(A.get_int(), int)
assert A.get_int() == 0
#A.set_int(42)
#assert A.get_int() == 42

B = m.TupleDoubleString()
assert isinstance(B.get_double(), float)
assert B.get_double() == 0.0
assert isinstance(B.get_str(), str)
assert B.get_str() == ""

C = m.WeirdNestedTuple()
assert isinstance(C.get_TupleInt(), m.TupleInt)
assert isinstance(C.get_TupleInt().get_int(), int)
assert C.get_TupleInt().get_int() == 0
assert isinstance(C.get_TupleDoubleStr(), m.TupleDoubleString)
assert isinstance(C.get_TupleDoubleStr().get_double(), float)
assert C.get_TupleDoubleStr().get_double() == 0.0
assert isinstance(C.get_TupleDoubleStr().get_str(), str)
assert C.get_TupleDoubleStr().get_str() == ""

