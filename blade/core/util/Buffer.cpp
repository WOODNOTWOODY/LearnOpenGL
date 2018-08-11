#include "CoreStd.h"
#include "Buffer.h"
#include <cassert>

BLADE_NAMESPACE_BEGIN

Buffer::Buffer(): 
m_data(NULL),
m_size(0),
m_offset(0)
{
}

Buffer::Buffer(const Buffer& buff):
m_data(NULL),
m_size(buff.m_size),
m_offset(0)
{
	if(m_size)
	{
		m_data = (Byte*)BLADE_MALLOC(sizeof(Byte)*m_size);
		memcpy(m_data, buff.m_data, m_size);
	}
}

Buffer::Buffer(Buffer&& buff):
m_data(buff.m_data),
m_size(buff.m_size),
m_offset(0)
{
	buff.m_size = 0;
	buff.m_offset = 0;
	buff.m_data = NULL;
}

Buffer::Buffer(const std::string& str) :
m_data(NULL),
m_offset(0)
{
	m_size = (uint32)str.size() + 1;

	if(m_size)
	{
		m_data = (Byte*)BLADE_MALLOC(sizeof(Byte)*m_size);
		memcpy(m_data, str.c_str(), m_size);
	}
}

Buffer::~Buffer()
{
	BLADE_SAFE_FREE(m_data);
}

Buffer& Buffer::operator = (const Buffer& buff)
{
	if(buff.m_size)
	{
		if (m_size != buff.m_size)
		{
			BLADE_SAFE_FREE(m_data);
			m_data = (Byte*)BLADE_MALLOC(sizeof(Byte)*buff.m_size);
			m_size = buff.m_size;
		}
		memcpy(m_data, buff.m_data, m_size);
		m_offset = 0;
	}
	else
	{
		clear();
	}
	return *this;
}

Buffer& Buffer::operator = (Buffer&& buff)
{
	BLADE_SAFE_FREE(m_data);
	m_data = buff.m_data;
	m_size = buff.m_size;
	m_offset = 0;

	buff.m_data = NULL;
	buff.m_size = 0;
	buff.m_offset = 0;
	return *this;
}

void Buffer::allocate(uint32 size)
{
	//KART_ASSERTS(size > 0, "Buffer allocated 0 size.");
	if (m_size == size)
	{
		return;
	}

	BLADE_SAFE_FREE(m_data);

	if (size == 0)
	{
		m_size = 0;
	}
	else
	{
		m_data = (Byte*)BLADE_MALLOC(sizeof(Byte)*size);
		m_size = size;
	}
}

void Buffer::clear()
{

	BLADE_SAFE_FREE(m_data);
	m_size = 0;
	m_offset = 0;
}

void Buffer::attach(uint32 size, void* data)
{
	BLADE_SAFE_FREE(m_data);
	m_data = (Byte*)data;
	m_size = size;
	m_offset = 0;
}

Byte* Buffer::detach()
{
	Byte* data = m_data;
	m_data = NULL;
	m_size = 0;
	m_offset = 0;
	return data;
}

void Buffer::append(const Buffer& buff)
{
	if(buff.size())
	{
		uint32 size = m_size + buff.size();

		Byte* data = (Byte*)BLADE_MALLOC(sizeof(Byte)*size);

		if(m_data)
		{
			memcpy(data, m_data, m_size);
			BLADE_FREE(m_data);
		}

		memcpy(data + m_size, buff.data(), buff.size());

		m_data = data;
		m_size = size;
	}
}

void Buffer::seek(int offset, BufferSeek bs) const
{
	switch (bs)
	{
	case BS_SET:	m_offset = offset;				break;
	case BS_CUR:	m_offset = m_offset + offset;	break;
	case BS_END:	m_offset = m_size - offset;		break;
	default:	assert(false);
	}

	assert(m_offset <= m_size);
}

void Buffer::seekFit(int offset, BufferSeek bs)
{
	switch (bs)
	{
	case BS_SET:
		{
			growToFit(offset);
			m_offset = offset;
		} break;
	case BS_CUR:
		{
			growToFit(m_offset + offset);
			m_offset = m_offset + offset;
		} break;
	case BS_END:
		{
			growToFit(m_size - offset);
			m_offset = m_size - offset;
		} break;
	default:	assert(false);
	}
}

char* Buffer::readLine()
{
	if (m_offset < m_size)
	{
		char* buf = (char*)m_data + m_offset;
		char* p = buf;
		bool hasMore = false;
		for (; m_offset < m_size; m_offset++, p++)
		{
			if (*p == '\n' || *p == 0)
			{
				hasMore = true;
				break;
			}
		}

		if (hasMore)
		{
			if (m_offset && *(p - 1) == '\r')
				*(p - 1) = 0;

			*p = 0;
			m_offset++;
		}
		else
		{
			// memory size > m_size
			// m_data[m_size] = 0;
			m_offset = m_size;
		}

		return buf;
	}
	return NULL;
}

uint32 Buffer::readLine(char* data, size_t maxCount) const
{
	uint32 pos = 0;

	// Make sure pos can never go past the end of the data 
	while (pos < maxCount && m_offset < m_size)
	{
		if (*(m_data + m_offset) == '\n')
		{
			// Trim off trailing CR if this was a CR/LF entry
			if (pos && data[pos-1] == '\r')
			{
				// terminate 1 character early
				--pos;
			}

			// Found terminator, skip and break out
			++m_offset;
			break;
		}

		data[pos++] = *(m_data + m_offset++);
	}

	// terminate
	data[pos] = '\0';

	return (pos || m_offset < m_size) ? pos : NPOS;
}

BLADE_NAMESPACE_END