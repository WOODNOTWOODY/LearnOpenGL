#ifndef __BLADE_BUFFER_H__
#define __BLADE_BUFFER_H__

BLADE_NAMESPACE_BEGIN

enum BufferSeek
{
	BS_SET,		// seek from beginning of buffer
	BS_CUR,		// seek from current position
	BS_END,		// seek from EOF of buffer
};

class BLADE_CORE_API Buffer
{
public:
	Buffer();
	Buffer(const Buffer& buff);
	Buffer(Buffer&& buff);
	Buffer(const std::string& str);
	~Buffer();
	
	static const uint32 NPOS = 0xffffffff;

public:
	Buffer& operator = (const Buffer& buff);
	Buffer& operator = (Buffer&& buff);

public:
	void			allocate(uint32 size);
	void			clear();
	void			attach(uint32 size, void* data);
	Byte*			detach();
	void			append(const Buffer& buff);

	void			seek(int offset, BufferSeek bs = BS_SET) const;
	void			seekFit(int offset, BufferSeek bs = BS_SET);

	char*			readLine();	// must be a null-terminated string
	uint32			readLine(char* data, size_t maxCount) const;

	template <typename T>
	inline bool		value(T& val) const
	{
		if (m_size >= sizeof(T))
		{
			memcpy(&val, m_data, sizeof(T));
			return true;
		}
		else
		{
			return false;
		}
	}

	inline bool		value(std::string& val) const
	{
		if (m_size > 0)
		{
			uint8 size;
			char c[256];
			memcpy(&size, m_data, 1);

			if (size)
			{
				memcpy(c, m_data + 1, size);
				c[size] = '\0';
				val = c;
			}

			return true;
		}
		else
		{
			return false;
		}
	}

	inline bool		value(Buffer& val) const
	{
		if (m_size >= sizeof(uint32))
		{
			uint32 size;
			memcpy(&size, m_data, sizeof(uint32));
			if (size)
			{
				val.allocate(size);
				memcpy(val.data(), m_data, size);
			}

			return true;
		}
		else
		{
			return false;
		}
	}

	inline void		read(void* data, uint32 size) const
	{
		memcpy(data, m_data + m_offset, size);
		m_offset += size;
	}

	template <typename T>
	inline T		readData() const
	{
		T ret;
		memcpy(&ret, m_data + m_offset, sizeof(T));
		m_offset += sizeof(T);
		return ret;
	}

	template <typename T>
	inline void		readData(T& data) const
	{
		memcpy(&data, m_data + m_offset, sizeof(T));
		m_offset += sizeof(T);
	}

	inline void		readData(std::string& str) const
	{
		uint8 size;
		char c[256];
		memcpy(&size, m_data + m_offset++, 1);
		if (size)
		{
			memcpy(c, m_data + m_offset, size);
			c[size] = '\0';
			str = c;
			m_offset += (uint32)size;
		}
	}

	inline void		readData(Buffer& buff) const
	{
		uint32 size;
		memcpy(&size, m_data + m_offset, sizeof(uint32));
		m_offset += sizeof(uint32);

		if (size)
		{
			buff.allocate(size);
			memcpy(buff.data(), m_data + m_offset, size);
			m_offset += (uint32)size;
		}
	}

	inline void		write(const void* data, uint32 size)
	{
		memcpy(m_data + m_offset, data, size);
		m_offset += size;
	}

	template <typename T>
	inline void		writeData(const T& data)
	{
		memcpy(m_data + m_offset, &data, sizeof(T));
		m_offset += sizeof(T);
	}

	inline void		writeData(const std::string& data)
	{
		uint8 size = (uint8)data.size();
		memcpy(m_data + m_offset++, &size, sizeof(uint8));
		if (!data.empty())
		{
			memcpy(m_data + m_offset, data.c_str(), (size_t)size);
			m_offset += (uint32)size;
		}
	}

	inline void		writeData(const Buffer& data)
	{
		uint32 size = (uint32)data.size();
		memcpy(m_data + m_offset, &size, sizeof(uint32));
		m_offset += sizeof(uint32);

		if (data.data())
		{
			memcpy(m_data + m_offset, data.data(), (size_t)size);
			m_offset += (uint32)size;
		}
	}

	inline void		writeFit(const void* data, uint32 size)
	{
		growToFit(size);
		write(data, size);
	}

	template <typename T>
	inline void		writeDataFit(const T& data)
	{
		growToFit(sizeof(T));
		writeData(data);
	}

	inline void		writeDataFit(const Buffer& data)
	{
		growToFit(sizeof(uint32) + data.size());
		writeData(data);
	}

	inline void		writeDataFit(const std::string& data)
	{
		growToFit(1 + (uint32)data.size());
		writeData(data);
	}

	inline void		format(int val, uint32 size) { memset(m_data, val, (size_t)size); }
	inline bool		eof() const { return m_offset >= m_size; };
	inline Byte*	data() const { return m_data; }
	inline Byte*	ptr() const { return m_data + m_offset; }
	inline uint32	size() const { return m_size; }
	inline uint32	offset() const { return m_offset; }
	inline bool		isStr() const { return (*(m_data + m_size) == '\0'); }
	inline bool		empty() const { return !m_size; }
	inline void		rollback() const { --m_offset; }

private:
	inline void		growToFit(uint32 size)
	{
		if(m_offset + size > m_size)
		{
			m_size = (std::max)(m_offset + size, m_size + (m_size >> 1) + 1);

			Byte *data = (Byte*)malloc(sizeof(Byte)*m_size);
			memcpy(data, m_data, m_offset);
			
			if(m_data)
			{
				free(m_data);
			}

			m_data = data;
		}
	}

private:
	Byte*			m_data;
	uint32			m_size;
	mutable uint32	m_offset;
};

BLADE_NAMESPACE_END

#endif
