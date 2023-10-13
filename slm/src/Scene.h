#pragma once

namespace slm {

	template<class T>
	class Scene {
		Scene() = default;
		~Scene() = default;

		template<class U>
		void translateAll(U amount) {
			for (auto object : m_objects) {
				object.translate(amount);
			}
		}
		void rotateAll(int degreesCounterClockwise) {
			for (auto object : m_objects) {
				object.rotate(degreesCounterClockwise);
			}
		}
		void scaleAll(float factor) {
			for (auto object : m_objects) {
				object.scale(factor);
			}
		}

		void addObject(T object) {
			m_objects.push_back(object);
		}

	private:
		std::vector<T> m_objects{};
	};

}