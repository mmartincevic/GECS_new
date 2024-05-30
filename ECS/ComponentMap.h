#pragma once

#include <iostream>
#include <unordered_map>

namespace gecs {
	class ComponentMap {

		public:
			ComponentMap() {}
			~ComponentMap() {}

			// Method to check if an outer element exists
			bool outerElementExists(size_t outerKey) const {
				return m_MapComp.find(outerKey) != m_MapComp.end();
			}

			// Method to check if an inner element exists for a specific outer key
			bool innerElementExists(size_t outerKey, size_t innerKey) const {
				auto outerIt = m_MapComp.find(outerKey);
				if (outerIt != m_MapComp.end()) {
					const auto& innerMap = outerIt->second;
					return innerMap.find(innerKey) != innerMap.end();
				}
				return false;
			}

			// Method to add an element to the outer map
			[[deprecated("Use appendElement() instead.")]]
			void addElement(size_t outerKey) {
				m_MapComp[outerKey] = std::unordered_map<size_t, size_t>();
			}

			void appendElement(size_t outerKey, size_t innerKey, const size_t& value) {
				//m_MapComp[outerKey][innerKey] = value;
				if (!outerElementExists(outerKey)) {
					// If outer key doesn't exist, create a new inner map
					m_MapComp[outerKey] = std::unordered_map<size_t, size_t>();
				}
				// Add the element to the inner map
				m_MapComp[outerKey][innerKey] = value;
			}

			std::vector<std::pair<size_t, size_t>> getInnerElements(size_t outerKey) const {
				std::vector<std::pair<size_t, size_t>> result;
				auto it = m_MapComp.find(outerKey);
				if (it != m_MapComp.end()) {
					const auto& innerMap = it->second;
					for (const auto& innerPair : innerMap) {
						result.push_back(innerPair);
					}
				}
				return result;
			}

			// Method to print the entire map
			void printMap() {
				for (const auto& outerPair : m_MapComp) {
					size_t outerKey = outerPair.first;
					const auto& innerMap = outerPair.second;
					for (const auto& innerPair : innerMap) {
						size_t innerKey = innerPair.first;
						size_t value = innerPair.second;
						std::cout << "Outer key: " << outerKey << ", Inner key: " << innerKey << ", Value: " << value << std::endl;
					}
				}
			}
		private:
			std::unordered_map<size_t, std::unordered_map<size_t, std::size_t>> m_MapComp;
	};
};