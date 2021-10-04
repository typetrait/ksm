#pragma once

#include "Kreckanism/Graphics/Buffer.h"

namespace Ksm
{
	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(float* vertices, size_t size);
		void Bind() const override;
		void Unbind() const override;
	private:
		size_t size;
	};
}