#pragma once

namespace Ksm
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		void Bind() const;
		void Unbind() const;
	private:
		unsigned int id;
	};
}