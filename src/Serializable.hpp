#ifndef _SERIALIZABLE_HPP_
#define _SERIALIZABLE_HPP_

#include <fstream>

class ISerializable
{
protected:
	~ISerializable() = default;

public:
	virtual void Serialize(std::ostream& RefOS)		= 0;
	virtual void Deserialize(std::istream& RefIS)	= 0;

protected:
	// Запаковка данных в файл.
	void Save(std::ostream& RefOS, const void* InAddress, size_t InSize)
	{
		if (!InAddress) return;
		
		RefOS.write(reinterpret_cast<const char*>(InAddress), InSize);
	}

	// Распаковка данных из файла.
	void Load(std::istream& RefIS, void* InAddress, size_t InSize)
	{
		if (!InAddress) return;
		
		RefIS.read(reinterpret_cast<char*>(InAddress), InSize);
	}
};

#endif // _SERIALIZABLE_HPP_