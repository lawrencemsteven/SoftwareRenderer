#include "Vec.h"

namespace slm {

	//////////
	// Vec2 //
	//////////

	std::size_t Vec2::getSize() {
		return 2;
	}




	///////////
	// Vec2f //
	///////////

	Vec2f::Vec2f()
		: m_values{0.0f, 0.0f} {}

	Vec2f::Vec2f(float vals[2])
		: m_values{vals[0], vals[1]} {}

	Vec2f::Vec2f(const std::array<float, 2>& vals)
		: m_values{vals[0], vals[1]} {}

	Vec2f::Vec2f(float x, float y)
		: m_values{x, y} {}

	void Vec2f::x(float x) {
		m_values[0] = x;
	}

	void Vec2f::y(float y) {
		m_values[1] = y;
	}

	float Vec2f::x() const {
		return m_values[0];
	}

	float Vec2f::y() const {
		return m_values[1];
	}

	void Vec2f::translate(const Vec2& amount) {
		const auto values = amount.getValsAsFloat();
		translate(std::move(values));
	}

	void Vec2f::translate(const std::array<float, 2>& amount) {
		translateX(amount[0]);
		translateY(amount[1]);
	}

	void Vec2f::translate(const float amount[2]) {
		translateX(amount[0]);
		translateY(amount[1]);
	}

	void Vec2f::translateX(float amount) {
		m_values[0] += amount;
	}

	void Vec2f::translateY(float amount) {
		m_values[1] += amount;
	}

	void Vec2f::rotate(int32_t degreesCounterClockwise) {
		const float radians =
			static_cast<float>(degreesCounterClockwise) * (static_cast<float>(M_PI) / 180.0f);
		const float sinRads = sin(radians);
		const float cosRads = cos(radians);

		m_values[0] = x() * cosRads - y() * sinRads;
		m_values[1] = y() * cosRads + x() * sinRads;
	}

	void Vec2f::scale(const Vec2& amount) {
		const auto values = amount.getValsAsFloat();
		scale(std::move(values));
	}

	void Vec2f::scale(float factor) {
		scaleX(factor);
		scaleY(factor);
	}

	void Vec2f::scale(float factors[2]) {
		scaleX(factors[0]);
		scaleY(factors[1]);
	}

	void Vec2f::scale(std::array<float, 2> factors) {
		scaleX(factors[0]);
		scaleY(factors[1]);
	}

	void Vec2f::scaleX(float factor) {
		m_values[0] *= factor;
	}

	void Vec2f::scaleY(float factor) {
		m_values[1] *= factor;
	}

	float Vec2f::operator[](std::size_t idx) const {
		return m_values[idx];
	}

	Vec2f& Vec2f::operator+=(const Vec2& other) {
		translate(other);

		return *this;
	}

	Vec2f& Vec2f::operator+=(const std::array<float, 2>& amount) {
		translate(amount);

		return *this;
	}

	Vec2f& Vec2f::operator+=(const float amount[2]) {
		translate(amount);

		return *this;
	}

	Vec2f& Vec2f::operator-=(const Vec2& other) {
		const auto values = other.getValsAsFloat();

		translate({-values[0], -values[1]});

		return *this;
	}

	Vec2f& Vec2f::operator-=(const std::array<float, 2>& amount) {
		translate({-amount[0], -amount[1]});

		return *this;
	}

	Vec2f& Vec2f::operator-=(const float amount[2]) {
		translate({-amount[0], -amount[1]});

		return *this;
	}

	Vec2f& Vec2f::operator*=(const Vec2& other) {
		scale(other);

		return *this;
	}

	Vec2f& Vec2f::operator*=(const float factor) {
		scale(factor);
	}

	bool Vec2f::operator==(const Vec2& other) const {
		const auto otherValues = other.getValsAsFloat();

		return *this == otherValues;
	}

	bool Vec2f::operator==(const std::array<float, 2>& other) const {
		return m_values[0] == other[0] && m_values[1] == other[1];
	}

	bool Vec2f::operator==(const float other[2]) const {
		return m_values[0] == other[0] && m_values[1] == other[1];
	}

	std::array<float, 2> Vec2f::getValsAsFloat() const {
		return std::array<float, 2>{m_values[0], m_values[1]};
	}

	std::array<int32_t, 2> Vec2f::getValsAsInt() const {
		return std::array<int32_t, 2>{static_cast<int32_t>(m_values[0]),
									  static_cast<int32_t>(m_values[1])};
	}




	///////////
	// Vec2i //
	///////////

	Vec2i::Vec2i()
		: m_values{0, 0} {}

	Vec2i::Vec2i(int32_t vals[2])
		: m_values{vals[0], vals[1]} {}

	Vec2i::Vec2i(const std::array<int32_t, 2>& vals)
		: m_values{vals[0], vals[1]} {}

	Vec2i::Vec2i(int32_t x, int32_t y)
		: m_values{x, y} {}

	void Vec2i::x(int32_t x) {
		m_values[0] = x;
	}

	void Vec2i::y(int32_t y) {
		m_values[1] = y;
	}

	int32_t Vec2i::x() const {
		return m_values[0];
	}

	int32_t Vec2i::y() const {
		return m_values[1];
	}

	void Vec2i::translate(const Vec2& amount) {
		const auto values = amount.getValsAsInt();
		translate(std::move(values));
	}

	void Vec2i::translate(const std::array<int32_t, 2>& amount) {
		translateX(amount[0]);
		translateY(amount[1]);
	}

	void Vec2i::translate(const int32_t amount[2]) {
		translateX(amount[0]);
		translateY(amount[1]);
	}

	void Vec2i::translateX(int32_t amount) {
		m_values[0] += amount;
	}

	void Vec2i::translateY(int32_t amount) {
		m_values[1] += amount;
	}

	void Vec2i::rotate(int32_t degreesCounterClockwise) {
		const float radians =
			static_cast<float>(degreesCounterClockwise) * (static_cast<float>(M_PI) / 180.0f);
		const float sinRads = sin(radians);
		const float cosRads = cos(radians);

		m_values[0] = static_cast<int32_t>(x() * cosRads - y() * sinRads);
		m_values[1] = static_cast<int32_t>(y() * cosRads + x() * sinRads);
	}

	void Vec2i::scale(const Vec2& amount) {
		const auto values = amount.getValsAsFloat();
		scale(values);
	}

	void Vec2i::scale(float factor) {
		scaleX(factor);
		scaleY(factor);
	}

	void Vec2i::scale(float factors[2]) {
		scaleX(factors[0]);
		scaleY(factors[1]);
	}

	void Vec2i::scale(std::array<float, 2> factors) {
		scaleX(factors[0]);
		scaleY(factors[1]);
	}

	void Vec2i::scaleX(float factor) {
		m_values[0] *= factor;
	}

	void Vec2i::scaleY(float factor) {
		m_values[1] *= factor;
	}

	int32_t Vec2i::operator[](std::size_t idx) const {
		return m_values[idx];
	}

	Vec2i& Vec2i::operator+=(const Vec2& other) {
		translate(other);

		return *this;
	}

	Vec2i& Vec2i::operator+=(const std::array<int32_t, 2>& amount) {
		translate(amount);

		return *this;
	}

	Vec2i& Vec2i::operator+=(const int32_t amount[2]) {
		translate(amount);

		return *this;
	}

	Vec2i& Vec2i::operator-=(const Vec2& other) {
		const auto values = other.getValsAsInt();

		translate({-values[0], -values[1]});

		return *this;
	}

	Vec2i& Vec2i::operator-=(const std::array<int32_t, 2>& amount) {
		translate({-amount[0], -amount[1]});

		return *this;
	}

	Vec2i& Vec2i::operator-=(const int32_t amount[2]) {
		translate({-amount[0], -amount[1]});

		return *this;
	}

	Vec2i& Vec2i::operator*=(const Vec2& other) {
		scale(other);

		return *this;
	}

	Vec2i& Vec2i::operator*=(const float other) {
		scale(other);

		return *this;
	}

	bool Vec2i::operator==(const Vec2& other) const {
		const auto otherValues = other.getValsAsInt();

		return *this == otherValues;
	}

	bool Vec2i::operator==(const std::array<int32_t, 2>& other) const {
		return m_values[0] == other[0] && m_values[1] == other[1];
	}

	bool Vec2i::operator==(const int32_t other[2]) const {
		return m_values[0] == other[0] && m_values[1] == other[1];
	}

	std::array<float, 2> Vec2i::getValsAsFloat() const {
		return std::array<float, 2>{static_cast<float>(m_values[0]),
									static_cast<float>(m_values[1])};
	}

	std::array<int32_t, 2> Vec2i::getValsAsInt() const {
		return std::array<int32_t, 2>{m_values[0], m_values[1]};
	}

}