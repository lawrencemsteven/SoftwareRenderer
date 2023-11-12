#pragma once

namespace slm {

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

		virtual std::array<float, 2> getValsAsFloat() const = 0;
		virtual std::array<int32_t, 2> getValsAsInt() const = 0;

	protected:
		std::array<float, 2> rotationHelper(const int32_t degreesCounterClockwise) const;
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

	protected:
		int32_t m_values[2];
	};
}