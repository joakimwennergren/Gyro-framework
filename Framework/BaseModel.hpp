#pragma once

class BaseModel
{
public:
	struct Data {
		tinyobj::attrib_t attributes;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
	};
protected:
private:

};