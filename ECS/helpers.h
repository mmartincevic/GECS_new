#pragma once
#ifndef GECS_HELPERS_H_
#define GECS_HELPERS_H_

#include <iostream>

namespace gecs {

	template<typename Object>
	std::string classNameOf() {
		std::string name = typeid(Object).name();
		size_t spacePosition = name.find_first_of(" ");
		if (spacePosition != std::string::npos) {
			return name.substr(spacePosition + 1, name.length());
		}
		return name;
	};

	template<typename Object>
	std::size_t classHash() {
		const std::string name = classNameOf<Object>();
		return std::hash<std::string>{}(name);
	};

};

#endif // GECS_HELPERS_H_