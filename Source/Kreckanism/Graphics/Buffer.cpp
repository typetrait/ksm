#include "Kreckanism/Graphics/Buffer.h"

#include "glad/glad.h"

namespace Ksm
{
	Buffer::Buffer()
	{
		glGenBuffers(1, &id);
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &id);
	}
}