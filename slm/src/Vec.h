#pragma once

namespace slm {

	class AxisAlignedBox2u;

	/////////////////
	// BitLocation //
	/////////////////

	class BitLocation {
	public:
		struct BIT_LOCATIONS {
			enum : unsigned char { NONE = 0b0000, ABOVE = 0b1000, BELOW = 0b0100, RIGHT = 0b0010, LEFT = 0b0001 };
		};
		struct BIT_LOCATIONS_INVERTED {
			enum : unsigned char { NONE = 0b1111, ABOVE = 0b0111, BELOW = 0b1011, RIGHT = 0b1101, LEFT = 0b1110 };
		};

		BitLocation();
		BitLocation(unsigned char location);
		BitLocation(bool above, bool below, bool left, bool right);

		void setLocation(unsigned char location);
		void setAbove(bool above);
		void setBelow(bool below);
		void setLeft(bool left);
		void setRight(bool right);

		unsigned char getLocation() const;
		bool getAbove() const;
		bool getBelow() const;
		bool getLeft() const;
		bool getRight() const;
		bool getInside() const;
		bool getOutside() const;
		bool getVertical() const;
		bool getHorizontal() const;

		unsigned char compareLocations(const BitLocation& other) const;

	protected:
		unsigned char m_location : 4 = 0b0000;
	};




	/////////
	// Vec //
	/////////

	class Vec {};




	//////////
	// Vec2 //
	//////////

	class Vec2 : public Vec {
	public:
		static std::size_t getSize();

		virtual std::array<float, 2> getValsAsFloat() const	  = 0;
		virtual std::array<int32_t, 2> getValsAsInt() const	  = 0;
		virtual std::array<uint32_t, 2> getValsAsUint() const = 0;

	protected:
		std::array<float, 2> rotationHelper(const int32_t degreesCounterClockwise) const;
	};




	//////////
	// Vec3 //
	//////////

	class Vec3 : public Vec {
	public:
		static std::size_t getSize();

		virtual std::array<float, 3> getValsAsFloat() const	  = 0;
		virtual std::array<int32_t, 3> getValsAsInt() const	  = 0;
		virtual std::array<uint32_t, 3> getValsAsUint() const = 0;

	protected:
	};




	///////////
	// Vec2f //
	///////////

	class Vec2f : public Vec2 {
	public:
		Vec2f();
		Vec2f(const float vals[2]);
		Vec2f(const std::array<float, 2>& vals);
		Vec2f(const float x, const float y);

		void x(const float x);
		void y(const float y);
		float x() const;
		float y() const;

		BitLocation insideBox(const AxisAlignedBox2u& box) const;

		void translate(const Vec2& amount);
		void translate(const std::array<float, 2>& amount);
		void translate(const float amount[2]);
		void translateX(const float amount);
		void translateY(const float amount);
		void rotate(const int32_t degreesCounterClockwise);
		void scale(const Vec2& amount);
		void scale(const float factor);
		void scale(const float factors[2]);
		void scale(const std::array<float, 2>& factors);
		void scaleX(const float factor);
		void scaleY(const float factor);

		float operator[](const std::size_t idx) const;
		Vec2f& operator+=(const Vec2& other);
		Vec2f& operator+=(const std::array<float, 2>& amount);
		Vec2f& operator+=(const float amount[2]);
		Vec2f& operator-=(const Vec2& other);
		Vec2f& operator-=(const std::array<float, 2>& amount);
		Vec2f& operator-=(const float amount[2]);
		Vec2f& operator*=(const Vec2& other);
		Vec2f& operator*=(const float factor);
		Vec2f& operator*=(const std::array<float, 2>& amount);
		Vec2f& operator*=(const float amount[2]);
		bool operator==(const Vec2f& other) const;
		bool operator==(const std::array<float, 2>& other) const;
		bool operator==(const float other[2]) const;
		bool operator!=(const Vec2f& other) const;
		bool operator!=(const std::array<float, 2>& other) const;
		bool operator!=(const float other[2]) const;

		std::array<float, 2> getValsAsFloat() const override;
		std::array<int32_t, 2> getValsAsInt() const override;
		std::array<uint32_t, 2> getValsAsUint() const override;

	protected:
		float m_values[2];
	};




	///////////
	// Vec2i //
	///////////

	class Vec2i : public Vec2 {
	public:
		Vec2i();
		Vec2i(const int32_t vals[2]);
		Vec2i(const std::array<int32_t, 2>& vals);
		Vec2i(const int32_t x, const int32_t y);

		void x(const int32_t x);
		void y(const int32_t y);
		int32_t x() const;
		int32_t y() const;

		void translate(const Vec2& amount);
		void translate(const std::array<int32_t, 2>& amount);
		void translate(const int32_t amount[2]);
		void translateX(const int32_t amount);
		void translateY(const int32_t amount);
		void rotate(const int32_t degreesCounterClockwise);
		void scale(const Vec2& amount);
		void scale(const float factor);
		void scale(const float factors[2]);
		void scale(const std::array<float, 2>& factors);
		void scaleX(const float factor);
		void scaleY(const float factor);

		int32_t operator[](const std::size_t idx) const;
		Vec2i& operator+=(const Vec2& other);
		Vec2i& operator+=(const std::array<int32_t, 2>& amount);
		Vec2i& operator+=(const int32_t amount[2]);
		Vec2i& operator-=(const Vec2& other);
		Vec2i& operator-=(const std::array<int32_t, 2>& amount);
		Vec2i& operator-=(const int32_t amount[2]);
		Vec2i& operator*=(const Vec2& other);
		Vec2i& operator*=(const float factor);
		Vec2i& operator*=(const std::array<float, 2>& amount);
		Vec2i& operator*=(const float amount[2]);
		bool operator==(const Vec2i& other) const;
		bool operator==(const std::array<int32_t, 2>& other) const;
		bool operator==(const int32_t other[2]) const;
		bool operator!=(const Vec2i& other) const;
		bool operator!=(const std::array<int32_t, 2>& other) const;
		bool operator!=(const int32_t other[2]) const;

		std::array<float, 2> getValsAsFloat() const override;
		std::array<int32_t, 2> getValsAsInt() const override;
		std::array<uint32_t, 2> getValsAsUint() const override;

	protected:
		int32_t m_values[2];
	};




	///////////
	// Vec2u //
	///////////

	class Vec2u : public Vec2 {
	public:
		Vec2u();
		Vec2u(const uint32_t vals[2]);
		Vec2u(const std::array<uint32_t, 2>& vals);
		Vec2u(const uint32_t x, const uint32_t y);

		void x(const uint32_t x);
		void y(const uint32_t y);
		uint32_t x() const;
		uint32_t y() const;

		void translate(const Vec2& amount);
		void translate(const std::array<uint32_t, 2>& amount);
		void translate(const uint32_t amount[2]);
		void translateX(const uint32_t amount);
		void translateY(const uint32_t amount);
		void rotate(const int32_t degreesCounterClockwise);
		void scale(const Vec2& amount);
		void scale(const float factor);
		void scale(const float factors[2]);
		void scale(const std::array<float, 2>& factors);
		void scaleX(const float factor);
		void scaleY(const float factor);

		uint32_t operator[](const std::size_t idx) const;
		Vec2u& operator+=(const Vec2& other);
		Vec2u& operator+=(const std::array<uint32_t, 2>& amount);
		Vec2u& operator+=(const uint32_t amount[2]);
		Vec2u& operator-=(const Vec2& other);
		Vec2u& operator-=(const std::array<uint32_t, 2>& amount);
		Vec2u& operator-=(const uint32_t amount[2]);
		Vec2u& operator*=(const Vec2& other);
		Vec2u& operator*=(const float factor);
		Vec2u& operator*=(const std::array<float, 2>& amount);
		Vec2u& operator*=(const float amount[2]);
		bool operator==(const Vec2u& other) const;
		bool operator==(const std::array<uint32_t, 2>& other) const;
		bool operator==(const uint32_t other[2]) const;
		bool operator!=(const Vec2u& other) const;
		bool operator!=(const std::array<uint32_t, 2>& other) const;
		bool operator!=(const uint32_t other[2]) const;

		std::array<float, 2> getValsAsFloat() const override;
		std::array<int32_t, 2> getValsAsInt() const override;
		std::array<uint32_t, 2> getValsAsUint() const override;

	protected:
		uint32_t m_values[2];
	};




	///////////
	// Vec3f //
	///////////

	class Vec3f : public Vec3 {
	public:
		Vec3f();
		Vec3f(const float vals[3]);
		Vec3f(const std::array<float, 3>& vals);
		Vec3f(const float x, const float y, const float z);

		void x(const float x);
		void y(const float y);
		void z(const float z);
		float x() const;
		float y() const;
		float z() const;

		void translate(const Vec3& amount);
		void translate(const std::array<float, 3>& amount);
		void translate(const float amount[3]);
		void translateX(const float amount);
		void translateY(const float amount);
		void translateZ(const float amount);
		void scale(const Vec3& amount);
		void scale(const float factor);
		void scale(const float factors[3]);
		void scale(const std::array<float, 3>& factors);
		void scaleX(const float factor);
		void scaleY(const float factor);
		void scaleZ(const float factor);

		float operator[](const std::size_t idx) const;
		Vec3f& operator+=(const Vec3& other);
		Vec3f& operator+=(const std::array<float, 3>& amount);
		Vec3f& operator+=(const float amount[3]);
		Vec3f& operator-=(const Vec3& other);
		Vec3f& operator-=(const std::array<float, 3>& amount);
		Vec3f& operator-=(const float amount[3]);
		Vec3f& operator*=(const Vec3& other);
		Vec3f& operator*=(const float factor);
		Vec3f& operator*=(const std::array<float, 3>& amount);
		Vec3f& operator*=(const float amount[3]);
		bool operator==(const Vec3f& other) const;
		bool operator==(const std::array<float, 3>& other) const;
		bool operator==(const float other[3]) const;
		bool operator!=(const Vec3f& other) const;
		bool operator!=(const std::array<float, 3>& other) const;
		bool operator!=(const float other[3]) const;

		std::array<float, 3> getValsAsFloat() const override;
		std::array<int32_t, 3> getValsAsInt() const override;
		std::array<uint32_t, 3> getValsAsUint() const override;

	protected:
		float m_values[3];
	};




	///////////
	// Vec3i //
	///////////

	class Vec3i : public Vec3 {
	public:
		Vec3i();
		Vec3i(const int32_t vals[3]);
		Vec3i(const std::array<int32_t, 3>& vals);
		Vec3i(const int32_t x, const int32_t y, const int32_t z);

		void x(const int32_t x);
		void y(const int32_t y);
		void z(const int32_t z);
		int32_t x() const;
		int32_t y() const;
		int32_t z() const;

		void translate(const Vec3& amount);
		void translate(const std::array<int32_t, 3>& amount);
		void translate(const int32_t amount[3]);
		void translateX(const int32_t amount);
		void translateY(const int32_t amount);
		void translateZ(const int32_t amount);
		void scale(const Vec3& amount);
		void scale(const float factor);
		void scale(const float factors[3]);
		void scale(const std::array<float, 3>& factors);
		void scaleX(const float factor);
		void scaleY(const float factor);
		void scaleZ(const float factor);

		int32_t operator[](const std::size_t idx) const;
		Vec3i& operator+=(const Vec3& other);
		Vec3i& operator+=(const std::array<int32_t, 3>& amount);
		Vec3i& operator+=(const int32_t amount[3]);
		Vec3i& operator-=(const Vec3& other);
		Vec3i& operator-=(const std::array<int32_t, 3>& amount);
		Vec3i& operator-=(const int32_t amount[3]);
		Vec3i& operator*=(const Vec3& other);
		Vec3i& operator*=(const float factor);
		Vec3i& operator*=(const std::array<float, 3>& amount);
		Vec3i& operator*=(const float amount[3]);
		bool operator==(const Vec3i& other) const;
		bool operator==(const std::array<int32_t, 3>& other) const;
		bool operator==(const int32_t other[3]) const;
		bool operator!=(const Vec3i& other) const;
		bool operator!=(const std::array<int32_t, 3>& other) const;
		bool operator!=(const int32_t other[3]) const;

		std::array<float, 3> getValsAsFloat() const override;
		std::array<int32_t, 3> getValsAsInt() const override;
		std::array<uint32_t, 3> getValsAsUint() const override;

	protected:
		int32_t m_values[3];
	};




	///////////
	// Vec4f //
	///////////

	class Vec4f {
	public:
		Vec4f();
		Vec4f(const float vals[4]);
		Vec4f(const std::array<float, 4>& vals);
		Vec4f(const float x, const float y, const float z, const float w);

		void x(const float x);
		void y(const float y);
		void z(const float z);
		void w(const float w);
		float x() const;
		float y() const;
		float z() const;
		float w() const;

		float operator[](const std::size_t idx) const;

	protected:
		float m_values[4];
	};
}