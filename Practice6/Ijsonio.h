#pragma once
#include <C:\Libs\json\single_include\nlohmann\json.hpp>

class Ijsonio
{
public:
	virtual void fromJson(nlohmann::json json) = 0; //���������� ��
	virtual nlohmann::json toJson() = 0; //���������� �
};
