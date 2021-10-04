#pragma once

namespace Ksm
{
	class Buffer
	{
	public:
		Buffer();
		~Buffer();
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	protected:
		unsigned int id;
	};
}