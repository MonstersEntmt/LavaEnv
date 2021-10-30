#include "LavaEnv/Object.h"
#include "LavaEnv/Class.h"

namespace LavaEnv {
	LAVA_CALL_CONV void Object::destroy() {
		m_Class.destroy(this);
	}
} // namespace LavaEnv
