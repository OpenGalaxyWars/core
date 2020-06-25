#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <vector>

namespace ogw {

typedef std::string gobj_t;

class GameObject {
public:
	GameObject(gobj_t id): m_id(id) {}
	GameObject(gobj_t id, const std::wstring &name): m_id(id), m_name(name) {}
	virtual ~GameObject() {}

	void setName(const std::wstring &name) { m_name = name; }
	const gobj_t &getId() const { return m_id; }
private:
	std::wstring m_name;
	gobj_t m_id = 0;
};

class StellarObject: public GameObject {
public:
	StellarObject(gobj_t id, const std::wstring &name) : GameObject(id, name) {}
	virtual ~StellarObject() {}
private:
	std::vector<std::unique_ptr<StellarObject>> m_childs;

	double pos_x = 0.0;
	double pos_y = 0.0;
};
}