#pragma once
#include <C:\Libs\json\single_include\nlohmann\json.hpp>

class Ijsonio
{
public:
	virtual void fromJson(nlohmann::json json) = 0; //извлечение из
	virtual nlohmann::json toJson() = 0; //сохранение в
};
