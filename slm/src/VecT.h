#pragma once

namespace slm {

	template <class T, std::size_t N>
	class VecT {
	public:
		VecT() {
			checkSize();

			for (int i = 0; i < N; i++) {
				m_vals[i] = static_cast<T>(0);
			}
		}
		VecT(T x) {
			static_assert(N == 1, "Too many arguments!");
			m_vals[0] = x;
		}
		VecT(T x, T y) {
			static_assert(N == 2, "Too many arguments!");
			m_vals[0] = x;
			m_vals[1] = y;
		}
		VecT(T x, T y, T z) {
			static_assert(N == 3, "Too many arguments!");
			m_vals[0] = x;
			m_vals[1] = y;
			m_vals[2] = z;
		}
		VecT(T x, T y, T z, T w) {
			static_assert(N == 4, "Too many arguments!");
			m_vals[0] = x;
			m_vals[1] = y;
			m_vals[2] = z;
			m_vals[3] = w;
		}

		T x() const {
			return m_vals[0];
		}
		T y() const {
			return m_vals[1];
		}
		T z() const {
			return m_vals[2];
		}
		T w() const {
			return m_vals[3];
		}

		void x(T val) {
			m_vals[0] = val;
		}
		void y(T val) {
			m_vals[1] = val;
		}
		void z(T val) {
			m_vals[2] = val;
		}
		void w(T val) {
			m_vals[3] = val;
		}

		template <class U>
		void translate(U amount) {
			*this += amount;
		}
		void rotate(int degreesCounterClockwise) {
			const float radians =
				static_cast<float>(degreesCounterClockwise) * (static_cast<float>(M_PI) / 180.0f);
			const float sinRads = sin(radians);
			const float cosRads = cos(radians);

			const float x = static_cast<float>(m_vals[0]);
			const float y = static_cast<float>(m_vals[1]);

			m_vals[0] = static_cast<T>(x * cosRads - y * sinRads);
			m_vals[1] = static_cast<T>(y * cosRads + x * sinRads);
		}
		void scale(float factor) {
			*this *= factor;
		}
		void flip() {
			for (int i = 0; i < N; i++) {
				m_vals[i] = -m_vals[i];
			}
		}

		static std::size_t getSize() {
			return N;
		}

		T operator[](std::size_t idx) const {
			return m_vals[idx];
		}

		template <class U>
		VecT& operator+=(const U& vec) {
			const std::size_t smallestSize = getSize() < vec.getSize() ? getSize() : vec.getSize();

			for (int i = 0; i < smallestSize; i++) {
				m_vals[i] += static_cast<T>(vec[i]);
			}

			return *this;
		}
		template <class U>
		VecT& operator-=(const U& vec) {
			U other = vec;
			*this += other.flip();
		}
		VecT& operator*=(const float scalar) {
			for (int i = 0; i < getSize(); i++) {
				m_vals[i] = static_cast<T>(static_cast<float>(m_vals[i]) * scalar);
			}

			return *this;
		}

	private:
		T m_vals[N];

		void checkSize() const {
			static_assert(N >= 1 && N <= 4, "1 <= N >= 4");
		}
	};

	typedef VecT<int, 2> vec2i;
	typedef VecT<float, 2> vec2f;
}