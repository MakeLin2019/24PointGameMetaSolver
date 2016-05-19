Copyright @ Harry Leong

// fraction number, present a / b
template<int a, int b>
struct Number {
	static const int A = a;
	// b == 0 means this is a bad number
	static const int B = b;
	static const bool is24 = (b != 0) && (a / b * b == a) && (a / b == 24);
	static const bool value = is24;
};

template<class N1, class N2>
struct Add {
	typedef Number<N1::A*N2::B + N2::A*N1::B, N1::B*N2::B> type;
};

template<class N1, class N2>
struct Sub {
	typedef Number<N1::A*N2::B - N2::A*N1::B, N1::B*N2::B> type;
};

template<class N1, class N2>
struct Mul {
	typedef Number<N1::A*N2::A, N1::B*N2::B> type;
};

template<class N1, class N2>
struct Div {
	// keep result as bad number
	typedef Number<N1::A*N2::B, (N2::B == 0 ? 0 : N1::B*N2::A)> type;
};

// following is c++11 feature
template<class N1, class N2>
using AddT = typename Add<N1, N2>::type;
template<class N1, class N2>
using SubT = typename Sub<N1, N2>::type;
template<class N1, class N2>
using MulT = typename Mul<N1, N2>::type;
template<class N1, class N2>
using DivT = typename Div<N1, N2>::type;

template<bool a, bool... b>
struct Or {
	static const bool value = a || Or<b...>::value;
};

template<bool a>
struct Or<a> {
	static const bool value = a;
};

// finally, we have two numbers
template<class N1, class N2>
struct DFS2 {
	static const bool value = Or<
		AddT<N1, N2>::value,
		SubT<N1, N2>::value,
		SubT<N2, N1>::value,
		MulT<N1, N2>::value,
		DivT<N1, N2>::value,
		DivT<N2, N1>::value
	>::value;
};

template<class N1, class N2, class N3>
struct DFS3Step2 {
	static const bool value = Or<
		DFS2<AddT<N1, N2>, N3>::value, // N1+N2 == N2+N1
		DFS2<SubT<N1, N2>, N3>::value,
		DFS2<SubT<N2, N1>, N3>::value,
		DFS2<MulT<N1, N2>, N3>::value,
		DFS2<DivT<N1, N2>, N3>::value,
		DFS2<DivT<N2, N1>, N3>::value
	>::value;
};

// we have 3 numbers
template<class N1, class N2, class N3>
struct DFS3Step1 { // select two value
	static const bool value = Or<

		DFS3Step2<N1, N2, N3>::value,
		DFS3Step2<N1, N3, N2>::value,
		DFS3Step2<N2, N3, N1>::value

	>::value;
};

template<class N1, class N2, class N3, class N4>
struct DFS4Step2 {
	static const bool value = Or<
		DFS3Step1<AddT<N1, N2>, N3, N4>::value,
		DFS3Step1<SubT<N1, N2>, N3, N4>::value,
		DFS3Step1<SubT<N2, N1>, N3, N4>::value,
		DFS3Step1<MulT<N1, N2>, N3, N4>::value,
		DFS3Step1<DivT<N1, N2>, N3, N4>::value,
		DFS3Step1<DivT<N2, N1>, N3, N4>::value
	>::value;
};

// we have 4 numbers
template<class N1, class N2, class N3, class N4>
struct DFS4Step1 { // select two value
	static const bool value = Or<

		DFS4Step2<N1, N2, N3, N4>::value,
		DFS4Step2<N1, N3, N2, N4>::value,
		DFS4Step2<N1, N4, N2, N3>::value,
		DFS4Step2<N2, N3, N1, N4>::value,
		DFS4Step2<N2, N4, N1, N3>::value,
		DFS4Step2<N3, N4, N1, N2>::value

	>::value;
};

template<int N1, int N2, int N3, int N4>
struct Game24Point { // select two value
	static const bool value = DFS4Step1<Number<N1, 1>, Number<N2, 1>, Number<N3, 1>, Number<N4, 1> >::value;
};


int main() {
	static_assert(Game24Point<1, 1, 1, 1>::value == false, "");
	static_assert(Game24Point<1, 1, 1, 2>::value == false, "");
	static_assert(Game24Point<1, 1, 1, 3>::value == false, "");
	static_assert(Game24Point<1, 1, 1, 4>::value == false, "");
	static_assert(Game24Point<1, 1, 1, 5>::value == false, "");
	static_assert(Game24Point<1, 1, 1, 6>::value == false, "");
	static_assert(Game24Point<1, 1, 1, 7>::value == false, "");
	static_assert(Game24Point<1, 1, 1, 8>::value == true, "");
	static_assert(Game24Point<1, 1, 1, 9>::value == false, "");
	static_assert(Game24Point<1, 1, 1, 10>::value == false, "");
	static_assert(Game24Point<1, 1, 2, 2>::value == false, "");
	static_assert(Game24Point<1, 1, 2, 3>::value == false, "");
	static_assert(Game24Point<1, 1, 2, 4>::value == false, "");
	static_assert(Game24Point<1, 1, 2, 5>::value == false, "");
	static_assert(Game24Point<1, 1, 2, 6>::value == true, "");
	static_assert(Game24Point<1, 1, 2, 7>::value == true, "");
	static_assert(Game24Point<1, 1, 2, 8>::value == true, "");
	static_assert(Game24Point<1, 1, 2, 9>::value == true, "");
	static_assert(Game24Point<1, 1, 2, 10>::value == true, "");
	static_assert(Game24Point<1, 1, 3, 3>::value == false, "");
	static_assert(Game24Point<1, 1, 3, 4>::value == true, "");
	static_assert(Game24Point<1, 1, 3, 5>::value == true, "");
	static_assert(Game24Point<1, 1, 3, 6>::value == true, "");
	static_assert(Game24Point<1, 1, 3, 7>::value == true, "");
	static_assert(Game24Point<1, 1, 3, 8>::value == true, "");
	static_assert(Game24Point<1, 1, 3, 9>::value == true, "");
	static_assert(Game24Point<1, 1, 3, 10>::value == true, "");

	static_assert(Game24Point<10, 3, 1, 1>::value == true, "");
	static_assert(Game24Point<3, 1, 1, 10>::value == true, "");
	static_assert(Game24Point<1, 3, 10, 1>::value == true, "");

	static_assert(Game24Point<1, 6, 7, 8>::value == false, "");
	static_assert(Game24Point<2, 2, 4, 5>::value == true, "");


	return 0;
}

