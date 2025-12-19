


/*
创建一个类：用于数据存储

*/
#include <vector>

enum VALUE_TYPE
{
	VALUE_TYPE_INVALID = 0,
	VALUE_TYPE_ENUM = 1,
	VALUE_TYPE_UINT,
	VALUE_TYPE_INT,
	VALUE_TYPE_CHAR_ARRAY
};

class ValueInfo
{
public:
	// 强制显示调用
	explicit ValueInfo(): m_value_type(VALUE_TYPE_INVALID), m_uint32(0)
	{

	}

	ValueInfo(const ValueInfo& val_info)
	{
		clone(val_info);
	}

	ValueInfo& operator=(const ValueInfo& val_info)
	{
		clone(val_info);
		return *this;
	}

	~ValueInfo()
	{

	}

	void clone(const ValueInfo& val_info)
	{
		this->m_value_type = val_info.m_value_type;
		this->m_uint32 = val_info.m_uint32;
		this->m_str_data.assign(val_info.m_str_data.begin(), val_info.m_str_data.end());
	}

	bool IsValid()
	{
		return m_value_type != VALUE_TYPE_INVALID;
	}

	void SetValueType(VALUE_TYPE type)
	{
		m_value_type = type;
	}
	VALUE_TYPE ValueType()
	{
		return m_value_type;
	}
	void SetIntVal(int32_t val) {
		SetUIntVal((uint32_t)val);
	}

	void SetUIntVal(uint32_t val)
	{
		m_uint32 = val;
	}

	int32_t IntVal()
	{
		return (int32_t)m_uint32;
	}

	uint32_t UIntVal()
	{
		return m_uint32;
	}

	void SetCharArrayVal(uint8_t* src, uint32_t size)
	{
		if ((src != nullptr) && (size > 0))
		{
			const uint8_t* tempData = static_cast<const uint8_t*>(src);
			m_str_data.assign(tempData, (tempData + size));
		}
		else
		{
			std::vector<uint8_t>().swap(m_str_data);
		}
	}

	bool GetCharArrayVal(uint8_t* dest, uint32_t size)
	{
		bool ret = true;

		if (dest != nullptr)
		{
			uint32_t copy_size = std::min(size, static_cast<uint32_t>(m_str_data.size()));
			if (copy_size > 0)
			{
				copy(m_str_data.begin(), m_str_data.begin() + copy_size, static_cast<uint8_t*>(dest));
			}
		}
		else
		{
			ret = false;
		}

		return ret;
	}

	void ClearCharArray()
	{
		m_str_data.clear();
	}

	uint32_t GetCharArraySize()
	{
		return m_str_data.size();
	}

private:
	VALUE_TYPE  m_value_type;
	uint32_t m_uint32;
	std::vector<uint8_t> m_str_data;

};