#include "Vec.h"

#include "Primitive.h"

namespace slm {

	/////////////////
	// BitLocation //
	/////////////////

	BitLocation::BitLocation() {}

	BitLocation::BitLocation(unsigned char location) {
		setLocation(location);
	}

	BitLocation::BitLocation(bool above, bool below, bool left, bool right) {
		setAbove(above);
		setBelow(below);
		setLeft(left);
		setRight(right);
	}

	void BitLocation::setLocation(unsigned char location) {
		m_location = std::move(location);
	}

	void BitLocation::setAbove(bool above) {
		m_location =
			above ? m_location | BIT_LOCATIONS::ABOVE : m_location & BIT_LOCATIONS_INVERTED::ABOVE;
	}

	void BitLocation::setBelow(bool below) {
		m_location =
			below ? m_location | BIT_LOCATIONS::BELOW : m_location & BIT_LOCATIONS_INVERTED::BELOW;
	}

	void BitLocation::setLeft(bool left) {
		m_location =
			left ? m_location | BIT_LOCATIONS::LEFT : m_location & BIT_LOCATIONS_INVERTED::LEFT;
	}

	void BitLocation::setRight(bool right) {
		m_location =
			right ? m_location | BIT_LOCATIONS::RIGHT : m_location & BIT_LOCATIONS_INVERTED::RIGHT;
	}

	unsigned char BitLocation::getLocation() const {
		return m_location;
	}

	bool BitLocation::getAbove() const {
		return m_location & BIT_LOCATIONS::ABOVE;
	}

	bool BitLocation::getBelow() const {
		return m_location & BIT_LOCATIONS::BELOW;
	}

	bool BitLocation::getLeft() const {
		return m_location & BIT_LOCATIONS::LEFT;
	}

	bool BitLocation::getRight() const {
		return m_location & BIT_LOCATIONS::RIGHT;
	}

	bool BitLocation::getInside() const {
		return !m_location;
	}

	bool BitLocation::getOutside() const {
		return m_location;
	}

	bool BitLocation::getVertical() const {
		return getAbove() || getBelow();
	}

	bool BitLocation::getHorizontal() const {
		return getLeft() || getRight();
	}

	unsigned char BitLocation::compareLocations(const BitLocation& other) const {
		return getLocation() & other.getLocation();
	}




	//////////
	// Vec2 //
	//////////

	std::size_t Vec2::getSize() {
		return 2;
	}

	std::array<float, 2> Vec2::rotationHelper(const int32_t degreesCounterClockwise) const {
		const auto values = getValsAsFloat();

		const float radians =
			static_cast<float>(degreesCounterClockwise) * (static_cast<float>(M_PI) / 180.0f);
		const float sinRads = sin(radians);
		const float cosRads = cos(radians);

		const float outX = values[0] * cosRads - values[1] * sinRads;
		const float outY = values[1] * cosRads + values[0] * sinRads;

		return {outX, outY};
	}




	//////////
	// Vec3 //
	//////////

	std::size_t Vec3::getSize() {
		return 3;
	}




	///////////
	// Vec2f //
	///////////

	Vec2f::Vec2f()
		: m_values{0.0f, 0.0f} {}

	Vec2f::Vec2f(const float vals[2])
		: m_values{vals[0], vals[1]} {}

	Vec2f::Vec2f(const std::array<float, 2>& vals)
		: m_values{vals[0], vals[1]} {}

	Vec2f::Vec2f(const float x, const float y)
		: m_values{x, y} {}

	void Vec2f::x(const float x) {
		m_values[0] = x;
	}

	void Vec2f::y(const float y) {
		m_values[1] = y;
	}

	float Vec2f::x() const {
		return m_values[0];
	}

	float Vec2f::y() const {
		return m_values[1];
	}

	BitLocation Vec2f::insideBox(const AxisAlignedBox2u& box) const {
		BitLocation loc{};

		loc.setLeft(x() < box.getLeft());
		loc.setRight(x() > box.getRight());
		loc.setAbove(y() > box.getTop());
		loc.setBelow(y() < box.getBottom());

		return loc;
	}

	void Vec2f::translate(const Vec2& amount) {
		const auto values = amount.getValsAsFloat();
		translate(values);
	}

	void Vec2f::translate(const std::array<float, 2>& amount) {
		translateX(amount[0]);
		translateY(amount[1]);
	}

	void Vec2f::translate(const float amount[2]) {
		translateX(amount[0]);
		translateY(amount[1]);
	}

	void Vec2f::translateX(const float amount) {
		m_values[0] += amount;
	}

	void Vec2f::translateY(const float amount) {
		m_values[1] += amount;
	}

	void Vec2f::rotate(const int32_t degreesCounterClockwise) {
		const auto values = rotationHelper(degreesCounterClockwise);
		m_values[0]		  = values[0];
		m_values[1]		  = values[1];
	}

	void Vec2f::scale(const Vec2& amount) {
		const auto values = amount.getValsAsFloat();
		scale(values);
	}

	void Vec2f::scale(const float factor) {
		scaleX(factor);
		scaleY(factor);
	}

	void Vec2f::scale(const float factors[2]) {
		scaleX(factors[0]);
		scaleY(factors[1]);
	}

	void Vec2f::scale(const std::array<float, 2>& factors) {
		scaleX(factors[0]);
		scaleY(factors[1]);
	}

	void Vec2f::scaleX(const float factor) {
		m_values[0] *= factor;
	}

	void Vec2f::scaleY(const float factor) {
		m_values[1] *= factor;
	}

	float Vec2f::operator[](const std::size_t idx) const {
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

		return *this;
	}

	Vec2f& Vec2f::operator*=(const std::array<float, 2>& amount) {
		scale(amount);

		return *this;
	}

	Vec2f& Vec2f::operator*=(const float amount[2]) {
		scale(amount);

		return *this;
	}

	bool Vec2f::operator==(const Vec2f& other) const {
		return m_values[0] == other[0] && m_values[1] == other[1];
	}

	bool Vec2f::operator==(const std::array<float, 2>& other) const {
		return m_values[0] == other[0] && m_values[1] == other[1];
	}

	bool Vec2f::operator==(const float other[2]) const {
		return m_values[0] == other[0] && m_values[1] == other[1];
	}

	bool Vec2f::operator!=(const Vec2f& other) const {
		return !(*this == other);
	}

	bool Vec2f::operator!=(const std::array<float, 2>& other) const {
		return !(*this == other);
	}

	bool Vec2f::operator!=(const float other[2]) const {
		return !(*this == other);
	}

	std::array<float, 2> Vec2f::getValsAsFloat() const {
		return std::array<float, 2>{m_values[0], m_values[1]};
	}

	std::array<int32_t, 2> Vec2f::getValsAsInt() const {
		return std::array<int32_t, 2>{static_cast<int32_t>(m_values[0]),
									  static_cast<int32_t>(m_values[1])};
	}

	std::array<uint32_t, 2> Vec2f::getValsAsUint() const {
		return std::array<uint32_t, 2>{static_cast<uint32_t>(m_values[0]),
									   static_cast<uint32_t>(m_values[1])};
	}




	///////////
	// Vec2i //
	///////////

	Vec2i::Vec2i()
		: m_values{0, 0} {}

	Vec2i::Vec2i(const int32_t vals[2])
		: m_values{vals[0], vals[1]} {}

	Vec2i::Vec2i(const std::array<int32_t, 2>& vals)
		: m_values{vals[0], vals[1]} {}

	Vec2i::Vec2i(const int32_t x, const int32_t y)
		: m_values{x, y} {}

	void Vec2i::x(const int32_t x) {
		m_values[0] = x;
	}

	void Vec2i::y(const int32_t y) {
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
		translate(values);
	}

	void Vec2i::translate(const std::array<int32_t, 2>& amount) {
		translateX(amount[0]);
		translateY(amount[1]);
	}

	void Vec2i::translate(const int32_t amount[2]) {
		translateX(amount[0]);
		translateY(amount[1]);
	}

	void Vec2i::translateX(const int32_t amount) {
		m_values[0] += amount;
	}

	void Vec2i::translateY(const int32_t amount) {
		m_values[1] += amount;
	}

	void Vec2i::rotate(const int32_t degreesCounterClockwise) {
		const auto values = rotationHelper(degreesCounterClockwise);
		m_values[0]		  = static_cast<int32_t>(values[0]);
		m_values[1]		  = static_cast<int32_t>(values[1]);
	}

	void Vec2i::scale(const Vec2& amount) {
		const auto values = amount.getValsAsFloat();
		scale(values);
	}

	void Vec2i::scale(const float factor) {
		scaleX(factor);
		scaleY(factor);
	}

	void Vec2i::scale(const float factors[2]) {
		scaleX(factors[0]);
		scaleY(factors[1]);
	}

	void Vec2i::scale(const std::array<float, 2>& factors) {
		scaleX(factors[0]);
		scaleY(factors[1]);
	}

	void Vec2i::scaleX(const float factor) {
		m_values[0] *= factor;
	}

	void Vec2i::scaleY(const float factor) {
		m_values[1] *= factor;
	}

	int32_t Vec2i::operator[](const std::size_t idx) const {
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

	Vec2i& Vec2i::operator*=(const std::array<float, 2>& amount) {
		scale(amount);

		return *this;
	}

	Vec2i& Vec2i::operator*=(const float amount[2]) {
		scale(amount);

		return *this;
	}

	bool Vec2i::operator==(const Vec2i& other) const {
		return m_values[0] == other[0] && m_values[1] == other[1];
	}

	bool Vec2i::operator==(const std::array<int32_t, 2>& other) const {
		return m_values[0] == other[0] && m_values[1] == other[1];
	}

	bool Vec2i::operator==(const int32_t other[2]) const {
		return m_values[0] == other[0] && m_values[1] == other[1];
	}

	bool Vec2i::operator!=(const Vec2i& other) const {
		return !(*this == other);
	}

	bool Vec2i::operator!=(const std::array<int32_t, 2>& other) const {
		return !(*this == other);
	}

	bool Vec2i::operator!=(const int32_t other[2]) const {
		return !(*this == other);
	}

	std::array<float, 2> Vec2i::getValsAsFloat() const {
		return std::array<float, 2>{static_cast<float>(m_values[0]),
									static_cast<float>(m_values[1])};
	}

	std::array<int32_t, 2> Vec2i::getValsAsInt() const {
		return std::array<int32_t, 2>{m_values[0], m_values[1]};
	}

	std::array<uint32_t, 2> Vec2i::getValsAsUint() const {
		return std::array<uint32_t, 2>{static_cast<uint32_t>(m_values[0]),
									   static_cast<uint32_t>(m_values[1])};
	}




	///////////
	// Vec2u //
	///////////

	Vec2u::Vec2u()
		: m_values{0u, 0u} {}

	Vec2u::Vec2u(const uint32_t vals[2])
		: m_values{vals[0], vals[1]} {}

	Vec2u::Vec2u(const std::array<uint32_t, 2>& vals)
		: m_values{vals[0], vals[1]} {}

	Vec2u::Vec2u(const uint32_t x, const uint32_t y)
		: m_values{x, y} {}

	void Vec2u::x(const uint32_t x) {
		m_values[0] = x;
	}

	void Vec2u::y(const uint32_t y) {
		m_values[1] = y;
	}

	uint32_t Vec2u::x() const {
		return m_values[0];
	}

	uint32_t Vec2u::y() const {
		return m_values[1];
	}

	void Vec2u::translate(const Vec2& amount) {
		const auto values = amount.getValsAsUint();
		translate(values);
	}

	void Vec2u::translate(const std::array<uint32_t, 2>& amount) {
		translateX(amount[0]);
		translateY(amount[1]);
	}

	void Vec2u::translate(const uint32_t amount[2]) {
		translateX(amount[0]);
		translateY(amount[1]);
	}

	void Vec2u::translateX(const uint32_t amount) {
		m_values[0] += amount;
	}

	void Vec2u::translateY(const uint32_t amount) {
		m_values[1] += amount;
	}

	void Vec2u::rotate(const int32_t degreesCounterClockwise) {
		const auto values = rotationHelper(degreesCounterClockwise);
		m_values[0]		  = static_cast<uint32_t>(values[0]);
		m_values[1]		  = static_cast<uint32_t>(values[1]);
	}

	void Vec2u::scale(const Vec2& amount) {
		const auto values = amount.getValsAsFloat();
		scale(values);
	}

	void Vec2u::scale(const float factor) {
		scaleX(factor);
		scaleY(factor);
	}

	void Vec2u::scale(const float factors[2]) {
		scaleX(factors[0]);
		scaleY(factors[1]);
	}

	void Vec2u::scale(const std::array<float, 2>& factors) {
		scaleX(factors[0]);
		scaleY(factors[1]);
	}

	void Vec2u::scaleX(const float factor) {
		m_values[0] *= factor;
	}

	void Vec2u::scaleY(const float factor) {
		m_values[1] *= factor;
	}

	uint32_t Vec2u::operator[](const std::size_t idx) const {
		return m_values[idx];
	}

	Vec2u& Vec2u::operator+=(const Vec2& other) {
		translate(other);

		return *this;
	}

	Vec2u& Vec2u::operator+=(const std::array<uint32_t, 2>& amount) {
		translate(amount);

		return *this;
	}

	Vec2u& Vec2u::operator+=(const uint32_t amount[2]) {
		translate(amount);

		return *this;
	}

	Vec2u& Vec2u::operator-=(const Vec2& other) {
		const auto values = other.getValsAsUint();

		translate({-values[0], -values[1]});

		return *this;
	}

	Vec2u& Vec2u::operator-=(const std::array<uint32_t, 2>& amount) {
		translate({-amount[0], -amount[1]});

		return *this;
	}

	Vec2u& Vec2u::operator-=(const uint32_t amount[2]) {
		translate({-amount[0], -amount[1]});

		return *this;
	}

	Vec2u& Vec2u::operator*=(const Vec2& other) {
		scale(other);

		return *this;
	}

	Vec2u& Vec2u::operator*=(const float factor) {
		scale(factor);

		return *this;
	}

	Vec2u& Vec2u::operator*=(const std::array<float, 2>& amount) {
		scale(amount);

		return *this;
	}

	Vec2u& Vec2u::operator*=(const float amount[2]) {
		scale(amount);

		return *this;
	}

	bool Vec2u::operator==(const Vec2u& other) const {
		return m_values[0] == other[0] && m_values[1] == other[1];
	}

	bool Vec2u::operator==(const std::array<uint32_t, 2>& other) const {
		return m_values[0] == other[0] && m_values[1] == other[1];
	}

	bool Vec2u::operator==(const uint32_t other[2]) const {
		return m_values[0] == other[0] && m_values[1] == other[1];
	}

	bool Vec2u::operator!=(const Vec2u& other) const {
		return !(*this == other);
	}

	bool Vec2u::operator!=(const std::array<uint32_t, 2>& other) const {
		return !(*this == other);
	}

	bool Vec2u::operator!=(const uint32_t other[2]) const {
		return !(*this == other);
	}

	std::array<float, 2> Vec2u::getValsAsFloat() const {
		return std::array<float, 2>{static_cast<float>(m_values[0]),
									static_cast<float>(m_values[1])};
	}

	std::array<int32_t, 2> Vec2u::getValsAsInt() const {
		return std::array<int32_t, 2>{static_cast<int32_t>(m_values[0]),
									  static_cast<int32_t>(m_values[1])};
	}

	std::array<uint32_t, 2> Vec2u::getValsAsUint() const {
		return std::array<uint32_t, 2>{m_values[0], m_values[1]};
	}




	///////////
	// Vec3f //
	///////////

	Vec3f::Vec3f()
		: m_values{0.0f, 0.0f, 0.0f} {}

	Vec3f::Vec3f(const float vals[3])
		: m_values{vals[0], vals[1], vals[2]} {}

	Vec3f::Vec3f(const std::array<float, 3>& vals)
		: m_values{vals[0], vals[1], vals[2]} {}

	Vec3f::Vec3f(const float x, const float y, const float z)
		: m_values{x, y, z} {}

	void Vec3f::x(const float x) {
		m_values[0] = x;
	}

	void Vec3f::y(const float y) {
		m_values[1] = y;
	}

	void Vec3f::z(const float z) {
		m_values[2] = z;
	}

	float Vec3f::x() const {
		return m_values[0];
	}

	float Vec3f::y() const {
		return m_values[1];
	}

	float Vec3f::z() const {
		return m_values[2];
	}

	void Vec3f::translate(const Vec3& amount) {
		const auto values = amount.getValsAsFloat();
		translate(values);
	}

	void Vec3f::translate(const std::array<float, 3>& amount) {
		translateX(amount[0]);
		translateY(amount[1]);
		translateZ(amount[2]);
	}

	void Vec3f::translate(const float amount[3]) {
		translateX(amount[0]);
		translateY(amount[1]);
		translateZ(amount[2]);
	}

	void Vec3f::translateX(const float amount) {
		m_values[0] += amount;
	}

	void Vec3f::translateY(const float amount) {
		m_values[1] += amount;
	}

	void Vec3f::translateZ(const float amount) {
		m_values[2] += amount;
	}

	void Vec3f::scale(const Vec3& amount) {
		const auto values = amount.getValsAsFloat();
		scale(values);
	}

	void Vec3f::scale(const float factor) {
		scaleX(factor);
		scaleY(factor);
		scaleZ(factor);
	}

	void Vec3f::scale(const float factors[3]) {
		scaleX(factors[0]);
		scaleY(factors[1]);
		scaleZ(factors[2]);
	}

	void Vec3f::scale(const std::array<float, 3>& factors) {
		scaleX(factors[0]);
		scaleY(factors[1]);
		scaleZ(factors[2]);
	}

	void Vec3f::scaleX(const float factor) {
		m_values[0] *= factor;
	}

	void Vec3f::scaleY(const float factor) {
		m_values[1] *= factor;
	}

	void Vec3f::scaleZ(const float factor) {
		m_values[2] *= factor;
	}

	float Vec3f::operator[](const std::size_t idx) const {
		return m_values[idx];
	}

	Vec3f& Vec3f::operator+=(const Vec3& other) {
		translate(other);

		return *this;
	}

	Vec3f& Vec3f::operator+=(const std::array<float, 3>& amount) {
		translate(amount);

		return *this;
	}

	Vec3f& Vec3f::operator+=(const float amount[3]) {
		translate(amount);

		return *this;
	}

	Vec3f& Vec3f::operator-=(const Vec3& other) {
		const auto values = other.getValsAsFloat();

		translate({-values[0], -values[1], -values[2]});

		return *this;
	}

	Vec3f& Vec3f::operator-=(const std::array<float, 3>& amount) {
		translate({-amount[0], -amount[1], -amount[2]});

		return *this;
	}

	Vec3f& Vec3f::operator-=(const float amount[3]) {
		translate({-amount[0], -amount[1], -amount[2]});

		return *this;
	}

	Vec3f& Vec3f::operator*=(const Vec3& other) {
		scale(other);

		return *this;
	}

	Vec3f& Vec3f::operator*=(const float factor) {
		scale(factor);

		return *this;
	}

	Vec3f& Vec3f::operator*=(const std::array<float, 3>& amount) {
		scale(amount);

		return *this;
	}

	Vec3f& Vec3f::operator*=(const float amount[3]) {
		scale(amount);

		return *this;
	}

	bool Vec3f::operator==(const Vec3f& other) const {
		return m_values[0] == other[0] && m_values[1] == other[1] && m_values[2] == other[2];
	}

	bool Vec3f::operator==(const std::array<float, 3>& other) const {
		return m_values[0] == other[0] && m_values[1] == other[1] && m_values[2] == other[2];
	}

	bool Vec3f::operator==(const float other[3]) const {
		return m_values[0] == other[0] && m_values[1] == other[1] && m_values[2] == other[2];
	}

	bool Vec3f::operator!=(const Vec3f& other) const {
		return !(*this == other);
	}

	bool Vec3f::operator!=(const std::array<float, 3>& other) const {
		return !(*this == other);
	}

	bool Vec3f::operator!=(const float other[3]) const {
		return !(*this == other);
	}

	std::array<float, 3> Vec3f::getValsAsFloat() const {
		return std::array<float, 3>{m_values[0], m_values[1], m_values[2]};
	}

	std::array<int32_t, 3> Vec3f::getValsAsInt() const {
		return std::array<int32_t, 3>{static_cast<int32_t>(m_values[0]),
									  static_cast<int32_t>(m_values[1]),
									  static_cast<int32_t>(m_values[2])};
	}

	std::array<uint32_t, 3> Vec3f::getValsAsUint() const {
		return std::array<uint32_t, 3>{static_cast<uint32_t>(m_values[0]),
									   static_cast<uint32_t>(m_values[1]),
									   static_cast<uint32_t>(m_values[2])};
	}




	///////////
	// Vec3i //
	///////////

	Vec3i::Vec3i()
		: m_values{0, 0, 0} {}

	Vec3i::Vec3i(const int32_t vals[3])
		: m_values{vals[0], vals[1], vals[2]} {}

	Vec3i::Vec3i(const std::array<int32_t, 3>& vals)
		: m_values{vals[0], vals[1], vals[2]} {}

	Vec3i::Vec3i(const int32_t x, const int32_t y, const int32_t z)
		: m_values{x, y, z} {}

	void Vec3i::x(const int32_t x) {
		m_values[0] = x;
	}

	void Vec3i::y(const int32_t y) {
		m_values[1] = y;
	}

	void Vec3i::z(const int32_t z) {
		m_values[2] = z;
	}

	int32_t Vec3i::x() const {
		return m_values[0];
	}

	int32_t Vec3i::y() const {
		return m_values[1];
	}

	int32_t Vec3i::z() const {
		return m_values[2];
	}

	void Vec3i::translate(const Vec3& amount) {
		const auto values = amount.getValsAsInt();
		translate(values);
	}

	void Vec3i::translate(const std::array<int32_t, 3>& amount) {
		translateX(amount[0]);
		translateY(amount[1]);
		translateZ(amount[2]);
	}

	void Vec3i::translate(const int32_t amount[3]) {
		translateX(amount[0]);
		translateY(amount[1]);
		translateZ(amount[2]);
	}

	void Vec3i::translateX(const int32_t amount) {
		m_values[0] += amount;
	}

	void Vec3i::translateY(const int32_t amount) {
		m_values[1] += amount;
	}

	void Vec3i::translateZ(const int32_t amount) {
		m_values[2] += amount;
	}

	void Vec3i::scale(const Vec3& amount) {
		const auto values = amount.getValsAsFloat();
		scale(values);
	}

	void Vec3i::scale(const float factor) {
		scaleX(factor);
		scaleY(factor);
		scaleZ(factor);
	}

	void Vec3i::scale(const float factors[3]) {
		scaleX(factors[0]);
		scaleY(factors[1]);
		scaleZ(factors[2]);
	}

	void Vec3i::scale(const std::array<float, 3>& factors) {
		scaleX(factors[0]);
		scaleY(factors[1]);
		scaleZ(factors[2]);
	}

	void Vec3i::scaleX(const float factor) {
		m_values[0] *= factor;
	}

	void Vec3i::scaleY(const float factor) {
		m_values[1] *= factor;
	}

	void Vec3i::scaleZ(const float factor) {
		m_values[2] *= factor;
	}

	int32_t Vec3i::operator[](const std::size_t idx) const {
		return m_values[idx];
	}

	Vec3i& Vec3i::operator+=(const Vec3& other) {
		translate(other);

		return *this;
	}

	Vec3i& Vec3i::operator+=(const std::array<int32_t, 3>& amount) {
		translate(amount);

		return *this;
	}

	Vec3i& Vec3i::operator+=(const int32_t amount[3]) {
		translate(amount);

		return *this;
	}

	Vec3i& Vec3i::operator-=(const Vec3& other) {
		const auto values = other.getValsAsInt();

		translate({-values[0], -values[1], -values[2]});

		return *this;
	}

	Vec3i& Vec3i::operator-=(const std::array<int32_t, 3>& amount) {
		translate({-amount[0], -amount[1], -amount[2]});

		return *this;
	}

	Vec3i& Vec3i::operator-=(const int32_t amount[3]) {
		translate({-amount[0], -amount[1], -amount[2]});

		return *this;
	}

	Vec3i& Vec3i::operator*=(const Vec3& other) {
		scale(other);

		return *this;
	}

	Vec3i& Vec3i::operator*=(const float factor) {
		scale(factor);

		return *this;
	}

	Vec3i& Vec3i::operator*=(const std::array<float, 3>& amount) {
		scale(amount);

		return *this;
	}

	Vec3i& Vec3i::operator*=(const float amount[3]) {
		scale(amount);

		return *this;
	}

	bool Vec3i::operator==(const Vec3i& other) const {
		return m_values[0] == other[0] && m_values[1] == other[1] && m_values[2] == other[2];
	}

	bool Vec3i::operator==(const std::array<int32_t, 3>& other) const {
		return m_values[0] == other[0] && m_values[1] == other[1] && m_values[2] == other[2];
	}

	bool Vec3i::operator==(const int32_t other[3]) const {
		return m_values[0] == other[0] && m_values[1] == other[1] && m_values[2] == other[2];
	}

	bool Vec3i::operator!=(const Vec3i& other) const {
		return !(*this == other);
	}

	bool Vec3i::operator!=(const std::array<int32_t, 3>& other) const {
		return !(*this == other);
	}

	bool Vec3i::operator!=(const int32_t other[3]) const {
		return !(*this == other);
	}

	std::array<float, 3> Vec3i::getValsAsFloat() const {
		return std::array<float, 3>{static_cast<float>(m_values[0]),
									static_cast<float>(m_values[1]),
									static_cast<float>(m_values[2])};
	}

	std::array<int32_t, 3> Vec3i::getValsAsInt() const {
		return std::array<int32_t, 3>{m_values[0], m_values[1], m_values[2]};
	}

	std::array<uint32_t, 3> Vec3i::getValsAsUint() const {
		return std::array<uint32_t, 3>{static_cast<uint32_t>(m_values[0]),
									   static_cast<uint32_t>(m_values[1]),
									   static_cast<uint32_t>(m_values[2])};
	}

}