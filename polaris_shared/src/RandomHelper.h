namespace Polaris
{
    std::string string_format(const char *fmt, ...);

	template<typename T>
	void copy_array(T source[], T dest[], int size)
	{
		for (int i = 0; i < size; i++)
			dest[i] = source[i];
	}
}
