#include "LavaEnv/Method.h"
#include "LavaEnv/Class.h"

#include <utility>

namespace LavaEnv {
	Method::Method(Class& clazz, RegisterMethod&& method)
	    : m_Class(clazz), m_Flags(method.m_Flags), m_Id(std::move(method.m_Id)), m_FunctionPtr(method.m_FunctionPtr) {
		std::string_view view = m_Id;
		auto nameEnd          = view.find_first_of(';');
		m_Name                = view.substr(0, nameEnd);

		auto parametersBegin            = view.find_first_of('(', nameEnd + 1);
		auto parametersEnd              = view.find_first_of(')', parametersBegin + 1);
		std::string_view parameterTypes = view.substr(parametersBegin + 1, parametersEnd - 1 - parametersBegin);
		while (!parameterTypes.empty()) {
			auto parameterEnd = parameterTypes.find_first_of(',');
			m_ParameterTypes.push_back(parseType(m_Class.getRegistry(), parameterTypes.substr(0, parameterEnd)));
			if (parameterEnd != std::string_view::npos)
				parameterTypes = parameterTypes.substr(parameterEnd + 1);
			else
				parameterTypes = {};
		}

		m_ReturnType = parseType(m_Class.getRegistry(), view.substr(parametersEnd + 1));
	}
} // namespace LavaEnv
