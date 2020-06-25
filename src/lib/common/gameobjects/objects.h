#pragma once

#include <cstdint>
#include <string>

namespace ogw {
class GameObject {
public:
	GameObject(uint64_t id): m_id(id) {}
	virtual ~GameObject() {}
private:
	std::wstring m_name;
	uint64_t m_id = 0;
};

}