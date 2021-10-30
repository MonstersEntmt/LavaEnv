#include <LavaEnv.h>

#include <iostream>
#include <stdexcept>

LAVA_CALL_CONV void testCtor(LavaEnv::Object* object) {
	std::cout << "test ctor" << std::endl;
	LavaEnv::Class& clazz = object->getClass();
	object->set<std::int32_t>("a;I4", clazz.getStatic<std::int32_t>("A;I4"));
}

LAVA_CALL_CONV void testDtor(LavaEnv::Object* object) {
	std::cout << "test dtor" << std::endl;
}

LAVA_CALL_CONV std::int32_t add(LavaEnv::Object* object, std::int32_t b) {
	return object->get<std::int32_t>("a;I4") + b;
}

LAVA_CALL_CONV std::int32_t Add(std::int32_t a, std::int32_t b) {
	return a + b;
}

LAVA_CALL_CONV int lavaMain(int argc, char** argv) {
	try {
		LavaEnv::ClassRegistry registry;
		LavaEnv::Class* testClass;
		{
			LavaEnv::RegisterClass registerTestClass;
			registerTestClass.m_Id = "Test";

			LavaEnv::RegisterField registerAField;
			registerAField.m_Id = "a;I4";
			registerTestClass.m_Fields.push_back(registerAField);

			LavaEnv::RegisterField registerStaticAField;
			registerStaticAField.m_Flags = LavaEnv::EFieldFlag::Static;
			registerStaticAField.m_Id    = "A;I4";
			registerTestClass.m_Fields.push_back(registerStaticAField);

			LavaEnv::RegisterMethod registerCtorMethod;
			registerCtorMethod.m_Id          = "_ctor;(LTest;)V";
			registerCtorMethod.m_FunctionPtr = &testCtor;
			registerTestClass.m_Methods.push_back(registerCtorMethod);

			LavaEnv::RegisterMethod registerDtorMethod;
			registerDtorMethod.m_Id          = "_dtor;(LTest;)V";
			registerDtorMethod.m_FunctionPtr = &testDtor;
			registerTestClass.m_Methods.push_back(registerDtorMethod);

			LavaEnv::RegisterMethod registerAddMethod;
			registerAddMethod.m_Id          = "add;(I4)I4";
			registerAddMethod.m_FunctionPtr = &add;
			registerTestClass.m_Methods.push_back(registerAddMethod);

			LavaEnv::RegisterMethod registerStaticAddMethod;
			registerStaticAddMethod.m_Flags       = LavaEnv::EMethodFlag::Static;
			registerStaticAddMethod.m_Id          = "Add;(I4,I4)I4";
			registerStaticAddMethod.m_FunctionPtr = &Add;
			registerTestClass.m_Methods.push_back(registerStaticAddMethod);

			testClass = registry.registerClass(std::move(registerTestClass));
		}
		if (!testClass)
			throw std::runtime_error("Failed to register class!");

		testClass->setStatic<std::int32_t>("A;I4", 10);
		LavaEnv::Object* object = testClass->instantiate();
		// object->set<std::int32_t>("a", 10);
		std::int32_t result = object->invoke<std::int32_t>("add;(I4)I4", 5);
		std::cout << result << std::endl;
		object->destroy();

		result = testClass->invokeStatic<std::int32_t, std::int32_t, std::int32_t>("Add;(I4,I4)I4", 10, 5);
		std::cout << result << std::endl;
		return EXIT_SUCCESS;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}

int main(int argc, char** argv) {
	return lavaMain(argc, argv);
}
