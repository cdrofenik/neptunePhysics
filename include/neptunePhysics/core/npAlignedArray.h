#ifndef NEPTUNE_NPALIGNEDARRAY_H
#define NEPTUNE_NPALIGNEDARRAY_H

#include <malloc.h>

namespace NeptunePhysics
{
	template<typename T>
	class npAlignedArray
	{
		//TODO: add allocator for alignment

	protected:
		int m_size;
		int m_capacity;
		T* m_data;

	protected:
		int getAllocationSize(int _size)
		{
			return (_size ? _size * 2 : 1);
		}

		void copy(int _start, int _end, T* destination) const
		{
			int i;
			for (i = _start; i < _end; ++i)
			{
				destination[i] = T(m_data[i]);
			}
				
		}

		void destroy(int _first, int _last)
		{
			for (int i = _first; i < _last; i++)
			{
				m_data[i].~T();
			}
		}
		
		void* allocate(int _size)
		{
			if (_size)
				return malloc(_size);
			return 0;
		}

		void deallocate()
		{
			m_data = 0;
		}

		void init()
		{
			m_size = 0;
			m_capacity = 0;
			m_data = 0;
		}

	public:
		npAlignedArray()
		{
			init();
		}

		npAlignedArray(int _size)
		{
			init();
			reserve(_size);
		}

		//TODO: Copy constructor

		~npAlignedArray()
		{
			clear();
		}

		int size() const
		{
			return m_size;
		}

		int capacity() const
		{
			return m_capacity;
		}

		const T operator[](int _index) const
		{
			//Assert if index >= 0
			//Asert if index < size
			return m_data[_index];

		}

		T& operator[](int _index)
		{
			//Assert if index >= 0
			//Asert if index < size
			return m_data[_index];
		}

		const T at(int _index) const
		{
			//Assert if index >= 0
			//Asert if index < size
			m_data[_index];
		}

		T& at(int _index)
		{
			//Assert if index >= 0
			//Asert if index < size
			return m_data[_index];
		}

		void reserve(int _size)
		{
			if (capacity() < _size)
			{
				int memorySize = _size * sizeof(T);
				T* source = (T*)allocate(memorySize);
				copy(0, size(), source);
				destroy(0, size());
				deallocate();

				m_data = source;
				m_capacity = _size;
			}
		}

		void push_back(const T& _value)
		{
			const int sz = size();
			if (sz == capacity())
			{
				reserve(getAllocationSize(size()));
			}

			m_data[m_size] = T(_value);
			m_size++;
		}

		void pop_back()
		{
			//Assert if size >= 0
			m_size--;
			m_data[m_size].~T();
		}

		void swap(const int& _index0, const int& _index1)
		{
			T tmp = m_data[_index0];
			m_data[_index0] = m_data[_index1];
			m_data[_index1] = tmp;
		}

		void removeAt(const int& _index)
		{
			if (_index < size())
			{
				swap(_index, size() - 1);
				pop_back();
			}
		}

		void clear()
		{
			destroy(0, size());
			deallocate();
			init();
		}

		void bubbleSort(bool(*compareFunc)(T, T))
		{
			int sz = size();
			for (int i = 0; i < sz; i++)
			{
				for (int j = 0; j < sz; j++)
				{
					if (compareFunc(m_data[i], m_data[j]))
						swap(i, j);
				}
			}
		}
	};
}


#endif