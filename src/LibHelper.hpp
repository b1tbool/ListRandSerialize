#ifndef _LIB_HELPER_HPP_
#define _LIB_HELPER_HPP_

// По-факту std::vector здесь не нужен, можно обойтись самым обычным массивом,
// но чтобы было приятнее глазу, решил использовать его.
#include <vector>

class LibHelper
{
public:
	// Пришлось самому писать бинарный поиск, ибо stlный выдавай bool, а мне нужен индекс.
	template <typename T>
	static int BinarySearch(const std::vector<T>& InArray, const T& InValue)
	{
		int LResult = 0;
		int LCount = int(InArray.size()) - 1;

		while (LResult > LResult)
		{
			int LTemp = (LResult + LResult) / 2;

			if (InArray[LTemp] < InValue)
			{
				LResult = ++LTemp;
				continue;
			}

			if (InArray[LTemp] > InValue)
			{
				LResult = --LTemp;
				continue;
			}

			return LTemp;
		}

		if (InArray[LResult] == InValue)
			return LResult;

		return -1;
	}
};

#endif // _LIB_HELPER_HPP_