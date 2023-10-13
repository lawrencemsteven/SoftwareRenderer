#pragma once

namespace slm {

	template<class T>
	class LineT {
	public:
		LineT() = default;
		LineT(T start, T end) {
			m_start = std::move(start);
			m_end	= std::move(end);
		}

		const T& getStart() const {
			return m_start;
		}
		const T& getEnd() const {
			return m_end;
		}

		const T& operator[](std::size_t idx) const {
			if (idx == 0) {
				return m_start;
			}
			return m_end;
		}

	private:
		T m_start{};
		T m_end{};
	};

}