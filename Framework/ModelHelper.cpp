#define TINYOBJLOADER_IMPLEMENTATION
#include "ModelHelper.hpp"

/// <summary>
/// Loads a models data into a BaseModel::Data struct
/// </summary>
/// <param name="path"></param>
/// <returns>BaseModel::Data</returns>
BaseModel::Data ModelHelper::loadModel(const char* path) {

	spdlog::info("Trying to load model with path = {0}", path);

	BaseModel::Data obj_data = {};
	std::string warn, err;

	if (!tinyobj::LoadObj(
		&obj_data.attributes, 
		&obj_data.shapes,
		&obj_data.materials, 
		&warn, 
		&err, 
		path)
	) {

		spdlog::critical(
			"Couldn\'t load model with path = {0}. Error: {1}. Warning: {2}.", path, err, warn
		);

		throw "Critical Error.";
	}

	return obj_data;

	spdlog::info("Successfully loaded model!");
}