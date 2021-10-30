#include <LavaEnv.h>

#include <iostream>
#include <stdexcept>

LAVA_CALL_CONV void testSctor(LavaEnv::Class* clazz) {
	std::cout << "test sctor" << std::endl;
	clazz->setStatic<std::int32_t>("A;I4", 10);
}

LAVA_CALL_CONV void testSdtor(LavaEnv::Class* clazz) {
	std::cout << "test sdtor" << std::endl;
}

LAVA_CALL_CONV void testCtor(LavaEnv::Object* object) {
	std::cout << "test ctor" << std::endl;
	LavaEnv::Class& clazz = object->getClass();
	object->set<std::int32_t>("a;I4", clazz.getStatic<std::int32_t>("A;I4"));
}

LAVA_CALL_CONV void testDtor(LavaEnv::Object* object) {
	std::cout << "test dtor" << std::endl;
}

LAVA_CALL_CONV std::int32_t add(LavaEnv::Object* object, std::int32_t b) {
	std::cout << "test add" << std::endl;
	return object->get<std::int32_t>("a;I4") + b;
}

LAVA_CALL_CONV std::int32_t Add(std::int32_t a, std::int32_t b) {
	std::cout << "test Add" << std::endl;
	return a + b;
}

LAVA_CALL_CONV int lavaMain(int argc, char** argv) {
	try {
		LavaEnv::ClassRegistry registry;
		LavaEnv::Class* testClass;
		{
			using namespace LavaEnv;
			testClass = registry.registerClass(RegisterClass {
			    EClassFlag::None,
			    "Test",
			    {},
			    {
			        RegisterMethod {
			            EMethodFlag::Static,
			            "_sctor;()V",
			            &testSctor,
			        },
			        RegisterMethod {
			            EMethodFlag::Static,
			            "_sdtor;()V",
			            &testSdtor,
			        },
			        RegisterMethod {
			            EMethodFlag::Static,
			            "Add;(I4,I4)I4",
			            &Add,
			        },
			        RegisterMethod {
			            EMethodFlag::None,
			            "_ctor;(LTest;)V",
			            &testCtor,
			        },
			        RegisterMethod {
			            EMethodFlag::None,
			            "_dtor;(LTest;)V",
			            &testDtor,
			        },
			        RegisterMethod {
			            EMethodFlag::None,
			            "add;(I4)I4",
			            &add,
			        },
			    },
			    {
			        RegisterField {
			            EFieldFlag::Static,
			            "A;I4",
			        },
			        RegisterField {
			            EFieldFlag::None,
			            "a;I4",
			        },
			    },
			});
		}
		if (!testClass)
			throw std::runtime_error("Failed to register class!");

		LavaEnv::Object* object = testClass->instantiate();
		// object->set<std::int32_t>("a", 10);
		std::int32_t result = object->invoke<std::int32_t>("add;(I4)I4", 5);
		object->destroy();

		result = testClass->invokeStatic<std::int32_t, std::int32_t, std::int32_t>("Add;(I4,I4)I4", 10, 5);
		return result;
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}

int main(int argc, char** argv) {
	return lavaMain(argc, argv);
}
