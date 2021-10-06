#pragma once

#include <vector>

#include "Kreckanism/Graphics/VertexAttribute.h"

namespace Ksm
{
	class BufferLayout
	{
	public:
		BufferLayout(std::initializer_list<VertexAttribute> attributes);
		const std::vector<VertexAttribute>& GetAttributes() const;
	private:
		std::vector<VertexAttribute> attributes;
	};
}