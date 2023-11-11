#pragma once

namespace slm {

	class Vec {};

	class Vec2 : public Vec {
	public:
		static std::size_t getSize();

		virtual std::array<float, 2> getValsAsFloat() const = 0;
		virtual std::array<int32_t, 2> getValsAsInt() const = 0;
	};


	class Vec2f : public Vec2 {
	public:
		Vec2f();
		Vec2f(float vals[2]);
		Vec2f(const std::array<float, 2>& vals);
		Vec2f(float x, float y);

		void x(float x);
		void y(float y);
		float x() const;
		float y() const;

		void translate(const Vec2& amount);
		void translate(const std::array<float, 2>& amount);
		void translate(const float amount[2]);
		void translateX(float amount);
		void translateY(float amount);
		void rotate(int32_t degreesCounterClockwise);
		void scale(const Vec2& amount);
		void scale(float factor);
		void scale(float factors[2]);
		void scale(std::array<float, 2> factors);
		void scaleX(float factor);
		void scaleY(float factor);

		float operator[](std::size_t idx) const;
		Vec2f& operator+=(const Vec2& other);
		Vec2f& operator+=(const std::array<float, 2>& amount);
		Vec2f& operator+=(const float amount[2]);
		Vec2f& operator+=(const Vec2& other);
		Vec2f& operator-=(const Vec2& other);
		Vec2f& operator-=(const std::array<float, 2>& amount);
		Vec2f& operator-=(const float amount[2]);
		Vec2f& operator*=(const Vec2& other);
		Vec2f& operator*=(const float factor);
		bool operator==(const Vec2& other) const;

		std::array<float, 2> getValsAsFloat() const override;
		std::array<int32_t, 2> getValsAsInt() const override;

	protected:
		float m_values[2];
	};


	class Vec2i : public Vec2 {
	public:
		Vec2i();
		Vec2i(int32_t vals[2]);
		Vec2i(const std::array<int32_t, 2>& vals);
		Vec2i(int32_t x, int32_t y);

		void x(int32_t x);
		void y(int32_t y);
		int32_t x() const;
		int32_t y() const;

		void translate(const Vec2& amount);
		void translate(const std::array<int32_t, 2>& amount);
		void translate(const int32_t amount[2]);
		void translateX(int32_t amount);
		void translateY(int32_t amount);
		void rotate(int32_t degreesCounterClockwise);
		void scale(const Vec2& amount);
		void scale(float factor);
		void scale(float factors[2]);
		void scale(std::array<float, 2> factors);
		void scaleX(float factor);
		void scaleY(float factor);

		int32_t operator[](std::size_t idx) const;
		Vec2i& operator+=(const Vec2& other);
		Vec2i& operator+=(const std::array<int32_t, 2>& amount);
		Vec2i& operator+=(const int32_t amount[2]);
		Vec2i& operator-=(const Vec2& other);
		Vec2i& operator-=(const std::array<int32_t, 2>& amount);
		Vec2i& operator-=(const int32_t amount[2]);
		Vec2i& operator*=(const Vec2& other);
		Vec2i& operator*=(const float factor);
		bool operator==(const Vec2& other) const;

		std::array<float, 2> getValsAsFloat() const override;
		std::array<int32_t, 2> getValsAsInt() const override;

	protected:
		int32_t m_values[2];
	};
}