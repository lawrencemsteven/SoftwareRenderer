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
		VecT(T args...) {
			checkSize();

			std::va_list vals;
			va_start(vals, args);

			m_vals[0] = args;

			for (int i = 1; i < N; i++) {
				m_vals[i] = va_arg(vals, T);
			}

			va_end(vals);
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

		template<class U>
		void translate(U amount) {
			*this += amount;
		}
		void rotate(int degreesCounterClockwise) {

		}
		void scale(float factor) {
			*this *= factor;
		}
		void flip() {
			for (int i = 0; i < N; i++) {
				m_vals[i] = -m_vals[i];
			}
		}

		std::size_t getSize() const {
			return N;
		}

		T operator[](std::size_t idx) const {
			return m_vals[idx];
		}

		template<class U>
		VecT& operator+=(const U& vec) {
			const std::size_t smallestSize = getSize() > vec.getSize();

			for (int i = 0; i < smallestSize; i++) {
				m_vals[i] += static_cast<T>(vec[i]);
			}

			return *this;
		}
		template<class U>
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

}